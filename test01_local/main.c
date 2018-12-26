
#include <at8.h>
#include "at8_constant.h"
unsigned char _R_state ;

#define UPDATE_REG(x)	__asm__("MOVR _" #x ",F")
#define  _action_01_toggle_B5       { PORTB ^= C_PB5_Input ; } // 414 byte
#define  _action_11_set_600mv__on   {}
#define  _action_11_set_600mv_off   {}

void _FadcRead_pin(void);
void _Fanalyze_State(void);
void _F_wait_adc_conver_end(void);
void _FdelayMS(int count);
void _FmainLoop(void);
unsigned long  _Rcnt64H ; 
unsigned long  _Rcnt64L ; 
void _halt_01_for_no_shake_need( void );
unsigned int  _RadcH ;
unsigned int  _RadcL ;
unsigned char _RadcREAL ;

void main(void)
{

    //----- Initial GPIO-----
    IOSTA = C_PA_Input;						// Set PortA as input port
    PORTA = 0xFF;							// PortA Data Register = 0xFF
    INTE  = 0x00;							// INTE = 0x00

    IOSTB = C_PB_Input & ( ~ C_PB5_Input ) ;// Set PortB as input port , except PortB5 is output
    //IOSTB = (IOSTB | C_PB_Input) & ( ~ C_PB5_Input ) ;// Set PortB as input port , except PortB5 is output

    //----- Initial ADC-----	  
    ADMD  = C_ADC_En | C_ADC_CH_Dis | C_ADC_PA4 ;	// Enable ADC power, Disable global ADC input channel, Select PA4 pad as ADC input (SFR "ADMD")

    //----- ADC high reference voltage source select-----
    ADVREFH = C_Vrefh_2V;					// ADC reference high voltage is supplied by internal 2V  (Note: ADC clock freq. must be equal or less 250KHz)

    //----- ADC clock frequency select----------------------------	 
    ADR	  = C_Ckl_Div8;						// ADC clock=Fcpu/8, Clear ADIF, disable ADC interrupt	

    //----- ADC Sampling pulse width select-------------	 
    ADCR  = C_Sample_1clk | C_12BIT;		// Sample pulse width=1 adc clock, ADC select 12-bit conversion ( Note: ADC clock freq. must be equal or less 500KHz)

    //--------------------------------------------------	
    PACON = C_PA4_AIN4;						// Set AIN4(PA4) as pure ADC input for reduce power consumption (SFR "PACON")
    ADMDbits.GCHS = 1;						// Enable global ADC channel	(SFR "ADMD")
    _FdelayMS(50);								// Delay 0.56ms(Instruction clock=4MHz/2T) waiting ADC stable 
    _R_state = 0 ;
    _Rcnt64H = 0x1 ;
    _Rcnt64L = 0xffffffff ;
    while(1)
    {
        _FmainLoop();
    }
} // main()

void _FmainLoop(void)
{
    CLRWDT();							// Clear WatchDog

    _Rcnt64L -- ;
    if ( ! _Rcnt64L ) {
        _Rcnt64H -- ;
    }
    if ( ! _Rcnt64H ) {
        _halt_01_for_no_shake_need();
    }

    _FadcRead_pin();					// executing AIN4 ADC converting 8 times

    _Fanalyze_State() ;

    _action_01_toggle_B5  

} // _FmainLoop

/*
 * 2000mv / 256(ADD,8bit) == XXX mv / resistor
 * 400mv --> 51  --> 0x33
 * 450mv --> 57  --> 0x39
 * 750mv --> 96  --> 0x60
 * 800mv --> 102 --> 0x66
 *
 */
#define _setADC_L       51
#define _setADC_H       102

void _Fanalyze_L(void){
} // _Fanalyze_L
void _Fanalyze_H(void){
} // _Fanalyze_H
void _Fanalyze_M(void){
} // _Fanalyze_M

void _Fanalyze_State(void){
    if ( _RadcREAL < _setADC_L ) {
        _Fanalyze_L();
    } else
    if ( _RadcREAL > _setADC_H ) {
        _Fanalyze_H();
    } else { // between _setADC_L to _setADC_H
        _Fanalyze_M();
    }
} // _Fanalyze_State(void)

//----- Sub-Routine ----- 
void _FadcRead_pin(void)
{
    char __i01 ;

    ADMD  = 0x90 | C_ADC_PA4;				// Select AIN4(PA4) pad as ADC input
    _RadcL = 0 ;
    _RadcH = 0 ;

    for ( __i01 = 4 ; __i01 ; __i01 -- ) {
        ADMDbits.START = 1;					// Start a ADC conversion session
        _F_wait_adc_conver_end();							// Waiting for ADC conversion complet	
        _RadcL += ( 0x0F & ADR); 
        _RadcH += ADD; 
    }
    _RadcH <<=4 ;
    _RadcH += _RadcL ;
    _RadcH >>= 2 ; // div 4
    _RadcREAL = _RadcH  ;
} // _FadcRead_pin


void _F_wait_adc_conver_end(void)
{
    while(ADMDbits.EOC==0)
        ;
} // _F_wait_adc_conver_end

void _FdelayMS(int count)
{
    int __t02;
    for(__t02=count;__t02;__t02--)
        ;
} // _FdelayMS

void _halt_01_for_no_shake_need( void )
{
    while(1){ ; } 
} // _halt_01_for_no_shake_need
