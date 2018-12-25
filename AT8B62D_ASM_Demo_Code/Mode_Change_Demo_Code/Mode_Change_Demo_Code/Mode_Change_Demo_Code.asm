                                                           ; =========================================================================
; Created by ATW IDE.
; User: VincentLin
; Date: 2015/7/17
; Time: 13:40
; 说明：此Demo Code 共呈现4种工作模式（Normal/Slow/standby/sleep)
; 	┌->	开机时为Normal Mode(4M/2T)，PB0(1.024ms)转态输出约4s后进入Slow Mode。
;	│	Slow Mode为32K/2T，PB0(32ms)转态输出3.2s后进入 Standby Mode。
;	│	Standby Mode下约4S后唤醒(WDT唤醒），进入Normal Mode。
;	│	Normal Mode下，PB0(1.024ms)转态输出约4s后进入Sleep Mode。
;	└<-	Sleep Mode下，IOB3电位有变化唤醒，进入 Normal Mode。
; =========================================================================
	#include	AT8B62D.h

		
;; User Register Define (0x20~0x7F)
	R_ACC_Buf	EQU		0x20
	R_Status_Buf	EQU		0x21
	R_flag		EQU		0x22
		f_1ms		= 0
		f_Sleep		= 1
		f_TimeOut	= 2
	R_100ms_Reg	EQU		0x23
	R_1S_Reg	EQU		0x24
	R_CountTemp1	EQU		0x25
	R_CountTemp2	EQU		0x26
	R_OSCCRTEMP	EQU		0x27


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
		BTRSS		INTF, WDTIF_B
		GOTO		ISR_Prog200
		MOVIA		0xBF				;; Clear WDT INT Flag
		MOVAR		INTF
		MOVIA		0x02
		XORAR		PB, R
	
	ISR_Prog200:
		BTRSS		INTF, T0IF_B
		GOTO		ISR_End
		MOVIA		0xFE
		MOVAR		INTF				;; CLR TIMER0 FLAG
		MOVIA		0x01
		XORAR		PB, R
		BSR		R_Flag, f_1ms

	ISR_End:
		SWAPR		R_Status_Buf, A			;; 取回 ACC	及 Status 的状态值
		MOVAR		STATUS
		SWAPR		R_ACC_Buf, A
		RETIE
		
		

;; Main Program
Main_Prog:
		LCALL		F_ClearAllRAM
		LCALL		F_IOInit
		
		MOVIA		0x01				;; ENABLE T0 Interrupt
		MOVAR		INTE
		
		ENI						;; Enable Goble Interrupt

Main_Start:
		BCR		R_Flag, f_TimeOut
		LCALL		F_NormalMode_Set		;; 切换到4M/2T模式，并且设定Timer0=1.024ms
	Normal_Test:
		CLRWDT
		LCALL		F_Time_Count
		BTRSS		R_Flag, f_TimeOut
		GOTO		Normal_Test
		
		BCR		R_Flag, f_TimeOut
		LCALL		F_SlowMode_Set			;; 切换到32K/2T模式，并且设定Timer0=32ms
	SlowMode_Test:
		CLRWDT
		LCALL		F_Time_Count
		BTRSS		R_Flag, f_TimeOut
		GOTO		SlowMode_Test

		BCR		R_Flag, f_TimeOut
		
	StandbyMode_Test:
		LCALL		F_WDT_4s			;; if WDT is Int (2S)
;into standby Mode (Wait 4S)
		MOVIA		0x0A				;; 切换到StandBy Mode (L_IRC=32KHz/4T) & Disable H_IRC OSC
		SFUN		OSCCR
		;SFUNR		OSCCR
		;MOVAR		R_OSCCRTEMP
		;BSR		R_OSCCRTEMP, 3
		;BCR		R_OSCCRTEMP, 2
		;BSR		R_OSCCRTEMP, 1
		;BCR		R_OSCCRTEMP, 0
		;MOVR		R_OSCCRTEMP, A
		;SFUN		OSCCR
		
		NOP
		NOP
;into Normal Mode(1S)
		BCR		R_Flag, f_TimeOut
		LCALL		F_NormalMode_Set		;; 切换到4M/2T模式，并且设定Timer0=1.024ms		
	Normal_Test1:
		CLRWDT
		LCALL		F_Time_Count
		BTRSS		R_Flag, f_TimeOut
		GOTO		Normal_Test1

;; into Sleep Mode (Wait 4S)
		BCR		R_Flag, f_TimeOut
		LCALL		F_SleepMode

		GOTO		Main_Start




F_Time_Count:
		BTRSS		R_Flag, f_1ms
		RET
		
		BCR		R_Flag, f_1ms
		
		incr		R_100ms_Reg, R
		MOVR		R_CountTemp1, W
		SUBAR		R_100ms_Reg, W
		BTRSS		Status, C_B
		RET
		CLRR		R_100ms_Reg
		INCR		R_1S_Reg, R
		MOVR		R_CountTemp2, W
		SUBAR		R_1S_Reg, W
		BTRSS		Status, C_B
		RET
		CLRR		R_100ms_Reg
		CLRR		R_1S_Reg
		BSR		R_Flag, f_TimeOut
		RET
		


F_SleepMode:
		MOVIA		0x08
		MOVAR		BWUCON					;; PB3 is Wackup pin

		DISI							;; DIsable Int
		
		MOVIA		0x00
		MOVAR		PCON					;; disable wdt & LVDT
		MOVIA		0x02
		MOVAR		INTE
	 	MOVIA		0x00
	 	MOVAR		INTF
		MOVR		PB, R

	;; into Sleep Status
		NOP
		NOP
		SLEEP							;; into sleep mode
		NOP
		NOP
		MOVIA		0x88
		MOVAR		PCON
	F_SleepMode900:
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
		MOVIA		0xff
		MOVAR		PB				;; 初始值
		MOVAR		PA
		MOVIA		0x08
		IOST		PB				;; 设定为IO状态	0=Output,  1=Input
		MOVIA		0xff				;; 设定PA状态  0=Output, 1=Input
		IOST		PA

		MOVIA		0x00
		MOVAR		BPHCON				;; Set PB have Pull-hi
		IOST		APHCON				;; Set PA have hull-hi, but PA5 is Pull-Low		
		
		MOVIA		0x88				;; 设定为 WDT(B7)=1:EN/0:DIS, PB0(B6)=1:INT/0:GPIO, LVR(B3)=1:EN/0:DIS
		MOVAR		PCON

		RET
		

;====================================================================
; Project Name: Normal Mode 初始化 
; Madify Data: 2014.12.11
F_NormalMode_Set:
;; into High Frequency Mode
		SFUNR		OSCCR			;; 读取目前震荡模式 
		
		ANDIA		0xFD			;; 开启 Normal Mode 高速频率电路
		SFUN		OSCCR
		
		IORIA		0x01			;; Fosc切换到高速频率(H_IRC=4MHz)
		SFUN		OSCCR
		
		DISI
		
		MOVIA		0x00
		MOVAR		TMR0
		MOVIA		0xBF
		MOVIA		INTF			;; Clr Timer0 Flag

		MOVIA		0x02			;; Set Timer0 Prescale=1:8 (1.024ms)
		T0MD

		MOVIA		0x01			;; Timer0 Enable
		MOVAR		INTE

		MOVIA		100			;; 时间计算(1.024ms*100*40=4.096S)
		MOVAR		R_CountTemp1
		MOVIA		40
		MOVAR		R_CountTemp2
		
		ENI
		
		RET

;====================================================================
; Project Name: Slow Mode 初始化 
; Madify Data: 2014.12.11
F_SlowMode_Set:
;; into Slow Frequency Mode & Disable High Frequency
		SFUNR		OSCCR			;; 读取目前震荡模式
		
		ANDIA		0xfe			;; 切换到低速频率(L_IRC=32KHz)
		SFUN		OSCCR
		
		IORIA		0x02			;; 关闭高频震荡
		SFUN		OSCCR
		
		DISI
		
		MOVIA		0x00
		MOVAR		TMR0
		MOVIA		0xBF
		MOVIA		INTF			;; Clr Timer0 Flag

		MOVIA		0x00			;; Set Timer0 Prescale=1:2 (32ms)
		T0MD

		MOVIA		0x01			;; Timer0 Enable
		MOVAR		INTE

		MOVIA		10			;; 时间计算(32ms*10*10=3.2S)
		MOVAR		R_CountTemp1
		MOVIA		10			;; 320ms*0=3.2s
		MOVAR		R_CountTemp2
		
		ENI
		
		RET


;====================================================================
; Project Name: WDT 初始化 
; Madify Data: 2014.12.11
F_WDT_4S:
		MOVIA		0x00		;; 关闭 WDT & lvdt 
		MOVAR		PCON
		CLRWDT				;; clar WDT
		MOVIA		0x0B		;; Set WDT Prescaler(1:16) (WDT=250ms*16=4S)
		T0MD
		MOVIA		0x80		;; Enable WDT，关闭lvdt
		MOVAR		PCON
	 	MOVIA		0x00		;; clear all int_flag
	 	MOVAR		INTF
		MOVIA		0x40		;; Enable WDT Int & Disable TM0 Int 
		MOVAR		INTE

	 	RET

		end
;Program END	

	

	
