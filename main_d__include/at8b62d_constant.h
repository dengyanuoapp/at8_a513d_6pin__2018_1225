#ifndef NY8B062D_constant_H_IGT7A1JL
#define NY8B062D_constant_H_IGT7A1JL
//;=======================================================================================================================
//;=======================================================================================================================
//;File:			NY8B062D.h
//;Description:		The Header File for NY8B062D
//;Author:			JasonLee
//;Date:			2018/01/31
//;=======================================================================================================================
//;=======================================================================================================================
//;-----------------------------------------------------------------------------------------------------------------------
//;MOVR and MOVAR instrutions for access R-page Register (General Purpose Register)
//;-----------------------------------------------------------------------------------------------------------------------
//;R-page sregisters				;	bit7	|	bit6	|	bit5	|	bit4	|	bit3	|	bit2	|	bit1	|	bit0
//;-----------------------------------------------------------------------------------------------------------------------	
//; 00H --------- Indirect Addressing Register
//INDF				
//
//; 01H --------- Timer0 Data Register	
//TMR0				
//
//; 02H --------- Low Byte of Program Counter
//PCL			
//
//; 03H --------- Status Register
//STATUS		
//										BK[1]		BK[0]		GP5			/WDT_TO		/Sleep		Z			Half_C		C	
//
//; 04H --------- File Selection Register (Include SRAM Bank Select)
//FSR
//										-			FSR[6]		FSR[5]		FSR[4]		FSR[3]		FSR[2]		FSR[1]		FSR[0]	         
//; 05H --------- PortA Data Register
//PORTA
//
//; 06H --------- PortB Data Register
//PORTB			
//	
//; 07H --------- Reserved
//; 08H --------- Power Control Register (WatchDog,LVD and LVR Control,/PA[5]: Pull-High)
//PCON
//										WDTEn		-			LVDEN		/PA[5]		LVREn		GP2			GP1			GP0	
//; 09H --------- PortB Wakeup Control Register
//BWUCON
//										-			-			PB[5]		PB[4]		PB[3]		PB[2]		PB[1]		PB[0]
//; 0AH --------- High Byte of Program Counter (B'xxxxxDDD')
//PCHBUF
//										-			XSPD_STP	-			-			-			PCHBUF[2]	PCHBUF[1]	PCHBUF[0]
//; 0BH --------- PortA/B Pull-Low Control Register
//ABPLCON
//										/PB[3]		/PB[2]		/PB[1]		/PB[0]		/PA[3]		/PA[2]		/PA[1]		/PA[0]		
//; 0CH --------- PortB Pull-High Control Register
//BPHCON
//										-			-			/PB[5]		/PB[4]		/PB[3]	    /PB[2]		/PB[1]		/PB[0]	
//; 0DH --------- Reserved
//; 0EH --------- Interrupt Enable Register
//INTE
//										ExtINT1		WDT			TMR2		LVDIE		TMR1		ExtINT0		PABKey		TMR0	
//; 0FH --------- Interrupt Flag	(Write '0' to Clear Flag)
//INTF
//										ExtINT1		WDT			TMR2		LVDIF		TMR1		ExtINT0		PABKey		TMR0	
//; 10H --------- ADC mode Register
//ADMD
//										ADEN		ADC_START	ADC_EOC		ADC_CHEN	AD_CHSel[3]	AD_CHSel[2] AD_CHSel[1] AD_CHSel[0]		
//; 11H --------- ADC clock, ADC interrupt flag and ADC low 4-bit data output Register
//ADR
//										ADIF		ADIE		AD_ClK[1]	AD_ClK[0]	AD_Data[3]	AD_Data[2] 	AD_Data[1] 	AD_Data[0]
//; 12H --------- ADC output data Register  (ADC high 8-bit data output Register)
//ADD
//										AD_Data[11]	AD_Data[10]	AD_Data[9]	AD_Data[8]	AD_Data[7]	AD_Data[6] 	AD_Data[5] 	AD_Data[4]
//; 13H --------- ADC high reference voltage Register
//ADVREFH
//										AD_VREFH	-			-			-			-			- 			AD_VSel[1] 	AD_VSel[0]
//; 14H --------- ADC Sampling pulse width and ADC conversion bit Register(include PB5~PB3 pure ADC input select)
//ADCR
//										GP7			PB[5]		PB[4]		PB[3]		AD_SAMP[1]	AD_SAMP[0] 	AD_BIT[1] 	AD_BIT[0]
//; 15H --------- PortA Wakeup Control Register
//AWUCON
//										PA[7]		PA[6]		PA[5]		PA[4]		PA[3]		PA[2]		PA[1]		PA[0]
//; 16H --------- AIN pin control Register
//PACON
//										PB[2]		PB[1]		PB[0]		PA[4]		PA[3]		PA[2]		PA[1]		PA[0]
//; 17H --------- Reserved
//; 18H --------- External Interrupt Contorl Register
//INTEDG
//										-			-			ExINT1En	ExINT0En	INT1_Edg[1]	INT1_Edg[0]	INT0_Edg[1]	INT0_Edg[0]	
//; 19H --------- TIMER1/2 Data and PWMDUTY1/2 msb 2 bits Register
//TMRH
//										TMR2_DATA9	TMR2_DATA8	TMR1_DATA9	TMR1_DATA8	PWM2_DUTY9	PWM2_DUTY8	PWM1_DUTY9	PWM1_DUTY8	
//; 1AH --------- Voltage comparator Control Register
//ANAEN
//										CMPEN		-			-			-			-			-			-			-	
//; 1BH --------- Resistor to Frency Converter Control Register
//RFC
//										RFCEN		-			-			-			PADSel[3]	PADSel[2]	PADSel[1]	PADSel[0]
//; 1CH --------- TIMER3 Data and PWMDUTY3 msb 2 bits Register
//TM3RH
//										-			-			TMR3_DATA9	TMR3_DATA8	-			-			PWM3_DUTY9	PWM3_DUTY8	
//; 1DH --------- Reserved
//; 1EH --------- Reserved
//; 1FH --------- Interrupt2 Enable Register
//INTE2		
//										-			-			-			T3IF		-			-			-			T3IE			
//;-----------------------------------------------------------------------------------------------------------------------
//;T0MD and T0MDR instrutions for access T0MD Register
//;-----------------------------------------------------------------------------------------------------------------------
//; xxH --------- Timer0 Control Register (Only Accessed by Instruction T0MD / T0MDR)
//;T0MD									LClkSrc		-			ClkSel		EdgeSel		PS0WDT		PS0Div[2]	PS0Div[1]	PS0Div[0]	
//
//;-----------------------------------------------------------------------------------------------------------------------
//;IOST and IOSTR instrution for access F-page Register (IO Configuration Register)
//;-----------------------------------------------------------------------------------------------------------------------
//;F-page registers					;	bit7	|	bit6	|	bit5	|	bit4	|	bit3	|	bit2	|	bit1	|	bit0
//;-----------------------------------------------------------------------------------------------------------------------	
//; 05H --------- PortA Direction(1:Input/0:Output) Control Register
//IOSTA
//
//; 06H --------- PortB Direction(1:Input/0:Output) Control Register
//IOSTB
//
//; 09H --------- PortA Pull-High Control Register (/PA[5]: Pull-Low)
//APHCON
//										/PA[7]		/PA[6]		/PA[5]		/PA[4]		/PA[3]		/PA[2]		/PA[1]		/PA[0]	
//; 0AH --------- Prescaler0 Counter Value Register
//PS0CV
//
//; 0CH --------- PortB Open-Drain Control Register
//BODCON
//										-			-			PB[5]		PB[4]		PB[3]  		PB[2]		PB[1]		PB[0]		
//; 0EH --------- Comparator voltage select Control Register
//CMPCR
//										PS3  		PS2	 		PS1			PS0			VS3			VS2			VS1			VS0	
//; 0FH --------- Power Control Register 1
//PCON1
//										GIE			LVDOUT		GP5			LVDS2		LVDS1		LVDS0		-			TMR0En	
//
//;-----------------------------------------------------------------------------------------------------------------------
//;SFUN and SFUNR instrution for access S-page Register (Special Function Register)
//;-----------------------------------------------------------------------------------------------------------------------
//;S-page registers					;	bit7	|	bit6	|	bit5	|	bit4	|	bit3	|	bit2	|	bit1	|	bit0
//;-----------------------------------------------------------------------------------------------------------------------											
//; 00H --------- Timer1 Data Register	
//TMR1
//
//; 01H --------- Timer1 Control Register	1
//T1CR1
//										PWM1En		PWM1ActB	-			-			-			OneShot		Reload		TMR1En	
//; 02H --------- Timer1 Control Register	2
//T1CR2
//										-			-			ClkSel		EdgeSel		/PS1En		PS1Div[2]	PS1Div[1]	PS1Div[0]	
//; 03H --------- PWM1 Duty Register
//PWM1DUTY
//
//; 04H --------- Prescaler1 Counter Value Register
//PS1CV
//
//; 05H --------- Buzzer1 Control Register
//BZ1CR
//										BZ1En		-			-			-			FSel[3]		FSel[2]		FSel[1]		FSel[0]	
//; 06H --------- IR Control Register
//IRCR
//										IROSC358M   -			-			-			-			PolSel  	IRF57K		IREn	
//; 07H --------- Table Access High Byte Address Pointer Register
//TBHP				
//										-			-			-			GP4			GP3			HPoint[2]	HPoint[1]	HPoint[0]	
//; 08H --------- Table Access High Byte Data Register
//TBHD
//										-			-			HData[5]	HData[4]	HData[3]	HData[2]	HData[1]	HData[0]	
//; 09H --------- Timer2 Data Register	
//TMR2
//
//; 0AH --------- Timer2 Control Register	1
//T2CR1
//										PWM2En		PWM2ActB	-			-			-			OneShot		Reload		TMR2En	
//; 0BH --------- Timer2 Control Register	2
//T2CR2
//										-			-			ClkSel		EdgeSel		/PS2En		PS2Div[2]	PS2Div[1]	PS2Div[0]	
//; 0CH --------- PWM2 Duty Register
//PWM2DUTY
//
//; 0DH --------- Prescaler2 Counter Value Register
//PS2CV		
//
//; 0EH --------- Buzzer2 Control Register
//BZ2CR	
//										BZ2En		-			-			-			FSel[3]		FSel[2]		FSel[1]		FSel[0]	
//; 0FH --------- Oscillation Control Register (Include Switch Working Mode)
//OSCCR	
//										CMPOUT		CMPOE		CMPIF		CMPIE		Mode[1]		Mode[0]		HOSC_Stop	HOSC_Sel
//; 10H --------- Timer3 Data Register	
//TMR3
//
//; 11H --------- Timer3 Control Register	1
//T3CR1
//										PWM3En		PWM3ActB	-			-			-			OneShot		Reload		TMR3En	
//; 12H --------- Timer3 Control Register	2
//T3CR2
//										-			-			ClkSel		EdgeSel		/PS3En		PS3Div[2]	PS3Div[1]	PS3Div[0]	
//; 13H --------- PWM3 Duty Register
//PWM3DUTY
//
//; 14H --------- Prescaler3 Counter Value Register
//PS3CV		
//
//; 15H --------- Buzzer3 Control Register
//BZ3CR		
//										BZ3En		-			-			-			FSel[3]		FSel[2]		FSel[1]		FSel[0]	
//
//;=======================================================================================================================
//;=======================================================================================================================
//;-----------------------------------------------------------------------------------------------------------------------
//; R-page Special Function Register (General Purpose Register)
//;-----------------------------------------------------------------------------------------------------------------------
//;------------------------------------------------------------
//; Pr_Indir_Addr (00H)	--------- Indirect Addressing Register
//;------------------------------------------------------------
//;Bit[7:0] : Indirect Address
#define		C_Indir_Addr				0xFF
//
//;------------------------------------------------------------
//; Pr_TMR0_Data (01H)	--------- Timer0 Data Register	
//;------------------------------------------------------------
//;Bit[7:0] : Timer0 Data
#define		C_TMR0_Data					0xFF
//
//;------------------------------------------------------------
//; Pr_PCLow_Data (02H)	--------- Low Byte of Program Counter
//;------------------------------------------------------------
//;Bit[7:0] : Low Byte of Program Counter
#define		C_PCLow_Data				0xFF
//
//;------------------------------------------------------------
//; Pr_Status (03H)		--------- Status Register (Include RAM Bank Select)
//;------------------------------------------------------------
//;Bit[7:6] : RAM Bank Selection
#define		C_RAM_Bank					0xC0			//; Select Ram Bank
#define		C_RAM_Bank0					0x00			//; Select Ram Bank0
#define		C_RAM_Bank1					0x40			//; Select Ram Bank1
#define		C_RAM_Bank2					0x80			//; Select Ram Bank2
#define		C_RAM_Bank3					0xC0			//; Select Ram Bank3	
//;Bit[4:0] : System Status                             
#define		C_Status_WDT				0x10			//; WatchDog Overflow Flag
#define		C_Status_Slp				0x08			//; Sleep (Power Down) Flag
#define		C_Status_Z					0x04			//; Zero Flag
#define		C_Status_HalfC				0x02			//; Half Carry/Half Borrow Flag
#define		C_Status_C					0x01			//; Carry/Borrow Flag	

//;------------------------------------------------------------ 
//; Pr_File_Sel (04H)		--------- File Selection Register       
//;------------------------------------------------------------
//;Bit[7] : Reserved	
//;Bit[6:0] : Select one Register out of 128 registers of specific Bank.
#define		C_SFR_RAM_Addr				0x7F			//; RAM Address Bit[6:0] 
//
//;------------------------------------------------------------	 
//; Pr_PA_Data (05H)		--------- PortA Data Register
//;------------------------------------------------------------ 
//;Bit[7:0] : PORTA Data Bit Define	
#define		C_PA_Data					0xFF			//; PA  Data
#define		C_PA7_Data					0x80			//; PA7 Data
#define		C_PA6_Data					0x40			//; PA6 Data
#define		C_PA5_Data					0x20			//; PA5 Data
#define		C_PA4_Data					0x10			//; PA4 Data	
#define		C_PA3_Data					0x08			//; PA3 Data
#define		C_PA2_Data					0x04			//; PA2 Data
#define		C_PA1_Data					0x02			//; PA1 Data
#define		C_PA0_Data					0x01			//; PA0 Data
//	
//;------------------------------------------------------------
//; Pr_PB_Data (06H)		--------- PortB Data Register
//;------------------------------------------------------------
//;Bit[7:6] : Reserved	
//;Bit[5:0] : PORTB Data Bit Define	
#define		C_PB_Data					0x3F			//; PB  Data
#define		C_PB5_Data					0x20			//; PB5 Data	
#define		C_PB4_Data					0x10			//; PB4 Data	
#define		C_PB3_Data					0x08			//; PB3 Data
#define		C_PB2_Data					0x04			//; PB2 Data
#define		C_PB1_Data					0x02			//; PB1 Data
#define		C_PB0_Data					0x01			//; PB0 Data
//
//;------------------------------------------------------------	
//; Pr_PWR_Ctrl (08H)		--------- Power Control Register (WatchDog,LVD,PA5 Pull-High and LVR Control) 
//;------------------------------------------------------------
//;Bit[7] : WatchDog Eanble
#define		C_WDT_En					0x80			//; WatchDog Enable
//;Bit[6] : Reserved                                    
//;Bit[5] : LVD Eanble                                  
#define		C_LVD_En					0x20			//; LVD Enable	
//;Bit[4] : PA5 Pull-High                               
#define		C_PA5_PHB					0x00			//; Enable PA5 Pull-High
//;Bit[3] : LVR Enable                                  
#define		C_LVR_En					0x08			//; LVR Enable
//;Bit[2:0] : Reserved

//;------------------------------------------------------------	
//; Pr_PB_WakeUp_Ctrl (09H)	--------- PortB Wakeup Control Register
//;------------------------------------------------------------
//;Bit[7:6] : Reserved
//;Bit[5:0] : BWUCON Bit Define
#define		C_PB_Wakeup					0x3F			//; PortB Wakeup Enable	
#define		C_PB5_Wakeup				0x20			//; PB5 Wakeup Enable	
#define		C_PB4_Wakeup				0x10			//; PB4 Wakeup Enable	
#define		C_PB3_Wakeup				0x08			//; PB3 Wakeup Enable
#define		C_PB2_Wakeup				0x04			//; PB2 Wakeup Enable 
#define		C_PB1_Wakeup				0x02			//; PB1 Wakeup Enable
#define		C_PB0_Wakeup				0x01			//; PB0 Wakeup Enable
//		
//;------------------------------------------------------------	
//; Pr_PCHigh_Data (0AH) --------- High Byte of Program Counter
//;------------------------------------------------------------
//;Bit[7] : Reserved
//;Bit[6] : E_LXT Buckup Contorl Bit	(1:Disable, 0:Enable)
#define		C_ELXT_Backup_Dis			0x40	
//;Bit[5] : Reserved
//;Bit[2:0] : High Byte of Program Counter
#define		C_PCHigh_Data				0x07
	
//;------------------------------------------------------------		
//; Pr_PAB_PL_Ctrl (0BH)	--------- PortA/B Pull-Low Control Register
//;------------------------------------------------------------
//;Bit[7:4] : PortB Pull-Low Control Register (1:Disable, 0:Pull-High)
#define    C_PB_PLB						0xF0			//; PortB Pull-Low Control bit
#define    C_PB3_PLB					0x80			//; PB3 Pull-Low Control bit
#define    C_PB2_PLB					0x40			//; PB2 Pull-Low Control bit	
#define    C_PB1_PLB					0x20			//; PB1 Pull-Low Control bit 	
#define    C_PB0_PLB					0x10			//; PB0 Pull-Low Control bit
//;Bit[3:0] : PortA Pull-Low Control Register
#define    C_PA_PLB						0x0F			//; PortA Pull-Low Control bit
#define    C_PA3_PLB					0x08			//; PA3 Pull-Low Control bit
#define    C_PA2_PLB					0x04			//; PA2 Pull-Low Control bit	
#define    C_PA1_PLB					0x02			//; PA1 Pull-Low Control bit	
#define    C_PA0_PLB					0x01			//; PA0 Pull-Low Control bit
//
//;------------------------------------------------------------	
//; Pr_PB_PH_Ctrl (0CH)	--------- PortB Pull-High Control Register
//;------------------------------------------------------------
//;Bit[7:6] : Reserved
//;Bit[5:0] : PortB Pull-High Control Register (1:Disable, 0:Pull-High)
#define		C_PB_PHB					0x3F			//; PortB Pull-High Control bit 
#define		C_PB5_PHB					0x20			//; PB5 Pull-High Control bit	
#define		C_PB4_PHB					0x10			//; PB4 Pull-High Control bit	
#define		C_PB3_PHB					0x08			//; PB3 Pull-High Control bit	
#define		C_PB2_PHB					0x04			//; PB2 Pull-High Control bit
#define		C_PB1_PHB					0x02			//; PB1 Pull-High Control bit
#define		C_PB0_PHB					0x01			//; PB0 Pull-High Control bit
//
//;------------------------------------------------------------	
//; Pr_INT_Ctrl (0EH)		--------- Interrupt Enable Register
//; Pr_INT_Flag (0FH)		--------- Interrupt Flag
//;------------------------------------------------------------
//;Bit[7:0] : Interrupt Source
#define		C_INT_EXT1					0x80			//; EX_INT1 interrupt enable bit
#define		C_INT_WDT					0x40			//; WDT timeout interrupt enable bit
#define		C_INT_TMR2					0x20			//; Timer2 underfolw interrupt enable bit
#define		C_INT_LVD					0x10			//; LVD interrupt enable bit	
#define		C_INT_TMR1					0x08			//; Timer1 underflow interrupt enable bit
#define		C_INT_EXT0					0x04			//; EX_INT0 interrupt enable bit
#define		C_INT_PABKey				0x02			//; PortA/B input change interrupt enable bit
#define		C_INT_TMR0					0x01			//; Timer0 overflow interrupt enable bit 

//;------------------------------------------------------------	
//; Pr_ADC_ADMD (10H) --------- ADC mode Register
//;------------------------------------------------------------			
//;Bit[7] : Enable/Disable ADC bit
#define		C_ADC_En					0x80			//; Enable ADC
#define		C_ADC_Dis					0x00			//; Disable ADC	
//;Bit[6] : Start a ADC conversion session          
#define		C_ADC_Start					0x40			//; Write 1 to this bit, start ADC converting
//;Bit[5] : ADC is end-of-convert                   
#define		C_ADC_Finish				0x20			//; (1:ADC is Finish, 0:ADC is in procession) Read-only
//;Bit[4] : Enable/Disable All ADC input channel bit
#define		C_ADC_CH_En					0x10			//; Enable ADC input channel
#define		C_ADC_CH_Dis				0x00			//; Disable all ADC input channel
//;Bit[3:0] : Select ADC input channel              
#define		C_Quarter_VDD				0x0B			//; 1/4 VDD as ADC input	
#define		C_ADC_PB5					0x0A			//; PB5(AIN10) pad as ADC input channel		
#define		C_ADC_PB4					0x09			//; PB4(AIN9) pad as ADC input channel	
#define		C_ADC_PB3					0x08			//; PB3(AIN8) pad as ADC input channel	
#define		C_ADC_PB2					0x07			//; PB2(AIN7) pad as ADC input channel	
#define		C_ADC_PB1					0x06			//; PB1(AIN6) pad as ADC input channel		
#define		C_ADC_PB0					0x05			//; PB0(AIN5) pad as ADC input channel	
#define		C_ADC_PA4					0x04			//; PA4(AIN4) pad as ADC input channel	
#define		C_ADC_PA3					0x03			//; PA3(AIN3) pad as ADC input channel	
#define		C_ADC_PA2					0x02			//; PA2(AIN2) pad as ADC input channel	
#define		C_ADC_PA1					0x01			//; PA1(AIN1) pad as ADC input channel		
#define		C_ADC_PA0					0x00			//; PA0(AIN0) pad as ADC input channel
	
//;------------------------------------------------------------	
//; Pr_ADC_ADR (11H) 	--------- ADC clock, ADC interrupt control and ADC low 4-bit data output Register
//;------------------------------------------------------------	
//;Bit[7] : ADC interrupt flag
#define		C_INF_ADC					0x00			//; clear ADC interrupt flag
//;Bit[6] : Enable/Disable of ADC interrupt             
#define		C_INT_ADC					0x40			//; Enable ADC interrupt	
//;Bit[5:4] : Select one of the 4 ADC clock             
#define		C_Ckl_Div2					0x30			//; ADC clock is Fcpu/2
#define		C_Ckl_Div1					0x20			//; ADC clock is Fcpu/1	
#define		C_Ckl_Div8					0x10			//; ADC clock is Fcpu/8
#define		C_Ckl_Div16					0x00			//; ADC clock is Fcpu/16	
//;Bit[3:0] : ADC low 4-bit data output Register.       
#define		C_ADC_Data_L				0x0F			//; AD3 ~ AD0 ,Read-only	

//;------------------------------------------------------------	
//; Pr_ADC_Data (12H) 	--------- ADC high 8-bit data output Register 
//;------------------------------------------------------------		
//;Bit[7:0] : High 8-bit of ADC data buffer
#define		C_ADC_Data_H				0xFF			//; AD11 ~ AD4 , Read-only	
//
//;------------------------------------------------------------	
//; Pr_ADC_Vrefh (13H) 	--------- ADC high reference voltage Register
//;------------------------------------------------------------		
//;Bit[7] : ADC reference high voltage (VREFH) select control bit	
#define		C_Vrefh_External			0x80			//; ADC reference high voltage is supplied by external pin PA0
#define		C_Vrefh_Internal			0x00			//; ADC reference high voltage is internal generated, the voltage selected depends on VHS1~0.
//;Bit[6:2] : Reserved
//;Bit[1:0] : Select ADC internal high reference voltage
#define		C_Vrefh_VDD					0x03			//; ADC reference high voltage is VDD
#define		C_Vrefh_4V					0x02			//; ADC reference high voltage is 4V	
#define		C_Vrefh_3V					0x01			//; ADC reference high voltage is 3V	
#define		C_Vrefh_2V					0x00			//; ADC reference high voltage is 2V
//
//;------------------------------------------------------------	
//; Pr_ADC_ADCR (14H) 	--------- ADC Sampling pulse width and select ADC conversion bit Register and AIN pin control Register
//;------------------------------------------------------------
//;Bit[7] : Reserved
#define		C_PB5_AIN10 				0x40			//; Select PB5 as pure AIN10 pin 
#define		C_PB4_AIN9 					0x20			//; Select PB4 as pure AIN9 pin 
#define		C_PB3_AIN8 					0x10			//; Select PB3 as pure AIN8 pin 
//;Bit[3:2] : Select ADC sampling pulse width           
#define		C_Sample_8clk				0x0C			//; ADC Sampling pulse width is 8 ADC clock
#define		C_Sample_4clk				0x08			//; ADC Sampling pulse width is 4 ADC clock
#define		C_Sample_2clk				0x04			//; ADC Sampling pulse width is 2 ADC clock
#define		C_Sample_1clk				0x00			//; ADC Sampling pulse width is 1 ADC clock
//;Bit[1:0] : Select ADC conversion bit numbers         
#define		C_12BIT						0x03			//; 12-bit ADC
#define		C_10BIT						0x01			//; 10-bit ADC
#define		C_8BIT						0x00			//;  8-bit ADC
//	
//;------------------------------------------------------------	
//; Pr_PA_WakeUp_Ctrl (15H) 	--------- PortA Wakeup Control Register
//;------------------------------------------------------------	
//;Bit[7:0] : AWUCON Bit Define
#define		C_PA_Wakeup					0xFF			//; Port A Wakeup Enable		
#define		C_PA7_Wakeup				0x80			//; PA7 Wakeup Enable
#define		C_PA6_Wakeup				0x40			//; PA6 Wakeup Enable 
#define		C_PA5_Wakeup				0x20			//; PA5 Wakeup Enable
#define		C_PA4_Wakeup				0x10			//; PA4 Wakeup Enable	
#define		C_PA3_Wakeup				0x08			//; PA3 Wakeup Enable
#define		C_PA2_Wakeup				0x04			//; PA2 Wakeup Enable 
#define		C_PA1_Wakeup				0x02			//; PA1 Wakeup Enable
#define		C_PA0_Wakeup				0x01			//; PA0 Wakeup Enable
//
//;------------------------------------------------------------	
//; Pr_AIN_Ctrl (16H) 	--------- AIN pin control Register
//;------------------------------------------------------------	
//;Bit[7:5] : Reserved
//;Bit[4:0] : Select PortA/B as pure AIN or GPIO pin
#define		C_PA_AIN 					0xFF			//; Select Port A/B as pure AIN pin for power-saving
//	                                                    
#define		C_PB2_AIN7 					0x80			//; Select PB2 as pure AIN7 pin 
#define		C_PB1_AIN6 					0x40			//; Select PB1 as pure AIN6 pin 	
#define		C_PB0_AIN5 					0x20			//; Select PB0 as pure AIN5 pin 	
#define		C_PA4_AIN4 					0x10			//; Select PA4 as pure AIN4 pin 
#define		C_PA3_AIN3 					0x08			//; Select PA3 as pure AIN3 pin 
#define		C_PA2_AIN2 					0x04			//; Select PA2 as pure AIN2 pin 
#define		C_PA1_AIN1 					0x02			//; Select PA1 as pure AIN1 pin 	
#define		C_PA0_AIN0 					0x01			//; Select PA0 as pure AIN0 pin 	

//;------------------------------------------------------------	
//; Pr_EXINT_Ctrl (18H) 	--------- External Interrupt Contorl Register
//;------------------------------------------------------------	
//;Bit[7:6] : Reserved	
//;Bit[5] : External INT1 Eanble
#define		C_INT1_En					0x20			//; PB1 set as INT1 input
//;Bit[4] : External INT0 Eanble	                    
#define		C_INT0_En					0x10			//; PB0 set as INT0 input
//;Bit[3:2] : INT1 edge trigger select                  
#define 	C_INT1_Edge					0x0C			//; INT1 trigger edge  --- 11b: Rising & Falling Edge, 10b:Falling Edge, 01b:Rising Edge    
#define		C_INT1_TwoEdge				0x0C			//; Rising & Falling edge trigger
#define		C_INT1_FallingEdge			0x08			//; Falling edge trigger	
#define		C_INT1_RisingEdge			0x04			//; Rising edge trigger			
//;Bit[1:0] : INT0 edge trigger select                  
#define 	C_INT0_Edge					0x03			//; INT0 trigger edge  --- 11b: Rising & Falling Edge, 10b:Falling Edge, 01b:Rising Edge  
#define		C_INT0_TwoEdge				0x03			//; Rising & Falling edge trigger
#define		C_INT0_FallingEdge			0x02			//; Falling edge trigger	
#define		C_INT0_RisingEdge			0x01			//; Rising edge trigger	
	
//;------------------------------------------------------------	
//; Pr_TMR_Data_PWM (19H) 	--------- TIMER1/2 Data and PWMDUTY1/2 msb 2 bits Register
//;------------------------------------------------------------	
//;Bit[7] : Timer2 Data Bit9	
#define		C_TMR2_Data_b9				0x80			//; Timer2 data bit9 
//;Bit[6] : Timer2 Data Bit8	
#define		C_TMR2_Data_b8				0x40			//; Timer2 data bit8
//;Bit[5] : Timer1 Data Bit9	
#define		C_TMR1_Data_b9				0x20			//; Timer1 data bit9 
//;Bit[4] : Timer1 Data Bit8	
#define		C_TMR1_Data_b8				0x10			//; Timer1 data bit8		
//;Bit[3] : Timer2 PWM Duty Bit9	
#define		C_PWM2_Duty_b9				0x08			//; PWM2 Duty bit9 
//;Bit[2] : Timer2 PWM Duty Bit8	
#define		C_PWM2_Duty_b8				0x04			//; PWM2 Duty bit8
//;Bit[1] : Timer1 PWM Duty Bit9	
#define		C_PWM1_Duty_b9				0x02			//; PWM1 Duty bit9 
//;Bit[0] : Timer1 PWM Duty Bit8	
#define		C_PWM1_Duty_b8				0x01			//; PWM1 Duty bit8	

//;------------------------------------------------------------	
//; Pr_CMP_PWR_Ctrl (1AH) 	--------- Voltage comparator Control Register
//;------------------------------------------------------------		
//;Bit[7] : Enable/disable voltage comparator
#define		C_CMP_En					0x80			//; Enable voltage comparator 
#define		C_CMP_Dis					0x00			//; Disable voltage comparator 	
//;Bit[6:0] : Reserved

//;------------------------------------------------------------	
//; Pr_RFC_Ctrl (1BH) 	--------- Resistor to Frency Converter Control Register
//;------------------------------------------------------------		
//;Bit[7] : Enable/disable RFC function
#define		C_RFC_En					0x80			//; Enable RFC function
#define		C_RFC_Dis					0x00			//; Disable RFC function	
//;Bit[6:4] : Reserved	
//;Bit[3:0] : Select one of the RFC pad
#define		C_RFC_PB5					0x0D			//; Select PB5 as RFC pad
#define		C_RFC_PB4					0x0C			//; Select PB4 as RFC pad	
#define		C_RFC_PB3					0x0B			//; Select PB3 as RFC pad
#define		C_RFC_PB2					0x0A			//; Select PB2 as RFC pad	
#define		C_RFC_PB1					0x09			//; Select PB1 as RFC pad	
#define		C_RFC_PB0					0x08			//; Select PB0 as RFC pad	
#define		C_RFC_PA7					0x07			//; Select PA7 as RFC pad
#define		C_RFC_PA6					0x06			//; Select PA6 as RFC pad
#define		C_RFC_PA5					0x05			//; Select PA5 as RFC pad
#define		C_RFC_PA4					0x04			//; Select PA4 as RFC pad
#define		C_RFC_PA3					0x03			//; Select PA3 as RFC pad
#define		C_RFC_PA2					0x02			//; Select PA2 as RFC pad	
#define		C_RFC_PA1					0x01			//; Select PA1 as RFC pad
#define		C_RFC_PA0					0x00			//; Select PA0 as RFC pad	
			
//;------------------------------------------------------------	
//; Pr_TMR3_Data_PWM (1CH) 	--------- TIMER3 Data and PWMDUTY3 msb 2 bits Register
//;------------------------------------------------------------	
//;Bit[7:6] : Reserved
//;Bit[5] : Timer3 Data Bit9	
#define		C_TMR3_Data_b9				0x20			//; Timer3 data bit9 
//;Bit[4] : Timer3 Data Bit8	
#define		C_TMR3_Data_b8				0x10			//; Timer3 data bit8		
//;Bit[3:2] : Reserved
//;Bit[1] : Timer3 PWM Duty Bit9	
#define		C_PWM3_Duty_b9				0x02			//; PWM3 Duty bit9 
//;Bit[0] : Timer3 PWM Duty Bit8	
#define		C_PWM3_Duty_b8				0x01			//; PWM3 Duty bit8	
		
//;------------------------------------------------------------	
//; Pr_INT2_Ctrl (1FH)		--------- Interrupt2 Enable Register
//;------------------------------------------------------------
//;Bit[7:5] : Reserved
//;Bit[4] : Timer3 underfolw Interrupt flag bit
#define		C_INF_TMR3					0x10			//; Timer3 underfolw interrupt flag bit
//;Bit[3:1] : Reserved
//;Bit[0] : Timer3 underfolw Interrupt enable bit
#define		C_INE_TMR3					0x01			//; Timer3 underfolw interrupt enable bit 

//;------------------------------------------------------------	
//; P_TMR0_Ctrl (xxH)		--------- T0MD Register
//;------------------------------------------------------------
//;		C_TMR0_Clk		C_TMR0_LowClk	|	Timer 0 Clock Source
//;------------------------------------------------------------
//;		0				x				|	From Instruction Clock
//;		1				0				|	From External Pin
//;		1				1				|	From Low Oscillator Frency (I_LRC or E_LXT)
//;------------------------------------------------------------
//;Bit[7,5:4] : Timer0 Clock Source Selection
#define		C_TMR0_LowClk				0x80			//; Same as LCKTM0	
#define		C_TMR0_Clk					0x20			//; Same as T0CS
#define		C_TMR0_ExtClk_Edge			0x10			//; Timer0 External Clock Edge Select --- 1:Falling Edge, 0:Rising Edge
//;Bit[6] : Reserved
//;Bit[3] : Watchdog Interrupt Source Selection / Timer0 Prescaler0 Selection
#define		C_PS0_WDT					0x08			//; Prescaler0 is assigned to WDT
#define		C_PS0_TMR0					0x00			//; Prescaler0 is assigned to TMR0
//;Bit[2:0] : Prescaler0 Dividing Rate Selection
#define		C_PS0_Div					0x07			//; Prescaler0 Dividing Rate Selection
#define		C_PS0_Div2					0x00
#define		C_PS0_Div4					0x01
#define		C_PS0_Div8					0x02
#define		C_PS0_Div16					0x03
#define		C_PS0_Div32					0x04
#define		C_PS0_Div64					0x05
#define		C_PS0_Div128				0x06
#define		C_PS0_Div256				0x07
//
//;=======================================================================================================================
//;=======================================================================================================================
//;-----------------------------------------------------------------------------------------------------------------------
//; F-page Special Function Register (IO Configuration Register)
//;-----------------------------------------------------------------------------------------------------------------------	
//;------------------------------------------------------------
//; Pf_PA_Dir_Ctrl (05H)	--------- PortA Direction(Input/Output) Control Register
//;------------------------------------------------------------
//;Bit[7:0] : Port A Input/Output Mode Selection (1:Input, 0:Output)
#define		C_PA_Input					0xFF			//; Port A Input Mode Control
#define		C_PA_Output					0x00			//; Port A Output Mode Control
                                                        
#define		C_PA7_Input					0x80			//; PA7 I/O mode Control bit
#define		C_PA6_Input					0x40			//; PA6 I/O mode Control bit
#define		C_PA5_Input					0x20			//; PA5 I/O mode Control bit
#define		C_PA4_Input					0x10			//; PA4 I/O mode Control bit 
#define		C_PA3_Input					0x08			//; PA3 I/O mode Control bit
#define		C_PA2_Input					0x04			//; PA2 I/O mode Control bit
#define		C_PA1_Input					0x02			//; PA1 I/O mode Control bit
#define		C_PA0_Input					0x01			//; PA0 I/O mode Control bit 
#define		C_PA7_Output				0x00			//; PA7 I/O mode Control bit
#define		C_PA6_Output				0x00			//; PA6 I/O mode Control bit
#define		C_PA5_Output				0x00			//; PA5 I/O mode Control bit
#define		C_PA4_Output				0x00			//; PA4 I/O mode Control bit 	
#define		C_PA3_Output				0x00			//; PA3 I/O mode Control bit
#define		C_PA2_Output				0x00			//; PA2 I/O mode Control bit
#define		C_PA1_Output				0x00			//; PA1 I/O mode Control bit
#define		C_PA0_Output				0x00			//; PA0 I/O mode Control bit 
//
//;------------------------------------------------------------	
//; Pf_PB_Dir_Ctrl (06H)	--------- PortB Direction(Input/Output) Control Register
//;------------------------------------------------------------
//;Bit[7:6] : Reserved
//;Bit[5:0] : Port B Input/Output Mode Selection (1:Input, 0:Output)
#define		C_PB_Input					0x3F			//; Port B Input Mode Control
#define		C_PB_Output					0x00			//; Port B Output Mode Control
	                                                    
#define		C_PB5_Input					0x20			//; PB5 I/O mode Control bit
#define		C_PB4_Input					0x10			//; PB4 I/O mode Control bit
#define		C_PB3_Input					0x08			//; PB3 I/O mode Control bit
#define		C_PB2_Input					0x04			//; PB2 I/O mode Control bit
#define		C_PB1_Input					0x02			//; PB1 I/O mode Control bit
#define		C_PB0_Input					0x01			//; PB0 I/O mode Control bit
#define		C_PB5_Output				0x00			//; PB5 I/O mode Control bit
#define		C_PB4_Output				0x00			//; PB4 I/O mode Control bit	
#define		C_PB3_Output				0x00			//; PB3 I/O mode Control bit
#define		C_PB2_Output				0x00			//; PB2 I/O mode Control bit
#define		C_PB1_Output				0x00			//; PB1 I/O mode Control bit
#define		C_PB0_Output				0x00			//; PB0 I/O mode Control bit

//;------------------------------------------------------------	
//; Pr_PA_PH_Ctrl (09H)	--------- PortA Pull-High Control Register
//;------------------------------------------------------------
//;Bit[7:0] : PortA Pull-High Control Register (1:Disable, 0:Pull-High)
#define		C_PA_PHB					0xFF			//; PortA Pull-High Control bit 
#define		C_PA7_PHB					0x80			//; PA7 Pull-High Control bit 
#define		C_PA6_PHB					0x40			//; PA6 Pull-High Control bit   
#define		C_PA5_PLB					0x20			//; PA5 Pull-Low  Control bit
#define		C_PA4_PHB					0x10			//; PA4 Pull-High Control bit
#define		C_PA3_PHB					0x08			//; PA3 Pull-High Control bit	
#define		C_PA2_PHB					0x04			//; PA2 Pull-High Control bit
#define		C_PA1_PHB					0x02			//; PA1 Pull-High Control bit
#define		C_PA0_PHB					0x01			//; PA0 Pull-High Control bit
//		
//;------------------------------------------------------------	
//; Pf_PS0_Cnt (0AH)		--------- Prescaler0 Counter Value Register
//;------------------------------------------------------------
//;Bit[7:0] : Prescaler0 Counter Value
#define		C_PS0_Cnt					0xFF			//; Read-only	
//	
//;------------------------------------------------------------	
//; Pf_PB_OD_Ctrl (0CH)	--------- PortB Open-Drain Control Register
//;------------------------------------------------------------
//;Bit[7:6] : Reserved
//;Bit[5:0] : PortB Open-Drain Control (1:Open-Drain, 0:Disable)
#define		C_PB_OD						0x3F			//; Port B Open-Drain Control
#define		C_PB5_OD					0x20			//; PB5 Open-Drain Control bit	
#define		C_PB4_OD					0x10			//; PB4 Open-Drain Control bit	
#define		C_PB3_OD					0x08			//; PB3 Open-Drain Control bit	
#define		C_PB2_OD					0x04			//; PB2 Open-Drain Control bit
#define		C_PB1_OD					0x02			//; PB1 Open-Drain Control bit 
#define		C_PB0_OD					0x01			//; PB0 Open-Drain Control bit
//
//;------------------------------------------------------------	
//; Pf_CMP_Ctrl (0EH)	--------- Comparator voltage select Control Register
//;------------------------------------------------------------
//;Bit[7:4] : PS[3:0]
#define		C_CMP_PinSelect				0xF0
//;Bit[3:0] : VS[3:0]
#define		C_CMP_VolSelect				0x0F
//;P2V MODE
//;VS[3:0]	V- of Comparator	PS[3:0]		Selected pad
//;--------------------------------------------------------
//;0000		P2P mode			0000		PA0
//;0001		1 / 16 VDD			0001		PA1
//;0010		2 / 16 VDD			0010		PA2
//;0011		3 / 16 VDD			0011		PA3
//;0100		4 / 16 VDD			0100		NA
//;0101		5 / 16 VDD			0101		NA
//;0110		6 / 16 VDD			0110		NA
//;0111		7 / 16 VDD			0111		NA
//;1000		8 / 16 VDD			1000		NA
//;1001		9 / 16 VDD			1001		NA
//;1010		10 / 16 VDD			1010		NA
//;1011		11 / 16 VDD			1011		NA
//;1100		12 / 16 VDD			1100		NA
//;1101		13 / 16 VDD			1101		NA
//;1110		14 / 16 VDD			1110		NA
//;1111		15 / 16 VDD			1111		NA
//
//;P2P MODE
//;PS[3:0]	Non-inverting input		Inverting input
//;-------------------------------------------
//;0000		PA0						PA1
//;0001		PA1						PA0
//;0010		PA2						PA3
//;0011		PA3						PA2
//
//;------------------------------------------------------------	
//; Pf_PWR_Ctrl1 (0FH)	--------- Power Control Register 1
//;------------------------------------------------------------
//;Bit[7] : All Interrupt Enable (Set by instruction ENI, clear by instruction DISI)
#define		C_All_INT_En				0x80			//; Enable all unmasked interrupts
//;Bit[6] : Low voltage detector output 
#define		C_LVDOUT					0x40			//; read-only
//;Bit[5] : Reserved
//;Bit[4:2] : Select one of the 8 LVD voltage
#define		C_LVD_4P3V					0x1C			//; LVD Voltage=4.3V
#define		C_LVD_3P6V					0x18			//; LVD Voltage=3.6V	
#define		C_LVD_3P3V					0x14			//; LVD Voltage=3.3V	
#define		C_LVD_3P0V					0x10			//; LVD Voltage=3.0V	
#define		C_LVD_2P7V					0x0C			//; LVD Voltage=2.7V	
#define		C_LVD_2P4V					0x08			//; LVD Voltage=2.4V	
#define		C_LVD_2P2V					0x04			//; LVD Voltage=2.2V	
#define		C_LVD_2P0V					0x00			//; LVD Voltage=2.0V		
//;Bit[0] : Timer0 Enable                               
#define		C_TMR0_En					0x01			//; Enable Timer0
#define		C_TMR0_Dis					0x00			//; Disable Timer0

//;=======================================================================================================================
//;=======================================================================================================================
//;-----------------------------------------------------------------------------------------------------------------------
//; S-page Special Function Register (Special Function Register)
//;-----------------------------------------------------------------------------------------------------------------------		
//;------------------------------------------------------------
//; Ps_TMR1_Data (00H)	--------- Timer1 Data Register
//;------------------------------------------------------------
//;Bit[7:0] : Timer1 Data
#define		C_TMR1_Data					0xFF	
//	
//;------------------------------------------------------------	
//; Ps_TMR1_Ctrl1 (01H)	--------- Timer1 Control Register 1
//;------------------------------------------------------------
//;Bit[7:6] : PWM1 Control
#define		C_PWM1_En					0x80 			//; PWM1 output will be present on PB3
#define		C_PWM1_Active				0x40 			//; PWM1 output is active
#define		C_PWM1_Active_Lo			0x40 			//; PWM1 output is active low 
#define		C_PWM1_Active_Hi			0x00 			//; PWM1 output is active high 
//;Bit[5:3] : Reserved                              	
//;Bit[2:0] : Timer1 Control                        	
#define		C_TMR1_OneShot				0x04 			//; One-Shot mode. Timer1 will count once from the initial value to 0x00
#define		C_TMR1_Reload				0x02 			//; Initial value is reloaded from reload register TMR1(T1OS=0)
														
#define		C_TMR1_En					0x01 			//; Enable Timer1
#define		C_TMR1_Dis					0x00 			//; Disable Timer1

//;------------------------------------------------------------	
//; Ps_TMR1_Ctrl2 (02H)	--------- Timer1 Control Register 2
//;------------------------------------------------------------
//;Bit[7:6] : Reserved
//;Bit[5] : Timer1 Clock Source Select
#define		C_TMR1_ClkSrc_Ext			0x20			//; Timer1 clock source from External Clock Input(EX_CKI0)
#define		C_TMR1_ClkSrc_Inst			0x00			//; Timer1 clock source from Internal Instruction Clock	
//;Bit[4] : Timer1 external clock edge selection        
#define 	C_TMR1_ExtClk_Edge			0x10			//; Timer1 External Clock Edge Select --- 1:Falling Edge, 0:Rising Edge  
#define		C_TMR1_ExtFalling			0x10			//; Timer1 will decrease one while EX_CKI0 Falling Edge.
#define		C_TMR1_ExtRising			0x00			//; Timer1 will decrease one while EX_CKI0 Rising Edge.
//;Bit[3] :  Disable/enable Prescaler1                  
#define 	C_PS1_Dis           		0x08			//; Disable Prescaler1
#define		C_PS1_EN					0x00			//; Enable Prescaler1
//;Bit[2:0] : Prescaler 1 Dividing Rate Selection       
#define		C_PS1_Div					0x07			//; Prescaler1 Dividing Rate Selection
#define		C_PS1_Div2					0x00
#define		C_PS1_Div4					0x01
#define		C_PS1_Div8					0x02
#define		C_PS1_Div16					0x03
#define		C_PS1_Div32					0x04
#define		C_PS1_Div64					0x05
#define		C_PS1_Div128				0x06
#define		C_PS1_Div256				0x07
//
//;------------------------------------------------------------	
//; Ps_PWM1_Duty (03H)	--------- PWM1 Duty Register
//;------------------------------------------------------------
//;Bit[7:0] : PWM1 Duty Value
#define		C_PWM1_Duty					0xFF
//
//;------------------------------------------------------------	
//; Ps_PS1_Cnt (04H)		--------- Prescaler1 Counter Value Register
//;------------------------------------------------------------
//;Bit[7:0] : Prescaler1 Counter Value
#define		C_PS1_Cnt					0xFF			//; Read-only
//
//;------------------------------------------------------------	
//; Ps_BZ1_Ctrl (05H)		--------- Buzzer1 Control Register
//;------------------------------------------------------------
//;Bit[7] : BZ1 Enable
#define		C_BZ1_En					0x80			//; Enable BZ1 output
//;Bit[6:4] : Reserved
//;Bit[3:0] : BZ1 Frency Selection
#define		C_BZ1_FSel					0x0F			//; BZ1 frency selection

#define		C_BZ1_PS1Div2				0x00			//; Clock Soruce from Prescaler 1
#define		C_BZ1_PS1Div4				0x01
#define		C_BZ1_PS1Div8				0x02
#define		C_BZ1_PS1Div16				0x03
#define		C_BZ1_PS1Div32				0x04
#define		C_BZ1_PS1Div64				0x05
#define		C_BZ1_PS1Div128				0x06
#define		C_BZ1_PS1Div256				0x07
                                
#define		C_BZ1_TMR1B0				0x08			//; Clock Source from Timer 1
#define		C_BZ1_TMR1B1				0x09
#define		C_BZ1_TMR1B2				0x0A
#define		C_BZ1_TMR1B3				0x0B
#define		C_BZ1_TMR1B4				0x0C
#define		C_BZ1_TMR1B5				0x0D
#define		C_BZ1_TMR1B6				0x0E
#define		C_BZ1_TMR1B7				0x0F
//
//;------------------------------------------------------------	
//; Ps_IR_Ctrl (06H)		--------- IR Control Register
//;------------------------------------------------------------
//;Bit[7] : IR Clock Source Selection (1:3.58MHz, 0:455KHz)
#define		C_IR_ClkSrc_358M			0x80			//; IRCR[7]=1 , external crystal is 3.58MHz (This bit is ignored if internal high frency oscillation is used)
#define		C_IR_ClkSrc_455K			0x00			//; IRCR[7]=0 , external crystal is 455KHz
//;Bit[6:3] : Reserved
//;Bit[2] : IR Polarity Selection
#define		C_IR_Pol_Sel				0x04
//;Bit[1] : IR Carrier Frency Selection (1:57KHz, 0:38KHz)
#define		C_IR_57K					0x02			//; IRCR[1]=1 , IR carrier frency is 57KHz
#define		C_IR_38K					0x00			//; IRCR[1]=0 , IR carrier frency is 38KHz
//;Bit[0] : IR Enable
#define		C_IR_En						0x01			//; Enable IR carrier output
//
//;------------------------------------------------------------	
//; Ps_TbHigh_Addr (07H)	--------- Table Access High Byte Address Pointer Register
//;------------------------------------------------------------
//;Bit[7:4] : Reserved
//;Bit[2:0] : Table Access High Byte Address Pointer
#define		C_TbHigh_Addr				0x07			//; When instruction CALLA, GOTOA or TABLEA is executed TBHP[2:0] is PC[10:8] (NY8B062D)
//
//;------------------------------------------------------------	
//; Ps_TbHigh_Data (08H)	--------- Table Access High Byte Data Register
//;------------------------------------------------------------
//;Bit[7:6] : Reserved
//;Bit[5:0] : Table Access High Byte Data
#define		C_TbHigh_Data				0x3F
//	
//;------------------------------------------------------------
//; Ps_TMR2_Data (09H)	--------- Timer2 Data Register
//;------------------------------------------------------------
//;Bit[7:0] : Timer2 Data
#define		C_TMR2_Data					0xFF	

//;------------------------------------------------------------	
//; Ps_TMR2_Ctrl1 (0AH)	--------- Timer2 Control Register 1
//;------------------------------------------------------------
//;Bit[7:6] : PWM2 Control
#define 	C_PWM2_En					0x80 			//; PWM2 output will be present on PB2
#define 	C_PWM2_Active				0x40 			//; PWM2 output is active
#define 	C_PWM2_Active_Lo			0x40 			//; PWM2 output is active low 
#define 	C_PWM2_Active_Hi			0x00 			//; PWM2 output is active high 
//;Bit[5:3] : Reserved                              	
//;Bit[2:0] : Timer2 Control                        	
#define		C_TMR2_OneShot				0x04 			//; One-Shot mode. Timer2 will count once from the initial value to 0x00
#define		C_TMR2_Reload				0x02 			//; Initial value is reloaded from reload register TMR2(T2OS=0)                                               
#define		C_TMR2_En					0x01 			//; Enable Timer2
#define		C_TMR2_Dis					0x00 			//; Disable Timer2

//;------------------------------------------------------------	
//; Ps_TMR2_Ctrl2 (0BH)	--------- Timer2 Control Register 2
//;------------------------------------------------------------
//;Bit[7:6] : Reserved
//;Bit[5] : Timer2 Clock Source Select
#define		C_TMR2_ClkSrc_Ext			0x20			//; Timer2 clock source from External Clock Input
#define		C_TMR2_ClkSrc_Inst			0x00			//; Timer2 clock source from Internal Instruction Clock	
//;Bit[4] : Timer2 external clock edge selection        
#define 	C_TMR2_ExtClk_Edge			0x10			//; Timer2 External Clock Edge Select --- 1:Falling Edge, 0:Rising Edge  
#define		C_TMR2_ExtFalling			0x10			//; Timer2 will decrease one while EX_CKI1 Falling Edge.
#define		C_TMR2_ExtRising			0x00			//; Timer2 will decrease one while EX_CKI1 Rising Edge.
//;Bit[3] :  Disable/enable Prescaler2                  
#define 	C_PS2_Dis           		0x08			//; Disable Prescaler2
#define		C_PS2_EN					0x00			//; Enable Prescaler2
//;Bit[2:0] : Prescaler 2 Dividing Rate Selection       
#define		C_PS2_Div					0x07			//; Prescaler2 Dividing Rate Selection
#define		C_PS2_Div2					0x00
#define		C_PS2_Div4					0x01
#define		C_PS2_Div8					0x02
#define		C_PS2_Div16					0x03
#define		C_PS2_Div32					0x04
#define		C_PS2_Div64					0x05
#define		C_PS2_Div128				0x06
#define		C_PS2_Div256				0x07
//
//;------------------------------------------------------------	
//; Ps_PWM2_Duty (0CH)	--------- PWM2 Duty Register
//;------------------------------------------------------------
//;Bit[7:0] : PWM2 Duty Value
#define		C_PWM2_Duty					0xFF
//
//;------------------------------------------------------------	
//; Ps_PS2_Cnt (0DH)		--------- Prescaler2 Counter Value Register
//;------------------------------------------------------------
//;Bit[7:0] : Prescaler2 Counter Value
#define		C_PS2_Cnt					0xFF			//; Read-only	
//
//;------------------------------------------------------------	
//; Ps_BZ2_Ctrl (0EH)		--------- Buzzer2 Control Register
//;------------------------------------------------------------
//;Bit[7] : BZ2 Enable
#define		C_BZ2_En					0x80			//; Enable BZ2 output 
//;Bit[6:4] : Reserved
//;Bit[3:0] : BZ2 Frency Selection
#define		C_BZ2_FSel					0x0F			//; BZ2 frency selection

#define		C_BZ2_PS2Div2				0x00			//; Clock Soruce from Prescaler 2
#define		C_BZ2_PS2Div4				0x01
#define		C_BZ2_PS2Div8				0x02
#define		C_BZ2_PS2Div16				0x03
#define		C_BZ2_PS2Div32				0x04
#define		C_BZ2_PS2Div64				0x05
#define		C_BZ2_PS2Div128				0x06
#define		C_BZ2_PS2Div256				0x07

#define		C_BZ2_TMR2B0				0x08			//; Clock Source from Timer 2
#define		C_BZ2_TMR2B1				0x09
#define		C_BZ2_TMR2B2				0x0A
#define		C_BZ2_TMR2B3				0x0B
#define		C_BZ2_TMR2B4				0x0C
#define		C_BZ2_TMR2B5				0x0D
#define		C_BZ2_TMR2B6				0x0E
#define		C_BZ2_TMR2B7				0x0F
//	
//;------------------------------------------------------------   
//; Ps_SYS_Ctrl (0FH)	--------- Oscillation Control Register (Include Switch Working Mode)
//;------------------------------------------------------------
//;Bit[7] : Comparator output status
#define		C_CMPOUT					0x80			//; Read-only
//;Bit[6] : Disable/enable comparator output to pad PB3 
#define		C_CMPOPB3_Dis				0x00			//; Disable comparator output to pad PB3
#define		C_CMPOPB3_En				0x40			//; Enable comparator output to pad PB3
//;Bit[5] : Comparator output change state interrupt flag
#define		C_INF_CMP					0x00			//; clear comparator interrupt flag
//;Bit[4] : Enable/Disable of comparator interrupt      
#define		C_INT_CMP					0x10			//; Enable comparator interrupt
//;Bit[3:2] : System Mode Select                        
#define		C_Mode						0x0C			//; System Operating Mode Selection
#define		C_Normal_Mode				0x00			//; Enter Normal mode
#define		C_Halt_Mode					0x04			//; Enter Halt mode
#define		C_Standby_Mode				0x08			//; Enter Standby mode
//;Bit[1] : Stop FHOSC                                  
#define		C_FHOSC_Stop				0x02			//; Disable high-frency oscillation (FHOSC)
//;Bit[0] : FOSC Seletction                             
#define		C_FHOSC_Sel					0x01			//; OSCCR[0]=1 , FOSC is high-frency oscillation (FHOSC)
#define		C_FLOSC_Sel					0x00			//; OSCCR[0]=0 , FOSC is Low-frency oscillation (FLOSC)	

//;------------------------------------------------------------
//; Ps_TMR3_Data (10H)	--------- Timer3 Data Register
//;------------------------------------------------------------
//;Bit[7:0] : Timer3 Data
#define		C_TMR3_Data					0xFF	
//	
//;------------------------------------------------------------	
//; Ps_TMR3_Ctrl1 (11H)	--------- Timer3 Control Register 1
//;------------------------------------------------------------
//;Bit[7:6] : PWM3 Control
#define		C_PWM3_En					0x80 		//; PWM3 output will be present on PA2
#define		C_PWM3_Active				0x40 		//; PWM3 output is active
#define		C_PWM3_Active_Lo			0x40 		//; PWM3 output is active low 
#define		C_PWM3_Active_Hi			0x00 		//; PWM3 output is active high 
//;Bit[5:3] : Reserved                              
//;Bit[2:0] : Timer3 Control                        
#define		C_TMR3_OneShot				0x04 		//; One-Shot mode. Timer3 will count once from the initial value to 0x00
#define		C_TMR3_Reload				0x02 		//; Initial value is reloaded from reload register TMR3(T3OS=0)
		                                            
#define		C_TMR3_En					0x01 		//; Enable Timer3
#define		C_TMR3_Dis					0x00 		//; Disable Timer3
//
//;------------------------------------------------------------	
//; Ps_TMR3_Ctrl2 (12H)	--------- Timer3 Control Register 2
//;------------------------------------------------------------
//;Bit[7:6] : Reserved
//;Bit[5] : Timer3 Clock Source Select
#define		C_TMR3_ClkSrc_Ext			0x20		//; Timer3 clock source from External Clock Input(EX_CKI1)
#define		C_TMR3_ClkSrc_Inst			0x00		//; Timer3 clock source from Internal Instruction Clock	
//;Bit[4] : Timer3 external clock edge selection       
#define	  	C_TMR3_ExtClk_Edge			0x10		//; Timer3 External Clock Edge Select --- 1:Falling Edge, 0:Rising Edge  
#define		C_TMR3_ExtFalling			0x10		//; Timer3 will decrease one while EX_CKI1 Falling Edge.
#define		C_TMR3_ExtRising			0x00		//; Timer3 will decrease one while EX_CKI1 Rising Edge.
//;Bit[3] : Disable/enable Prescaler3                 
#define	  	C_PS3_Dis           		0x08		//; Disable Prescaler3
#define		C_PS3_EN					0x00		//; Enable Prescaler3
//;Bit[2:0] : Prescaler 3 Dividing Rate Selection     
#define		C_PS3_Div					0x07		//; Prescaler3 Dividing Rate Selection
#define		C_PS3_Div2					0x00
#define		C_PS3_Div4					0x01
#define		C_PS3_Div8					0x02
#define		C_PS3_Div16					0x03
#define		C_PS3_Div32					0x04
#define		C_PS3_Div64					0x05
#define		C_PS3_Div128				0x06
#define		C_PS3_Div256				0x07
//
//;------------------------------------------------------------	
//; Ps_PWM3_Duty (13H)	--------- PWM3 Duty Register
//;------------------------------------------------------------
//;Bit[7:0] : PWM3 Duty Value
#define		C_PWM3_Duty					0xFF
//
//;------------------------------------------------------------	
//; Ps_PS3_Cnt (14H)		--------- Prescaler3 Counter Value Register
//;------------------------------------------------------------
//;Bit[7:0] : Prescaler3 Counter Value
#define		C_PS3_Cnt					0xFF		//; Read-only	
//
//;------------------------------------------------------------	
//; Ps_BZ3_Ctrl (15H)		--------- Buzzer3 Control Register
//;------------------------------------------------------------
//;Bit[7] : BZ3 Enable
#define		C_BZ3_En					0x80		//; Enable BZ3 output
//;Bit[6:4] : Reserved                  
//;Bit[3:0] : BZ3 Frency Selection      
#define		C_BZ3_FSel					0x0F		//; BZ3 frency selection
                                        
#define		C_BZ3_PS3Div2				0x00		//; Clock Soruce from Prescaler 3
#define		C_BZ3_PS3Div4				0x01
#define		C_BZ3_PS3Div8				0x02
#define		C_BZ3_PS3Div16				0x03
#define		C_BZ3_PS3Div32				0x04
#define		C_BZ3_PS3Div64				0x05
#define		C_BZ3_PS3Div128				0x06
#define		C_BZ3_PS3Div256				0x07
                                        
#define		C_BZ3_TMR3B0				0x08		//; Clock Source from Timer 3
#define		C_BZ3_TMR3B1				0x09
#define		C_BZ3_TMR3B2				0x0A
#define		C_BZ3_TMR3B3				0x0B
#define		C_BZ3_TMR3B4				0x0C
#define		C_BZ3_TMR3B5				0x0D
#define		C_BZ3_TMR3B6				0x0E
#define		C_BZ3_TMR3B7				0x0F	
//;=======================================================================================================================
//;=======================================================================================================================
//;-----------------------------------------------------------------------------------------------------------------------
//;General Constant Define
//;-----------------------------------------------------------------------------------------------------------------------
#define		C_SaveToAcc					0x00	
#define		C_SaveToReg					0x01	
                                        
#define		C_Bit0						0x01
#define		C_Bit1						0x02
#define		C_Bit2						0x04
#define		C_Bit3						0x08
#define		C_Bit4						0x10
#define		C_Bit5						0x20
#define		C_Bit6						0x40
#define		C_Bit7						0x80

#endif	