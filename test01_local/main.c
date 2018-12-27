
/* AT8 - B62D sot23-6pin
 * 1 : PA4 /AIN4 / EX_CKIO / SCK       --------> --------> --------> --------> --------> ADC in, check 600mv wave
 * 2 : VSS / GND
 * 3 : PA5 / RSTb / VPP                --------> --------> --------> --------> --------> down, OD 
 * 4 : PB3 / AIN3 / PWM1 / BZ1 / CMPO / SDO      --------> --------> --------> --------> indecator
 * 5 : VDD / VCC
 * 6 : PA2 / AIN2 / PWM3 / BZ3 / SDI   --------> --------> --------> --------> --------> up, input/off , output /on 
 * A2 as 600mv_up
 * A5 as 600mv_down (OD)
 */
void _Fanalyze_L(void);
void _Fanalyze_H(void);
void _Fanalyze_M(void);

#include <at8.h>
#include "at8_constant.h"

#define UPDATE_REG(x)	__asm__("MOVR _" #x ",F")

unsigned char _bitB3  ;
unsigned char _bitA25 ;
#define _bitA2 _bitA25 
#define _bitA5 _bitA25 

//#define _action_01_toggle_B3       { PORTB ^= C_PB3_Input ; } // less byte , but unstable , for the B3 bit maybe force change by the ext voltage.
//#define _action_01_toggle_B3       { _bitB3 = ! _bitB3 ; PORTBbits.PB3 = _bitB3 ; } //  more bytes : 20 bytes
//#define _action_01_toggle_B3       { _bitB3 = ! _bitB3 ; if (_bitB3 ) PORTBbits.PB3 = 1; else PORTBbits.PB3 = 0; } //  more bytes : 27 bytes : 0x2c-0x47
#define _action_01_toggle_B3       { _bitB3 ^= 0x01 ; if (_bitB3 ) PORTBbits.PB3 = 1; else PORTBbits.PB3 = 0; } //  more bytes : 10 bytes :0x2c-0x35

#define _action_21_set_600mv__onA2 { PORTAbits.PA2 = 1; _set_A2_as_output ; PORTAbits.PA2 = 1; }
#define _action_21_set_600mv_offA2 { _set_A2_as__input }
#define _action_22_set_600mv__onA5 { _set_A5_OD__on }
#define _action_22_set_600mv_offA5 { _set_A5_OD_off }

#define _action_11_set_600mv__on   { _action_21_set_600mv__onA2 ; _action_22_set_600mv__onA5 ; }
#define _action_11_set_600mv_off   { _action_21_set_600mv_offA2 ; _action_22_set_600mv_offA5 ; }
//#define _action_11_set_600mv__on   { _action_21_set_600mv__onA2 ; }
//#define _action_11_set_600mv_off   { _action_21_set_600mv_offA2 ; }
//#define _action_11_set_600mv__on   { _action_22_set_600mv__onA5 ; }
//#define _action_11_set_600mv_off   { _action_22_set_600mv_offA5 ; }

#define _set_A5_ctrl_1      { IOSTA |=   C_PA5_Input  ; }       
#define _set_A5_ctrl_0      { IOSTA &= (~C_PA5_Input) ; } 
#define _set_A5_data_1      { _bitA5 = 0x1  ; PORTAbits.PA5 = 1; }
#define _set_A5_data_0      { _bitA5 = 0x0  ; PORTAbits.PA5 = 0; }
#define _set_A5_data_1only  {                 PORTAbits.PA5 = 1; }
#define _set_A5_data_0only  {                 PORTAbits.PA5 = 0; }

#define _set_A2_data_1      { _bitA2 = 0x1  ; PORTAbits.PA2 = 1; }
#define _set_A2_data_0      { _bitA2 = 0x0  ; PORTAbits.PA2 = 0; }
#define _set_A2_data_1only  {                 PORTAbits.PA2 = 1; }
#define _set_A2_data_0only  {                 PORTAbits.PA2 = 0; }

#define _set_A2_ctrl_1      { IOSTA |=   C_PA2_Input  ; }       
#define _set_A2_ctrl_0      { IOSTA &= (~C_PA2_Input) ; }       

#define _set_A5_OD__on        _set_A5_data_0only
#define _set_A5_OD_off        _set_A5_data_1only
#define _set_A5_as_output      _set_A5_ctrl_0

#define _set_A2_as__input   _set_A2_ctrl_1      // 1 -> input ; 0 -> output             
#define _set_A2_as_output   _set_A2_ctrl_0      // 1 -> input ; 0 -> output             

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
unsigned char _R_state ;

void main(void)
{

    //----- Initial GPIO-----
    IOSTA = C_PA_Input;						// Set PortA as input port
    PORTA = 0xFF;							// PortA Data Register = 0xFF
    INTE  = 0x00;							// INTE = 0x00

    _bitB3  = 0 ;
    _bitA25 = 0 ;

    // B3 as the indecator
    IOSTB = C_PB_Input & ( ~ C_PB3_Input ) ;// Set PortB as input port , except PortB3 is output
    //IOSTB = (IOSTB | C_PB_Input) & ( ~ C_PB3_Input ) ;// Set PortB as input port , except PortB3 is output

    _set_A2_data_1 ;
#if 0
    _set_A2_as_output ;
    _set_A2_data_1 ;
    _set_A2_as__input ;

    _set_A2_data_0 ;
    _set_A2_as_output ;
    _set_A2_data_0 ;
    _set_A2_as__input ;

    _set_A2_data_1 ;
    _set_A2_as_output ;
    _set_A2_data_1 ;
    _set_A2_as__input ;
#endif

    _set_A5_OD_off ;
    _set_A5_as_output ;

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

    _action_01_toggle_B3   ;

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
#define _state6mvOKmax  2
#define _stateOveride   (_state6mvOKmax + 1 )

void _Fanalyze_L(void){
    _action_11_set_600mv_off ;
    _R_state = 0 ;
} // _Fanalyze_L

void _Fanalyze_M(void){
    if ( _R_state > _state6mvOKmax ) {
        _action_11_set_600mv_off ;
        _R_state = 0 ;
    } else
        if ( _R_state == _state6mvOKmax ) {
            _action_11_set_600mv__on ;
        } else 
        {
            _action_11_set_600mv_off ;
            _R_state ++ ;
        }
} // _Fanalyze_M
void _Fanalyze_H(void){
    _action_11_set_600mv_off ;
    _R_state = _stateOveride ;
} // _Fanalyze_H

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
        //_RadcL += ( 0x0F & ADR); 
        _RadcH += ADD; 
    }
    _RadcH <<=4 ;
    _RadcH += _RadcL ;
    _RadcH >>= 6 ; // div 4 , 2 + 4 == 6
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
