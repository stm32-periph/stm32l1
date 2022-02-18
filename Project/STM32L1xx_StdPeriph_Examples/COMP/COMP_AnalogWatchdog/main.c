/**
  ******************************************************************************
  * @file    COMP/COMP_AnalogWatchdog/main.c 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    31-December-2010
  * @brief   Main program body.
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
#include "main.h"

/** @addtogroup STM32L1xx_StdPeriph_Examples
  * @{
  */

/** @addtogroup COMP_AnalogWatchdog
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Init Structure definition */
GPIO_InitTypeDef        GPIO_InitStructure;

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
__IO uint32_t State = 0;

/* Private function prototypes -----------------------------------------------*/
void COMP_Config(void);
void STOPEntry(void);
void RestoreConfiguration(void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  /******* Initialize LEDs available on STM32L1XX-EVAL board ******************/
  STM_EVAL_LEDInit(LED1);
  STM_EVAL_LEDInit(LED2);
  STM_EVAL_LEDInit(LED3);
  STM_EVAL_LEDInit(LED4);

  /* PWR Peripheral clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);

  /* configure COMP1 and COMP2 with interrupts enabled */
  COMP_Config();

  /* Check input voltage level: within the thresholds, above the upper threshold
     or under the lower threshold */
  CheckState();

  while(1)
  {
    if (State == STATE_OVER_THRESHOLD)
    {
      /* Restore config: clock, GPIO... */
      RestoreConfiguration();

      /* Restore GPIO configuration */
      STM_EVAL_LEDInit(LED1);
      STM_EVAL_LEDInit(LED2);
      STM_EVAL_LEDInit(LED3);
      STM_EVAL_LEDInit(LED4);

      /* Turn on LD1 and LD3 and turn off LD2 and LD4 */
      STM_EVAL_LEDOn(LED1);
      STM_EVAL_LEDOff(LED2);
      STM_EVAL_LEDOn(LED3);
      STM_EVAL_LEDOff(LED4);
      
      while(State == STATE_OVER_THRESHOLD)
      {
         /* add your code here */
      }
    }
    else if (State == STATE_WITHIN_THRESHOLD)
    {
      /* Input voltage is within the thresholds: higher and lower thresholds */
      /* Enter STOP mode with regulator in low power */
      STOPEntry();
    }
    else /* (State == STATE_UNDER_THRESHOLD) */
    {
      /* Restore config: clock, GPIO... */
      RestoreConfiguration();

      /* Restore GPIO configuration */
      STM_EVAL_LEDInit(LED1);
      STM_EVAL_LEDInit(LED2);
      STM_EVAL_LEDInit(LED3);
      STM_EVAL_LEDInit(LED4);

      /* Turn on LD2 & LD4 and turn off LD1 & LD3 */
      STM_EVAL_LEDOff(LED1);
      STM_EVAL_LEDOn(LED2);
      STM_EVAL_LEDOff(LED3);
      STM_EVAL_LEDOn(LED4);

      while(State == STATE_UNDER_THRESHOLD)
      {
         /* add your code here */
      }
    }
  }
}

/**
  * @brief  Configure COMP1 and COMP2 with interrupt
  * @param  None
  * @retval None
  */
void COMP_Config(void)
{
  COMP_InitTypeDef        COMP_InitStructure;
  EXTI_InitTypeDef        EXTI_InitStructure;
  NVIC_InitTypeDef        NVIC_InitStructure;

  /* GPIOB Peripheral clock enable */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);

  /* Configure PB5 in analog closes the switch GR6-2: PB5 is connected to COMP2 non inverting input */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  /* COMP Peripheral clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_COMP, ENABLE);

  /* COMP2 Init: COMP2 is enabled as soon as inverting input is selected */
  /* In this example, the lower threshold is set to VREFINT/4 ~ 1.22 / 4 ~ 0.305 V 
     but can be changed to other available possibilities */
  COMP_InitStructure.COMP_InvertingInput = COMP_InvertingInput_1_4VREFINT;
  COMP_InitStructure.COMP_OutputSelect = COMP_OutputSelect_None;
  COMP_InitStructure.COMP_Speed = COMP_Speed_Slow;
  COMP_Init(&COMP_InitStructure);

  /* Enable Window mode */
  COMP_WindowCmd(ENABLE);

  /* Enable COMP1: the higher threshold is set to VREFINT ~ 1.22 V */
  COMP_Cmd(ENABLE);

  /* Configure EXTI Line 21 in interrupt mode */
  EXTI_InitStructure.EXTI_Line = EXTI_Line21;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);

  /* Configure EXTI Line 22 in interrupt mode */
  EXTI_InitStructure.EXTI_Line = EXTI_Line22;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);

  /* Clear EXTI21 line */
  EXTI_ClearITPendingBit(EXTI_Line21);

  /* Clear EXTI22 line */
  EXTI_ClearITPendingBit(EXTI_Line22);

  /* Configure COMP IRQ */
  NVIC_InitStructure.NVIC_IRQChannel = COMP_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

/**
  * @brief  Prepare the system to enter STOP mode.
  * @param  None
  * @retval None
  */
void STOPEntry(void)
{
  /* Enable GPIOs clock */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOB | RCC_AHBPeriph_GPIOC |
                        RCC_AHBPeriph_GPIOD | RCC_AHBPeriph_GPIOE | RCC_AHBPeriph_GPIOH, ENABLE);

  /* Configure all GPIO port pins in Analog mode */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  GPIO_Init(GPIOD, &GPIO_InitStructure);
  GPIO_Init(GPIOE, &GPIO_InitStructure);
  GPIO_Init(GPIOH, &GPIO_InitStructure);

  /* Request to enter STOP mode with regulator in low power */
  PWR_EnterSTOPMode(PWR_Regulator_LowPower, PWR_STOPEntry_WFI);
}

/**
  * @brief  check input voltage level: within the thresholds, above the upper 
  *         threshold or under the lower threshold
  * @param  None
  * @retval None
  */
void CheckState(void)
{
  /* Check if COMP2 output level is high */
  if ((COMP_GetOutputLevel(COMP_Selection_COMP1) == COMP_OutputLevel_High) 
   && (COMP_GetOutputLevel(COMP_Selection_COMP2) == COMP_OutputLevel_High))
  {
    /* A rising edge is detected so the input voltage is higher than VREFINT */
    State = STATE_OVER_THRESHOLD;
  }
  else if ((COMP_GetOutputLevel(COMP_Selection_COMP1) == COMP_OutputLevel_Low)
       && (COMP_GetOutputLevel(COMP_Selection_COMP2) == COMP_OutputLevel_High))
  {
    /* A falling edge is detected so the input voltage is lower than VREFINT */
    State = STATE_WITHIN_THRESHOLD;
  }
  else if ((COMP_GetOutputLevel(COMP_Selection_COMP1) == COMP_OutputLevel_Low)
       && (COMP_GetOutputLevel(COMP_Selection_COMP2) == COMP_OutputLevel_Low))
  {
    State = STATE_UNDER_THRESHOLD;
  }
}

/**
  * @brief  Restore peripheral config before entering STOP mode.
  * @param  None
  * @retval None
  */
void RestoreConfiguration(void)
{
  ErrorStatus HSEStartUpStatus;

  /* Restore system clock to 32MHz */
    
  /* Enable HSE */
  RCC_HSEConfig(RCC_HSE_ON);
  
  /* Wait till HSE is ready */
  HSEStartUpStatus = RCC_WaitForHSEStartUp();
  
  if (HSEStartUpStatus == SUCCESS)
  {
    /* Enable PLL */
    RCC_PLLCmd(ENABLE);
    /* Wait till PLL is ready */
    while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
    {}
    /* Select PLL as system clock source */
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
    /* Wait till PLL is used as system clock source */
    while (RCC_GetSYSCLKSource() != 0x0C)
    {}
  }
}


#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number where 
  *         the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */ 

/**
  * @}
  */ 

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/