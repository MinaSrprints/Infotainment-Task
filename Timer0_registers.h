/*-
 * Timer0_registers.h
 *
 *  Created on: 18/8/2019
 *  Author: Ahmed Mustafa Ekram
 */

#ifndef TIMER0_REGISTERS_H_
#define TIMER0_REGISTERS_H_
#include "function_macros.h"
#include "standard_types.h"
enum Prescaler{
	NO_PRESCALER=0,N_1=1,N_8=2,N_64=3,N_256=4,N_1024=5,EXT_SOURCE_Falling=6,EXT_SOURCE_Rising=7
};
enum WGM{
NORMAL=0x00,CTC_Normal=0x08,CTC_toggle=0x18,CTC_clear=0x28,CTC_set=0x38,PWM_PHASE_CLEAR=0x60,
PWM_FAST_NONINVERTING=0x68,PWM_PHASE_SET=0x70,PWM_FAST_INVERTING=0x78
};
struct Timer0_config{
	enum Prescaler PRE_SCALER;
    enum WGM Wave_generation_mode;
};
/*---Registers---*/
#define OCR0     (*(volatile uint8*)(0x5C))
#define TIMSK    (*(volatile uint8*)(0x59))
#define TIFR     (*(volatile uint8*)(0x58))
#define TCCR0    (*(volatile uint8*)(0x53))
#define TCNT0    (*(volatile uint8*)(0x52))
/*---Interrupts Registers---*/

#define SREG   (*(volatile uint8*)(0x5F))

/*---PINS---*/
//SREG
#define I 7
//TIMSK
#define TOIE0 0
#define OCIE0 1
//TIFR
#define OCF0  1
#define TOV0  0
//TCCR0
#define CS00  0
#define CS01  1
#define CS02  2
#define WGM01 3
#define COM00 4
#define COM01 5
#define WGM00 6
#define FOC0  7

/*---Prototype---*/
void timer0_init(void);
void timer_delay(uint32 num);
void global_interrupt_enable(void);
void global_interrupt_disable(void);
void timer0_Deinit(void);
void Set_OCR_Value(uint8 Tick_Time);
void OS_SetCallBack(void(*a_ptr)(void));
#endif /* TIMER0_REGISTERS_H_ */
