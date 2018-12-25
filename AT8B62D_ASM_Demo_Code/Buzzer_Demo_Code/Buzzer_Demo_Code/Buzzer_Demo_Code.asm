; =========================================================================
; Created by ATW.
; User: VincentLin
; Date: 2016/02/23
; Time: 20:53
; Chip: AT8B62D
; 说名：此程序是选择 PB3 当 BZ1 输出 ，PB2 当 BZ2 输出的 ，PA2 当 BZ3 输出的 Demo Code
; =========================================================================
	#include	AT8B62D.h
		
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
		MOVAR		R_ACC_Buf		;; 保留 ACC 及 Status 的状态值
		SWAPR		R_ACC_Buf, R
		SWAPR		STATUS, A
		MOVAR		R_Status_Buf
	
	ISR_Prog100:
		BTRSS		INTF, T0IF_B
		GOTO		ISR_End
;		BCR		INTF, T0IF		;; 不建议使用方式清除
		MOVIA		0xFE
		MOVAR		INTF			;; CLR TIMER0 FLAG
		MOVIA		0x01
		XORAR		PB, R

	ISR_End:
		SWAPR		R_Status_Buf, A		;; 取回 ACC 及 Status 的状态值
		MOVAR		STATUS
		SWAPR		R_ACC_Buf, A
		RETIE
		
		

;; Main Program
Main_Prog:
		LCALL		F_ClearAllRAM
		LCALL		F_IOInit
		
		MOVIA		0x00			;; Disable T0 Interrupt
		MOVAR		INTE
		
		ENI					;; Enable Goble Interrupt

Main_Start:
		CLRWDT
		MOVIA		0xff
		XORAR		PB, R
		GOTO		Main_Start

;==================================================================
; Project Name:	清零全部RAM
; Last Modify Date:2010-11-9 16:12
;
;;Clear	RAM Bnak0:0x20~0x7f Bank1:0x20~0x3f
F_ClearAllRAM:
	;Bank0	
		BCR		STATUS, BK0_B
		BCR		STATUS, BK1_B
		MOVIA		0x20			;; 切换到 RAM Bank0 $20
		MOVAR		FSR
	L_Clear_Next_Byte_Bank0:
		CLRR		INDF			;; 清除该地址资料
		INCR		FSR, R			;; 累加间接地址
		BTRSS		FSR, 7
		GOTO		L_Clear_Next_Byte_Bank0		;; 否，跳跃
	
	;Bnak1
		BSR		STATUS, BK0_B
		BCR		STATUS, BK1_B
		MOVIA		0x20			;; 切换到 RAM Bank1 $20
		MOVAR		FSR
	L_Clear_Next_Byte_Bank1:
		CLRR		INDF			;; 清除该地址资料
		INCR		FSR, R			;; 累加间接地址
		BTRSS		FSR, 6
		GOTO		L_Clear_Next_Byte_Bank1		;; 否，跳跃
		
		BCR		STATUS, Bk0_B		;; 切换到 RAM Bank0
		BCR		STATUS, BK1_B			
		RET

;====================================================================
; Project Name: IO 初始化
; Madify Data: 2014.12.11
;
F_IOInit:
		MOVIA		0xff
		MOVAR		PB			;; 初始值
		MOVIA		00000000
		IOST		PB			;; 设定为IO状态	0=Output,  1=Input
		
		MOVIA		0x80			;; 设定为 WDT(B7)=1:EN/0:DIS, PB0(B6)=1:INT/0:GPIO, LVR(B3)=1:EN/0:DIS
		MOVAR		PCON

;====================================================================
; Project Name: Time0 初始化
; Madify Data: 2014.12.11
;F_Timer0Set:
;		MOVIA		0xFE
;		MOVIA		INTF			;; Clr Timer0 Flag
;		MOVIA		00000001
;		T0MD	
;		MOVIA		0x00
;		MOVAR		TMR0

	
;====================================================================
; Project Name: Time1 初始化
; Madify Data: 2014.12.11
		MOVIA		00000000
		SFUN		T1CR1			;; Disale Timer1
		MOVIA		0xF7
		MOVIA		INTF			;; Clr Timer1 Flag
		MOVIA		0x00
		SFUN		T1CR2			;;
		
; Buzzer 频率= 1/((1/I_HRC)*指令频率*分频)
;			 = 1/((1/4MHz)*4*128)
;			 = 7.813KHz
		MOVIA		0X86			;; BZ1EN(B7):1:EN/0:Dis / B3~B0: BZ1 Frequecny Select
		SFUN		BZ1CR
		
		MOVIA		0x03			;; 
		SFUN		T1CR1

;====================================================================
; Project Name: Time2 初始化
; Madify Data: 2014.12.11
		MOVIA		00000000
		SFUN		T2CR1			;; Disale Timer2
		MOVIA		0xDF
		MOVIA		INTF			;; Clr Timer2 Flag
		MOVIA		0x00
		SFUN		T2CR2			;;

; Buzzer 频率= 1/((1/I_HRC)*指令频率*分频)
;			 = 1/((1/4MHz)*4*64)
;			 = 15.628KHz
		MOVIA		0X85			;; BZ2EN(B7):1:EN/0:Dis / B3~B0: BZ2 Frequecny Select
		SFUN		BZ2CR
		
		MOVIA		0x03			;; 
		SFUN		T2CR1

;====================================================================
; Project Name: Time3 初始化
; Madify Data: 2014.12.11
		MOVIA		00000000
		SFUN		T3CR1			;; Disale Timer2
		MOVIA		0xEF
		MOVIA		INTE2			;; Clr Timer2 Flag
		MOVIA		0x00
		SFUN		T3CR2			;;

; Buzzer 频率= 1/((1/I_HRC)*指令频率*分频)
;			 = 1/((1/4MHz)*4*256)
;			 = 3.9KHz
		MOVIA		0X87			;; BZ2EN(B7):1:EN/0:Dis / B3~B0: BZ2 Frequecny Select
		SFUN		BZ3CR
		
		MOVIA		0x03			;; 
		SFUN		T3CR1



		RET

		end
;Program END

	
