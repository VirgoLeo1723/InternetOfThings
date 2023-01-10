/*
 * urart.h
 *
 *  Created on: Dec 13, 2022
 *      Author: htn23
 */

#ifndef INC_URART_H_
#define INC_URART_H_

#include "main.h"
#include "global.h"
#include "timer.h"
#include "adc.h"

#define MAX_BUFFER_SIZE 30

extern int comm_adc;
extern int comm_control;
extern int status;

extern uint8_t buffer[MAX_BUFFER_SIZE];
extern uint8_t index_buffer;
extern uint8_t buffer_flag;

int isFlag();
void reset_buffer();
void command_parser_fsm(void);
void uart_communiation_fsm();



#endif /* INC_URART_H_ */
