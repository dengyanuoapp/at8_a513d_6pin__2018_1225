﻿; =========================================================================
; Created by ATW.
; User: VincentLin
; Date: 2016/02/25
; Time: 13:44
; 说明：PA0为电压V+输入端，PA1为电压V-输入端。
;		PB3为比较器直接输出。
;		PB2为读取CMPOUT状态输出。
;		PB1为侦测到中断标志会改变后输出。
;   PS：此功能需要在访真器上安装ADC/COMP板才能模拟。
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
	R_LVD_Temp	EQU		0x27
	R_Temp		EQU		0x28
		
		

;; Chip Reset Vector
; ===============================================================
		ORG	0x00
Reset:
		GOTO		Main_Prog

;; ISR Vector
		ORG	0x08
ISR_Prog:
		MOVAR		R_ACC_Buf		;; 保留 ACC 及 Status 的状态值
		SWAPR		R_ACC_Buf, R
		SWAPR		STATUS, A
		MOVAR		R_Status_Buf
	
	ISR_Prog100:
		BTRSS		INTF, T0IF_B
		GOTO		ISR_Prog900
		MOVIA		0xFE
		MOVAR		INTF			;; CLR TIMER0 FLAG
		MOVIA		0x01
		XORAR		PB, R
		BSR		R_Flag, f_1ms 

	ISR_Prog900:
		SFUNR		OSCCR
		ANDIA		00100000B
		BTRSC		Status, Z_B		;; 检查比较器是否中断产生，有，跳跃
		GOTO		ISR_End
		SFUNR		OSCCR			;; 清除比较器中断标志位
		ANDIA		11011111B
		SFUN		OSCCR
		MOVIA		0x02
		XORAR		PB, R


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
		
		MOVIA		0x01			;; ENABLE T0 Interrupt
		MOVAR		INTE
		
		ENI					;; Enable Goble Interrupt

Main_Start:
		CLRWDT
		
		SFUNR		OSCCR
		MOVAR		R_Temp
		BTRSS		R_Temp, CMPOUT_B
		GOTO		Main_Start100
		BSR		PB, PB2_B
		GOTO		Main_Start
	Main_Start100:
		BCR		PB, PB2_B
		GOTO		Main_Start		
		

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
		MOVIA		0xff
		MOVAR		PB			;; 初始值
		MOVIA		0x00
		IOST		PB			;; 设定为IO状态	0=Output,  1=Input
		
		MOVIA		0xff
		IOST		PA			;; 设定 PA 为输入状态
		
		MOVIA		0x00
		MOVAR		BPHCON			;; Set PB have Pull-hi
		
		MOVIA		0x88			;; 设定为 WDT(B7)=1:EN/0:DIS, PB0(B6)=1:INT/0:GPIO, LVR(B3)=1:EN/0:DIS
		MOVAR		PCON
		
		MOVIA		0x08
		MOVAR		BWUCON			;; 设定 PB3 Wackup 
		

;====================================================================
; Project Name: Time0 初始化
; Madify Data: 2014.12.11
F_Timer0Set:
		MOVIA		0xFE
		MOVIA		INTF			;; Clr Timer0 Flag
		MOVIA		0x00
		T0MD	
		MOVIA		0x00
		MOVAR		TMR0


;====================================================================
; Project Name: P2P Comparator 初始化
; Madify Data: 2016.02.25
F_P2PSet:
	;; Bit[3:0]:VS 此模式下无用
	;; Bit[7:4]:PS 设定P2P Mode的输入V+/V- 
		MOVIA		00000000b		;; P2P Mode ，V+->PA0 / V-->PA1
		IOST		CMPCR
		
		BSR		ANAEN, CMPEN_B		;; 使能电压比较电路
	
		SFUNR		OSCCR
		ANDIA		11011111b
		SFUN		OSCCR			;; 清除电压比较器中断标志位
	
		SFUNR		OSCCR
;		MOVAR		R_Temp
;		MOVIA		01000000b
;		IORAR		R_Temp, w
		IORIA		01010000b
		SFUN		OSCCR			;; 设定PB3为比较器输出，使能比较器中断。
				
		RET

		end
;Program END	
