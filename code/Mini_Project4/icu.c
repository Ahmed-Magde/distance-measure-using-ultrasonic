/*
 * icu.c
 *
 *  Created on: Oct 6, 2021
 *      Author: Ahmed Magdy
 */
#include "icu.h"
#include <avr/io.h>
#include <avr/interrupt.h>

static volatile void (*g_callBackPtr)(void) = NULL_PTR;


ISR(TIMER1_CAPT_vect)
{
	if(g_callBackPtr!=NULL_PTR)
	{
		(*g_callBackPtr)();
	}
}

void Icu_init( const Icu_ConfigType *ptr)
{
	DDRD &= ~(1<<PD6);
	TCCR1A |=(1<< FOC1A) | (1<<  FOC1B);

	TCCR1B = (ptr->clock ) | (TCCR1B & 0xF8);
	TCCR1B = ((ptr->edg)<<6 ) | (TCCR1B & 0XBF);

	TCNT1=0;
	ICR1=0;

	TIMSK |= (1<< TICIE1);

}

void Icu_DeInit(void)
{
	TCCR1A=0;
	TCCR1B=0;
	TCNT1=0;
	ICR1=0;

	TIMSK &=~(1<< TICIE1);
}


void Icu_setCallBack(void(*a_ptr)(void))
{
	g_callBackPtr = a_ptr;
}

uint16 Icu_getInputCaptureValue(void)
{
	return ICR1;
}

void Icu_setEdgeDetectionType(const Icu_Edgtype edg)
{
	TCCR1B = (edg<<6 ) | (TCCR1B & 0XBF);

}

void Icu_clearTimerValue(void)
{
	TCNT1 = 0;
}




