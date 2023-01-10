/*
 * timer.h
 *
 *  Created on: Dec 13, 2022
 *      Author: htn23
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_

#include "main.h"
#include "global.h"

extern int count;
extern int timer_flag;

void timerRun(void);
void timerSet(int);
int isTimeout();

#endif /* INC_TIMER_H_ */
