/**
  ******************************************************************************
  * @file    TIM/InputCaptureRouting/stm32l1xx_it.c 
  * @author  MCD Application Team
  * @version V1.2.2
  * @date    17-November-2021
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2015 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32l1xx_it.h"

/** @addtogroup STM32L1xx_StdPeriph_Examples
  * @{
  */

/** @addtogroup TIM_InputCaptureRouting
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint16_t IC4ReadValue1 = 0, IC4ReadValue2 = 0;
uint16_t CaptureNumber = 0;
uint32_t Capture = 0;
uint32_t TIM4Freq = 0;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{}

/**
  * @brief  This function handles PendSV_Handler exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{}

/******************************************************************************/
/*            STM32L1xx Peripherals Interrupt Handlers                        */
/******************************************************************************/
/**
  * @brief  This function handles TIM4 global interrupt request.
  * @param  None
  * @retval None
  */
void TIM4_IRQHandler(void)
{ 
  if (TIM_GetITStatus(TIM4, TIM_IT_CC2) != RESET)
  {
    /* Clear TIM4 Capture compare interrupt pending bit */
    TIM_ClearITPendingBit(TIM4, TIM_IT_CC2);

    if(CaptureNumber == 0)
    {
      /* Get the Input Capture value */
      IC4ReadValue1 = TIM_GetCapture2(TIM4);
      CaptureNumber = 1;
    }
    else if(CaptureNumber == 1)
    {
      /* Get the Input Capture value */
      IC4ReadValue2 = TIM_GetCapture2(TIM4); 
      
      /* Capture computation */
      if (IC4ReadValue2 > IC4ReadValue1)
      {
        Capture = (IC4ReadValue2 - IC4ReadValue1) - 1; 
      }
      else if (IC4ReadValue2 < IC4ReadValue1)
      {
        Capture = ((0xFFFF - IC4ReadValue1) + IC4ReadValue2) - 1; 
      }
      else
      {
        Capture = 0;
      }
      /* Frequency computation */ 
      TIM4Freq = (uint32_t) SystemCoreClock / Capture;
      CaptureNumber = 0;
    }
  }
}

/******************************************************************************/
/*                 STM32L1xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32l1xx_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 

/**
  * @}
  */ 

