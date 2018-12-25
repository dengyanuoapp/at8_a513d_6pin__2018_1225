﻿; =========================================================================
; Created by ATW.
; User: VincentLin
; Date: 2016/02/24
; Time: 21:25
; 说明：设定PB0为1.024ms转态，PB1为IR 38KH载波输出。PB2 为PB1的状态表现.
;	if IRCSEL= 0, 则 PB2 为高电平时，PB1输出IR载波。PB2为低电平，PB1不输出IR载波。
;	if IRCSEL= 1, 则 PB2 为高电平时, PB1不输出IR载波。PB2 为低电平，PB1输出IR载波.
;       欲验证IR 38KHz 载波，需要烧录芯片测试。
; =========================================================================
	#include	AT8B62D.h

		
;; User Register Define (0x20~0x7F)
	R_ACC_Buf	EQU		0x20
	R_Status_Buf	EQU		0x21

	R_PB_Temp		EQU		0x22
	R_Temp			EQU		0x23
	R_Flag0			EQU		0x24
		f_timer0		EQU		0
		f_keyflag		EQU		1
	
		

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
		GOTO		ISR_End
		
		MOVIA		0xFE
		MOVAR		INTF				;; CLR TIMER0 FLAG
		
		MOVIA		0x01
		XORAR		R_PB_Temp, R
		MOVR		R_PB_Temp, A
		MOVAR		PB
		
		BSR		R_Flag0, f_timer0
		
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
		
		MOVIA		0x01				;; ENABLE T0 Interrupt
		MOVAR		INTE
		
		ENI						;; Enable Goble Interrupt

		BCR		R_PB_Temp, 1
		MOVR		R_PB_Temp, A
		MOVAR		PB				;; IR输出

		
	
Main_Start:
		CLRWDT
		BTRSS		R_Flag0, f_timer0
		GOTO		Main_Start
		
		BCR		R_Flag0, f_timer0
	
		MOVR		R_PB_Temp, A
		MOVAR		R_Temp
		
		BTRSS		R_Temp, 0
		GOTO		Main_Start100

		BCR		R_PB_Temp, 2
		BCR		R_PB_Temp, 1			; IR 输出
		MOVR		R_PB_Temp, A
		MOVAR		PB

		GOTO		Main_Start
		
	Main_Start100:
		BSR		R_PB_Temp, 2
		BSR		R_PB_Temp, 1			; IR 不输出
		MOVR		R_PB_Temp, A
		MOVAR		PB
		
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
		MOVAR		PB				;; 初始值
		MOVAR		R_PB_Temp
		
		MOVIA		0x00
		IOST		PB				;; 设定为IO状态	0=Output,  1=Input

		MOVIA		0x80				;; 设定为 WDT(B7)=1:EN/0:DIS, PB0(B6)=1:INT/0:GPIO, LVR(B3)=1:EN/0:DIS
		MOVAR		PCON

;====================================================================
; Project Name: Time0 初始化
; Madify Data: 2014.12.11
F_Timer0Set:
		MOVIA		0xFE
		MOVIA		INTF				;; Clr Timer0 Flag
		MOVIA		0x01
		T0MD	
		MOVIA		0x00
		MOVAR		TMR0

	
;====================================================================
; Project Name: Time1 初始化
; Madify Data: 2014.12.11
	;	MOVIA		00000000
	;	SFUN		T1CR1			;; Disale Timer1
	;	MOVIA		0xF7
	;	MOVIA		INTF			;; Clr Timer1 Flag
;		MOVIA		0x10
;		SFUN		TMR1
	;	MOVIA		0x00
	;	SFUN		T1CR2			;; P1SEl(B2:B0), PS1EN(B3):0(EN)/1(Dis), T1CE(B4):0:Low->Hi/1:hi->Low, T1CS(B5):0:Instruction CLK/1:Ext CLK
	;	MOVIA		0X86
	;	SFUN		BZ1CR
	;	MOVIA		0x83			;; TIMER1(B0):1:EN/0:Dis, AUTO ReLoad(B1):1:En/0:Dis, PWM1oEN(B7):1:P2 is PWMO/0:P2 is GPIO
	;	SFUN		T1CR1

;====================================================================
; Project Name: IR 功能初始化
; Madify Data: 
		MOVIA		0x05				;; IREN(B0):1:EN/0:DIS, IRF57K(B1):1:57K,0:38K, IRCSEL(B2):1:PB.1=Low输出/0:PB.1=Hi输出,
		SFUN		IRCR
		
		RET


		end
;Program END	
