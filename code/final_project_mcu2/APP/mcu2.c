/*
 * mcu2.c
 *
 *  Created on: Oct 28, 2023
 *      Author: mario
 */
#include"HAL/buzzer.h"
#include"HAL/DCmotor.h"
#include"HAL/external_EEPROM.h"

#include"HAL/MCAL/UART.h"
#include"HAL/MCAL/timer1.h"

#include"util/delay.h"
#include"HAL/MCAL/AVRIO.h"

/***************************************************************************
 *                           Global variables
 *****************************************************************************/

UART_configType g_UART_configurations = {EIGHT_BIT,NO_PARITY,ONE_STOP,9600};
TIMER1_configType g_TIMER1_configurations;
/*
 * password1 >> first password during create password
 * password2 >> second password during create password
 * saved password >> The password actually saved in EEPROM
 * entered password >> The password that user enter to check with the one in EEPROM
 */
uint8 g_password1[5],g_password2[5],g_savedPassword[5],g_enteredPassword[5];

uint8 i; /* Counter for every for loop on any password */

/* Flag is set when the two password passed to check fn is matching */
uint8 matching=1;

/* Every tick is 3 seconds */
uint8 tick=0;

/***************************************************************************
 *                           Types declaration
 *****************************************************************************/

enum states{

	CREATE_PASSWORD,MAIN_OPTIONS,OPEN_DOOR,WRONG_PASSWORD,ENTER_PASSWORD
}currentState;

/***************************************************************************
 *                          Functions prototype
 *****************************************************************************/

void APP_receivePassword(uint8* pass);
void APP_sendPassword(uint8* pass);
void APP_readPassword_EEPROM(void);
void APP_writePassword_EEPROM(void);
void APP_checkPasswords(uint8* pass1,uint8* pass2);
void APP_gateControl(void);
void APP_errorControl(void);

/***************************************************************************
 *                               APPLICATION
 *****************************************************************************/

int main(void){

	SREG_R.bit.I_bit = 1;

	/* Variable containing  open door option or change password option */
	uint8 option;

	/* Number of consecutive times user enters wrong password */
	uint8 wrong_consecutive=0;

	UART_init(&g_UART_configurations);
	BUZZER_init();
	EEPROM_init();
	DCmotor_init();

	g_TIMER1_configurations.mode = COMPARE;
	g_TIMER1_configurations.prescaler = FACTOR1024;
	g_TIMER1_configurations.compare_value = 23500; /* 3 SECONDS */
	g_TIMER1_configurations.initial_value = 0;

	/* Go to first state */
	currentState = CREATE_PASSWORD;

	while(1){

		switch(currentState)
		{
		case CREATE_PASSWORD:

			APP_receivePassword(g_password1);

			APP_receivePassword(g_password2);

			/* Check if the password matching */
			APP_checkPasswords(g_password1,g_password2);
			/*
			 *  If the two passwords matched go to next state and save either
			 *  one to the EEPROM
			 *  else : repeat CREATE_PASSWORD state
			 */
			if(matching == 1)
			{
				UART_sendByte(MAIN_OPTIONS);
				currentState = MAIN_OPTIONS;

				APP_writePassword_EEPROM();
			}
			else
			{
				UART_sendByte(CREATE_PASSWORD);
				currentState = CREATE_PASSWORD;
			}

			break;

		case MAIN_OPTIONS:

			/* Receive the user's option */
			option = UART_receiveByte();

			currentState = ENTER_PASSWORD;

			break;

		case ENTER_PASSWORD:

			if(option == '+')
			{
				APP_receivePassword(g_enteredPassword);

				APP_readPassword_EEPROM();

				APP_checkPasswords(g_enteredPassword,g_savedPassword);

				/*
				 * if the entered password matches with the saved password in
				 * EEPROM the go to OPEN_DOOR state and clear the wrong_consecutive
				 *
				 * if it doesn't match then increment
				 * wrong-consecutive and check if it was the third time
				 * to go to error state
				 *
				 * */
				if(matching == 1)
				{
					UART_sendByte(OPEN_DOOR);
					currentState = OPEN_DOOR;
					wrong_consecutive = 0;
				}
				else
				{
					wrong_consecutive++;
					if(wrong_consecutive == 3)
					{
						UART_sendByte(WRONG_PASSWORD);
						currentState = WRONG_PASSWORD;
					}
					else
					{
						UART_sendByte(ENTER_PASSWORD);
						currentState = ENTER_PASSWORD;
					}
				}
			}
			else if(option == '-')
			{
				APP_receivePassword(g_enteredPassword);

				APP_readPassword_EEPROM();

				APP_checkPasswords(g_enteredPassword,g_savedPassword);
				/*
				 * if the entered password matches with the saved password in
				 * EEPROM the go to CHANGE_PASSWORD state and clear the wrong_consecutive
				 *
				 * if it doesn't match then increment
				 * wrong-consecutive and check if it was the third time
				 * to go to error state
				 *
				 * */
				if(matching == 1)
				{
					currentState = CREATE_PASSWORD;
					UART_sendByte(CREATE_PASSWORD);
					wrong_consecutive = 0;
				}
				else
				{
					wrong_consecutive++;
					if(wrong_consecutive == 3)
					{
						UART_sendByte(WRONG_PASSWORD);
						currentState = WRONG_PASSWORD;
					}
					else
					{
						UART_sendByte(ENTER_PASSWORD);
						currentState = ENTER_PASSWORD;
					}
				}
			}
			break;

		case OPEN_DOOR:

			TIMER1_setCallBack(APP_gateControl);
			DCmotor_rotate(CW,100);
			TIMER1_init(&g_TIMER1_configurations);

			/* Wait for timer to finish door processing in Main options for next state */
			currentState = MAIN_OPTIONS;
			break;

		case WRONG_PASSWORD:

			BUZZER_on();
			TIMER1_setCallBack(APP_errorControl);
			g_TIMER1_configurations.compare_value = 47000; /* 6 SECONDS */
			TIMER1_init(&g_TIMER1_configurations);

			/* Wait for timer to finish error processing in Main options for next state */
			currentState = MAIN_OPTIONS;

			break;
		}
	}
}

/***************************************************************************
 *                           Functions definition
 ***************************************************************************/
void APP_receivePassword(uint8* pass){

	/*
	 * Receive password
	 */
	for(i=0;i<5;i++){
		pass[i] = UART_receiveByte();
	}
}


void APP_sendPassword(uint8* pass){

	/*
	 * Send the password
	 */
	for(i=0;i<5;i++){
		UART_sendByte(pass[i]);
	}
}

/* Function to read the saved password from EEPROM */
void APP_readPassword_EEPROM(void){

	for(i=0;i<5;i++){
		EEPROM_readByte((0x0017 + i),&g_savedPassword[i]);
		_delay_ms(10);
	}
}

/* Function to save password in the EEPROM */
void APP_writePassword_EEPROM(void){

	for(i=0;i<5;i++){
		EEPROM_writeByte((0x0017 + i),g_password1[i]);
		_delay_ms(10);
	}
}

/* Function to check the two passed passwords */
void APP_checkPasswords(uint8* pass1,uint8* pass2){

	matching = 1;

	/* Check if two passwords matching */
	for(i=0;i<5;i++){
		if(pass1[i] != pass2[i]){
			matching = 0;
			break;
		}
	}
}


void APP_gateControl(void){

	tick++; /* Every tick means 3 seconds has passed */

	if(tick == 5) /* 15 seconds passed */
	{
		DCmotor_rotate(STOP_MOTOR,0);
	}
	else if(tick == 6) /* 18 seconds passed */
	{
		DCmotor_rotate(A_CW,100);
	}
	else if(tick == 11) /* After another 15 seconds */
	{
		DCmotor_rotate(STOP_MOTOR,0);
		TIMER1_deInit();
		tick = 0;
	}
}

void APP_errorControl(void){

	tick++; /* Every tick means 6 seconds has passed */


	if(tick == 10) /* 60 seconds passed */
	{
		BUZZER_off();
		g_TIMER1_configurations.compare_value = 23500; /* 3 SECONDS again */
		TIMER1_deInit();
		tick = 0;
	}
}
