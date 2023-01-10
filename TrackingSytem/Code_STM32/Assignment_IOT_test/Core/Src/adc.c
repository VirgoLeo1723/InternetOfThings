/*
 * adc.c
 *
 *  Created on: Dec 13, 2022
 *      Author: htn23
 */

#include "adc.h"

int ADC_val = 0;
int ADC_val1 = 0;
void ADC_Select_CH0(void){
	  ADC_ChannelConfTypeDef sConfig = {0};
	  sConfig.Channel = ADC_CHANNEL_0;
	  sConfig.Rank = ADC_REGULAR_RANK_1;
	  sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
	  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
	  {
	    Error_Handler();
	  }
}
void ADC_Select_CH1(void){
	  ADC_ChannelConfTypeDef sConfig = {0};
	  sConfig.Channel = ADC_CHANNEL_1;
	  sConfig.Rank = ADC_REGULAR_RANK_1;
	  sConfig.SamplingTime = ADC_SAMPLETIME_7CYCLES_5;
	  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
	  {
	    Error_Handler();
	  }
}
void ADC_Read(void){
	HAL_ADC_Start(&hadc1);
	ADC_Select_CH0();
	HAL_ADC_PollForConversion(&hadc1, 1000);
	ADC_val = HAL_ADC_GetValue(&hadc1);
	HAL_ADC_Stop(&hadc1);

	HAL_ADC_Start(&hadc1);
	ADC_Select_CH1();
	HAL_ADC_PollForConversion(&hadc1, 1000);
	ADC_val1 = HAL_ADC_GetValue(&hadc1);
	HAL_ADC_Stop(&hadc1);
}
