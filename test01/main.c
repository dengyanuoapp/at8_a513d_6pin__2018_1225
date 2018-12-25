/*!
 * \decribtion		ADC_Polling(eight times average)
 * \author  		JasonLee
 * \date    		2018.08.30
 * \Version 		1.1
 * ADC Convert With Polling AIN0 or Internal 1/4 VDD eight times then calculate average.
 * 1. Set ADC clock frequency is 250KHz , Sample pulse width is 1 ADC clock,  
 *	  ADC conversion time = (1+12+2)*4us = 60us , ADC conversion rate = 1/60us = 16.6KHz
 * 2. Polling one of PA0(AIN0) or internal 1/4 VDD as ADC analog input eight times then calculate average.
 * 3. Store AIN0 channel ADC convert result bit11~ bit0 to RAM "R_AIN0_DATA[11:0]"
 * 4. Store internal 1/4VDD channel ADC convert result bit11~ bit0 to RAM "R_Quarter_VDD_DATA[11:0]"
 */

#include <at8.h>
#include "at8_constant.h"
unsigned int  R_AIN0_DATA;	
unsigned char R_AIN0_DATA_LB;			
unsigned int  R_Quarter_VDD_DATA;	
unsigned char R_Quarter_VDD_DATA_LB;	

#define UPDATE_REG(x)	__asm__("MOVR _" #x ",F")

void F_AIN0_Convert(char);
void F_Quarter_VDD_Convert(char);
void F_wait_eoc(void);
void delay(int);

void main(void)
{
    
  //----- Initial GPIO-----
    IOSTA = C_PA_Input;						// Set PortA as input port
    PORTA = 0xFF;							// PortA Data Register = 0xFF
    INTE  = 0x00;							// INTE = 0x00

 //----- Initial ADC-----	  
	ADMD  = C_ADC_En | C_ADC_CH_Dis | C_ADC_PA0 ;	// Enable ADC power, Disable global ADC input channel, Select PA0 pad as ADC input (SFR "ADMD")
 
 //----- ADC high reference voltage source select-----
 	//ADVREFH = C_Vrefh_4V;					// ADC reference high voltage is supplied by internal 4V  (Note: ADC clock freq. must be equal or less 1MHz)
 	//ADVREFH = C_Vrefh_3V;					// ADC reference high voltage is supplied by internal 3V  (Note: ADC clock freq. must be equal or less 500KHz)
 	ADVREFH = C_Vrefh_2V;					// ADC reference high voltage is supplied by internal 2V  (Note: ADC clock freq. must be equal or less 250KHz)
 
//----- ADC clock frequency select----------------------------	 
	//ADR	 = C_Ckl_Div1;					// ADC clock=Fcpu/1, Clear ADIF, disable ADC interrupt	
	//ADR	 = C_Ckl_Div2;					// ADC clock=Fcpu/2, Clear ADIF, disable ADC interrupt	
	ADR	  = C_Ckl_Div8;						// ADC clock=Fcpu/8, Clear ADIF, disable ADC interrupt	
	//ADR	 = C_Ckl_Div16;					// ADC clock=Fcpu/16, Clear ADIF, disable ADC interrupt	
 
//----- ADC Sampling pulse width select-------------	 
 	ADCR  = C_Sample_1clk | C_12BIT;		// Sample pulse width=1 adc clock, ADC select 12-bit conversion ( Note: ADC clock freq. must be equal or less 500KHz)
 	//ADCR  = C_Sample_2clk | C_12BIT;		// Sample pulse width=2 adc clock, ADC select 12-bit conversion ( Note: ADC clock freq. must be equal or less 1MHz)
 	//ADCR  = C_Sample_4clk | C_12BIT;		// Sample pulse width=4 adc clock, ADC select 12-bit conversion ( Note: ADC clock freq. must be equal or less 1.25MHz)
 	//ADCR  = C_Sample_8clk | C_12BIT; 		// Sample pulse width=8 adc clock, ADC select 12-bit conversion ( Note: ADC clock freq. must be equal or less 2MHz)	

//--------------------------------------------------	
	PACON = C_PA0_AIN0;						// Set AIN0(PA0) as pure ADC input for reduce power consumption (SFR "PACON")
	ADMDbits.GCHS = 1;						// Enable global ADC channel	(SFR "ADMD")
	delay(50);								// Delay 0.56ms(Instruction clock=4MHz/2T) waiting ADC stable 
    while(1)
    {
        CLRWDT();							// Clear WatchDog
		R_AIN0_DATA=R_AIN0_DATA_LB=R_Quarter_VDD_DATA=R_Quarter_VDD_DATA_LB=0x00;            
        F_AIN0_Convert(8);					// executing AIN0 ADC converting 8 times
        R_AIN0_DATA <<= 4;					// R_AIN0_DATA shift left 4 bit
        R_AIN0_DATA_LB &= 0xF0;				// Only get Bit7~4
        R_AIN0_DATA += R_AIN0_DATA_LB;		// R_AIN0_DATA + R_AIN0_DATA_LB
        R_AIN0_DATA >>=3;					// R_AIN0_DATA dividing 8
        
        F_Quarter_VDD_Convert(8);			// executing 1/4VDD input channel ADC converting 8 times
        R_Quarter_VDD_DATA <<= 4;			// R_Quarter_VDD_DATA shift left 4 bit
        R_Quarter_VDD_DATA_LB &= 0xF0;		// Only get Bit7~4
        R_Quarter_VDD_DATA += R_Quarter_VDD_DATA_LB; //// R_Quarter_VDD_DATA + R_Quarter_VDD_DATA_LB
        R_Quarter_VDD_DATA >>=3;			// R_Quarter_VDD_DATA dividing 8
    }
}

//----- Sub-Routine ----- 
void F_AIN0_Convert(char count)
{
  	char i;
  	ADMD  = 0x90 | C_ADC_PA0;				// Select AIN0(PA0) pad as ADC input
  	for(i=1;i<=count;i++)
  	{     			 
  	 ADMDbits.START = 1;					// Start a ADC conversion session
  	 F_wait_eoc();							// Waiting for ADC conversion complet	
  	 R_AIN0_DATA_LB += ( 0x0F & ADR); 
  	 R_AIN0_DATA    += ADD; 
  	}
}

void F_Quarter_VDD_Convert(char count)
{
  	char i;
  	ADMD  = 0x90 | C_Quarter_VDD;			// Select internal 1/4VDD as ADC input
  	for(i=1;i<=count;i++)
  	{     			 
  	 ADMDbits.START = 1;					// Start a ADC conversion session
  	 F_wait_eoc();							// Waiting for ADC conversion complet	
  	 R_Quarter_VDD_DATA_LB += ( 0x0F & ADR); 
  	 R_Quarter_VDD_DATA    += ADD; 
  	}
}

void F_wait_eoc(void)
{
   while(ADMDbits.EOC==0)
   ;
}

void delay(int count)
{
	int i;
	for(i=1;i<=count;i++)
	;
}