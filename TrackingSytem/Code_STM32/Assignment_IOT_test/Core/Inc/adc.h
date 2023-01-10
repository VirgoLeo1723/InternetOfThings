/*
 * adc.h
 *
 *  Created on: Dec 13, 2022
 *      Author: htn23
 */

#ifndef INC_ADC_H_
#define INC_ADC_H_

#include "main.h"
#include "global.h"
#include "timer.h"

extern int ADC_val;
extern int ADC_val1;

void ADC_Select_CH0(void);
void ADC_Select_CH1(void);
void ADC_Read(void);

#endif /* INC_ADC_H_ */
