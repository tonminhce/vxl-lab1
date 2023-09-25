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
 TIM_HandleTypeDef htim2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int const HOUR = 12;
int const MINUTE = 60;
int const SECOND = 60;

int currentHour = 0;
int currentMinute = 0;
int currentSecond = 0;

char initialTest = 1;
int testLed = 0;
int timerCount = 0;

uint16_t LED_PIN[12] = {RED_12_Pin, RED_1_Pin, RED_2_Pin, RED_3_Pin, RED_4_Pin, RED_5_Pin, RED_6_Pin, RED_7_Pin, RED_8_Pin, RED_9_Pin, RED_10_Pin, RED_11_Pin};

void setNumberOnClock(int num){
	HAL_GPIO_WritePin(GPIOA, LED_PIN[num],0);
}

void clearNumberOnClock(int num){
	HAL_GPIO_WritePin(GPIOA, LED_PIN[num],1);
}

void clearAllClock(){
	for (int i = 0; i < 12; i++){
		clearNumberOnClock(i);
	}
}

int hour2clock(int n){
	return n;
}

int minute2clock(int n){
//	float result = (float)(n)/5.0;

//	if (result - (int)result >= 0.5)
//		return (int)(result)+1;
//	else
//		return (int)result;
	return n/5;
}

int second2clock(int n){
//	float result = (float)(n)/5.0;
//
//	if (result - (int)result >= 0.5)
//		return (int)(result)+1;
//	else
//		return (int)result;

	return n/5;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	// LED test
	if (initialTest == 1){
		if (testLed >= 12){
			initialTest = 0;
		}
		else{
			timerCount++;

			if(timerCount >= 10){
				timerCount = 0;
				HAL_GPIO_WritePin(GPIOA, LED_PIN[testLed], 0);

				for (int i = 0; i < 12; i++){
					if (i != testLed)
						HAL_GPIO_WritePin(GPIOA, LED_PIN[i], 1);
				}
				timerCount = 0;
				testLed++;
			}
		}
	}
	else{

		// Clock simulation
		int hourClock = hour2clock(currentHour);
		int minuteClock = minute2clock(currentMinute);
		int secondClock = second2clock(currentSecond);

		clearAllClock();

		setNumberOnClock(secondClock);
		setNumberOnClock(minuteClock);
		setNumberOnClock(hourClock);

		currentSecond++;

		if (currentSecond >= 60){
			currentSecond = 0;
			currentMinute++;
		}

		if (currentMinute >= 60){
			currentMinute = 0;
			currentHour++;
		}

		if (currentHour >= 12){
			currentHour = 0;
			currentSecond = 0;
			currentMinute = 0;
		}
	}
}
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
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT(&htim2);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI_DIV2;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM2 Initialization Function
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
  htim2.Init.Period = 99;
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
  HAL_GPIO_WritePin(GPIOA, RED_1_Pin|RED_2_Pin|RED_3_Pin|RED_4_Pin
                          |RED_5_Pin|RED_6_Pin|RED_7_Pin|RED_8_Pin
                          |RED_9_Pin|RED_10_Pin|RED_11_Pin|RED_12_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : RED_1_Pin RED_2_Pin RED_3_Pin RED_4_Pin
                           RED_5_Pin RED_6_Pin RED_7_Pin RED_8_Pin
                           RED_9_Pin RED_10_Pin RED_11_Pin RED_12_Pin */
  GPIO_InitStruct.Pin = RED_1_Pin|RED_2_Pin|RED_3_Pin|RED_4_Pin
                          |RED_5_Pin|RED_6_Pin|RED_7_Pin|RED_8_Pin
                          |RED_9_Pin|RED_10_Pin|RED_11_Pin|RED_12_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

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
