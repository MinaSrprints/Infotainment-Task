/*
 * Keybad.c
 *
 *  Created on: Aug 26, 2017
 *      Author: Avenger
 */
#include"standard_types.h"
#include"DIO_operations.h"
#include<util/delay.h>
#define F_CPU 8000000UL
#include"Keybad_CFG.h"

void Keybad_Init(void)
{
	//  DIO_SetPortDirection(Keybad_Port,255); //Setting keypad port as output port

	//Setting the rows as input pins
	DIO_SetPinDirection(PinC2,0);
	DIO_SetPinDirection(PinC3,0);
	DIO_SetPinDirection(PinC4,0);

	//Enabling the pull up resistors on input pins
	DIO_WritePin(PinC5,1);
	DIO_WritePin(PinC6,1);
	DIO_WritePin(PinC7,1);
}

uint8 Keybad_CheckButton(uint8 Key_Number)
{
	uint8 result=0;

	uint8 row=Key_Number/3;
	uint8 col=Key_Number%3;
	uint8 Real_row[]={PinC2,PinC3,PinC4};
	uint8 Real_col[]={PinC5,PinC6,PinC7};

	DIO_WritePin(PinC5,1);
	DIO_WritePin(PinC6,1);
	DIO_WritePin(PinC7,1);
	DIO_WritePin(Real_col[col],0);

	uint8 x=DIO_ReadPin(Real_row[row]);
	if(x==0)
	{
		_delay_us(500);
		x=DIO_ReadPin(Real_row[row]);
		if(x==0)
		{
			result=1;
		}
	}
	return result;
}

