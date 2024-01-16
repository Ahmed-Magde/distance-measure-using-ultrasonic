/*
 * ultarsonic.c
 *
 *  Created on: Oct 12, 2021
 *      Author: Ahmed Magdy
 */
#include "ultrasonic.h"
#include "gpio.h"
#include "icu.h"
#include <util/delay.h>


static uint8 counter=0;
static uint16 high_time=0;



void Ultrasonic_init(void)
{
	Icu_ConfigType Icu_Config = {F_CPU_8,RISING};

	Icu_init(&Icu_Config);	/*Initialize the ICU driver*/

	Icu_setCallBack(Ultrasonic_edgeProcessing);  /*Setup the ICU call back function*/

	GPIO_setupPinDirection(trigger_port,trigger_pin,PIN_OUTPUT);/*Setup the direction for the trigger pin as output pin */
	GPIO_writePin(trigger_port, trigger_pin, LOGIC_LOW);


}


void Ultrasonic_Trigger(void)
{
	GPIO_writePin(trigger_port, trigger_pin, LOGIC_HIGH);
	_delay_us(50);
	GPIO_writePin(trigger_port, trigger_pin, LOGIC_LOW);
}


uint16 Ultrasonic_readDistance(void)
{
	uint16 d=0;

	Ultrasonic_Trigger();
	d = ((high_time*Sound_velocity)/(F_CPU*2));
//	d =high_time/57.8;
	return d;

}


void Ultrasonic_edgeProcessing(void)
{
	counter++;

		if(counter==1)
		{
			Icu_clearTimerValue();
			Icu_setEdgeDetectionType(FALLING);
		}
		else if(counter==2)
		{
			high_time=Icu_getInputCaptureValue();
			Icu_setEdgeDetectionType(RISING);
			counter = 0;

		}

}




