/*
 * icu.h
 *
 *  Created on: Oct 6, 2021
 *      Author: Ahmed Magdy
 */

#ifndef ICU_H_
#define ICU_H_

#include "std_types.h"
#include "common_macros.h"

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

typedef enum
{
	NO_CLOCK,F_CPU_CLOCK,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024
}Icu_Clock;

typedef enum
{
	FALLING,RISING
}Icu_Edgtype;

typedef struct
{
	Icu_Clock clock;
	Icu_Edgtype edg;
}Icu_ConfigType;

void Icu_init( const Icu_ConfigType *ptr);
void Icu_DeInit(void);
void Icu_setCallBack(void(*a_ptr)(void));
uint16 Icu_getInputCaptureValue(void);
void Icu_setEdgeDetectionType(const Icu_Edgtype edg);
void Icu_clearTimerValue(void);


#endif /* ICU_H_ */
