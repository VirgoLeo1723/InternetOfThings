/*
 * urart.c
 *
 *  Created on: Dec 13, 2022
 *      Author: htn23
 */


#include "urart.h"

int comm_adc = 0;
int comm_control = 0;
int status = 0;


char str[50];
uint8_t buffer[MAX_BUFFER_SIZE];
uint8_t index_buffer = 0;
uint8_t buffer_flag = 0;

// Urart.c
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	if (huart->Instance == USART2){
		//HAL_GPIO_TogglePin(LED_G_GPIO_Port, LED_G_Pin);
		buffer[index_buffer] = temp;
		index_buffer = (index_buffer + 1) % MAX_BUFFER_SIZE;
		buffer_flag = 1;
		HAL_UART_Receive_IT(&huart2, &temp, 1);
	}
}
void command_parser_fsm(void){
	int i = 0;
	int char_begin = 0;

	for (i=0; i< index_buffer; i++){

		//special signal detect
		if (buffer[i]=='$')
			reset_buffer();
		if (buffer[i]=='!') {
			//HAL_GPIO_TogglePin(LED_G_GPIO_Port, LED_G_Pin);
			char_begin = 1;
		}
		if (buffer[i]=='*') {
			//HAL_GPIO_TogglePin(LED_G_GPIO_Port, LED_G_Pin);
			char_begin = 2;
		}

		//signal to send adc
		if (char_begin == 1){
				if (buffer[i+1]=='R' && buffer[i+2]=='S' && buffer[i+3]=='T' && buffer[i+4]=='#'){
					comm_adc = 1;
					reset_buffer();
					//HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
				}
				if (buffer[i+1]=='O' && buffer[i+2]=='K' && buffer[i+3]=='#'){
					comm_adc = 2;
					reset_buffer();
					//HAL_GPIO_TogglePin(LED_R_GPIO_Port, LED_R_Pin);
				}
		}

		//signal to control led
		if (char_begin == 2){
			if (buffer[i+1]=='L' && buffer[i+2]=='E' && buffer[i+3]=='D' && buffer[i+4]=='1' && buffer[i+5]==':' && buffer[i+6]=='0' && buffer[i+7]=='/'){
				comm_control = 3;
				reset_buffer();
			}
			if (buffer[i+1]=='L' && buffer[i+2]=='E' && buffer[i+3]=='D' && buffer[i+4]=='1' && buffer[i+5]==':' && buffer[i+6]=='1' && buffer[i+7]=='/'){
				comm_control = 4;
				reset_buffer();
			}
			if (buffer[i+1]=='L' && buffer[i+2]=='E' && buffer[i+3]=='D' && buffer[i+4]=='2' && buffer[i+5]==':' && buffer[i+6]=='0' && buffer[i+7]=='/'){
				comm_control = 5;
				reset_buffer();

			}
			if (buffer[i+1]=='L' && buffer[i+2]=='E' && buffer[i+3]=='D' && buffer[i+4]=='2' && buffer[i+5]==':' && buffer[i+6]=='1' && buffer[i+7]=='/'){
				comm_control = 6;
				reset_buffer();

			}
		}

	}

}
void uart_communiation_fsm(){
	// Control ADCs
	if (status == 0){
		if (comm_adc == 1) status = 1;
		ADC_Read();
	}
	else if (status == 1){
			status = 2;
			HAL_UART_Transmit(&huart2, (uint8_t *)str, sprintf(str, "*LIGHT:%d/*TEMP:%d/\r\n", ADC_val, ADC_val1), 1000);
			timer_flag = 0;
			timerSet(100);
	}
	else if (status == 2){
		if (isTimeout()){
			status = 1;
		}
		if (comm_adc == 2) status = 0;

	}

	// Control LEDs
	if (comm_control == 3){
		HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, 1);
	} else if (comm_control == 4){
		HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, 0);
	} else if (comm_control == 5){
		HAL_GPIO_WritePin(LED_GPIO_Port, LED_G_Pin, 1);
	} else if (comm_control == 6){
		HAL_GPIO_WritePin(LED_GPIO_Port, LED_G_Pin, 0);
	}


}
void reset_buffer(){
	int i;
	for (i=0; i<MAX_BUFFER_SIZE; i++){
		buffer[i] = 0;
		index_buffer = 0;
	}
}

int isFlag(){
	if (buffer_flag == 1){
		buffer_flag = 0;
		return 1;
	} else return 0;
}

