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

void Infotainment(void);
void KeyPad_Task(void);

/**************************************************************************
 * 				       		  Enum Prototype						      *
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

/**************************************************************************
 * 				 Global variables and shared resource		  		      *
 *************************************************************************/
uint8 KeyPad_state_g = KeyPad_IDEAL;
uint8 Infotainment_state_g = Infotainment_IDEAL;
sint8 Infotainment_Result_Counter=0;
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
	 * 				               Start OS								      *
	 *************************************************************************/

	LCD_INIT();			/*initialize LCD driver*/
	KeyPad_init();		/*initialize KeyPad driver*/
	OS_init();			/*initialize OS driver*/

	Create_Task(KeyPad_Task,SECOND_LVL_PRIORITY,1u,1u,0u);
	/*create KeyPad Task to get pressed key with handling debouncing*/
	Create_Task(Infotainment,HIGHST_PRIORITY,20U,20U,0U);
	/*create Infotainment task to display the game*/
	OS_Run();
	/*create Infotainment task to display the game*/
	return 0;
	/**************************************************************************
	 * 				         Main function end							      *
	 *************************************************************************/
}
/**************************************************************************
 * 				            set of tasks							      *
 *************************************************************************/

/**************************************************************************
 * Function Name : Infotainment
 *
 * Description	 : this function contains the game code
 *
 * INPUTS		 : void
 *
 * OUTPUTS 		 : void
 *
 * Return		 : void
 **************************************************************************/
void Infotainment(void) /*Infotainment Task*/
{
	LCD_Clear();								/*clear lcd at the beginning */
	switch(Infotainment_state_g)				/* switch on the stats starting form ideal state till the end of state machine*/
	{
	case Infotainment_IDEAL:					/* in case this is ideal case display the welcome massage*/

		Infotainment_Result_Counter=0;
		LCD_goToRowColumn(0,0);
		LCD_sendString("welcome :D ");
		LCD_goToRowColumn(1,0);
		LCD_sendString("To start press 5");
		LCD_goToRowColumn(0,13);
		LCD_sendChar(keypressed+'0');

		if(keypressed==5)								/* if button pressed = 5 start the challange */
		{
			Infotainment_state_g=Infotainment_Q1;		/*update state to Q1 state*/
			keypressed=0;								/*restart the shared resource to get new value*/
		}
		break;

	case Infotainment_Q1:								/* in case Q1 display Question1 */
		LCD_goToRowColumn(0,0);
		LCD_sendString("can u read? :D");
		LCD_goToRowColumn(1,0);
		LCD_sendString("4-yes   6-no");
		LCD_goToRowColumn(0,13);
		LCD_sendChar(keypressed+'0');

		if(keypressed==4)								/* if button pressed = 4 means user wants to say yes*/
		{
			Infotainment_Result_Counter++;				/* increment the counter in case of correct answer*/
			Infotainment_state_g=Infotainment_Q2;		/*update state to Q2 state*/
			keypressed=0;
		}
		if(keypressed==6)								/* if button pressed = 6 means user wants to say yes*/
		{
			Infotainment_Result_Counter--;				/* decrement the counter in case of incorrect answer*/
			Infotainment_state_g=Infotainment_Q2;		/*update state to Q2 state*/
			keypressed=0;
		}

		break;
	case Infotainment_Q2:								/* in case Q2 display Question2 */
		LCD_goToRowColumn(0,0);
		LCD_sendString("r u here?");
		LCD_goToRowColumn(1,0);
		LCD_sendString("4-yes   6-no");
		LCD_goToRowColumn(0,13);
		LCD_sendChar(keypressed+'0');

		if(keypressed==4)								/* if button pressed = 4 means user wants to say yes*/
		{
			Infotainment_Result_Counter++;				/* increment the counter in case of correct answer*/
			Infotainment_state_g=Infotainment_Q3;		/*update state to Q3 state*/
			keypressed=0;
		}
		if(keypressed==6)								/* if button pressed = 6 means user wants to say yes*/
		{
			Infotainment_Result_Counter--;				/* decrement the counter in case of correct answer*/
			Infotainment_state_g=Infotainment_Q3;		/*update state to Q3 state*/
			keypressed=0;
		}
		break;
	case Infotainment_Q3:								/* in case Q3 display Question */
		LCD_goToRowColumn(0,0);
		LCD_sendString("r u loser?");
		LCD_goToRowColumn(1,0);
		LCD_sendString("4-yes   6-no");
		LCD_goToRowColumn(0,13);
		LCD_sendChar(keypressed+'0');

		if(keypressed==4)								/* if button pressed = 4 means user wants to say yes*/
		{
			Infotainment_Result_Counter--;				/* decrement the counter in case of correct answer*/
			Infotainment_state_g = Infotainment_Q4;		/*update state to Q4 state*/
			keypressed=0;
		}
		if(keypressed==6)								/* if button pressed = 6 means user wants to say yes*/
		{
			Infotainment_Result_Counter++;				/* increment the counter in case of correct answer*/
			Infotainment_state_g=Infotainment_Q4;		/*update state to Q4 state*/
			keypressed=0;
		}
		break;

	case Infotainment_Q4:								/* in case Q4 display Question4 */
		LCD_goToRowColumn(0,0);
		LCD_sendString("r u ?");
		LCD_goToRowColumn(1,0);
		LCD_sendString("4-yes   6-no");

		if(keypressed==4)								/* if button pressed = 4 means user wants to say yes*/
		{
			Infotainment_Result_Counter++;				/* increment the counter in case of correct answer*/
			Infotainment_state_g=Infotainment_Q5;		/*update state to Q5 state*/
			keypressed=0;
		}
		if(keypressed==6)								/* if button pressed = 6 means user wants to say yes*/
		{
			Infotainment_Result_Counter--;				/* increment the counter in case of correct answer*/
			Infotainment_state_g=Infotainment_Q5;		/*update state to Q5 state*/
			keypressed=0;
		}
		break;
	case Infotainment_Q5:								/* in case Q5 display Question */
		LCD_goToRowColumn(0,0);
		LCD_sendString("r u here?");
		LCD_goToRowColumn(1,0);
		LCD_sendString("4-yes   6-no");
		if(keypressed==4)								/* if button pressed = 4 means user wants to say yes*/
		{
			Infotainment_Result_Counter++;				/* increment the counter in case of correct answer*/
			Infotainment_state_g=Infotainment_Result;	/*update state to infotainment result state*/
			keypressed=0;
		}
		if(keypressed==6)								/* if button pressed = 6 means user wants to say yes*/
		{
			Infotainment_Result_Counter--;				/* increment the counter in case of correct answer*/
			Infotainment_state_g=Infotainment_Result;	/*update state to infotainment result state*/
			keypressed=0;
		}
		break;
	case Infotainment_Result:							/* in case infotainment result display result */
		LCD_goToRowColumn(0,0);
		LCD_sendString("res=");
		LCD_goToRowColumn(0,5);
		if(Infotainment_Result_Counter<0)
		{
			LCD_sendChar(0+'0');						/*display 0 in case of -ve*/
		}
		else
		{
			LCD_sendChar(Infotainment_Result_Counter+'0');		/*display result*/
		}
		LCD_goToRowColumn(1,0);
		LCD_sendString("restart-4 crct-6");

		if(keypressed==4)								/* if button pressed = 4 means user wants to say yes*/
		{
			Infotainment_state_g=Infotainment_IDEAL;	/*update state to infotainment ideal state*/
			keypressed=0;
		}
		if(keypressed==6)
		{
			LCD_goToRowColumn(0,0);
			LCD_sendString("y y y n y");
			Delete_Task(Infotainment);
		}
		break;
	}
}

/**************************************************************************
 * Function Name : keyPad_Task
 *
 * Description	 : this function takes number from user and puts it in a shared resource
 *
 * INPUTS		 : void
 *
 * OUTPUTS 		 : void
 *
 * Return		 : void
 **************************************************************************/
void KeyPad_Task(void)
{
	cur=prev;								/*	cur and prev to handle long press */
	prev=KeyPad_getPressedKey();			/*	get the prev value of button*/
	switch(KeyPad_state_g)					/*	switch case to handel keypad states*/
	{
	case KeyPad_IDEAL:						/*  case of the keypad*/

		if(prev != 'a')						/*	'a' is just a symbol to check if the button is pressed*/
		{
			count++;						/*	if button is pressed start samping*/
			if(count==10)					/*	if sampling value is equal 10 then we have a full press */
			{
				KeyPad_state_g=PRESSED;		/*switch state to pressed state*/
			}
			else							/*if sampling not equal 10 then we are on debouncing phase*/
			{
				KeyPad_state_g=RELEASD;		/*switch state to released state*/
			}
		}
		break;
	case PRESSED:							/*in case of pressed*/
		if(cur!=prev && prev != 'a')		/*we should make sure that cur not equal previous and prev not equal the 'a' sympol*/
		{
			keypressed=KeyPad_getPressedKey();	/*take the value of the button in shared resource variable*/
			cur=prev;							/*set cur equal to prev*/
			KeyPad_state_g= RELEASD;			/*switch state to released*/
		}
		else
		{
												/*else do nothing*/
		}
		count=0;								/*set count to zero to start sampling new press */
		break;

	case RELEASD:								/*case of released*/
		KeyPad_state_g =KeyPad_IDEAL;			/*switch state to keypad ideal to start the cycle */
		break;
	}
}
