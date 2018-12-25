; =========================================================================
; Created by ATW.
; User: VincentLin
; Date: 2014/12/14
; Time: 21:25
; 说明：设定PB1为IR大电流Sink动作。PB3为按键侦测。共有PB1输出高低两种模式。
; =========================================================================
; Chip Register Define
;; Register R
		INDF		EQU		0x00
		TMR0		EQU		0x01
		PCL		EQU		0x02
		
		STATUS		EQU		0x03
			C		EQU		0
			DC		EQU		1
			Z		EQU		2
;			PD		EQU		3
;			TO		EQU		4
			
		FSR		EQU		0x04
		PA		EQU		0x05
		PB		EQU		0x06
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
	R_Flag			EQU		0x12
		f_timer0		EQU		0
		f_keyflag		EQU		1
	R_KeyOldData	EQU		0x13
	R_KeyTemp		EQU		0x14
	R_KeyCount		EQU		0x15
	R_KeyData		EQU		0x16
	R_Mode			EQU		0x17
	
	C_KeyCount 		EQU		50
	C_MaxMode		EQU		2

		
		

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
		BSR			R_Flag, f_timer0
		
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
		LCALL		F_KEYSCAN
		LCALL		F_ModeChange
		LCALL		F_MODE_Exec
		GOTO		Main_Start
		
;		BTRSS		PB, 0
;		GOTO		Main_Start100
;		BSR			PB, 1			;; IR输出
;		GOTO		Main_Start
;	Main_Start100:
;		BCR			PB, 1			;; IR 不输出
;		GOTO		Main_Start



F_KEYSCAN:
		BTRSS		R_Flag, f_timer0
		RET
		
		BCR			R_Flag, f_timer0
		MOVR		PB, w
		ANDIA		0x08
		MOVAR		R_KeyTemp
		XORAR		R_KeyOldData, w
		BTRSS		Status, Z
		LGOTO		F_Keyscan900
		INCR		R_KeyCount, R
		MOVIA		C_KeyCount
		SUBAR		R_KeyCount, w
		BTRSS		Status, c
		LGOTO		F_KeyScan_End
		BSR			R_Flag, f_Keyflag
	F_Keyscan900:
		CLRR		R_KeyCount
		MOVR		R_KeyTemp, w
		MOVAR		R_KeyOldData
	F_KeyScan_End:
		RET


F_ModeChange:
		BTRSS		R_Flag, f_keyflag
		RET
		
		BCR			R_Flag, f_Keyflag
		MOVAR		R_KeyOldData
		XORAR		R_KeyData, w
		BTRSC		Status, z
		RET
		MOVR		R_KeyOldData, w
		MOVAR		R_KeyData
		BTRSC		R_KeyData, 3
		RET
		INCR		R_Mode, r
		MOVIA		C_MaxMode
		SUBAR		R_Mode, w
		BTRSS		STatus, c
		RET
		CLRR		R_Mode
		RET

F_Mode_Exec:
		MOVR		R_Mode, w
		ANDIA		0x01
		ADDaR		PCL, R
		LGOTO		F_Mode0
		LGOTO		F_Mode1

F_Mode0:
		BSR			PB, 1
		RET

F_Mode1:
		BCR			PB, 1
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
		
		MOVIA		0x80			;; 设定为 WDT(B7)=1:EN/0:DIS, PB0(B6)=1:INT/0:GPIO, LVR(B3)=1:EN/0:DIS
		MOVAR		PCON

;====================================================================
; Project Name: Time0 初始化
; Madify Data: 2014.12.11
F_Timer0Set:
		MOVIA		0xFE
		MOVIA		INTF			;; Clr Timer0 Flag
		MOVIA		0x01
		T0MD	
		MOVIA		0x00
		MOVAR		TMR0

	
;====================================================================
; Project Name: Time1 初始化
; Madify Data: 2014.12.11
		MOVIA		00000000
		SFUN		T1CR1			;; Disale Timer1
		MOVIA		0xF7
		MOVIA		INTF			;; Clr Timer1 Flag
;		MOVIA		0x10
;		SFUN		TMR1
		MOVIA		0x00
		SFUN		T1CR2			;; P1SEl(B2:B0), PS1EN(B3):0(EN)/1(Dis), T1CE(B4):0:Low->Hi/1:hi->Low, T1CS(B5):0:Instruction CLK/1:Ext CLK
		MOVIA		0X86
		SFUN		BZ1CR
		MOVIA		0x83			;; TIMER1(B0):1:EN/0:Dis, AUTO ReLoad(B1):1:En/0:Dis, PWM1oEN(B7):1:P2 is PWMO/0:P2 is GPIO
		SFUN		T1CR1

;====================================================================
; Project Name: IR 功能初始化
; Madify Data: 
;		MOVIA		0x05			;; IREN(B0):1:EN/0:DIS, IRF57K(B1):1:57K,0:38K, IRCSEL(B2):1:PB.0=Low输出/0:PB.0=Hi输出,
		movia		0x00			;; disble IR Function
		SFUN		IRCR
		
		RET


		end
;Program END	
