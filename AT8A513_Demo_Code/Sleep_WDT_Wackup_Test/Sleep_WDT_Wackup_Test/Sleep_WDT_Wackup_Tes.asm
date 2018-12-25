; =========================================================================
; Created by ATW IDE.
; User: VincentLin
; Date: 2015/7/16
; Time: 14:24
; 说明：开机时为Normal Mode，PB0 1.024ms转态输出1s后进入Sleep Mode。
;		如果wdt配置选用Reset模式，则要选用 F_WDT_ResetSet 此流程。 WDT在2s后溢出，进行复位。
;		如果wdt配置选用Int模式，则要选用 F_WDT_IntSet 此流程。 WDT在4s后中断唤醒，PB1转态输出并回到Normal Mode。
; =========================================================================
; Chip Register Define
;; Register R
		INDF		EQU		0x00
		TMR0		EQU		0x01
		PCL			EQU		0x02
		
		STATUS		EQU		0x03
			C		EQU		0
			DC		EQU		1
			Z		EQU		2
;			PD		EQU		3
;			TO		EQU		4
			
		FSR			EQU		0x04
		
		PA			EQU		0x05
		
		PB			EQU		0x06
			PB0		EQU		0
			PB1		EQU		1
			PB2		EQU		2
			PB3		EQU		3
			PB4		EQU		4
			PB5		EQU		5
			
		PCON		EQU		0x08
		BWUCON		EQU		0x09
		PCHBUF		EQU		0x0A
		ABPLCON		EQU		0x0B
		BPHCON		EQU		0x0C
		
		INTE		EQU		0x0E
			T0IE	EQU		0
			PBIE	EQU		1
			INTIE	EQU		2
			T1IE	EQU		3
			WDTIE	EQU		6
			
		INTF		EQU		0x0f
			T0IF	EQU		0
			PBIF	EQU		1
			INTIF	EQU		2
			T1IF	EQU		3
			WDTIF	EQU		6

;; Register F
		PS0CV		EQU		0x0a
		BOBCON		EQU		0x0c
		
		PCON1		EQU		0x0f
			T0EN	EQU		0
			GIE	EQU		7
		
;; Register S
		TMR1		EQU		0x00
		
		T1CR1		EQU		0x01
			T1EN	EQU		0
			T1RL	EQU		1
			T1OS	EQU		2
			
			PWM1OAL	EQU		6
			PWM1OEN	EQU		7
			
		T1CR2		EQU		0x02
			PS1EN	EQU		3
			T1CE	EQU		4
			T1CS	EQU		5
			
		PWM1DUTY	EQU		0x03
		PS1CV		EQU		0x04
		BZ1CR		EQU		0x05
		
		IRCR		EQU		0x06
			IREN		EQU	0
			IRF57K		EQU	1
			IRCSEL		EQU	2
			IROSC358M	EQU	7
			
		TBHP		EQU		0x07
		TBHD		EQU		0x08
		
		OSCCR		EQU		0x0f
			SELHSC	EQU		0
			STPHOSC	EQU		1
			OPMD0	EQU		2
			OPMD1	EQU		3

		f			EQU		1
		R			EQU		1
		W			EQU		0
		A			EQU		0
		
;; User Register Define (0x10~0x3F)
	R_ACC_Buf	EQU		0x10
	R_Status_Buf	EQU		0x11
	R_flag			EQU		0x12
		f_1ms			EQU		0
		f_Sleep			EQU		1
		f_Key			EQU		2
	R_100ms_Reg		EQU		0x13
	R_1S_Reg		EQU		0x14

		
		

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
		BTRSS		INTF, WDTIF
		GOTO		ISR_Prog200
		MOVIA		0xBF				;; Clear WDT INT Flag
		MOVAR		INTF
		MOVIA		0x02
		XORAR		PB, R
	
	ISR_Prog200:
		BTRSS		INTF, T0IF
		GOTO		ISR_End
;		BCR			INTF, T0IF		;; 不建议使用方式清除
		MOVIA		0xFE
		MOVAR		INTF			;; CLR TIMER0 FLAG
		MOVIA		0x01
		XORAR		PB, R
		BSR			R_Flag, f_1ms

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
		
		ENI							;; Enable Goble Interrupt

Main_Start:
		CLRWDT
		LCALL		F_1S_Count
		LCALL		F_SleepMode
		GOTO		Main_Start


F_1S_Count:
		BTRSS		R_Flag, f_1ms
		RET
		
		BCR			R_Flag, f_1ms
		
		incr		R_100ms_Reg, R
		MOVIA		100	;C_100ms
		SUBAR		R_100ms_Reg, W
		BTRSS		Status, C
		RET
		CLRR		R_100ms_Reg
		INCR		R_1S_Reg, R
		MOVIA		10	;C_1S
		SUBAR		R_1S_Reg, W
		BTRSS		Status, C
		RET
		CLRR		R_100ms_Reg
		CLRR		R_1S_Reg
		BSR			R_Flag, f_sleep
		RET
		


F_SleepMode:
		BTRSS		R_Flag, f_sleep
		RET
		
		BCR			R_Flag, f_sleep
		
;		LCALL		F_WDT_ResetSet		;; if WDT is Reset
		LCALL		F_WDT_IntSet		;; if WDT is Int
		MOVR		PB, R
	;; into Sleep Status
		NOP
		NOP
		SLEEP					;; into sleep mode
		NOP
		NOP
		LCALL		F_Timer0Set
		CLRWDT
		MOVIA		0x88
		MOVAR		PCON
	F_SleepMode900:
		RET


;==================================================================
; Project Name:	清零全部RAM
; Last Modify Date:2010-11-9 16:12
;
;;Clear	RAM 0x10~0x3f
F_ClearAllRAM:
		MOVIA		0x2f
		MOVAR		0x10
		MOVIA		0X11
		MOVAR		FSR
	L_Clear_Next_Byte:
		CLRR		INDF
		INCR		FSR, R
		DECRSZ		10H, R
		LGOTO		L_Clear_Next_Byte
		CLRR		FSR
		RET

;====================================================================
; Project Name: IO 初始化
; Madify Data: 2014.12.11
;
F_IOInit:
		MOVIA		0xff
		MOVAR		PB				;; 初始值
		MOVIA		0x08
		IOST		PB				;; 设定为IO状态	0=Output,  1=Input
		
		MOVIA		0x88			;; 设定为 WDT(B7)=1:EN/0:DIS, PB0(B6)=1:INT/0:GPIO, LVR(B3)=1:EN/0:DIS
		MOVAR		PCON
		
;		MOVIA		0x08
;		MOVAR		BWUCON			;; 设定 PB3 Wackup 
		

;====================================================================
; Project Name: Timer0 初始化 
; Madify Data: 2014.12.11
F_Timer0Set:
		MOVIA		0x00
		MOVAR		TMR0
		MOVIA		0xBF
		MOVIA		INTF			;; Clr Timer0 Flag

		MOVIA		0x01			;; Set Timer0 Prescale=1:4 (1.024ms)
		T0MD

		MOVIA		0x01			;; Timer0 Enable
		MOVAR		INTE

		RET

;====================================================================
; Project Name: WDT 初始化 
; Madify Data: 2014.12.11
F_WDT_ResetSet:
		DISI
		MOVIA		0x00		;; 关闭 WDT & lvdt
		MOVAR		PCON
		CLRWDT					;; clar WDT
		MOVIA		0x0B		;; Set WDT Prescaler(1:8) (WDT=250ms*4=2S)
		T0MD
		MOVIA		0x80		;; Enable WDT，关闭lvdt
		MOVAR		PCON

	 	RET

F_WDT_IntSet:
		MOVIA		0x00		;; 关闭 WDT & lvdt 
		MOVAR		PCON
		CLRWDT					;; clar WDT
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

	
