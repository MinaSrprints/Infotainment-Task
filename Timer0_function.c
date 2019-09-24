/*
 * Timer0_function.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Faster
 */

#include "Timer0_registers.h"
#include "avr/interrupt.h"

//struct Timer0_config init={N_256,CTC_Normal};
static void (*OS_CallBackPtr_g)(void) = NULL;

ISR(TIMER0_COMP_vect)
{
	if(OS_CallBackPtr_g != NULL)
	{
		OS_CallBackPtr_g();
	}
}
void timer0_init(void)
{
	TCCR0=0;
	TCNT0=0;
	//TCCR0|=(T0_config->PRE_SCALER)|(T0_config->Wave_generation_mode);
	Set_Bit(TIMSK,OCIE0);
	TCCR0|=(N_256)|(CTC_Normal);
}
void Set_OCR_Value(uint8 Tick_Time_ms)
{
	switch(Tick_Time_ms)
	{
	case 1u:
		OCR0=31u;
		break;
	case 2u:
		OCR0=62u;
		break;
	case 3u:
		OCR0=94u;
		break;
	case 4u:
		OCR0=125u;
		break;
	case 5u:
		OCR0=156u;
		break;
	case 6u:
		OCR0=187u;
		break;
	case 7u:
		OCR0=219u;
		break;
	case 8u:
		OCR0=250u;
		break;
	default :
		OCR0=250u;
		break;
	}
}
void timer0_Deinit(void)
{
	Clear_Bit(TCCR0,CS00);
	Clear_Bit(TCCR0,CS01);
	Clear_Bit(TCCR0,CS02);
}
void global_interrupt_enable(void)
{
	Set_Bit(SREG,I);
}
void global_interrupt_disable(void)
{
	Clear_Bit(SREG,I);
}
void timer_delay(uint32 delay)
{
	uint32 i;
	TCNT0=0;
	for(i=0;i<(delay);i++)
	{
		while(!(TIFR&(1<<OCF0)));
		Set_Bit(TIFR,OCF0);
	}
}
void OS_SetCallBack(void(*a_ptr)(void))
{
	OS_CallBackPtr_g=a_ptr;
}
