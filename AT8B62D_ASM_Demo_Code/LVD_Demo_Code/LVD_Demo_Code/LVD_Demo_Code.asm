; =========================================================================
; Created by ATW.
; User: VincentLin
; Date: 2016/02/27
; Time: 13:44
; 说明：PA1~PA3为LVD设定参考输入。
;	若vdd电压低于设定参考电压，则PB1输出Low。反之为Hi
;	PB3为 LVDT 中断标志位产生后转态输出。
;   PS：此功能无法在访真器上模拟。
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
		GOTO		ISR_Program900

		MOVIA		0xFE
		MOVAR		INTF			;; CLR TIMER0 FLAG
		MOVIA		0x01
		XORAR		PB, R
		BSR		R_Flag, f_1ms

	ISR_Program900:
		BTRSS		INTF, LVDTIF_B
		GOTO		ISR_End
		MOVIA		0xEF			;; CLR LVDT Flag
		MOVAR		INTF
		MOVIA		0x08
		XORAR		PB, R

	ISR_End:
		SWAPR		R_Status_Buf, A		;; 取回 ACC	及 Status 的状态值
		MOVAR		STATUS
		SWAPR		R_ACC_Buf, A
		RETIE
		
		

;; Main Program
Main_Prog:
		LCALL		F_ClearAllRAM
		LCALL		F_IOInit
		
		MOVIA		0x00
		MOVAR		INTF			;; 清除所有中断标志位
		MOVIA		0x11			;; ENABLE T0/LVDT Interrupt
		MOVAR		INTE
		
		ENI							;; Enable Goble Interrupt
		
		BSR		PCON, LVDEN_B	;; Enable LVD Function

Main_Start:
		CLRWDT
		LCALL		F_KeyDetect
		LCALL		F_KeyProcess

		IOSTR		PCON1
		MOVAR		R_Temp
		BTRSS		R_Temp, LVDOUT_B
		GOTO		Main_Start100
		BSR		PB, PB1_B			;; VDD > LVD
		GOTO		Main_Start
	Main_Start100:
		BCR		PB, PB1_B			;; VDD < LVD
		GOTO		Main_Start



F_KeyProcess:
		BTRSS		R_Flag, f_key
		RET
		
		BCR		R_Flag, f_key
		CALL		F_Get_LVD
		MOVAR		R_LVD_Temp
		IOSTR		PCON1
		ANDIA		11100011B
		IORAR		R_LVD_Temp, A
		IOST		PCON1
		RET
	
F_Get_LVD:
		MOVR		R_KeyData, A
		MOVAR		R_LVD_Temp
		RRR		R_LVD_Temp, R
		MOVIA		0x07
		ANDAR		R_LVD_Temp, A
		ADDAR		PCL, R
		RETIA		00000000b			;; 2.0V
		RETIA		00000100b			;; 2.2V
		RETIA		00001000b			;; 2.4V
		RETIA		00001100b			;; 2.7V
		RETIA		00010000b			;; 3.0V
		RETIA		00010100b			;; 3.3V
		RETIA		00011000b			;; 3.6V
		RETIA		00011100b			;; 4.3V	
		

F_KeyDetect:
		BTRSS		R_Flag, f_1ms
		RET
		
		BCR		R_Flag, f_1ms
		
		BCR		R_Flag, f_Sleep

		MOVIA		0x0E
		ANDAR		PA, A
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
		MOVAR		PA				;; 初始值
		MOVAR		PB
		
		MOVIA		0xff
		IOST		PA
		MOVIA		0x00
		IOST		PB				;; 设定为IO状态	0=Output,  1=Input
		
		MOVIA		0x00
		IOST		APHCON				;; Set PA have Pull-hi
		
		MOVIA		0x88				;; 设定为 WDT(B7)=1:EN/0:DIS, PB0(B6)=1:INT/0:GPIO, LVR(B3)=1:EN/0:DIS
		MOVAR		PCON
		
		MOVIA		0x08
		MOVAR		BWUCON				;; 设定 PB3 Wackup 
		

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
