; =========================================================================
; Created by ATW.
; User: VincentLin
; Date: 2016/02/23
; Time: 7:38
; Chip: AT8B62D
; 说明：利用 ADC 读去外部电压，将其变化转入改变PWM1~3 Duty (10Bit解析度)
;	PA0/PA1/PA3:ADC Input
;	PB3:PWM1 输出(PA0控制)
;	PB2:PWM2 输出(PA1控制)
;	PA2:PWM3 输出(PA3控制)
; =========================================================================

	#include	AT8B62D.h
		
;; User Register Define (0x20~0x7F)
	R_ACC_Buf	EQU		0x20
	R_Status_Buf	EQU		0x21
	R_Flag		EQU		0x22
		f_1ms_B		= 0
		f_ADCIF_B	= 1
		f_adc_B		= 2


	R_ADC0LB	EQU		0x30
	R_ADC0HB	EQU		0x31
	R_ADC1LB	EQU		0x32
	R_ADC1HB	EQU		0x33
	R_ADC2LB	EQU		0x34
	R_ADC2HB	EQU		0x35
	
	R_ADC_Offset	EQU		0x36	
	
	R_SelADC	EQU		0x36
	R_10msCount	EQU		0X37

;; Chip Reset Vector
; ===============================================================
		ORG	0x00
Reset:
		GOTO	Main_Prog

;; ISR Vector
		ORG	0x08
ISR_Prog:
		MOVAR		R_ACC_Buf			;; 保留 ACC 及 Status 的状态值
		SWAPR		R_ACC_Buf, R
		SWAPR		STATUS, A
		MOVAR		R_Status_Buf
	
	ISR_Prog100:
		BTRSS		INTF, T0IF_B
		GOTO		ISR_ADC
		MOVIA		0xFE
		MOVAR		INTF				;; CLR TIMER0 FLAG
		MOVIA		0x01
		XORAR		PB, R
		BSR		R_Flag, f_1ms_B 

	ISR_ADC:
		BTRSS		ADR, ADIF_B
		GOTO		ISR_End
		BCR		ADR, ADIF_B
		BSR		R_Flag, f_ADCIF_B



	ISR_End:
		SWAPR		R_Status_Buf, A			;; 取回 ACC 及 Status 的状态值
		MOVAR		STATUS
		SWAPR		R_ACC_Buf, A
		RETIE
		
		

;; Main Program
;		ORG	0x10
Main_Prog:
		LCALL		F_ClearAllRAM
		LCALL		F_IOInit
		
		MOVIA		0x01				;; ENABLE T0 Interrupt
		MOVAR		INTE
		
		ENI						;; Enable Goble Interrupt

Main_Start:
		CLRWDT
		BTRSS		R_Flag, f_1ms_B
		GOTO		Main_Start
		
		BCR		R_Flag, f_1ms_B
		
		INCR		R_10msCount, R
		MOVIA		10
		SUBAR		R_10msCount, A
		BTRSS		STATUS, C_B
		GOTO		Main_Start
		
		CLRR		R_10msCount
		
		
F_GetADC0_Data:
		BCR		ADMD, CHS0_B			;; Set PA0 is AD Input
		BCR		ADMD, CHS1_B
		BCR		ADMD, CHS2_B
				
		BCR		R_Flag, f_ADCIF_B		;; Clear ADC Int Flag
		BSR		ADMD, START_B			;; Start ADC Converter
		BTRSS		R_Flag, f_ADCIF_B		;; if ADIF=1，ADC Converter End
		GOTO		$-1
		BCR		R_Flag, f_ADCIF_B


		MOVR		ADR, A
		ANDIA		0x0F
		MOVAR		R_ADC0LB
		SWAPR		ADD, A
		ANDIA		0xF0
		IORAR		R_ADC0LB, R
		
		SWAPR		ADD, A
		ANDIA		0x0F
		MOVAR		R_ADC0HB
		
		MOVR		ADD, A
		SFUN		PWM1DUTY		
		

F_GetADC1_Data:		
		BSR		ADMD, CHS0_B			;; Set PA1 is AD Input
		BCR		ADMD, CHS1_B
		BCR		ADMD, CHS2_B
		
		BCR		R_Flag, f_ADCIF_B		;; Clear ADC Int Flag
		BSR		ADMD, START_B			;; Start ADC Converter
		BTRSS		R_Flag, f_ADCIF_B		;; if ADIF=1，ADC Converter End
		GOTO		$-1
		BCR		R_Flag, f_ADCIF_B
		

		MOVR		ADR, A
		ANDIA		0x0F
		MOVAR		R_ADC1LB
		SWAPR		ADD, A
		ANDIA		0xF0
		IORAR		R_ADC1LB, R
		
		SWAPR		ADD, A
		ANDIA		0x0F
		MOVR		R_ADC1HB, R
		
		MOVR		ADD, A
		SFUN		PWM2DUTY
		

F_GetADC3_Data:
		BSR		ADMD, CHS0_B			;; Set PA3 is AD Input
		BSR		ADMD, CHS1_B
		BCR		ADMD, CHS2_B
		
		BCR		R_Flag, f_ADCIF_B		;; Clear ADC Int Flag
		BSR		ADMD, START_B			;; Start ADC Converter
		BTRSS		R_Flag, f_ADCIF_B		;; if ADIF=1，ADC Converter End
		GOTO		$-1
		BCR		R_Flag, f_ADCIF_B
		
		MOVR		ADR, A
		ANDIA		0x0f
		MOVAR		R_ADC2LB
		SWAPR		ADD, A
		ANDIA		0xf0
		IORAR		R_ADC2LB, R
		
		SWAPR		ADD, A
		ANDIA		0x0f
		MOVR		R_ADC2HB, R
		
		MOVR		ADD, A
		SFUN		PWM3DUTY
		
		GOTO		Main_Start	
		

;==================================================================
; Project Name:	清零全部RAM
; Last Modify Date:2010-11-9 16:12
;
;;Clear	RAM 0x20~0x7f
F_ClearAllRAM:
	;Bank0	
		MOVIA		0x20				;; 切换到 RAM Bank0
		MOVAR		FSR
	L_Clear_Next_Byte_Bank0:
		CLRR		INDF				;; 清除该地址资料
		INCR		FSR, R				;; 累加间接地址
		BTRSS		FSR, 7
		GOTO		L_Clear_Next_Byte_Bank0		;; 否，跳跃
		
		RET

;====================================================================
; Project Name: IO 初始化
; Madify Data: 2014.12.11
;
F_IOInit:
		MOVIA		0xff
		MOVAR		PA			;; 初始值
		MOVIA		B'00001011'
		IOST		IOSTA			;; 设定为IO状态	0=Output,  1=Input
		
		MOVIA		0xff
		MOVAR		PB			;; 初始值
		MOVIA		00000000
		IOST		IOSTB				;; 设定为IO状态	0=Output,  1=Input
		
		MOVIA		0x80			;; 设定为 WDT(B7)=1:EN/0:DIS, PB0(B6)=1:INT/0:GPIO, LVR(B3)=1:EN/0:DIS
		MOVAR		PCON

;====================================================================
; Project Name: Time0 初始化
; Madify Data: 2014.12.11
; T=（1/intruction clk)*分频*TMR0
;  = ((1/4MHz)*4)*4*256(00H)
;  = 1.024ms
F_Timer0Set:
		MOVIA		0xFE
		MOVAR		INTF			;; Clr Timer0 Flag
		MOVIA		00000001
		T0MD	
		MOVIA		0x00
		MOVAR		TMR0

;====================================================================
; Project Name: PWM1 初始化
; Madify Data: 2014.12.11
; PWM1 Frequecy=(1/H_IRC)*指令分频*时间分频＊(TMR1+1)
;             =(1/4MHz)*4T*256*(1FFH+1)
;             = 130.861ms
;
; Duty1 = (1/H_IRC)*指令分频*时间分频＊PWM1DUTY
;      = (1/4)*4*256*0aH
;      = 2.56ms
;
		MOVIA		00000000
		SFUN		T1CR1			;; Disale Timer1
		MOVIA		0xF7
		MOVIA		INTF			;; Clr Timer1 Flag

		MOVR		TMRH, A	
		ANDIA		B'11001111'
		IORIA		B'00010000'
		MOVAR		TMRH			;; Set Timer1 Data Bit[9:8]=01
		MOVIA		0xFF			;; Timer1 Data Byte Data[7:0]
		SFUN		TMR1

		MOVIA		0x07
		SFUN		T1CR2			;; P1SEl(B2:B0), PS1EN(B3):0(EN)/1(Dis), T1CE(B4):0:Low->Hi/1:hi->Low, T1CS(B5):0:Instruction CLK/1:Ext CLK

		BCR		TMRH, PWM1DUTY8_B
		BCR		TMRH, PWM1DUTY9_B
		MOVIA		0x0A
		SFUN		PWM1DUTY

		MOVIA		0x83			;; TIMER1(B0):1:EN/0:Dis, AUTO ReLoad(B1):1:En/0:Dis, PWM1oEN(B7):1:P2 is PWMO/0:P2 is GPIO
		SFUN		T1CR1

;====================================================================
; Project Name: PWM2 初始化
; Madify Data: 2016.02.20
; PWM2 Frequecy	=(1/H_IRC)*指令分频*时间分频＊(TMR2+1)
;  		=((1/4MHz)*4)*2*280H
;		=1.282ms

; Duty2	= (1/H_IRC)*指令分频*时间分频＊PWM2DUTY
;      	= (1/4)*4*2*10H
;      	= 32us
;
		MOVIA		00000000
		SFUN		T2CR1			;; Disale Timer2
		
		MOVIA		0xDF
		MOVAR		INTF			;; Clr Timer2 Flag

		MOVR		TMRH, A		
		ANDIA		B'00111111'
		IORIA		B'10000000'
		MOVAR		TMRH			;; Set Timer1 Data Bit[9:8]=10
		MOVIA		0x80
		SFUN		TMR2

		BCR		TMRH, PWM2DUTY8_B
		BCR		TMRH, PWM2DUTY9_B		
		MOVIA		0x10
		SFUN		PWM2DUTY

		MOVIA		0x00
		SFUN		T2CR2			;; P2SEl(B2:B0), PS2EN(B3):0(EN)/1(Dis), T2CE(B4):0:Low->Hi/1:hi->Low, T2CS(B5):0:Instruction CLK/1:Ext CLK

		MOVIA		0x83			;; T2EN(B0):1:EN Timer2/0:Dis, T2RL(B1):1:En Auto Load/0:Dis, T2OS(B2):1:One-Shot/0:No_Stop, PWM2OAL(B6):1:PWM2 active Low/0:High, PWM2oEN(B7):1:PB2 is PWM2 / 0:PB2 is GPIO
		SFUN		T2CR1

;====================================================================
; Project Name: Time3 初始化
; Madify Data: 2016.02.20
; PWM3 Frequecy	= (1/H_IRC)*指令分频*时间分频＊(TMR3+1)
;  		= ((1/4MHz)*4)*2*3ffH
;  		= 2.048ms
;
; Duty3	= (1/H_IRC)*指令分频*时间分频＊PWM3DUTY
;      	= (1/4)*4*2*(20H+1)
;      	= 66us
;
		MOVIA		00000000
		SFUN		T3CR1			;; Disale Timer3
		
		MOVIA		0xEE
		MOVAR		INTE2			;; Clr Timer3 Flag

		MOVR		TM3RH, A	
		ANDIA		B'11001111'
		IORIA		B'00110000'
		MOVAR		TM3RH			;; Set Timer3 Data Bit[9:8]=11

		MOVIA		0xFF
		SFUN		TMR3


		
		MOVIA		0x00
		SFUN		T3CR2			;; P3SEl(B2:B0), PS3EN(B3):0(EN)/1(Dis), T3CE(B4):0:Low->Hi/1:hi->Low, T3CS(B5):0:Instruction CLK/1:Ext CLK

		BCR		TM3RH, PWM3D8_B
		BCR		TM3RH, PWM3D9_B
		MOVIA		0x20
		SFUN		PWM3DUTY

		
		MOVIA		0x83			;; TIMER3(B0):1:EN/0:Dis, AUTO ReLoad(B1):1:En/0:Dis, PWM3oEN(B7):1:PA2 is PWM2 / 0:PA2 is GPIO
		SFUN		T3CR1


;====================================================================
; Project Name: ADC 初始化
; Madify Data: 2016.02.20
F_ADC_Set:
		MOVIA		0x00			;; Set PA0/PA1/PA3 is ADC or Digital Pin
		MOVAR		PACON

		BCR		ADMD, CHS0_B		;; 设定ADC通道
		BCR		ADMD, CHS1_B		;; 000:PA0 / 001:PA1 / 010:PA2 / 011:PA3 / 100:PA4 / 101:1/4VDD
		BCR		ADMD, CHS2_B
		
		BSR		ADMD, GCHS_B		;; Enable ADC Input channel
		
		BCR		ADR, ADCK0_B		;; Set ADC Clock
		BCR		ADR, ADCK1_B		;; <00:Fcpu/16> / <01:Fcpu/8>  / <10:Fcpu/1> / <11:Fcpu/2>

		BSR		ADR, ADIE_B		;; 0:Dis ADC Int / 1:En ADC Int

		BSR		ADCR, ADCR0_B		;; Select ADC Resolation
		BSR		ADCR, ADCR1_B		;; 00:8-Bit / 01:10-Bit / 1x:12-Bit
		
		BSR		ADCR, SHCK0_B		;; Select ADC Sampling Pulse 
		BSR		ADCR, SHCK1_B		;; 00:1 ADC CLK / 01:2 ADC CLK / 10:4 ADC CLK / 11:8 ADC CLK

		BCR		ADVREFH, EVHENB_B	;; 0:Internal LDO / 1:External LDO(PA0)
		BSR		ADVREFH, VHS0_B		;; Set Reference voltage 
		BCR		ADVREFH, VHS1_B		;; 00:2V / 01:3V / 10:4V / 11:VDD	

		BSR		ADMD, ADEN_B		;; Enable ADC	

		RET

		end
;Program END


