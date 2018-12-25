; =========================================================================
; Created by ATW IDE.
; User: VincentLin
; Date: 2015/7/2
; Time: 9:36
; 说明：切换高低频率的测试。H_IRC <-> l_IRC 互切。
;		可由PB1端口看到频率切换的变化。(H_IRC每1.024ms变化一次。L_IRC每128ms变化一次）
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
	R_RollCode_Buf_L	EQU		0x12
	R_RollCode_Buf_M	EQU		0x13
	R_RollCode_Buf_H	EQU		0x14
	R_Temp				EQU		0x15
	
	R_Time_Buf_H		EQU		0x16
	R_Time_Buf_M		EQU		0x17
	R_Time_Buf_L		EQU		0x18
	
	R_Flag				equ		0x19
		f_1ms			equ		0
	
		

;; Chip Reset Vector
; ===============================================================
		ORG	0x00
Reset:
		GOTO	Main_Prog

		ORG		0x08
		GOTO	ISR_Prog

;; 滚码位置区		
		ORG		0x0e
		NOP	;dw		0xfc01			;; 低10Bit
		NOP	;dw		0xfd00			;; 高10Bit
		
;; ISR Vector
		ORG	0x10
ISR_Prog:
		MOVAR		R_ACC_Buf			;; 保留 ACC 及 Status 的状态值
		SWAPR		R_ACC_Buf, R
		SWAPR		STATUS, A
		MOVAR		R_Status_Buf

;		BTRSS		INTF, T1IF
;		GOTO		ISR_Prog100
;		BCR			INTF, T1IF		;; 不建议使用方式清除
;		MOVIA		0xF7
;		MOVAR		INTF			;; CLR TIMER1 FLAG
;		MOVIA		0x04
;		XORAR		PB, R
	
	ISR_Prog100:
		BTRSS		INTF, T0IF
		GOTO		ISR_End
;		BCR			INTF, T0IF		;; 不建议使用方式清除
		MOVIA		0xFE
		MOVAR		INTF			;; CLR TIMER0 FLAG
;		MOVIA		0x01
;		XORAR		PB, R
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

		MOVIA		0x01			;; ENABLE T0/T1 Interrupt
		MOVAR		INTE
		
		ENI							;; Enable Goble Interrupt
		
Main_Prog10:
;; into High Frequency Mode
		SFUNR		OSCCR			;; 读取目前震荡模式 
		
		ANDIA		0xfd			;; 开启 Normal Mode 高速频率电路
		SFUN		OSCCR
		
		IORIA		0x01			;; Fosc切换到高速频率(H_IRC=4MHz/4T)
		SFUN		OSCCR
		
		MOVIA		0x00			;; 重新置入计数时间。中断时间为1.024ms
		MOVAR		TMR0
		
		MOVIA		0x00
		MOVAR		R_Temp
		
	Main_Prog100:
		CLRWDT
		BTRSS		R_Flag, f_1ms
		GOTO		Main_Prog100
		
		BCR			R_Flag, f_1ms
		
		MOVIA		0x02
		XORAR		PB, R
		
		DECRSZ		R_Temp, R
		GOTO		Main_Prog100
		
;; into Slow Frequency Mode & Disable High Frequency
		SFUNR		OSCCR			;; 读取目前震荡模式
		
		ANDIA		0xfe			;; 切换到低速频率(L_IRC=32KHz/4T)
		SFUN		OSCCR
		
		ANDIA		0x02			;; 关闭高频震荡
		SFUN		OSCCR
		
		MOVIA		0x00			;; 重新置入计数时间。中断时间约128ms
		MOVAR		TMR0
		
		MOVIA		32
		MOVAR		R_Temp
		
	Main_Prog300:
		CLRWDT
		BTRSS		R_Flag, f_1ms
		GOTO		Main_Prog300
		
		BCR			R_Flag, f_1ms
		
		MOVIA		0x02
		XORAR		PB, R
		
		DECRSZ		R_Temp, R
		GOTO		Main_Prog300

		GOTO		Main_Prog10

		ORG			0x300
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

;		ORG		0x300
;====================================================================
; Project Name: IO 初始化
; Madify Data: 2014.12.11
;
F_IOInit:
		MOVIA		0xff
		MOVAR		PB				;; 初始值
		MOVIA		00000000
		IOST		PB				;; 设定为IO状态	0=Output,  1=Input
		
		MOVIA		0x80			;; 设定为 WDT(B7)=1:EN/0:DIS, PB0(B6)=1:INT/0:GPIO, LVR(B3)=1:EN/0:DIS
		MOVAR		PCON

;====================================================================
; Project Name: Time0 初始化
; Madify Data: 2014.12.11
F_Timer0Set:
		MOVIA		0xFE
		MOVIA		INTF			;; Clr Timer0 Flag
		MOVIA		00000001
		T0MD	
		MOVIA		0x00
		MOVAR		TMR0

	
;====================================================================
; Project Name: Time1 初始化
; Madify Data: 2014.12.11
;		MOVIA		00000000
;		SFUN		T1CR1			;; Disale Timer1
;		MOVIA		0xF7
;		MOVIA		INTF			;; Clr Timer1 Flag
;		MOVIA		0x80
;		SFUN		TMR1
;		MOVIA		0x00
;;		SFUN		PWM1DUTY
;;		MOVIA		0x00
;		SFUN		T1CR2			;; P1SEl(B2:B0), PS1EN(B3):0(EN)/1(Dis), T1CE(B4):0:Low->Hi/1:hi->Low, T1CS(B5):0:Instruction CLK/1:Ext CLK
;;		MOVIA		0x00
;;		SFUN		BZ1CR
;		MOVIA		0x83			;; TIMER1(B0):1:EN/0:Dis, AUTO ReLoad(B1):1:En/0:Dis, PWM1oEN(B7):1:P2 is PWMO/0:P2 is GPIO
;		SFUN		T1CR1
		RET

		end
;Program END
	

	
