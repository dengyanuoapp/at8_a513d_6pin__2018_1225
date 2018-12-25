﻿; =========================================================================
; Created by ATW.
; User: VincentLin
; Date: 2014/12/15
; Time: 13:44
; 说明：PB3为按键输入。开机时为Normal Mode，按下按键后，进入Sleep Mode。在由按下按键唤醒进入Normal Mode。
; =========================================================================
	#include	AT8B62D.h
	
;; User Register Define (0x20~0x7F)
	R_ACC_Buf	EQU		0x20
	R_Status_Buf	EQU		0x21
	R_flag		EQU		0x22
		f_1ms		= 0
		f_Sleep		= 1
		f_Key		= 2
	R_KeyCount	EQU		0x23
	R_KeyTemp	EQU		0x24
	R_KeyData	EQU		0x25
	R_KeyOldData	EQU		0x26
	R_Mode		EQU		0x27
		
		

;; Chip Reset Vector
; ===============================================================
		ORG	0x00
Reset:
		GOTO	Main_Prog

;; ISR Vector
		ORG	0x08
ISR_Prog:
		MOVAR		R_ACC_Buf		;; 保留 ACC 及 Status 的状态值
		SWAPR		R_ACC_Buf, R
		SWAPR		STATUS, A
		MOVAR		R_Status_Buf
	
	ISR_Prog100:
		BTRSS		INTF, T0IF_B
		GOTO		ISR_End
		MOVIA		0xFE
		MOVAR		INTF			;; CLR TIMER0 FLAG
		MOVIA		0x01
		XORAR		PB, R
		BSR		R_Flag, f_1ms

	ISR_End:
		SWAPR		R_Status_Buf, A		;; 取回 ACC	及 Status 的状态值
		MOVAR		STATUS
		SWAPR		R_ACC_Buf, A
		RETIE
		
		

;; Main Program
;		ORG	0x10
Main_Prog:
		LCALL		F_ClearAllRAM
		LCALL		F_IOInit
		
		CLRR		INTF
		MOVIA		0x01			;; ENABLE T0 Interrupt
		MOVAR		INTE
		
		ENI					;; Enable Goble Interrupt

Main_Start:
		CLRWDT
		LCALL		F_KeyDetect
		LCALL		F_KeyProcess
		LCALL		F_SleepMode
		GOTO		Main_Start



F_KeyProcess:
		BTRSS		R_Flag, f_key
		RET
		
		BCR		R_Flag, f_key
		
		MOVR		R_KeyOldData, A
		XORAR		R_KeyData, A
		BTRSC		Status, Z_B
		GOTO		F_KeyProcess_End
		MOVR		R_KeyData,A
		MOVAR		R_KeyOldData
		BTRSC		R_KeyData, PB3_B
		GOTO		F_KeyProcess_End
		INCR		R_Mode, R
		MOVIA		0x02
		SUBAR		R_Mode, A
		BTRSC		Status, C_B
		CLRR		R_Mode
	F_KeyProcess_End:
		RET


F_SleepMode:
		MOVR		R_Mode, A
		BTRSS		Status, Z_B
		RET
		
	F_SleepMode100:	
		CLRWDT
		BTRSS		PB, PB3_B
		LGOTO		F_SleepMode100

		BCR		PB, PB0_B		;; 设定PB0=Low
		DISI					;; Disable Goble Interrupt
		
		CLRWDT
		MOVIA		0x08
		MOVAR		BWUCON			;; 设定 PB3 唤醒
		MOVIA		0x00
		MOVAR		AWUCON

		MOVIA		0x00
		MOVAR		PCON
		MOVR		PB, R
		MOVIA		0x02
		MOVAR		INTE
		MOVIA		0x00
	 	MOVAR		INTF
	;; into Sleep Status
		NOP
		NOP
		SLEEP
		NOP
		NOP
		MOVIA		0x00
		MOVAR		INTF
		MOVIA		0x01
		MOVAR		INTE
		CLRWDT
		MOVIA		0x88
		MOVAR		PCON
		ENI						;; Enable Goble Interrupt
		MOVIA		0x01
		MOVAR		R_Mode
	F_SleepMode900:
		RET
		

		
		
		

F_KeyDetect:
		BTRSS		R_Flag, f_1ms
		RET
		
		BCR		R_Flag, f_1ms
		
		BCR		R_Flag, f_Sleep

		MOVIA		0x08
		ANDAR		PB, A
		MOVAR		R_KeyTemp
		XORAR		R_KeyData, A
		BTRSS		Status, Z_B
		GOTO		F_KeyDetect100
		
		INCR		R_KeyCount, R
		MOVIA		60
		SUBAR		R_Keycount, A
		BTRSS		Status, C_B
		GOTO		F_KeyDetect_End
		BSR		R_Flag, f_key
	F_KeyDetect100:
		CLRR		R_KeyCount
		MOVR		R_KeyTemp, A
		MOVAR		R_KeyData
	F_KeyDetect_End:
		RET
		
		
		
		

;==================================================================
; Project Name:	清零全部RAM
; Last Modify Date:2010-11-9 16:12
;
; Clear	RAM 0x20~0x7f
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
		MOVIA		0x00
		MOVAR		PB				;; 初始值
		MOVAR		PA
		MOVIA		0x08
		IOST		PB				;; 设定为IO状态	0=Output,  1=Input
		MOVIA		0x00				;; 设定PA状态  0=Output, 1=Input
		IOST		PA

		MOVIA		0x00
		MOVAR		BPHCON				;; Set PB have Pull-hi
		IOST		APHCON				;; Set PA have hull-hi, but PA5 is Pull-Low		
		
		MOVIA		0x88				;; 设定为 WDT(B7)=1:EN/0:DIS, PB0(B6)=1:INT/0:GPIO, LVR(B3)=1:EN/0:DIS
		MOVAR		PCON

;====================================================================
; Project Name: Time0 初始化
; Madify Data: 2014.12.11
F_Timer0Set:
		MOVIA		0xFE
		MOVIA		INTF				;; Clr Timer0 Flag
		MOVIA		0x00
		T0MD	
		MOVIA		0x00
		MOVAR		TMR0

		RET

		end
;Program END	