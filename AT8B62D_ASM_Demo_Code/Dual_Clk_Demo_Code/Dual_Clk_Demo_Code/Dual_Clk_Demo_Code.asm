; =========================================================================
; Created by ATW.
; User: VincentLin
; Date: 2014/12/13
; Time: 17:11
; 说明：Timer0 CLK= I_LRC，溢出时 PB0 反态。 / Timer1 CLK= Instruction CLK(I_LRC or I_HRC)，溢出时 PB2 反态。
; =========================================================================
	#include	AT8B62D.h
		
;; User Register Define (0x20~0x7F)
	R_ACC_Buf	EQU		0x20
	R_Status_Buf	EQU		0x21

	
	R_temp0		EQU		0x22
	R_temp1		EQU		0x23


		
		

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

		BTRSS		INTF, T1IF_B
		GOTO		ISR_Prog100
		MOVIA		0xF7
		MOVAR		INTF				;; CLR TIMER1 FLAG
		MOVIA		0x04
		XORAR		PB, R
	
	ISR_Prog100:
		BTRSS		INTF, T0IF_B
		GOTO		ISR_End
		MOVIA		0xFE
		MOVAR		INTF				;; CLR TIMER0 FLAG
		MOVIA		0x01
		XORAR		PB, R
		
	ISR_End:
		SWAPR		R_Status_Buf, A			;; 取回 ACC	及 Status 的状态值
		MOVAR		STATUS
		SWAPR		R_ACC_Buf, A
		RETIE
		
		

;; Main Program
;		ORG	0x10
Main_Prog:
		LCALL		F_ClearAllRAM
		LCALL		F_IOInit

		movia		0x00
		movar		intf
		
		MOVIA		0x09			;; ENABLE T0/T1 Interrupt
		MOVAR		INTE
		
		ENI					;; Enable Goble Interrupt

Main_Start:
		CLRWDT
		
		SFUNR		OSCCR			;; 读取目前震荡模式
		
		ANDIA		0xfe			;; 切换到低速频率(L_IRC=32KHz)
		SFUN		OSCCR
		
		IORIA		0x02			;; 关闭高频震荡
		SFUN		OSCCR


		movia		0x20
		movar		R_temp1
main_90:
		movia		0xff
		movar		R_temp0
main_100:
		CLRWDT
		decrsz		R_temp0, R
		goto		main_100
		decrsz		R_Temp1, R
		goto		main_90
		
		SFUNR		OSCCR			;; 读取目前震荡模式 
		
		ANDIA		0xFD			;; 开启 Normal Mode 高速频率电路
		SFUN		OSCCR
		
		IORIA		0x01			;; Fosc切换到高速频率(H_IRC=4MHz)
		SFUN		OSCCR


		movia		0xff
		movar		R_temp1
main_110:
		movia		0xff
		movar		R_temp0
main_120:
		CLRWDT
		decrsz		R_temp0, R
		goto		main_120
		decrsz		R_Temp1, R
		goto		main_110
		
		GOTO		Main_Start

;==================================================================
; Project Name:	清零全部RAM
; Last Modify Date:2010-11-9 16:12
;
;;;Clear	RAM 0x20~0x7f
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
		MOVAR		PB				;; 初始值
		MOVIA		0x30
		IOST		PB				;; 设定为IO状态	0=Output,  1=Input
		
		MOVIA		0x80				;; 设定为 WDT(B7)=1:EN/0:DIS, PB0(B6)=1:INT/0:GPIO, LVR(B3)=1:EN/0:DIS
		MOVAR		PCON

;====================================================================
; Project Name: Time0 初始化
; Madify Data: 2014.12.11
; T=（1/I_LRC)*分频*TMR0
;  = (1/32KHz)*4*256
;  = 32ms
F_Timer0Set:
		MOVIA		0xFE
		MOVIA		INTF				;; Clr Timer0 Flag
		MOVIA		0xA1				;; Timer0 clk= I_LRC , 分频：4分频
		T0MD	
		MOVIA		0x00
		MOVAR		TMR0

;====================================================================
; Project Name: Time1 初始化
; Madify Data: 2014.12.11
; T=（1/intruction clk)*分频*TMR1
;  = ((1/4MHz)*4)*2*256
;  = 512us
		MOVIA		00000000
		SFUN		T1CR1				;; Disale Timer1
		MOVIA		0xF7
		MOVIA		INTF				;; Clr Timer1 Flag
		MOVIA		0xff
		SFUN		TMR1
	;	MOVIA		0x00
	;	SFUN		PWM1DUTY
		MOVIA		0x00
		SFUN		T1CR2				;; P1SEl(B2:B0), PS1EN(B3):0(EN)/1(Dis), T1CE(B4):0:Low->Hi/1:hi->Low, T1CS(B5):0:Instruction CLK/1:Ext CLK
	;	MOVIA		0X0f
	;	SFUN		BZ1CR
		MOVIA		0x03				;; TIMER1(B0):1:EN/0:Dis, AUTO ReLoad(B1):1:En/0:Dis, PWM1oEN(B7):1:P2 is PWMO/0:P2 is GPIO
		SFUN		T1CR1
		RET

		end
;Program END


	

	
