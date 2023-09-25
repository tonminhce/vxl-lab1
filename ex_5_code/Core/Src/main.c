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
char status = 'r';
char status_2 = 'g';

const int redTime = 5;
const int greenTime = 4;
const int yellowTime = 1;

int isYellow = 1;

const int delayTime = redTime-greenTime-yellowTime;

int currentTime = 0;
int currentYellowTIme = 0;

int countdownTime = 10;

void lightSwitch(int light, char signal){
	if (signal == 'r'){
		if (light == 1){
			HAL_GPIO_WritePin(RED_1_GPIO_Port, RED_1_Pin, 0);
			HAL_GPIO_WritePin(YELLOW_1_GPIO_Port, YELLOW_1_Pin, 1);
			HAL_GPIO_WritePin(GREEN_1_GPIO_Port, GREEN_1_Pin, 1);
		}
		else if (light == 2){
			HAL_GPIO_WritePin(RED_2_GPIO_Port, RED_2_Pin, 0);
			HAL_GPIO_WritePin(YELLOW_2_GPIO_Port, YELLOW_2_Pin, 1);
			HAL_GPIO_WritePin(GREEN_2_GPIO_Port, GREEN_2_Pin, 1);
		}
		else if (light == 3){
			HAL_GPIO_WritePin(RED_3_GPIO_Port, RED_3_Pin, 0);
			HAL_GPIO_WritePin(YELLOW_3_GPIO_Port, YELLOW_3_Pin, 1);
			HAL_GPIO_WritePin(GREEN_3_GPIO_Port, GREEN_3_Pin, 1);
		}
		else if (light == 4){
			HAL_GPIO_WritePin(RED_4_GPIO_Port, RED_4_Pin, 0);
			HAL_GPIO_WritePin(YELLOW_4_GPIO_Port, YELLOW_4_Pin, 1);
			HAL_GPIO_WritePin(GREEN_4_GPIO_Port, GREEN_4_Pin, 1);
		}
	}
	else if (signal == 'g'){
		if (light == 1){
			HAL_GPIO_WritePin(RED_1_GPIO_Port, RED_1_Pin, 1);
			HAL_GPIO_WritePin(YELLOW_1_GPIO_Port, YELLOW_1_Pin, 1);
			HAL_GPIO_WritePin(GREEN_1_GPIO_Port, GREEN_1_Pin, 0);
		}
		else if (light == 2){
			HAL_GPIO_WritePin(RED_2_GPIO_Port, RED_2_Pin, 1);
			HAL_GPIO_WritePin(YELLOW_2_GPIO_Port, YELLOW_2_Pin, 1);
			HAL_GPIO_WritePin(GREEN_2_GPIO_Port, GREEN_2_Pin, 0);
		}
		else if (light == 3){
			HAL_GPIO_WritePin(RED_3_GPIO_Port, RED_3_Pin, 1);
			HAL_GPIO_WritePin(YELLOW_3_GPIO_Port, YELLOW_3_Pin, 1);
			HAL_GPIO_WritePin(GREEN_3_GPIO_Port, GREEN_3_Pin, 0);
		}
		else if (light == 4){
			HAL_GPIO_WritePin(RED_4_GPIO_Port, RED_4_Pin, 1);
			HAL_GPIO_WritePin(YELLOW_4_GPIO_Port, YELLOW_4_Pin, 1);
			HAL_GPIO_WritePin(GREEN_4_GPIO_Port, GREEN_4_Pin, 0);
		}
	}
	else if(signal == 'y'){
		if (light == 1){
			HAL_GPIO_WritePin(RED_1_GPIO_Port, RED_1_Pin, 1);
			HAL_GPIO_WritePin(YELLOW_1_GPIO_Port, YELLOW_1_Pin, 0);
			HAL_GPIO_WritePin(GREEN_1_GPIO_Port, GREEN_1_Pin, 1);
		}
		else if (light == 2){
			HAL_GPIO_WritePin(RED_2_GPIO_Port, RED_2_Pin, 1);
			HAL_GPIO_WritePin(YELLOW_2_GPIO_Port, YELLOW_2_Pin, 0);
			HAL_GPIO_WritePin(GREEN_2_GPIO_Port, GREEN_2_Pin, 1);
		}
		else if (light == 3){
			HAL_GPIO_WritePin(RED_3_GPIO_Port, RED_3_Pin, 1);
			HAL_GPIO_WritePin(YELLOW_3_GPIO_Port, YELLOW_3_Pin, 0);
			HAL_GPIO_WritePin(GREEN_3_GPIO_Port, GREEN_3_Pin, 1);
		}
		else if (light == 4){
			HAL_GPIO_WritePin(RED_4_GPIO_Port, RED_4_Pin, 1);
			HAL_GPIO_WritePin(YELLOW_4_GPIO_Port, YELLOW_4_Pin, 0);
			HAL_GPIO_WritePin(GREEN_4_GPIO_Port, GREEN_4_Pin, 1);
		}
	}
}


void turnOnB(int *arr, int n){
  char state = 0;
  for (int i = 0; i < n; i++){
	  switch(arr[i]){
		  case 0:
			  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, state);
			  break;
		  case 1:
			  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, state);
			  break;
		  case 2:
			  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, state);
			  break;
		  case 3:
			  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, state);
			  break;
		  case 4:
			  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, state);
			  break;
		  case 5:
			  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, state);
			  break;
		  case 6:
			  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, state);
			  break;

		  default:
			  break;
	  }
  }
}


void turnOffB(int *arr, int n){
  char state = 1;
  for (int i = 0; i < n; i++){
	  switch(arr[i]){
		  case 0:
			  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, state);
			  break;
		  case 1:
			  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, state);
			  break;
		  case 2:
			  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, state);
			  break;
		  case 3:
			  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, state);
			  break;
		  case 4:
			  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, state);
			  break;
		  case 5:
			  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, state);
			  break;
		  case 6:
			  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, state);
			  break;

		  default:
			  break;
	  }
  }
}

void segmentLed(int n){
  int *arrOn;
  int *arrOff;
  int len = 0;
  int lenOff = 0;


  if(n==0){
	len = 6;
	int tempOn[7] = {1,2,3,4,5,6};
	int tempOff[7] = {0};
	lenOff = 1;
	arrOff = tempOff;
	arrOn = tempOn;
  }

  else if(n==1){
	len = 2;
	int tempOn[7] = {5,4};
	int tempOff[7] = {1,2,3,6,0};
	lenOff = 5;
	arrOff = tempOff;
	arrOn = tempOn;
  }

  else if(n==2){
	int tempOn[7] = {6,5,0,2,3};
	int tempOff[7] = {1,4};
	lenOff = 2;
	arrOff = tempOff;
	len = 5;
	arrOn = tempOn;
  }

  else if(n==3){
	int tempOn[7] = {6,5,0,4,3};
	int tempOff[7] = {1,2};
	lenOff = 2;
	arrOff = tempOff;
	len = 5;
	arrOn = tempOn;
  }

  else if(n==4){
	int tempOn[7] = {1,0,5,4};
	int tempOff[7] = {2,3,6};
	lenOff = 3;
	arrOff = tempOff;
	len = 4;
	arrOn = tempOn;
  }

  else if(n==5){
	int tempOn[7] = {6,1,0,4,3};
	int tempOff[7] = {2,5};
	lenOff = 2;
	arrOff = tempOff;
	len = 5;
	arrOn = tempOn;
  }

  else if(n==6){
	int tempOn[7] = {6,1,0,4,3,2};
	int tempOff[7] = {5};
	lenOff = 1;
	arrOff = tempOff;
	len = 6;
	arrOn = tempOn;
  }

  else if(n==7){
	int tempOn[7] = {4,5,6};
	int tempOff[7] = {0,1,2,3};
	lenOff = 4;
	arrOff = tempOff;
	len = 3;
	arrOn = tempOn;
  }

  else if(n==8){
	int tempOn[7] = {0,1,2,3,4,5,6};
	int tempOff[7] = {};
	lenOff = 0;
	arrOff = tempOff;
	len = 7;
	arrOn = tempOn;
  }

  else if(n==9){
	int tempOn[7] = {0,1,6,5,4,3};
	int tempOff[7] = {2};
	lenOff = 1;
	arrOff = tempOff;
	len = 6;
	arrOn = tempOn;
  }

  turnOnB(arrOn, len);
  turnOffB(arrOff, lenOff);
}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	countdownTime--;

	if (status == 'r' && countdownTime - 3 < 0 && status_2 != 'y'){
		status_2 = 'y';
	}
	else if (countdownTime < 0){
		if (status == 'r'){
			status = 'g';
			status_2 = 'r';
		}
		else if (status == 'g'){
			status = 'y';
			status_2 = 'r';
		}
		else if (status == 'y'){
			status = 'r';
			status_2 = 'g';
		}

		// SET COUNTDOWN TIME
		if (status == 'r'){
			countdownTime = 9;
		}
		else if (status == 'g'){
			countdownTime = 7;
		}
		else{
			countdownTime = 2;
		}
	}

	segmentLed(countdownTime);

	lightSwitch(1, status);
	lightSwitch(3, status);
	lightSwitch(2, status_2);
	lightSwitch(4, status_2);
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
  status = 'r';
  status_2 = 'g';
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
  htim2.Init.Period = 999;
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
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, RED_1_Pin|YELLOW_1_Pin|GREEN_1_Pin|RED_2_Pin
                          |YELLOW_2_Pin|GREEN_2_Pin|RED_3_Pin|YELLOW_3_Pin
                          |GREEN_3_Pin|RED_4_Pin|YELLOW_4_Pin|GREEN_4_Pin
                          |GPIO_PIN_13, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6, GPIO_PIN_RESET);

  /*Configure GPIO pins : RED_1_Pin YELLOW_1_Pin GREEN_1_Pin RED_2_Pin
                           YELLOW_2_Pin GREEN_2_Pin RED_3_Pin YELLOW_3_Pin
                           GREEN_3_Pin RED_4_Pin YELLOW_4_Pin GREEN_4_Pin
                           PA13 */
  GPIO_InitStruct.Pin = RED_1_Pin|YELLOW_1_Pin|GREEN_1_Pin|RED_2_Pin
                          |YELLOW_2_Pin|GREEN_2_Pin|RED_3_Pin|YELLOW_3_Pin
                          |GREEN_3_Pin|RED_4_Pin|YELLOW_4_Pin|GREEN_4_Pin
                          |GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 PB1 PB2 PB3
                           PB4 PB5 PB6 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

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
