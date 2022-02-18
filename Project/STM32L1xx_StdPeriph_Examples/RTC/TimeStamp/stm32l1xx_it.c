/**
  ******************************************************************************
  * @file    RTC/TimeStamp/stm32l1xx_it.c 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    31-December-2010
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and peripherals
  *          interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2010 STMicroelectronics</center></h2>
  ******************************************************************************  
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32l1xx_it.h"
#include "stm32_eval.h"

/** @addtogroup STM32L1xx_StdPeriph_Examples
  * @{
  */

/** @addtogroup RTC_TimeStamp
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern __IO uint32_t DisplayTimeDate;
extern __IO uint32_t DisplayTimeDateStamp;

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
  {
  }
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
  {
  }
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
  {
  }
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
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSV_Handler exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}

/******************************************************************************/
/*            STM32L1xx Peripherals Interrupt Handlers                        */
/******************************************************************************/
/**
  * @brief  This function handles External line 0 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI0_IRQHandler(void)
{
  /* Clear the TimeStamp registers */
  if(EXTI_GetITStatus(KEY_BUTTON_EXTI_LINE) != RESET)
  {
    /* Turn LED1 ON and LED2 OFF */
    STM_EVAL_LEDOn(LED1);
    STM_EVAL_LEDOff(LED2);

    /* Clear The TSF Flag (Clear TimeStamp Registers) */
    RTC_ClearFlag(RTC_FLAG_TSF);
        
    /* Clear the Key Button EXTI line pending bit */
    EXTI_ClearITPendingBit(KEY_BUTTON_EXTI_LINE);  
  }
}
 
/**
  * @brief  This function handles External lines 9 to 5 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI9_5_IRQHandler(void)
{
  /* TimeStamp event detected */
  if(EXTI_GetITStatus(SEL_BUTTON_EXTI_LINE) != RESET)
  {
    /* Turn LED1 OFF and LED2 ON */
    STM_EVAL_LEDOn(LED2);
    STM_EVAL_LEDOff(LED1);
        
    /* Clear the SEL Button EXTI line pending bit */
    EXTI_ClearITPendingBit(SEL_BUTTON_EXTI_LINE);
  }
  
  /* To display Time (Current or TimeStamp) */
  if(EXTI_GetITStatus(UP_BUTTON_EXTI_LINE) != RESET)
  {
    /* Turn the LED3 OFF */
    STM_EVAL_LEDOff(LED3);

    /* Clear the UP Button EXTI line pending bit */
    EXTI_ClearITPendingBit(UP_BUTTON_EXTI_LINE);
    DisplayTimeDate = 0;
  } 
}

/**
  * @brief  This function handles External lines 15 to 10 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI15_10_IRQHandler(void)
{  
  /* To display Current RTC Time and Date Calendar */
  if(EXTI_GetITStatus(LEFT_BUTTON_EXTI_LINE) != RESET)
  {
    /* Turn LED4 ON */
    STM_EVAL_LEDOn(LED4);
    
    /* Clear the LEFT Button EXTI line pending bit */
    EXTI_ClearITPendingBit(LEFT_BUTTON_EXTI_LINE); 
    
    DisplayTimeDateStamp = 0;	
  }
  
  /* To display TimeStamp RTC Time and Date Calendar */
  if(EXTI_GetITStatus(RIGHT_BUTTON_EXTI_LINE) != RESET)
  {
    /* Turn LED4 OFF */
    STM_EVAL_LEDOff(LED4);

    /* Clear the RIGHT Button EXTI line pending bit */
    EXTI_ClearITPendingBit(RIGHT_BUTTON_EXTI_LINE); 
    
    DisplayTimeDateStamp = 1;
  }
  
  /* To display Date (Current or TimeStamp) */
  if(EXTI_GetITStatus(DOWN_BUTTON_EXTI_LINE) != RESET)
  {
    /* Turn LED1 ON */
    STM_EVAL_LEDOn(LED3);

    /* Clear the DOWN Button EXTI line pending bit */
    EXTI_ClearITPendingBit(DOWN_BUTTON_EXTI_LINE); 
    
    DisplayTimeDate = 1;
  }
}

/******************************************************************************/
/*                 STM32L1xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32l1xx_md.s).                                            */
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

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
