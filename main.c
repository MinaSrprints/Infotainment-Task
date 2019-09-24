/***********************************************
 *  Module:OS
 *
 *  File Name:main.c
 *
 *  Description: OS application
 *
 *  Created on: 15/9/2019
 *
 *  Author: Ahmed Ekram
 ***********************************************/
/**************************************************************************
 * 				            Included files							      *
 *************************************************************************/
#include "OS.h"
#include "keypad.h"
#include "LCD.h"
/**************************************************************************
 * 				         Function Prototype							      *
 *************************************************************************/
enum
{
	Infotainment_IDEAL,
	Infotainment_Q1,
	Infotainment_Q2,
	Infotainment_Q3,
	Infotainment_Q4,
	Infotainment_Q5,
	Infotainment_Result

}EnmInfotainment_State;
void Task1(void);
void Task2(void);
void Imfotainment(void);
void KeyPad_Task(void);
uint8 KeyPad_state_g = KeyPad_IDEAL;
uint8 Infotainment_state_g = Infotainment_IDEAL;
uint8 Infotainment_Result_Counter=0;
uint8 count = 0;
uint8 stuck_flage=0;
uint8 keypressed=0;
static uint8 cur=0,prev=0;
uint8 num;


/**************************************************************************
 * 				            main Function							      *
 *************************************************************************/
int main(void)
{
	/**************************************************************************
	 * 				            Pin Defining							      *
	 *************************************************************************/
	DIO_SetPinDirection(PinB4,HIGH);
	DIO_SetPinDirection(PinB5,HIGH);
	DIO_SetPinDirection(PinB6,HIGH);
	DIO_SetPinDirection(PinB2,INPUT);
	DIO_WritePin(PinB4,LOW);
	DIO_WritePin(PinB5,LOW);
	DIO_WritePin(PinB6,LOW);
	/**************************************************************************
	 * 				               Start OS								      *
	 *************************************************************************/

	LCD_INIT();
	KeyPad_init();
	OS_init();

	Create_Task(KeyPad_Task,SECOND_LVL_PRIORITY,1u,1u,0u);
	Create_Task(Imfotainment,HIGHST_PRIORITY,1500U,1500U,0U);
	OS_Run();
	return 0;
	/**************************************************************************
	 * 				         Main function end							      *
	 *************************************************************************/
}
/**************************************************************************
 * 				            set of tasks							      *
 *************************************************************************/
void Task1(void)
{
}
void Task2(void)
{

}
void Imfotainment(void)
{
	LCD_Clear();
	switch(Infotainment_state_g)
	{
	case Infotainment_IDEAL:
		LCD_goToRowColumn(0,0);
		LCD_sendString("Hello ");
		LCD_goToRowColumn(1,0);
		LCD_sendString("To start press 5");
		LCD_goToRowColumn(0,13);
		LCD_sendChar(keypressed+'0');
		if(keypressed==5)
		{
			Infotainment_state_g=Infotainment_Q1;
			keypressed=0;
		}
		break;

	case Infotainment_Q1:
		LCD_goToRowColumn(0,0);
		LCD_sendString("r u here?");
		LCD_goToRowColumn(1,0);
		LCD_sendString("4-yes   6-no");
		LCD_goToRowColumn(0,13);
		LCD_sendChar(keypressed+'0');
		if(keypressed==4)
		{
			Infotainment_Result_Counter++;
			Infotainment_state_g=Infotainment_Q2;
			keypressed=0;
		}
		if(keypressed==6)
		{
			Infotainment_Result_Counter--;
			Infotainment_state_g=Infotainment_Q2;
			keypressed=0;
		}

		break;
	case Infotainment_Q2:
			LCD_goToRowColumn(0,0);
			LCD_sendString("r u one?");
			LCD_goToRowColumn(1,0);
			LCD_sendString("4-yes   6-no");
			LCD_goToRowColumn(0,13);
			LCD_sendChar(keypressed+'0');
			if(keypressed==4)
			{
				Infotainment_Result_Counter++;
				Infotainment_state_g=Infotainment_Q3;
				keypressed=0;
			}
			if(keypressed==6)
			{
				Infotainment_Result_Counter--;
				Infotainment_state_g=Infotainment_Q3;
				keypressed=0;
			}
			break;
	case Infotainment_Q3:
				LCD_goToRowColumn(0,0);
				LCD_sendString("r u two?");
				LCD_goToRowColumn(1,0);
				LCD_sendString("4-yes   6-no");
				LCD_goToRowColumn(0,13);
				LCD_sendChar(keypressed+'0');
				if(keypressed==4)
				{
					DIO_WritePin(PinB5,HIGH);
					Infotainment_Result_Counter++;
					Infotainment_state_g = Infotainment_Q4;
					keypressed=0;
				}
				if(keypressed==6)
				{
					Infotainment_Result_Counter--;
					Infotainment_state_g=Infotainment_Q4;
					keypressed=0;
				}
				break;
	case Infotainment_Q4:
				LCD_goToRowColumn(0,0);
				LCD_sendString("r u three?");
				LCD_goToRowColumn(1,0);
				LCD_sendString("4-yes   6-no");
				if(keypressed==4)
				{
					Infotainment_Result_Counter++;
					Infotainment_state_g=Infotainment_Result;
					keypressed=0;
				}
				if(keypressed==6)
				{
					Infotainment_Result_Counter--;
					Infotainment_state_g=Infotainment_Result;
					keypressed=0;
				}
				break;
	case Infotainment_Result:
				LCD_goToRowColumn(0,0);
				LCD_sendString("res=");
				LCD_goToRowColumn(1,0);
				LCD_sendChar(Infotainment_Result_Counter+'0');
				Infotainment_state_g=Infotainment_IDEAL;

				break;
	}
}
void KeyPad_Task(void)
{
	cur=prev;
	prev=KeyPad_getPressedKey();
	switch(KeyPad_state_g)
	{
	case KeyPad_IDEAL:

		if(prev != 'a')
		{
			count++;
			if(count==10)
			{
				KeyPad_state_g=PRESSED;
			}
			else
			{
				KeyPad_state_g=RELEASD;
			}
		}
		break;
	case PRESSED:
		if(cur!=prev && prev != 'a')
		{
			keypressed=KeyPad_getPressedKey();
			cur=prev;
			KeyPad_state_g= RELEASD;
		}
		else
		{
			DIO_WritePin(PinB6,LOW);
		}
		count=0;
		break;

	case RELEASD:
		KeyPad_state_g =KeyPad_IDEAL;
		break;
	}
}
