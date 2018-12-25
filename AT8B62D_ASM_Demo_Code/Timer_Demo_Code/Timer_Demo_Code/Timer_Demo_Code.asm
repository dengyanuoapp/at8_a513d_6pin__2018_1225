; =========================================================================
; Created by ATW.
; User: VincentLin
; Date: 2017/02/16
; Time: 
; Chip: AT8B62D
; 说明：PB0:Timer0中断输出。PB1:Timer1中断输出。PB2:Timer2中断输出。PB3:Timer3中断输出。
; =========================================================================

	#include		AT8B62D.H	
		
;; User Register Define (0x20~0x7F)
	R_ACC_Buf	EQU		0x20
	R_Status_Buf	EQU		0x21

		
		

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

		BTRSS		INTF, T2IF_B
		GOTO		ISR_Prog100
;		BCR		INTF, T1IF		;; 不建议使用方式清除
		MOVIA		0xDF
		MOVAR		INTF			;; CLR TIMER2 FLAG
		MOVIA		0x04
		XORAR		PB, R

	ISR_Prog100:		
		BTRSS		INTF, T1IF_B
		GOTO		ISR_Prog200
;		BCR		INTF, T1IF		;; 不建议使用方式清除
		MOVIA		0xF7
		MOVAR		INTF			;; CLR TIMER1 FLAG
		MOVIA		0x02
		XORAR		PB, R
	
	ISR_Prog200:
		BTRSS		INTF, T0IF_B
		GOTO		ISR_Prog300
;		BCR		INTF, T0IF		;; 不建议使用方式清除
		MOVIA		0xFE
		MOVAR		INTF			;; CLR TIMER0 FLAG
		MOVIA		0x01
		XORAR		PB, R

	ISR_Prog300:
		BTRSS		INTE2, T3IF_B
		GOTO		ISR_End
;		BCR		INTE2, T3IF_B		;; 不建议使用方式清除
		MOVIA		0xEF
		MOVAR		INTE2			;; CLR TIMER3 FLAG
		MOVIA		0x08
		XORAR		PB, R		

	ISR_End:
		SWAPR		R_Status_Buf, A		;; 取回 ACC	及 Status 的状态值
		MOVAR		STATUS
		SWAPR		R_ACC_Buf, A
		RETIE
		
		

;; Main Program
;		ORG	0x10
Main_Prog:
		movia		0x00
		movar		pcon
		
		LCALL		F_ClearAllRAM
		LCALL		F_IOInit
		
		MOVIA		0x29			;; ENABLE T0/T1/T2 Interrupt
		MOVAR		INTE
		MOVIA		0x01
		MOVAR		INTE2			;; Enable T3 Interrupt
		
		ENI					;; Enable Goble Interrupt

Main_Start:
		CLRWDT
		GOTO		Main_Start

;==================================================================
; Project Name:	清零全部RAM
; Last Modify Date:2010-11-9 16:12
;
;;Clear	RAM 0x20~0x7f
F_ClearAllRAM:
	;Bank0	
		MOVIA		0x20			;; 切换到 RAM Bank0
		MOVAR		FSR
	L_Clear_Next_Byte_Bank0:
		CLRR		INDF			;; 清除该地址资料
		INCR		FSR, R			;; 累加间接地址
		BTRSS		FSR, 7
		GOTO		L_Clear_Next_Byte_Bank0		;; 否，跳跃
		
		RET


;====================================================================
; Project Name: IO 初始化
; Madify Data: 2014.12.11
;
F_IOInit:
		MOVIA		0xff
		MOVAR		PA
		MOVAR		PB				;; 初始值
		
		MOVIA		00000000
		IOST		PA
		IOST		PB				;; 设定为IO状态	0=Output,  1=Input
		
		MOVIA		0x80				;; 设定为 WDT(B7)=1:EN/0:DIS, LVDEN(B5)=1:EN/0:DIS, LVREN(B3)=1:EN/0:DIS
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
; Project Name: Time1 初始化
; Madify Data: 2014.12.11
; T=（1/intruction clk)*分频*(TMR[9:8]:TMR1[7:0]+1)
;  = ((1/4MHz)*4)*2*(1ffh+1)
;  = 1024us
		MOVIA		00000000
		SFUN		T1CR1			;; Disale Timer1
		
		MOVIA		0xF7
		MOVAR		INTF			;; Clr Timer1 Flag
		
		MOVIA		0x10			;; Timer1 Data Bit[9:8] = 1
		MOVAR		TMRH
		MOVIA		0xff			;; Timer1 Data Byte Data[7:0]
		SFUN		TMR1


		MOVIA		0x00
		SFUN		T1CR2			;; P1SEl(B2:B0), PS1EN(B3):0(EN)/1(Dis), T1CE(B4):0:Low->Hi/1:hi->Low, T1CS(B5):0:Instruction CLK/1:Ext CLK
;
		MOVIA		0x03			;; TIMER1(B0):1:EN/0:Dis, AUTO ReLoad(B1):1:En/0:Dis, PWM1OAL(b6):1:PWM1 Out Low / 0: PWM1 Our Hi, PWM1oEN(B7):1:P3 is PWM1 Out / 0:P3 is GPIO
		SFUN		T1CR1

;====================================================================
; Project Name: Time2 初始化
; Madify Data: 2016.02.20
; T=（1/intruction clk)*分频*TMR2
;  = ((1/4MHz)*4)*2*(07FH+1)
;  = 258us
		MOVIA		00000000
		SFUN		T2CR1			;; Disale Timer2
		
		MOVIA		0xDF
		MOVAR		INTF			;; Clr Timer2 Flag
		

		MOVIA		0x00			;; Timer2 Data Bit[9:8] = 0
		MOVAR		TMRH
		MOVIA		0x7F			;; Timer2 Data Byte Data[7:0]
		SFUN		TMR2

		
;		MOVIA		0x00
;		SFUN		PWM2DUTY
		MOVIA		0x00
		SFUN		T2CR2			;; P2SEl(B2:B0), PS2EN(B3):0(EN)/1(Dis), T2CE(B4):0:Low->Hi/1:hi->Low, T2CS(B5):0:Instruction CLK/1:Ext CLK
;		MOVIA		0x00
;		SFUN		BZ2CR
		MOVIA		0x03			;; T2EN(B0):1:EN Timer2/0:Dis, T2RL(B1):1:En Auto Load/0:Dis, T2OS(B2):1:One-Shot/0:No_Stop, PWM2OAL(B6):1:PWM2 active Low/0:High, PWM2oEN(B7):1:PB2 is PWM2 / 0:PB2 is GPIO
		SFUN		T2CR1

;====================================================================
; Project Name: Time3 初始化
; Madify Data: 2016.02.20
; T=（1/intruction clk)*分频*(TMR3+1)
;  = ((1/4MHz)*4)*2*(27FH+1)
;  = 1280us
		MOVIA		00000000
		SFUN		T3CR1			;; Disale Timer3
		
		MOVIA		0xEE
		MOVAR		INTE2			;; Clr Timer3 Flag
		
		MOVIA		0x20			;; Timer3 Data Bit[9:8] = 2
		MOVAR		TM3RH
		MOVIA		0x7F			;; Timer3 Data Byte Data[7:0]
		SFUN		TMR3
	
		MOVIA		0x00
		SFUN		T3CR2			;; P3SEl(B2:B0), PS3EN(B3):0(EN)/1(Dis), T3CE(B4):0:Low->Hi/1:hi->Low, T3CS(B5):0:Instruction CLK/1:Ext CLK
;		MOVIA		0x00
;		SFUN		BZ3CR
		MOVIA		0x03			;; TIMER3(B0):1:EN/0:Dis, AUTO ReLoad(B1):1:En/0:Dis, PWM3oEN(B7):1:PA2 is PWM2 / 0:PA2 is GPIO
		SFUN		T3CR1

		RET
		
		end
;Program END



	
