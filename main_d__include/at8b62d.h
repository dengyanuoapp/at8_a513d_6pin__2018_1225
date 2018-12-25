/*!
 * \file       at8b62d.h
 * \brief      AT8B62D header file
 * \author     HuangTing
 * \date       2018.04.27
 * \details    define register
 */

#ifndef AT8B62D_H_S5PBG7ND
#define AT8B62D_H_S5PBG7ND

#ifndef __CPU_HAS_SET
#  ifdef __SDCC
#    warning "Use NY8.h instead of <icbody>.h for consistency."
#  endif
#endif

#include <at8common.h>

// R-Page special function register {{{

//! INDF (Indirect Addressing Register)
extern __at(0x0000) __sfr INDF;

//! TMR0 (Timer0 Register)
/**
 * When read the register TMR0, it actually read the current running value of Timer0.
 * Write the register TMR0 will change the current value of Timer0.
 * Timer0 clock source can be from instruction clock FINST, or from external pin EX_CKI,
 * or from Low Oscillator Frequency according to T0MD and configuration word setting.
 */
extern __at(0x0001) __sfr TMR0;

//! PCL (Low Byte of PC[10:0])
extern __at(0x0002) __sfr PCL;

//! STATUS (Status Register)
/**
 * |---------------+-------+-------+------+------+------+------+------+------|
 * |               | Bit7  | Bit6  | Bit5 | Bit4 | Bit3 | Bit2 | Bit1 | Bit0 |
 * |---------------+-------+-------+------+------+------+------+------+------|
 * |               | BK[1] | BK[0] | GP5  | /TO  | /PD  | Z    | DC   | C    |
 * |---------------+-------+-------+------+------+------+------+------+------|
 * | R/W Property  | R/W   | R/W   | R/W  | R/W  | R/W  | R/W  | R/W  | R/W  |
 * |---------------+-------+-------+------+------+------+------+------+------|
 * | Initial Value | 0     | 0     | 0    | 1    | 1    | X    | X    | X    |
 * |---------------+-------+-------+------+------+------+------+------+------|
 *
 */
extern __at(0x0003) __sfr STATUS;

//! FSR (Register File Selection Register)
/**
 * |---------------+------+-------+------+------+------+------+------+------|
 * |               | Bit7 | Bit6  | Bit5 | Bit4 | Bit3 | Bit2 | Bit1 | Bit0 |
 * |---------------+------+-------+------+------+------+------+------+------|
 * |               | GP7  |                     FSR[6:0]                    |
 * |---------------+--------------------------------------------------------|
 * | R/W Property  |                            R/W                         |
 * |---------------+------+-------+------+------+------+------+------+------|
 * | Initial Value | 0    | X     | X    | X    | X    | X    | X    | X    |
 * |---------------+------+-------+------+------+------+------+------+------|
 *
 */
extern __at(0x0004) __sfr FSR;

typedef struct __PORTAbits_t
{
    unsigned PA0    : 1;
    unsigned PA1    : 1;
    unsigned PA2    : 1;
    unsigned PA3    : 1;
    unsigned PA4    : 1;
    unsigned PA5    : 1;
    unsigned PA6    : 1;
    unsigned PA7    : 1;
} __PORTAbits_t;

//! PortA (PortA Data Register)
/**
 * |---------------+------+------+------+------+------+------+------+------|
 * |               | Bit7 | Bit6 | Bit5 | Bit4 | Bit3 | Bit2 | Bit1 | Bit0 |
 * |---------------+------+------+------+------+------+------+------+------|
 * |               | PA7  | PA6  | PA5  | PA4  | PA3  | PA2  | PA1  | PA0  |
 * |---------------+------+------+------+------+------+------+------+------|
 * | R/W Property  | R/W  | R/W  | R/W  | R/W  | R/W  | R/W  | R/W  | R/W  |
 * |---------------+------+------+------+------+------+------+------+------|
 * | Initial Value | X    | X    | X    | X    | X    | X    | X    | X    |
 * |---------------+------+------+------+------+------+------+------+------|
 *
 * While reading PortA, it will get the status of the specific pin if that pin
 * is configured as input pin. However, if that pin is configured as output pin,
 * whether it will get the status of the pin or the value of the corresponding
 * output data latch is depend on the configuration option RD_OPT. While writing
 * to PortA, data is written to PA’s output data latch.
 */
extern __at(0x0005) __sfr PORTA;
extern __at(0x0005) volatile __PORTAbits_t PORTAbits; //!< PortA Data Register

typedef struct __PORTBbits_t
{
    unsigned PB0    : 1;
    unsigned PB1    : 1;
    unsigned PB2    : 1;
    unsigned PB3    : 1;
    unsigned PB4    : 1;
    unsigned PB5    : 1;
    unsigned GP6    : 1; //!< General purpose read/write register bit
    unsigned GP7    : 1; //!< General purpose read/write register bit
} __PORTBbits_t;

//! PortB (PortB Data Register)
/**
 * |---------------+------+------+------+------+------+------+------+------|
 * |               | Bit7 | Bit6 | Bit5 | Bit4 | Bit3 | Bit2 | Bit1 | Bit0 |
 * |---------------+------+------+------+------+------+------+------+------|
 * |               | GP7  | GP6  | PB5  | PB4  | PB3  | PB2  | PB1  | PB0  |
 * |---------------+------+------+------+------+------+------+------+------|
 * | R/W Property  | R/W  | R/W  | R/W  | R/W  | R/W  | R/W  | R/W  | R/W  |
 * |---------------+------+------+------+------+------+------+------+------|
 * | Initial Value | X    | X    | X    | X    | X    | X    | X    | X    |
 * |---------------+------+------+------+------+------+------+------+------|
 *
 * While reading PortB, it will get the status of the specific pin if that pin is
 * configured as input pin. However, if that pin is configured as output pin, 
 * whether it will get the status of the pin or the value of the corresponding 
 * output data latch is depend on the configuration option RD_OPT. While writing
 * to PortB, data is written to PB’s output data latch.
 */
extern __at(0x0006) __sfr PORTB;
extern __at(0x0006) volatile __PORTBbits_t PORTBbits; //!< PortB Data Register

typedef struct __PCONbits_t
{
    unsigned GP0    : 1;
    unsigned GP1    : 1;
    unsigned GP2    : 1;
    unsigned LVREN  : 1; //!< Enable/disable LVR. LVREN=1, enable LVR.LVREN=0, disable LVR.
    unsigned PA5PH  : 1; //!< Enable/disable PA5 pull-high resistor. PA5PH=0, enable pull-high resistor. PA5PH=1, disable pull-high resistor.
    unsigned LVDEN  : 1; //!< Enable/disable LVD.
    unsigned GP6    : 1;
    unsigned WDTEN  : 1; //!< Enable/disable WDT. WDTEN=1, enable WDT. WDTEN=0, disable WDT.
} __PCONbits_t;

//! PCON (Power Control Register)
/**
 * |---------------+-------+------+-------+--------+-------+------+------+------|
 * |               | Bit7  | Bit6 | Bit5  | Bit4   | Bit3  | Bit2 | Bit1 | Bit0 |
 * |---------------+-------+------+-------+--------+-------+------+------+------|
 * |               | WDTEN | GP6  | LVDEN | /PHPA5 | LVREN | GP2  | GP1  | GP0  |
 * |---------------+-------+------+-------+--------+-------+------+------+------|
 * | R/W Property  |                              R/W                           |
 * |---------------+-------+------+-------+--------+-------+------+------+------|
 * | Initial Value | 1     | 0    | 0     | 1      | 1     | 0    | 0    | 0    |
 * |---------------+-------+------+-------+--------+-------+------+------+------|
 *
 */
extern __at(0x0008) __sfr PCON;
extern __at(0x0008) volatile __PCONbits_t PCONbits; //!< PCON (Power Control Register)

typedef struct __BWUCONbits_t
{
    unsigned WUPB0  : 1;
    unsigned WUPB1  : 1;
    unsigned WUPB2  : 1;
    unsigned WUPB3  : 1;
    unsigned WUPB4  : 1;
    unsigned WUPB5  : 1;
    unsigned        : 1;
    unsigned        : 1;
} __BWUCONbits_t;

//! BWUCON (PortB Wake-up Control Register)
/**
    Enable/disable PBx wake-up function, 0 ≤ x ≤ 5.
     - WUPBx=1, enable PBx wake-up function.
     - WUPBx=0, disable PBx wake-up function.
*/
extern __at(0x0009) __sfr BWUCON;
extern __at(0x0009) volatile __BWUCONbits_t BWUCONbits; //!< BWUCON (PortB Wake-up Control Register)

//! PCHBUF (High Byte of PC)
/**
 * PCHBUF[1:0]: Buffer of the 9th bit, 8th bit of PC
 *
 * |---------------+-------+----------+------+------+------+------+------+------|
 * |               | Bit7  | Bit6     | Bit5 | Bit4 | Bit3 | Bit2 | Bit1 | Bit0 |
 * |---------------+-------+----------+------+------+------+------+-------------|
 * |               | -     | XSPD_STP | -    | -    | -    |    PCHBUF[2:0]     |
 * |---------------+-------+----------+------+------+------+--------------------|
 * | R/W Property  | -     | W        | -    | -    | -    |       R/W          |
 * |---------------+-------+----------+------+------+------+--------------------|
 * | Initial Value | X     | 0        | X    | X    | X    |       000          |
 * |---------------+-------+----------+------+------+------+--------------------|
 *
 */
extern __at(0x000a) __sfr PCHBUF;

typedef struct __ABPLCONbits_t
{
    unsigned PLPA0  : 1;
    unsigned PLPA1  : 1;
    unsigned PLPA2  : 1;
    unsigned PLPA3  : 1;
    unsigned PLPB0  : 1;
    unsigned PLPB1  : 1;
    unsigned PLPB2  : 1;
    unsigned PLPB3  : 1;
} __ABPLCONbits_t;

//! ABPLCON (PortA/PortB Pull-Low Resistor Control Register)
/**
 * |---------------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |               | Bit7   | Bit6   | Bit5   | Bit4   | Bit3   | Bit2   | Bit1   | Bit0   |
 * |---------------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |               | /PLPB3 | /PLPB2 | /PLPB1 | /PLPB0 | /PLPA3 | /PLPA2 | /PLPA1 | /PLPA0 |
 * |---------------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | R/W Property  |                                  R/W                                  |
 * |---------------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | Initial Value | 1      | 1      | 1      | 1      | 1      | 1      | 1      | 1      |
 * |---------------+--------+--------+--------+--------+--------+--------+--------+--------|
 *
 */
extern __at(0x000b) __sfr ABPLCON;
extern __at(0x000b) volatile __ABPLCONbits_t ABPLCONbits; //!< ABPLCON (PortA/PortB Pull-Low Resistor Control Register)

typedef struct __BPHCONbits_t
{
    unsigned PHPB0  : 1;
    unsigned PHPB1  : 1;
    unsigned PHPB2  : 1;
    unsigned PHPB3  : 1;
    unsigned PHPB4  : 1;
    unsigned PHPB5  : 1;
    unsigned        : 1;
    unsigned        : 1;
} __BPHCONbits_t;

//! BPHCON (PortB Pull-High Resistor Control Register)
/**
 * |---------------+------+-------+--------+--------+--------+--------+--------+--------|
 * |               | Bit7 | Bit6  | Bit5   | Bit4   | Bit3   | Bit2   | Bit1   | Bit0   |
 * |---------------+------+-------+--------+--------+--------+--------+--------+--------|
 * |               | -    | -     | /PHPB5 | /PHPB4 | /PHPB3 | /PHP2B | /PHPB1 | /PHPB0 |
 * |---------------+------+-------+--------+--------+--------+--------+--------+--------|
 * | R/W Property  | -    | -     | R/W    | R/W    | R/W    | R/W    | R/W    | R/W    |
 * |---------------+------+-------+--------+--------+--------+--------+--------+--------|
 * | Initial Value | X    | X     | 1      | 1      | 1      | 1      | 1      | 1      |
 * |---------------+------+-------+--------+--------+--------+--------+--------+--------|
 *
 */
extern __at(0x000c) __sfr BPHCON;
extern __at(0x000c) volatile __BPHCONbits_t BPHCONbits; //!< BPHCON (PortB Pull-High Resistor Control Register)

typedef struct __INTEbits_t
{
    unsigned T0IE   : 1; //!< Timer0 overflow interrupt enable bit.
    unsigned PABIE  : 1; //!< PortA/PortB input change interrupt enable bit.
    unsigned INT0IE : 1; //!< External interrupt 0 enable bit.
    unsigned T1IE   : 1; //!< Timer1 underflow interrupt enable bit.
    unsigned LVDIE  : 1; //!< Low-voltage detector interrupt enable bit.
    unsigned T2IE   : 1; //!< Timer2 underflow interrupt enable bit.
    unsigned WDTIE  : 1; //!< WDT timeout interrupt enable bit.
    unsigned INT1IE : 1; //!< External interrupt 1 enable bit.
} __INTEbits_t;

//! INTE (Interrupt Enable Register)
/**
 * |---------------+--------+-------+------+-------+------+--------+-------+------|
 * |               | Bit7   | Bit6  | Bit5 | Bit4  | Bit3 | Bit2   | Bit1  | Bit0 |
 * |---------------+--------+-------+------+-------+------+--------+-------+------|
 * |               | INT1IE | WDTIE | T2IE | LVDIE | T1IE | INT0IE | PABIE | T0IE |
 * |---------------+--------+-------+------+-------+------+--------+-------+------|
 * | R/W Property  | R/W    | R/W   | R/W  | R/W   | R/W  | R/W    | R/W   | R/W  |
 * |---------------+--------+-------+------+-------+------+--------+-------+------|
 * | Initial Value | 0      | 0     | 0    | 0     | 0    | 0      | 0     | 0    |
 * |---------------+--------+-------+------+-------+------+--------+-------+------|
 *
 */
extern __at(0x000e) __sfr INTE;
extern __at(0x000e) volatile __INTEbits_t INTEbits; //!< INTE (Interrupt Enable Register)

typedef struct __INTFbits_t
{
    unsigned T0IF   : 1; //!< Timer0 overflow interrupt flag bit.
    unsigned PABIF  : 1; //!< PortA/PortB input change interrupt flag bit.
    unsigned INT0IF : 1; //!< External interrupt 0 flag bit.
    unsigned T1IF   : 1; //!< Timer1 underflow interrupt flag bit.
    unsigned LVDIF  : 1; //!< Low-voltage detector interrupt flag bit.
    unsigned T2IF   : 1; //!< Timer2 underflow interrupt flag bit.
    unsigned WDTIF  : 1; //!< WDT timeout interrupt flag bit.
    unsigned INT1IF : 1; //!< External interrupt 1 flag bit.
} __INTFbits_t;

//! INTF (Interrupt Flag Register)
/**
 * |---------------+--------+-------+------+-------+------+--------+-------+------|
 * |               | Bit7   | Bit6  | Bit5 | Bit4  | Bit3 | Bit2   | Bit1  | Bit0 |
 * |---------------+--------+-------+------+-------+------+--------+-------+------|
 * |               | INT1IF | WDTIF | T2IF | LVDIF | T1IF | INT0IF | PABIF | T0IF |
 * |---------------+--------+-------+------+-------+------+--------+-------+------|
 * | R/W Property  | R/W    | R/W   | R/W  | R/W   | R/W  | R/W    | R/W   | R/W  |
 * |---------------+--------+-------+------+-------+------+--------+-------+------|
 * | Initial Value | 0      | 0     | 0    | 0     | 0    | 0      | 0     | 0    |
 * |---------------+--------+-------+------+-------+------+--------+-------+------|
 *
 */
extern __at(0x000f) __sfr INTF;
extern __at(0x000f) volatile __INTFbits_t INTFbits; //!< INTF (Interrupt Flag Register)

typedef struct
{
    unsigned CHS0   : 1; //!< ADC input channel select bits.
    unsigned CHS1   : 1; //!< ADC input channel select bits.
    unsigned CHS2   : 1; //!< ADC input channel select bits.
    unsigned CHS3   : 1; //!< ADC input channel select bits.
    unsigned GCHS   : 1; //!< ADC global channel select bit.
    unsigned EOC    : 1; //!< ADC status bit, read-only.
    unsigned START  : 1; //!< Start an ADC conversion session.
    unsigned ADEN   : 1; //!< ADC enable bit.
} __ADMDbits_t;

//! ADMD (ADC mode Register)
/**
 *  |---------------+------+-------+------+------+------+------+------+------|
 *  |               | Bit7 | Bit6  | Bit5 | Bit4 | Bit3 | Bit2 | Bit1 | Bit0 |
 *  |---------------+------+-------+------+------+------+------+------+------|
 *  |               | ADEN | START | EOC  | GCHS | CHS3 | CHS2 | CHS1 | CHS0 |
 *  |---------------+------+-------+------+------+------+------+------+------|
 *  | R/W Property  | R/W  | W     | R    | R/W  | R/W  | R/W  | R/W  | R/W  |
 *  |---------------+------+-------+------+------+------+------+------+------|
 *  | Initial Value | 0    | 0     | 0    | 0    | 0    | 0    | 0    | 0    |
 *  |---------------+------+-------+------+------+------+------+------+------|
 *
 */
extern __at(0x0010) __sfr ADMD;
extern __at(0x0010) volatile __ADMDbits_t ADMDbits; //!< ADMD (ADC mode Register)

typedef struct
{
    unsigned AD0    : 1; //!< 12-bit low-nibble ADC data buffer.
    unsigned AD1    : 1; //!< 12-bit low-nibble ADC data buffer.
    unsigned AD2    : 1; //!< 12-bit low-nibble ADC data buffer.
    unsigned AD3    : 1; //!< 12-bit low-nibble ADC data buffer.
    unsigned ADCK0  : 1; //!< ADC clock select.
    unsigned ADCK1  : 1; //!< ADC clock select.
    unsigned ADIE   : 1; //!< ADC end-of-convert interrupt enable bit.
    unsigned ADIF   : 1; //!< ADC interrupt flag bit.
} __ADRbits_t;

//! ADR (ADC clock, ADC interrupt flag and ADC LSB output Register)
/**
 * |---------------+------+------+-------+-------+------+------+------+------|
 * |               | Bit7 | Bit6 | Bit5  | Bit4  | Bit3 | Bit2 | Bit1 | Bit0 |
 * |---------------+------+------+-------+-------+------+------+------+------|
 * |               | ADIF | ADIE | ADCK1 | ADCK0 | AD3  | AD2  | AD1  | AD0  |
 * |---------------+------+------+-------+-------+------+------+------+------|
 * | R/W Property  | R    | R/W  | R/W   | R/W   | R    | R    | R    | R    |
 * |---------------+------+------+-------+-------+------+------+------+------|
 * | Initial Value | 0    | 0    | 0     | 0     | X    | X    | X    | X    |
 * |---------------+------+------+-------+-------+------+------+------+------|
 *
 */
extern __at(0x0011) __sfr ADR;
extern __at(0x0011) volatile __ADRbits_t ADRbits; //!< ADR (ADC clock, ADC interrupt flag and ADC LSB output Register)

//! ADD (ADC output data Register)
/**
 * |---------------+------+------+------+------+------+------+------+------|
 * |               | Bit7 | Bit6 | Bit5 | Bit4 | Bit3 | Bit2 | Bit1 | Bit0 |
 * |---------------+------+------+------+------+------+------+------+------|
 * |               | AD11 | AD10 | AD9  | AD8  | AD7  | AD6  | AD5  | AD4  |
 * |---------------+------+------+------+------+------+------+------+------|
 * | R/W Property  | R    | R    | R    | R    | R    | R    | R    | R    |
 * |---------------+------+------+------+------+------+------+------+------|
 * | Initial Value | 0    | 0    | 0    | 0    | 0    | 0    | 0    | 0    |
 * |---------------+------+------+------+------+------+------+------+------|
 *
 */
extern __at(0x0012) __sfr ADD;

typedef struct
{
    unsigned VHS0 : 1; //!< ADC internal reference high voltage select bits.
    unsigned VHS1 : 1; //!< ADC internal reference high voltage select bits.
    unsigned      : 1;
    unsigned      : 1;
    unsigned      : 1;
    unsigned      : 1;
    unsigned      : 1;
    unsigned EVHENB : 1; //!< ADC reference high voltage (VREFH) select control bit.
} __ADVREFHbits_t;

//! ADVREFH (ADC high reference voltage Register)
/**
 * |---------------+--------+------+------+------+------+------+------+------|
 * |               | Bit7   | Bit6 | Bit5 | Bit4 | Bit3 | Bit2 | Bit1 | Bit0 |
 * |---------------+--------+------+------+------+------+------+------+------|
 * |               | EVHENB | -    | -    | -    | -    | -    | VHS1 | VHS0 |
 * |---------------+--------+------+------+------+------+------+------+------|
 * | R/W Property  | R/W    | -    | -    | -    | -    | -    | R/W  | R/W  |
 * |---------------+--------+------+------+------+------+------+------+------|
 * | Initial Value | 0      | X    | X    | X    | X    | X    | 1    | 1    |
 * |---------------+--------+------+------+------+------+------+------+------|
 *
 */
extern __at(0x0013) __sfr ADVREFH;
extern __at(0x0013) volatile __ADVREFHbits_t ADVREFHbits; //!< ADVREFH (ADC high reference voltage Register)

typedef struct
{
    unsigned ADCR0  : 1; //!< ADC conversion bit no. select.
    unsigned ADCR1  : 1; //!< ADC conversion bit no. select.
    unsigned SHCK0  : 1; //!< Sampling pulse width select.
    unsigned SHCK1  : 1; //!< Sampling pulse width select.
    unsigned PBCON3 : 1; //!< PB analog pin select.
    unsigned PBCON4 : 1; //!< PB analog pin select.
    unsigned PBCON5 : 1; //!< PB analog pin select.
    unsigned        : 1;
} __ADCRbits_t;

//! ADCR (Sampling pulse and ADC bit Register)
/**
 * |---------------+------+--------+--------+--------+-------+-------+-------+-------|
 * |               | Bit7 | Bit6   | Bit5   | Bit4   | Bit3  | Bit2  | Bit1  | Bit0  |
 * |---------------+------+--------+--------+--------+-------+-------+-------+-------|
 * |               | -    | PBCON5 | PBCON4 | PBCON3 | SHCK1 | SHCK0 | ADCR1 | ADCR0 |
 * |---------------+------+--------+--------+--------+-------+-------+-------+-------|
 * | R/W Property  | -    | R/W    | R/W    | R/W    | R/W   | R/W   | R/W   | R/W   |
 * |---------------+------+--------+--------+--------+-------+-------+-------+-------|
 * | Initial Value | X    | 0      | 0      | 0      | 1     | 0     | 1     | 0     |
 * |---------------+------+--------+--------+--------+-------+-------+-------+-------|
 *
 * PB analog pin select, 3 ≤ x ≤ 5.
 * 0=PBx can be analog ADC input or digital I/O pin.
 * 1=PBx is pure analog ADC input pin for power-saving.
 *
 */
extern __at(0x0014) __sfr ADCR;
extern __at(0x0014) volatile __ADCRbits_t ADCRbits; //!< ADCR (Sampling pulse and ADC bit Register)

typedef struct
{
    unsigned WUPA0  : 1; //!< Enable/disable PA0 wake-up function
    unsigned WUPA1  : 1; //!< Enable/disable PA1 wake-up function
    unsigned WUPA2  : 1; //!< Enable/disable PA2 wake-up function
    unsigned WUPA3  : 1; //!< Enable/disable PA3 wake-up function
    unsigned WUPA4  : 1; //!< Enable/disable PA4 wake-up function
    unsigned WUPA5  : 1; //!< Enable/disable PA5 wake-up function
    unsigned WUPA6  : 1; //!< Enable/disable PA6 wake-up function
    unsigned WUPA7  : 1; //!< Enable/disable PA7 wake-up function
} __AWUCONbits_t;

//! AWUCON (PortA Wake-up Control Register)
/**
 * |---------------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |               | Bit7  | Bit6  | Bit5  | Bit4  | Bit3  | Bit2  | Bit1  | Bit0  |
 * |---------------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |               | WUPA7 | WUPA6 | WUPA5 | WUPA4 | WUPA3 | WUPA2 | WUPA1 | WUPA0 |
 * |---------------+-------+-------+-------+-------+-------+-------+-------+-------|
 * | R/W Property  | R/W   | R/W   | R/W   | R/W   | R/W   | R/W   | R/W   | R/W   |
 * |---------------+-------+-------+-------+-------+-------+-------+-------+-------|
 * | Initial Value | 1     | 1     | 1     | 1     | 1     | 1     | 1     | 1     |
 * |---------------+-------+-------+-------+-------+-------+-------+-------+-------|
 *
 */
extern __at(0x0015) __sfr AWUCON;
extern __at(0x0015) volatile __AWUCONbits_t AWUCONbits; //!< AWUCON (PortA Wake-up Control Register)

typedef struct
{
    unsigned PACON0 : 1; //!< PA analog pin select
    unsigned PACON1 : 1; //!< PA analog pin select
    unsigned PACON2 : 1; //!< PA analog pin select
    unsigned PACON3 : 1; //!< PA analog pin select
    unsigned PACON4 : 1; //!< PA analog pin select
    unsigned PBCON0 : 1; //!< PB analog pin select
    unsigned PBCON1 : 1; //!< PB analog pin select
    unsigned PBCON2 : 1; //!< PB analog pin select
} __PACONbits_t;

//! PACON (ADC analog pin Register)
/**
 * |---------------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |               | Bit7   | Bit6   | Bit5   | Bit4   | Bit3   | Bit2   | Bit1   | Bit0   |
 * |---------------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |               | PBCON2 | PBCON1 | PBCON0 | PACON4 | PACON3 | PACON2 | PACON1 | PACON0 |
 * |---------------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | R/W Property  | R/W    | R/W    | R/W    | R/W    | R/W    | R/W    | R/W    | R/W    |
 * |---------------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | Initial Value | 0      | 0      | 0      | 0      | 0      | 0      | 0      | 0      |
 * |---------------+--------+--------+--------+--------+--------+--------+--------+--------|
 *
 */
extern __at(0x0016) __sfr PACON;
extern __at(0x0016) volatile __PACONbits_t PACONbits; //!< PACON (ADC analog pin Register)

typedef struct
{
    unsigned INT0G0 : 1; //!< INT0 edge trigger select bit.
    unsigned INT0G1 : 1; //!< INT0 edge trigger select bit.
    unsigned INT1G0 : 1; //!< INT1 edge trigger select bit.
    unsigned INT1G1 : 1; //!< INT1 edge trigger select bit.
    unsigned EIS0   : 1; //!< External interrupt 0 select bit
    unsigned EIS1   : 1; //!< External interrupt 1 select bit
    unsigned        : 1;
    unsigned        : 1;
} __INTEDGbits_t;


//! INTEDG (Interrupt Edge Register)
/**
 * |---------------+------+------+------+------+--------+--------+--------+--------|
 * |               | Bit7 | Bit6 | Bit5 | Bit4 | Bit3   | Bit2   | Bit1   | Bit0   |
 * |---------------+------+------+------+------+--------+--------+--------+--------|
 * |               | -    | -    | EIS1 | EIS0 | INT1G1 | INT1G0 | INT0G1 | INT0G0 |
 * |---------------+------+------+------+------+--------+--------+--------+--------|
 * | R/W Property  | -    | -    | R/W  | R/W  | R/W    | R/W    | R/W    | R/W    |
 * |---------------+------+------+------+------+--------+--------+--------+--------|
 * | Initial Value | X    | X    | 0    | 0    | 0      | 1      | 0      | 1      |
 * |---------------+------+------+------+------+--------+--------+--------+--------|
 *
 */
extern __at(0x0018) __sfr INTEDG;
extern __at(0x0018) volatile __INTEDGbits_t INTEDGbits; //!< INTEDG (Interrupt Edge Register)

//! TMRH (Timer High Byte Register)
/**
 * |---------------+-------+-------+-------+-------+-----------+-----------+-----------+-----------|
 * |               | Bit7  | Bit6  | Bit5  | Bit4  | Bit3      | Bit2      | Bit1      | Bit0      |
 * |---------------+-------+-------+-------+-------+-----------+-----------+-----------+-----------|
 * |               | TMR29 | TMR28 | TMR19 | TMR18 | PWM2DUTY9 | PWM2DUTY8 | PWM1DUTY9 | PWM1DUTY8 |
 * |---------------+-------+-------+-------+-------+-----------+-----------+-----------+-----------|
 * | R/W Property  | R/W   | R/W   | R/W   | R/W   | R/W       | R/W       | R/W       | R/W       |
 * |---------------+-------+-------+-------+-------+-----------+-----------+-----------+-----------|
 * | Initial Value | X     | X     | X     | X     | X         | X         | X         | X         |
 * |---------------+-------+-------+-------+-------+-----------+-----------+-----------+-----------|
 *
 */
extern __at(0x0019) __sfr TMRH;

typedef struct
{
    unsigned        : 7;
    unsigned CMPEN  : 1; //!< Enable/disable voltage comparator.
} __ANAENbits_t;

//! ANAEN (Analog Circuit Enable Register)
/**
 * |---------------+-------+------+------+------+------+------+------+------|
 * |               | Bit7  | Bit6 | Bit5 | Bit4 | Bit3 | Bit2 | Bit1 | Bit0 |
 * |---------------+-------+------+------+------+------+------+------+------|
 * |               | CMPEN | -    | -    | -    | -    | -    | -    | -    |
 * |---------------+-------+------+------+------+------+------+------+------|
 * | R/W Property  | R/W   | -    | -    | -    | -    | -    | -    | -    |
 * |---------------+-------+------+------+------+------+------+------+------|
 * | Initial Value | 0     | X    | X    | X    | X    | X    | X    | X    |
 * |---------------+-------+------+------+------+------+------+------+------|
 *
 */
extern __at(0x001a) __sfr ANAEN;
extern __at(0x001a) volatile __ANAENbits_t ANAENbits; //!< ANAEN (Analog Circuit Enable Register)

typedef struct
{
    unsigned PSEL0 : 1; //!< Select RFC pad.
    unsigned PSEL1 : 1; //!< Select RFC pad.
    unsigned PSEL2 : 1; //!< Select RFC pad.
    unsigned PSEL3 : 1; //!< Select RFC pad.
    unsigned       : 1;
    unsigned       : 1;
    unsigned       : 1;
    unsigned RFCEN : 1; //!< Enable/disable RFC function.
} __RFCbits_t;

//! RFC (RFC Register)
/**
 * |---------------+-------+------+------+------+------+------+------+-----------|
 * |               | Bit7  | Bit6 | Bit5 | Bit4 | Bit3 | Bit2 | Bit1 | Bit0      |
 * |---------------+-------+------+------+------+------+------+------+-----------|
 * |               | RFCEN | -    | -    | -    |           PSEL[3:0]            |
 * |---------------+-------+------+------+------+--------------------------------|
 * | R/W Property  | R/W   | -    | -    | -    |           R/W                  |
 * |---------------+-------+------+------+------+--------------------------------|
 * | Initial Value | 0     | X    | X    | X    |           0                    |
 * |---------------+-------+------+------+------+------+------+------+-----------|
 *
 */
extern __at(0x001b) __sfr RFC;
extern __at(0x001b) volatile __RFCbits_t RFCbits; //!< RFC (RFC Register)

//! TM3RH (Timer3 High Byte Register)
/**
 * |---------------+------+------+-------+-------+------+------+--------+--------|
 * |               | Bit7 | Bit6 | Bit5  | Bit4  | Bit3 | Bit2 | Bit1   | Bit0   |
 * |---------------+------+------+-------+-------+------+------+--------+--------|
 * |               | -    | -    | TMR39 | TMR38 | -    | -    | PWM3D9 | PWM3D8 |
 * |---------------+------+------+-------+-------+------+------+--------+--------|
 * | R/W Property  | -    | -    | R/W   | R/W   | -    | -    | W      | W      |
 * |---------------+------+------+-------+-------+------+------+--------+--------|
 * | Initial Value | -    | -    | X     | X     | -    | -    | X      | X      |
 * |---------------+------+------+-------+-------+------+------+--------+--------|
 *
 */
extern __at(0x001c) __sfr TM3RH;

typedef struct
{
    unsigned T3IE : 1; //!< Timer3 underflow interrupt enable bit.
    unsigned      : 3;
    unsigned T3IF : 1; //!< Timer3 underflow interrupt flag bit.
    unsigned      : 3;
} __INTE2bits_t;

//! INTE2 (Interrupt Enable and Flag 2nd. Register)
/**
 * |---------------+------+------+------+------+------+------+------+------|
 * |               | Bit7 | Bit6 | Bit5 | Bit4 | Bit3 | Bit2 | Bit1 | Bit0 |
 * |---------------+------+------+------+------+------+------+------+------|
 * |               | -    | -    | -    | T3IF | -    | -    | -    | T3IE |
 * |---------------+------+------+------+------+------+------+------+------|
 * | R/W Property  | -    | -    | -    | R/W  | -    | -    | -    | R/W  |
 * |---------------+------+------+------+------+------+------+------+------|
 * | Initial Value | -    | -    | -    | 0    | -    | -    | -    | 0    |
 * |---------------+------+------+------+------+------+------+------+------|
 *
 */
extern __at(0x001f) __sfr INTE2;
extern __at(0x001f) volatile __INTE2bits_t INTE2bits; //!< INTE2 (Interrupt Enable and Flag 2nd. Register)

// R-Page special function register }}}

// F-Page special function register {{{
// --------------------------------------------------------

//! IOSTA (PortA I/O Control Register)
/**
 * IOPAx: PAx I/O mode selection, 0 ≤ x ≤ 7.
 * IOPAx=1, PAx is input mode.
 * IOPAx=0, PAx is output mode.
 */
extern __at(0x00800005) volatile __fpage IOSTA;

//! IOSTB (PortB I/O Control Register)
/**
 * IOPBx: PBx I/O mode selection, 0 ≤ x ≤ 5.
 * IOPBx=1, PBx is input mode.
 * IOPBx=0, PBx is output mode.
 */
extern __at(0x00800006) volatile __fpage IOSTB;

//! APHCON (PortA Pull-High Resistor Control Register)
extern __at(0x00800009) volatile __fpage APHCON;

//! PS0CV (Prescaler0 Counter Value Register)
extern __at(0x0080000a) volatile __fpage PS0CV;

//! BODCON (PortB Open-Drain Control Register)
/**
 * ODPBx: Enable/disable open-drain of PBx, 0 ≤ x ≤ 5.
 *      ODPBx=1, enable open-drain of PBx.
 *      ODPBx=0, disable open-drain of PBx.
 */
extern __at(0x0080000c) volatile __fpage BODCON;

//! CMPCR (Comparator voltage select Control Register)
extern __at(0x0080000e) volatile __fpage CMPCR;

//! PCON1 (Power Control Register1)
/**
 * |---------------+------+--------+------+-------+-------+-------+------+------|
 * |               | Bit7 | Bit6   | Bit5 | Bit4  | Bit3  | Bit2  | Bit1 | Bit0 |
 * |---------------+------+--------+------+-------+-------+-------+------+------|
 * |               | GIE  | LVDOUT | GP5  | LVDS2 | LVDS1 | LVDS0 | GP1  | T0EN |
 * |---------------+------+--------+------+-------+-------+-------+------+------|
 * | R/W Property  | R/W  | R      | R/W  | R/W   | R/W   | R/W   | R/W  | R/W  |
 * |---------------+------+--------+------+-------+-------+-------+------+------|
 * | Initial Value | 0    | X      | 0    | 0     | 0     | 0     | 0    | 1    |
 * |---------------+------+--------+------+-------+-------+-------+------+------|
 *
 */
extern __at(0x0080000f) volatile __fpage PCON1;

// F-Page special function register }}}

// S-Page special function register {{{

//! TMR1 (Timer1 Register)
extern __at(0x01000000) volatile __spage TMR1;

//! T1CR1 (Timer1 Control Register1)
/**
 * |---------------+---------+---------+------+------+------+------+------+------|
 * |               | Bit7    | Bit6    | Bit5 | Bit4 | Bit3 | Bit2 | Bit1 | Bit0 |
 * |---------------+---------+---------+------+------+------+------+------+------|
 * |               | PWM1OEN | PWM1OAL | -    | -    | -    | T1OS | T1RL | T1EN |
 * |---------------+---------+---------+------+------+------+------+------+------|
 * | R/W Property  | R/W     | R/W     | -    | -    | -    | R/W  | R/W  | R/W  |
 * |---------------+---------+---------+------+------+------+------+------+------|
 * | Initial Value | 0       | 0       | X    | X    | X    | 0    | 0    | 0    |
 * |---------------+---------+---------+------+------+------+------+------+------|
 *
 */
extern __at(0x01000001) volatile __spage T1CR1;

//! T1CR2 (Timer1 Control Register2)
/**
 * |---------------+------+------+------+------+--------+------+------+------|
 * |               | Bit7 | Bit6 | Bit5 | Bit4 | Bit3   | Bit2 | Bit1 | Bit0 |
 * |---------------+------+------+------+------+--------+------+------+------|
 * |               | -    | -    | T1CS | T1CE | /PS1EN |     PS1SE[2:0]     |
 * |---------------+------+------+------+------+--------+------+------+------|
 * | R/W Property  | -    | -    | R/W  | R/W  | R/W    | R/W  | R/W  | R/W  |
 * |---------------+------+------+------+------+--------+------+------+------|
 * | Initial Value | X    | X    | 1    | 1    | 1      | 1    | 1    | 1    |
 * |---------------+------+------+------+------+--------+------+------+------|
 *
 * This register is used to configure Timer1 functionality.
 *
 * |-------------+---------------|
 * | PS1SEL[2:0] | Dividing Rate |
 * |-------------+---------------|
 * | 000         | 1:2           |
 * | 001         | 1:4           |
 * | 010         | 1:8           |
 * | 011         | 1:16          |
 * | 100         | 1:32          |
 * | 101         | 1:64          |
 * | 110         | 1:128         |
 * | 111         | 1:256         |
 * |-------------+---------------|
 */
extern __at(0x01000002) volatile __spage T1CR2;

//! PWM1DUTY (PWM1 Duty Register)
extern __at(0x01000003) volatile __spage PWM1DUTY;

//! PS1CV (Prescaler1 Counter Value Register)
extern __at(0x01000004) volatile __spage PS1CV;

//! BZ1CR (Buzzer1 Control Register)
/**
 * |---------------+-------+------+------+------+------+------+------+------|
 * |               | Bit7  | Bit6 | Bit5 | Bit4 | Bit3 | Bit2 | Bit1 | Bit0 |
 * |---------------+-------+------+------+------+------+------+------+------|
 * |               | BZ1EN | -    | -    | -    |     BZ1FSEL[3:0]          |
 * |---------------+-------+------+------+------+---------------------------|
 * | R/W Property  | W     | -    | -    | -    |          W                |
 * |---------------+-------+------+------+------+------+------+------+------|
 * | Initial Value | 0     | X    | X    | X    | 1    | 1    | 1    | 1    |
 * |---------------+-------+------+------+------+------+------+------+------|
 *
 */
extern __at(0x01000005) volatile __spage BZ1CR;

//! IRCR (IR Control Register)
/**
 * |---------------+-----------+------+------+------+------+--------+--------+------|
 * |               | Bit7      | Bit6 | Bit5 | Bit4 | Bit3 | Bit2   | Bit1   | Bit0 |
 * |---------------+-----------+------+------+------+------+--------+--------+------|
 * |               | IROSC358M | -    | -    | -    | -    | IRCSEL | IRF57K | IREN |
 * |---------------+-----------+------+------+------+------+--------+--------+------|
 * | R/W Property  | W         | -    | -    | -    | -    | W      | W      | W    |
 * |---------------+-----------+------+------+------+------+--------+--------+------|
 * | Initial Value | 0         | X    | X    | X    | X    | 0      | 0      | 0    |
 * |---------------+-----------+------+------+------+------+--------+--------+------|
 *
 */
extern __at(0x01000006) volatile __spage IRCR;

//! TBHP (Table Access High Byte Address Pointer Register)
extern __at(0x01000007) volatile __spage TBHP;

//! TBHD (Table Access High Byte Data Register)
extern __at(0x01000008) volatile __spage TBHD;

//! TMR2 (Timer2 Register)
/**
 * When reading register TMR2, it will obtain current value of 10-bit down-count Timer2 at TMR2[7:0].
 * When writing register TMR2, it will write data from TMRH[7:6] and Timer2 reload register to Timer2[9:0]  current content.
 */
extern __at(0x01000009) volatile __spage TMR2;

//! T2CR1 (Timer2 Control Register1)
/**
 * |---------------+---------+---------+------+------+------+------+------+------|
 * |               | Bit7    | Bit6    | Bit5 | Bit4 | Bit3 | Bit2 | Bit1 | Bit0 |
 * |---------------+---------+---------+------+------+------+------+------+------|
 * |               | PWM2OEN | PWM2OAL | -    | -    | -    | T2OS | T2RL | T2EN |
 * |---------------+---------+---------+------+------+------+------+------+------|
 * | R/W Property  | R/W     | R/W     | -    | -    | -    | R/W  | R/W  | R/W  |
 * |---------------+---------+---------+------+------+------+------+------+------|
 * | Initial Value | 0       | 0       | X    | X    | X    | 0    | 0    | 0    |
 * |---------------+---------+---------+------+------+------+------+------+------|
 *
 */
extern __at(0x0100000a) volatile __spage T2CR1;

//! T2CR2 (Timer2 Control Register2)
/**
 * |---------------+------+------+------+------+--------+------+------+------|
 * |               | Bit7 | Bit6 | Bit5 | Bit4 | Bit3   | Bit2 | Bit1 | Bit0 |
 * |---------------+------+------+------+------+--------+------+------+------|
 * |               | -    | -    | T2CS | T2CE | /PS2EN |   PS2SEL[2:0]      |
 * |---------------+------+------+------+------+--------+------+------+------|
 * | R/W Property  | -    | -    | R/W  | R/W  | R/W    | R/W  | R/W  | R/W  |
 * |---------------+------+------+------+------+--------+------+------+------|
 * | Initial Value | X    | X    | 1    | 1    | 1      | 1    | 1    | 1    |
 * |---------------+------+------+------+------+--------+------+------+------|
 *
 */
extern __at(0x0100000b) volatile __spage T2CR2;

//! PWM2DUTY (PWM2 Duty Register)
/**
 * The reload value of 10-bit Timer2 stored on registers TMRH[7:6] and TMR2[7:0] is used to define the PWM2 frame rate,
 * and registers TMRH[3:2] and PWM2DUTY[7:0] is used to define the duty cycle of PWM2.
 */
extern __at(0x0100000c) volatile __spage PWM2DUTY;

//! PS2CV (Prescaler2 Counter Value Register)
/**
 * While reading PS2CV, it will get current value of Prescaler2 counter.
 */
extern __at(0x0100000d) volatile __spage PS2CV;

//! BZ2CR (Buzzer2 Control Register)
/**
 * |---------------+-------+------+------+------+------+------+------+------|
 * |               | Bit7  | Bit6 | Bit5 | Bit4 | Bit3 | Bit2 | Bit1 | Bit0 |
 * |---------------+-------+------+------+------+------+------+------+------|
 * |               | BZ2EN | -    | -    | -    |         BZ2FSEL[3:0]      |
 * |---------------+-------+------+------+------+---------------------------|
 * | R/W Property  | W     | -    | -    | -    |         W                 |
 * |---------------+-------+------+------+------+------+------+------+------|
 * | Initial Value | 0     | X    | X    | X    | 1    | 1    | 1    | 1    |
 * |---------------+-------+------+------+------+------+------+------+------|
 *
 */
extern __at(0x0100000e) volatile __spage BZ2CR;

//! OSCCR (Oscillation Control Register)
/**
 * |---------------+--------+-------+-------+-------+------+------+---------+---------|
 * |               | Bit7   | Bit6  | Bit5  | Bit4  | Bit3 | Bit2 | Bit1    | Bit0    |
 * |---------------+--------+-------+-------+-------+------+------+---------+---------|
 * |               | CMPOUT | CMPOE | CMPIF | CMPIE | OPMD[1:0]   | STPHOSC | SELHOSC |
 * |---------------+--------+-------+-------+-------+-------------+---------+---------|
 * | R/W Property  | R      | R/W   | R/W   | R/W   | R/W         | R/W     | R/W     |
 * |---------------+--------+-------+-------+-------+-------------+---------+---------|
 * | Initial Value | X      | 0     | 0     | 0     | 00          | 0       | 1       |
 * |---------------+--------+-------+-------+-------+-------------+---------+---------|
 *
 * OPMD[1:0]: Selection of operating mode.
 *
 * |-----------+----------------|
 * | OPMD[1:0] | Operating Mode |
 * |-----------+----------------|
 * | 00        | Normal mode    |
 * | 01        | Halt mode      |
 * | 10        | Standby mode   |
 * | 11        | reserved       |
 * |-----------+----------------|
 *
 */
extern __at(0x0100000f) volatile __spage OSCCR;

//! TMR3 (Timer3 Register)
/**
 * When reading register TMR3, it will obtain current value of 10-bit down-count Timer3 at TMR3[7:0].
 * When writing register TMR3, it will write data from TM3RH[5:4] and Timer3 reload register to Timer3[9:0] current content.
 */
extern __at(0x01000010) volatile __spage TMR3;

//! T3CR1 (Timer3 Control Register1)
/**
 * |---------------+---------+---------+------+------+------+------+------+------|
 * |               | Bit7    | Bit6    | Bit5 | Bit4 | Bit3 | Bit2 | Bit1 | Bit0 |
 * |---------------+---------+---------+------+------+------+------+------+------|
 * |               | PWM3OEN | PWM3OAL | -    | -    | -    | T3OS | T3RL | T3EN |
 * |---------------+---------+---------+------+------+------+------+------+------|
 * | R/W Property  | R/W     | R/W     | -    | -    | -    | R/W  | R/W  | R/W  |
 * |---------------+---------+---------+------+------+------+------+------+------|
 * | Initial Value | 0       | 0       | X    | X    | X    | 0    | 0    | 0    |
 * |---------------+---------+---------+------+------+------+------+------+------|
 *
 */
extern __at(0x01000011) volatile __spage T3CR1;

//! T3CR2 (Timer3 Control Register2)
/**
 * |---------------+------+------+------+------+--------+------+------+------|
 * |               | Bit7 | Bit6 | Bit5 | Bit4 | Bit3   | Bit2 | Bit1 | Bit0 |
 * |---------------+------+------+------+------+--------+------+------+------|
 * |               | -    | -    | T3CS | T3CE | /PS3EN |   PS3SEL[2:0]      |
 * |---------------+------+------+------+------+--------+------+------+------|
 * | R/W Property  | -    | -    | R/W  | R/W  | R/W    | R/W  | R/W  | R/W  |
 * |---------------+------+------+------+------+--------+------+------+------|
 * | Initial Value | X    | X    | 1    | 1    | 1      | 1    | 1    | 1    |
 * |---------------+------+------+------+------+--------+------+------+------|
 *
 */
extern __at(0x01000012) volatile __spage T3CR2;

//! PWM3DUTY (PWM3 Duty Register)
/**
 * The reload value of 10-bit Timer3 stored on registers TM3RH[5:4] and TMR3[7:0] is used to define the
 * PWM3 frame rate, and registers TM3RH[1:0] and PWM3DUTY[7:0] is used to define the duty cycle of PWM3.
 */
extern __at(0x01000013) volatile __spage PWM3DUTY;

//! PS3CV (Prescaler3 Counter Value Register)
/**
 * While reading PS3CV, it will get current value of Prescaler3 counter.
 */
extern __at(0x01000014) volatile __spage PS3CV;

//! BZ3CR (Buzzer3 Control Register)
/**
 * |---------------+-------+------+------+------+------+------+------+--------------|
 * |               | Bit7  | Bit6 | Bit5 | Bit4 | Bit3 | Bit2 | Bit1 | Bit0         |
 * |---------------+-------+------+------+------+------+------+------+--------------|
 * |               | BZ3EN | -    | -    | -    |         BZ3FSEL[3:0]              |
 * |---------------+-------+------+------+------+-----------------------------------|
 * | R/W Property  | W     | -    | -    | -    |         W                         |
 * |---------------+-------+------+------+------+------+------+------+--------------|
 * | Initial Value | 0     | X    | X    | X    | 1    | 1    | 1    | 1            |
 * |---------------+-------+------+------+------+------+------+------+--------------|
 *
 */
extern __at(0x01000015) volatile __spage BZ3CR;

// S-Page special function register }}}

// T0MD special function register {{{

//! T0MD Register
/**
 * T0MD is a readable/writeable register which is only accessed by instruction T0MD / T0MDR.
 *
 * +----------------+--------+------+------+------+--------+------+------+------+
 * |                | Bit7   | Bit6 | Bit5 | Bit4 | Bit3   | Bit2 | Bit1 | Bit0 |
 * +----------------+--------+------+------+------+--------+--------------------+
 * |                | LCKTM0 | GP6  | T0CS | T0CE | PS0WDT |     PS0SEL[2:0]    |
 * +----------------+-----------------------------------------------------------+
 * | R/W Property   |                         R/W                               |
 * +----------------+-----------------------------------------------------------+
 * | Initial Value  |   0    |   0  |   1  |   1  |   1    |       111          |
 * +----------------+--------+------+------+------+--------+--------------------+
 *
 * PS0SEL[2:0]: Prescaler0 dividing rate selection. The rate depends on Prescaler0 is assigned to Timer0 or WDT.
 * When Prescaler0 is assigned to WDT, the dividing rate is dependent on which timeout mechanism is selected.
 * +-------------+------------------------------------------+
 * |             |              Dividing Rate               |
 * |             +----------+-------------+-----------------+
 * | PS0SEL[2:0] | PS0WDT=0 | PS0WDT=1    | PS0WDT=1        |
 * |             | (Timer0) | (WDT Reset) | (WDT Interrupt) |
 * +-------------+----------+-------------+-----------------+
 * |    000      |  1:2     |   1:1       |  1:2            |
 * |    001      |  1:4     |   1:2       |  1:4            |
 * |    010      |  1:8     |   1:4       |  1:8            |
 * |    011      |  1:16    |   1:8       |  1:16           |
 * |    100      |  1:32    |   1:16      |  1:32           |
 * |    101      |  1:64    |   1:32      |  1:64           |
 * |    110      |  1:128   |   1:64      |  1:128          |
 * |    111      |  1:256   |   1:128     |  1:256          |
 * +-------------+----------+-------------+-----------------+
 *
 */
extern __at(0x00800000) volatile __t0mdpage T0MD;

// T0MD special function register }}}

#endif /* end of include guard: AT8B62D_H_S5PBG7ND */
// vim:expandtab
