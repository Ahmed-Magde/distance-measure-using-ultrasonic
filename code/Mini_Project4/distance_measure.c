/*
 * distance_measure.c
 *
 *  Created on: Oct 12, 2021
 *      Author: Ahmed Magdy
 */


#include "lcd_driver.h"
#include "ultrasonic.h"
//#include <avr/interrupt.h>
#include <avr/io.h>


int main()
{
	uint16 distance=0;
	SREG |=(1<<7);

	LCD_init();
	Ultrasonic_init();


	LCD_moveCursor(0,0);
	LCD_displayString("Distance=");


	while(1)
	{

		distance = Ultrasonic_readDistance();

		LCD_moveCursor(0,9);

		LCD_intgerToString(distance);
		LCD_displayString(" ");
		LCD_displayString("cm");
		LCD_displayString("  ");



	}
}
