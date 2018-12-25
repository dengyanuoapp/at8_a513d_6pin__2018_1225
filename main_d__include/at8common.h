/*!
 * \file       at8common.h
 * \brief      AT8xxxx common header.
 * \author     HuangTing
 * \date       2017.04.14
 * \details    provide useful macro.
 */

#ifndef AT8COMMON_H_P69YF2F3
#define AT8COMMON_H_P69YF2F3

//! Enable interrupt
#define ENI() __asm__("ENI")

//! Disable interrupt
#define DISI() __asm__("DISI")

//! software interrupt
#define INT() __asm__("INT")

//! clear watch dog
#define CLRWDT() __asm__("clrwdt")

//! sleep
#define SLEEP() __asm__("sleep")

//! nop
#define NOP() __asm__("nop")

#endif /* end of include guard: AT8COMMON_H_P69YF2F3 */
// vim:expandtab
