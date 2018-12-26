/*!
 * \decribtion		ADC_Polling(eight times average)
 * \author  		JasonLee
 * \date    		2018.08.30
 * \Version 		1.1
 * ADC Convert With Polling AIN4 or Internal 1/4 VDD eight times then calculate average.
 * 1. Set ADC clock frequency is 250KHz , Sample pulse width is 1 ADC clock,  
 *	  ADC conversion time = (1+12+2)*4us = 60us , ADC conversion rate = 1/60us = 16.6KHz
 * 2. Polling one of PA4(AIN4) as ADC analog input eight times then calculate average.
 * 3. Store AIN4 channel ADC convert result bit11~ bit0 to RAM "_R_pin_adc_dataBit_411[11:0]"
 */

#include <at8.h>
#include "at8_constant.h"
unsigned int  _R_pin_adc_dataBit_411;	
unsigned char _R_pin_adc_dataBit_0_3;			

#define UPDATE_REG(x)	__asm__("MOVR _" #x ",F")

void _FadcRead_pin(char);
void _F_wait_adc_conver_end(void);
void _FdelayMS(int);
void _FmainLoop(void);

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
    while(1)
    {
        _FmainLoop();
    }
} // main()

void _FmainLoop(void)
{
    CLRWDT();							// Clear WatchDog
    _R_pin_adc_dataBit_411=0x00 ;
    _R_pin_adc_dataBit_0_3=0x00 ;

    _FadcRead_pin(8);					// executing AIN4 ADC converting 8 times
    _R_pin_adc_dataBit_411 <<= 4;					// _R_pin_adc_dataBit_411 shift left 4 bit
    _R_pin_adc_dataBit_0_3 &= 0xF0;				// Only get Bit7~4
    _R_pin_adc_dataBit_411 += _R_pin_adc_dataBit_0_3;		// _R_pin_adc_dataBit_411 + _R_pin_adc_dataBit_0_3
    _R_pin_adc_dataBit_411 >>=3;					// _R_pin_adc_dataBit_411 dividing 8

    //PORTBbits.PB5 = !PORTBbits.PB5 ; // 474 byte
    //if ( PORTBbits.PB5 ) { PORTBbits.PB5 = 0 ; } else { PORTBbits.PB5 = 1 ; } // 420 byte
    PORTB ^= C_PB5_Input ; // 414 byte

} // _FmainLoop


//----- Sub-Routine ----- 
void _FadcRead_pin(char count)
{
    char i;
    ADMD  = 0x90 | C_ADC_PA4;				// Select AIN4(PA4) pad as ADC input
    for(i=1;i<=count;i++)
    {     			 
        ADMDbits.START = 1;					// Start a ADC conversion session
        _F_wait_adc_conver_end();							// Waiting for ADC conversion complet	
        _R_pin_adc_dataBit_0_3 += ( 0x0F & ADR); 
        _R_pin_adc_dataBit_411    += ADD; 
    }
}


void _F_wait_adc_conver_end(void)
{
    while(ADMDbits.EOC==0)
        ;
}

void _FdelayMS(int count)
{
    int i;
    for(i=1;i<=count;i++)
        ;
}
