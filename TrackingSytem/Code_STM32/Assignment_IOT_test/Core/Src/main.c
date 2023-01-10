/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "global.h"
#include "timer.h"
#include "urart.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
//ADC_HandleTypeDef hadc1;
//TIM_HandleTypeDef htim2;
//UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
//#define MAX_BUFFER_SIZE 30
//int ADC_val;
//int ADC_val1;

//char str[50];
//uint8_t temp = 0;
//uint8_t buffer[MAX_BUFFER_SIZE];
//uint8_t index_buffer = 0;
//uint8_t buffer_flag = 0;

//int comm_adc = 0;
//int comm_control = 0;
//
//int status = 0;

//int count = 0;
//int timer_flag = 0;

char *init_char = (char*)"!RST#";
char *send_char = (char*)"!OK#";
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ADC1_Init(void);
static void MX_TIM2_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */
//void ADC_Select_CH0(void);
//void ADC_Select_CH1(void);
//void ADC_Read(void);

//void reset_buffer();
//void command_parser_fsm(void);
//void uart_communiation_fsm();

//void timerRun(void);
//void timerSet(int);
//int isTimeout();
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_ADC1_Init();
  MX_TIM2_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
  HAL_UART_Receive_IT(&huart2, &temp, 1);
  HAL_TIM_Base_Start_IT(&htim2);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, 1);
  while (1)
  {
	if (isFlag()){
		command_parser_fsm();
	}
	uart_communiation_fsm();

	  /* USER CODE END WHILE */

	  /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV2;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 7999;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 9;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  //ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Common config
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ScanConvMode = ADC_SCAN_ENABLE;
  hadc1.Init.ContinuousConvMode = ENABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
//  sConfig.Channel = ADC_CHANNEL_0;
//  sConfig.Rank = ADC_REGULAR_RANK_1;
//  sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
//  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
//  {
//    Error_Handler();
//  }
//
//  /** Configure Regular Channel
//  */
//  sConfig.Channel = ADC_CHANNEL_1;
//  sConfig.Rank = ADC_REGULAR_RANK_2;
//  sConfig.SamplingTime = ADC_SAMPLETIME_7CYCLES_5;
//  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
//  {
//    Error_Handler();
//  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 9600;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LED_Pin|LED_R_Pin|LED_Y_Pin|LED_G_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : LED_Pin LED_R_Pin LED_Y_Pin LED_G_Pin */
  GPIO_InitStruct.Pin = LED_Pin|LED_R_Pin|LED_Y_Pin|LED_G_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

//Timer.c
//void HAL_TIM_PeriodElapsedCallback (TIM_HandleTypeDef *htim ) {
//	timerRun();
//}
//void timerRun(void){
//	if (count>0) count -= 1;
//	else timer_flag = 1;
//}
//void timerSet(int time){
//	count = time;
//}
//int isTimeout(){
//	if (timer_flag == 1){
//		timer_flag = 0;
//		return 1;
//	} else
//		return 0;
//}
// Urart.c
//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
//	if (huart->Instance == USART2){
//		//HAL_GPIO_TogglePin(LED_G_GPIO_Port, LED_G_Pin);
//		buffer[index_buffer] = temp;
//		index_buffer = (index_buffer + 1) % MAX_BUFFER_SIZE;
//		buffer_flag = 1;
//		HAL_UART_Receive_IT(&huart2, &temp, 1);
//	}
//}
//void command_parser_fsm(void){
//	int i = 0;
//	int char_begin = 0;
//
//	for (i=0; i< index_buffer; i++){
//
//		//special signal detect
//		if (buffer[i]=='$')
//			reset_buffer();
//		if (buffer[i]=='!') {
//			//HAL_GPIO_TogglePin(LED_G_GPIO_Port, LED_G_Pin);
//			char_begin = 1;
//		}
//		if (buffer[i]=='*') {
//			//HAL_GPIO_TogglePin(LED_G_GPIO_Port, LED_G_Pin);
//			char_begin = 2;
//		}
//
//		//signal to send adc
//		if (char_begin == 1){
//				if (buffer[i+1]=='R' && buffer[i+2]=='S' && buffer[i+3]=='T' && buffer[i+4]=='#'){
//					comm_adc = 1;
//					reset_buffer();
//					//HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
//				}
//				if (buffer[i+1]=='O' && buffer[i+2]=='K' && buffer[i+3]=='#'){
//					comm_adc = 2;
//					reset_buffer();
//					//HAL_GPIO_TogglePin(LED_R_GPIO_Port, LED_R_Pin);
//				}
//		}
//
//		//signal to control led
//		if (char_begin == 2){
//			if (buffer[i+1]=='L' && buffer[i+2]=='E' && buffer[i+3]=='D' && buffer[i+4]=='1' && buffer[i+5]==':' && buffer[i+6]=='0' && buffer[i+7]=='/'){
//				comm_control = 3;
//				reset_buffer();
//			}
//			if (buffer[i+1]=='L' && buffer[i+2]=='E' && buffer[i+3]=='D' && buffer[i+4]=='1' && buffer[i+5]==':' && buffer[i+6]=='1' && buffer[i+7]=='/'){
//				comm_control = 4;
//				reset_buffer();
//			}
//			if (buffer[i+1]=='L' && buffer[i+2]=='E' && buffer[i+3]=='D' && buffer[i+4]=='2' && buffer[i+5]==':' && buffer[i+6]=='0' && buffer[i+7]=='/'){
//				comm_control = 5;
//				reset_buffer();
//
//			}
//			if (buffer[i+1]=='L' && buffer[i+2]=='E' && buffer[i+3]=='D' && buffer[i+4]=='2' && buffer[i+5]==':' && buffer[i+6]=='1' && buffer[i+7]=='/'){
//				comm_control = 6;
//				reset_buffer();
//
//			}
//		}
//
//	}
//
//}
//void uart_communiation_fsm(){
//	// Control ADCs
//	if (status == 0){
//		if (comm_adc == 1) status = 1;
//	}
//	else if (status == 1){
//			status = 2;
//			ADC_Read();
//			HAL_UART_Transmit(&huart2, (uint8_t *)str, sprintf(str, "*LIGHT:%d/*TEMP:%d/\r\n", ADC_val, ADC_val1), 1000);
//			timer_flag = 0;
//			timerSet(500);
//	}
//	else if (status == 2){
//		if (isTimeout()){
//			status = 1;
//		}
//		if (comm_adc == 2) status = 0;
//
//	}
//
//	// Control LEDs
//	if (comm_control == 3){
//		HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, 1);
//	} else if (comm_control == 4){
//		HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, 0);
//	} else if (comm_control == 5){
//		HAL_GPIO_WritePin(LED_GPIO_Port, LED_G_Pin, 1);
//	} else if (comm_control == 6){
//		HAL_GPIO_WritePin(LED_GPIO_Port, LED_G_Pin, 0);
//	}
//
//
//}
//void reset_buffer(){
//	int i;
//	for (i=0; i<MAX_BUFFER_SIZE; i++){
//		buffer[i] = 0;
//		index_buffer = 0;
//	}
//}
//Adc.c
//void ADC_Select_CH0(void){
//	  ADC_ChannelConfTypeDef sConfig = {0};
//	  sConfig.Channel = ADC_CHANNEL_0;
//	  sConfig.Rank = ADC_REGULAR_RANK_1;
//	  sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
//	  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
//	  {
//	    Error_Handler();
//	  }
//}
//void ADC_Select_CH1(void){
//	  ADC_ChannelConfTypeDef sConfig = {0};
//	  sConfig.Channel = ADC_CHANNEL_1;
//	  sConfig.Rank = ADC_REGULAR_RANK_1;
//	  sConfig.SamplingTime = ADC_SAMPLETIME_7CYCLES_5;
//	  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
//	  {
//	    Error_Handler();
//	  }
//}
//void ADC_Read(void){
//	HAL_ADC_Start(&hadc1);
//	ADC_Select_CH0();
//	HAL_ADC_PollForConversion(&hadc1, 1000);
//	ADC_val = HAL_ADC_GetValue(&hadc1);
//	HAL_ADC_Stop(&hadc1);
//
//	HAL_ADC_Start(&hadc1);
//	ADC_Select_CH1();
//	HAL_ADC_PollForConversion(&hadc1, 1000);
//	ADC_val1 = HAL_ADC_GetValue(&hadc1);
//	HAL_ADC_Stop(&hadc1);
//}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
