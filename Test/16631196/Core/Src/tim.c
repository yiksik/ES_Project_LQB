/**
  ******************************************************************************
  * @file    tim.c
  * @brief   This file provides code for the configuration
  *          of the TIM instances.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "tim.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

TIM_HandleTypeDef htim2;
DMA_HandleTypeDef hdma_tim2_ch1;
DMA_HandleTypeDef hdma_tim2_ch2;
DMA_HandleTypeDef hdma_tim2_ch3;
DMA_HandleTypeDef hdma_tim2_ch4;

/* TIM2 init function */
void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_IC_InitTypeDef sConfigIC = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 80-1;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 65535;
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
  if (HAL_TIM_IC_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_FALLING;
  sConfigIC.ICSelection = TIM_ICSELECTION_INDIRECTTI;
  sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
  sConfigIC.ICFilter = 0;
  if (HAL_TIM_IC_ConfigChannel(&htim2, &sConfigIC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
  sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
  if (HAL_TIM_IC_ConfigChannel(&htim2, &sConfigIC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_IC_ConfigChannel(&htim2, &sConfigIC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_FALLING;
  sConfigIC.ICSelection = TIM_ICSELECTION_INDIRECTTI;
  if (HAL_TIM_IC_ConfigChannel(&htim2, &sConfigIC, TIM_CHANNEL_4) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* tim_baseHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(tim_baseHandle->Instance==TIM2)
  {
  /* USER CODE BEGIN TIM2_MspInit 0 */

  /* USER CODE END TIM2_MspInit 0 */
    /* TIM2 clock enable */
    __HAL_RCC_TIM2_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**TIM2 GPIO Configuration
    PA1     ------> TIM2_CH2
    PA2     ------> TIM2_CH3
    */
    GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_2;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF1_TIM2;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* TIM2 DMA Init */
    /* TIM2_CH1 Init */
    hdma_tim2_ch1.Instance = DMA1_Channel1;
    hdma_tim2_ch1.Init.Request = DMA_REQUEST_TIM2_CH1;
    hdma_tim2_ch1.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_tim2_ch1.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_tim2_ch1.Init.MemInc = DMA_MINC_ENABLE;
    hdma_tim2_ch1.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
    hdma_tim2_ch1.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
    hdma_tim2_ch1.Init.Mode = DMA_NORMAL;
    hdma_tim2_ch1.Init.Priority = DMA_PRIORITY_LOW;
    if (HAL_DMA_Init(&hdma_tim2_ch1) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(tim_baseHandle,hdma[TIM_DMA_ID_CC1],hdma_tim2_ch1);

    /* TIM2_CH2 Init */
    hdma_tim2_ch2.Instance = DMA1_Channel2;
    hdma_tim2_ch2.Init.Request = DMA_REQUEST_TIM2_CH2;
    hdma_tim2_ch2.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_tim2_ch2.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_tim2_ch2.Init.MemInc = DMA_MINC_ENABLE;
    hdma_tim2_ch2.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
    hdma_tim2_ch2.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
    hdma_tim2_ch2.Init.Mode = DMA_NORMAL;
    hdma_tim2_ch2.Init.Priority = DMA_PRIORITY_LOW;
    if (HAL_DMA_Init(&hdma_tim2_ch2) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(tim_baseHandle,hdma[TIM_DMA_ID_CC2],hdma_tim2_ch2);

    /* TIM2_CH3 Init */
    hdma_tim2_ch3.Instance = DMA1_Channel4;
    hdma_tim2_ch3.Init.Request = DMA_REQUEST_TIM2_CH3;
    hdma_tim2_ch3.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_tim2_ch3.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_tim2_ch3.Init.MemInc = DMA_MINC_ENABLE;
    hdma_tim2_ch3.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
    hdma_tim2_ch3.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
    hdma_tim2_ch3.Init.Mode = DMA_NORMAL;
    hdma_tim2_ch3.Init.Priority = DMA_PRIORITY_LOW;
    if (HAL_DMA_Init(&hdma_tim2_ch3) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(tim_baseHandle,hdma[TIM_DMA_ID_CC3],hdma_tim2_ch3);

    /* TIM2_CH4 Init */
    hdma_tim2_ch4.Instance = DMA1_Channel3;
    hdma_tim2_ch4.Init.Request = DMA_REQUEST_TIM2_CH4;
    hdma_tim2_ch4.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_tim2_ch4.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_tim2_ch4.Init.MemInc = DMA_MINC_ENABLE;
    hdma_tim2_ch4.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
    hdma_tim2_ch4.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
    hdma_tim2_ch4.Init.Mode = DMA_NORMAL;
    hdma_tim2_ch4.Init.Priority = DMA_PRIORITY_LOW;
    if (HAL_DMA_Init(&hdma_tim2_ch4) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(tim_baseHandle,hdma[TIM_DMA_ID_CC4],hdma_tim2_ch4);

  /* USER CODE BEGIN TIM2_MspInit 1 */

  /* USER CODE END TIM2_MspInit 1 */
  }
}

void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* tim_baseHandle)
{

  if(tim_baseHandle->Instance==TIM2)
  {
  /* USER CODE BEGIN TIM2_MspDeInit 0 */

  /* USER CODE END TIM2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM2_CLK_DISABLE();

    /**TIM2 GPIO Configuration
    PA1     ------> TIM2_CH2
    PA2     ------> TIM2_CH3
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_1|GPIO_PIN_2);

    /* TIM2 DMA DeInit */
    HAL_DMA_DeInit(tim_baseHandle->hdma[TIM_DMA_ID_CC1]);
    HAL_DMA_DeInit(tim_baseHandle->hdma[TIM_DMA_ID_CC2]);
    HAL_DMA_DeInit(tim_baseHandle->hdma[TIM_DMA_ID_CC3]);
    HAL_DMA_DeInit(tim_baseHandle->hdma[TIM_DMA_ID_CC4]);
  /* USER CODE BEGIN TIM2_MspDeInit 1 */

  /* USER CODE END TIM2_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
