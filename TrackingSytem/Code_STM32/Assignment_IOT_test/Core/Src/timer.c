/*
 * timer.c
 *
 *  Created on: Dec 13, 2022
 *      Author: htn23
 */


#include "timer.h"

int count = 0;
int timer_flag = 0;

void HAL_TIM_PeriodElapsedCallback (TIM_HandleTypeDef *htim ) {
	timerRun();
}
void timerRun(void){
	if (count>0) count -= 1;
	else timer_flag = 1;
}
void timerSet(int time){
	count = time;
}
int isTimeout(){
	if (timer_flag == 1){
		timer_flag = 0;
		return 1;
	} else
		return 0;
}
