; =========================================================================
; Created by ATW.
; User: VincentLin
; Date: 2014/12/15
; Time: 13:44
; 说明：PB3为按键输入。开机时为Normal Mode，按下按键后，进入Sleep Mode。在由按下按键唤醒进入Normal Mode。
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
	R_KeyCount		EQU		0x13
	R_KeyTemp		EQU		0x14
	R_KeyData		EQU		0x15
	R_KeyOldData	EQU		0x16
	R_Mode			EQU		0x17
		
		

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
		LCALL		F_KeyDetect
		LCALL		F_KeyProcess
		LCALL		F_SleepMode
		GOTO		Main_Start



F_KeyProcess:
		BTRSS		R_Flag, f_key
		RET
		
		BCR			R_Flag, f_key
		
		MOVR		R_KeyOldData, A
		XORAR		R_KeyData, A
		BTRSC		Status, Z
		GOTO		F_KeyProcess_End
		MOVR		R_KeyData,A
		MOVAR		R_KeyOldData
		BTRSC		R_KeyData, PB3
		GOTO		F_KeyProcess_End
		INCR		R_Mode, R
		MOVIA		0x02
		SUBAR		R_Mode, A
		BTRSC		Status, C
		CLRR		R_Mode
	F_KeyProcess_End:
		RET


F_SleepMode:
		MOVR		R_Mode, A
		BTRSS		Status, Z
		RET
		
	F_SleepMode100:	
		CLRWDT
		BTRSS		R_KeyData, PB3
		RET

		BCR			PB, PB0		;; 设定PB0=Low
		DISI					;; Disable Goble Interrupt
		
		CLRWDT
		MOVIA		0x00
		MOVAR		PCON
		MOVIA		0x02
		MOVAR		INTE
	 	MOVIA		0x00
	 	MOVAR		INTF
	;;	CLRR		INTIF
		MOVR		PB, R
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
		
		BCR			R_Flag, f_1ms
		
		BCR			R_Flag, f_Sleep

		MOVIA		0x08
		ANDAR		PB, A
		MOVAR		R_KeyTemp
		XORAR		R_KeyData, A
		BTRSS		Status, Z
		GOTO		F_KeyDetect100
		
		INCR		R_KeyCount, R
		MOVIA		60
		SUBAR		R_Keycount, A
		BTRSS		Status, C
		GOTO		F_KeyDetect_End
		BSR			R_Flag, f_key
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

		RET

		end
;Program END	
