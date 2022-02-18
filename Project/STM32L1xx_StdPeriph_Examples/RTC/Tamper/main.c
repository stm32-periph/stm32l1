/**
  ******************************************************************************
  * @file    RTC/Tamper/main.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    31-December-2010
  * @brief   Main program body
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

/** @addtogroup RTC_Tamper
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define RTC_BKP_DR_NUMBER              20

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint32_t RTC_BKP_DR[RTC_BKP_DR_NUMBER] =
  {
    RTC_BKP_DR0, RTC_BKP_DR1, RTC_BKP_DR2, RTC_BKP_DR3, 
    RTC_BKP_DR4, RTC_BKP_DR5, RTC_BKP_DR6, RTC_BKP_DR7,
    RTC_BKP_DR8, RTC_BKP_DR9, RTC_BKP_DR10, RTC_BKP_DR11,
    RTC_BKP_DR12, RTC_BKP_DR13, RTC_BKP_DR14, RTC_BKP_DR15,
    RTC_BKP_DR16, RTC_BKP_DR17, RTC_BKP_DR18, RTC_BKP_DR19
  };

/* Private function prototypes -----------------------------------------------*/
void RTC_Config(void);
void WriteToRTC_BKP_DR(uint32_t FirstRTCBackupData);
uint32_t CheckRTC_BKP_DR(uint32_t FirstRTCBackupData);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief   Main program
  * @param  None
  * @retval None
  */
int main(void)
{
  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_stm32l1xx_md.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32l1xx.c file
     */      
  
  /* Initialize Leds mounted on STM32LXXX-EVAL board */
  STM_EVAL_LEDInit(LED1);
  STM_EVAL_LEDInit(LED2);
  STM_EVAL_LEDInit(LED3);
  STM_EVAL_LEDInit(LED4);
  
  /* RTC configuration */
  RTC_Config();
      
  /* Write To RTC Backup Data registers */
  WriteToRTC_BKP_DR(0xA53C);   
  
  /* Check if the written data are correct */
  if(CheckRTC_BKP_DR(0xA53C) == 0x00)
  {
    /* Turn on LED1 */
    STM_EVAL_LEDOn(LED1);
  }
  else
  {
    /* Turn on LED3 */
    STM_EVAL_LEDOn(LED3);
  }
               
  while (1)
  {}
}

/**
  * @brief  Configures the RTC clock source.
  * @param  None
  * @retval None
  */
void RTC_Config(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  EXTI_InitTypeDef  EXTI_InitStructure; 
  
  /* PWR Clock Enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
  
  /* Allow access to BKP Domain */
  PWR_RTCAccessCmd(ENABLE);

  /* Enable the LSE Clock */  
  RCC_LSEConfig(RCC_LSE_ON);
  
  /* Wait till LSE is ready */  
  while(RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)
  {}
  
  /* Select the RTC Clock Source */
  RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
  
  /* Reset RTC Domain */
  RCC_RTCResetCmd(ENABLE);
  RCC_RTCResetCmd(DISABLE);

  /* Enable The external line19 interrupt */
  EXTI_ClearITPendingBit(EXTI_Line19);
  EXTI_InitStructure.EXTI_Line = EXTI_Line19;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);

  /* Enable TAMPER IRQChannel */
  NVIC_InitStructure.NVIC_IRQChannel = TAMPER_STAMP_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);   

  /* Disable the Tamper 1 detection */
  RTC_TamperCmd(RTC_Tamper_1, DISABLE);
  
  /* Clear Tamper 1 pin Event(TAMP1F) pending flag */
  RTC_ClearFlag(RTC_FLAG_TAMP1F);
  
  /* Configure the Tamper 1 Trigger */
  RTC_TamperTriggerConfig(RTC_Tamper_1, RTC_TamperTrigger_FallingEdge);
   
  /* Enable the Tamper interrupt */
  RTC_ITConfig(RTC_IT_TAMP, ENABLE);
  
  /* Clear Tamper 1 pin interrupt pending bit */
  RTC_ClearITPendingBit(RTC_IT_TAMP1);
  
  /* Enable the Tamper 1 detection */
  RTC_TamperCmd(RTC_Tamper_1, ENABLE);   
}

/**
  * @brief  Writes data RTC Backup DRx registers.
  * @param  FirstRTCBackupData: data to be written to RTC Backup data registers.
  * @retval None
  */
void WriteToRTC_BKP_DR(uint32_t FirstRTCBackupData)
{
  uint32_t index = 0;

  for (index = 0; index < RTC_BKP_DR_NUMBER; index++)
  {
    /* write To bkp data register */
    RTC_WriteBackupRegister(RTC_BKP_DR[index], FirstRTCBackupData + (index * 0x5A));
  }  
}

/**
  * @brief  Checks if the RTC Backup DRx registers values are correct or not.
  * @param  FirstRTCBackupData: data to be compared with RTC Backup data registers.
  * @retval 
  *         - 0: All RTC Backup DRx registers values are correct
  *         - Value different from 0: Number of the first Backup register
  *           which value is not correct
  */
uint32_t CheckRTC_BKP_DR(uint32_t FirstRTCBackupData)
{
  uint32_t index = 0;

  for (index = 0; index < RTC_BKP_DR_NUMBER; index++)
  {
    /* Read from data register */
    if (RTC_ReadBackupRegister(RTC_BKP_DR[index]) != (FirstRTCBackupData + (index * 0x5A)))
    {
      return (index + 1);
    }
  }
    return 0;  
}

/**
  * @brief  Checks if the RTC Backup DRx registers are reset or not.
  * @param  None
  * @retval 
  *          - 0: All RTC Backup DRx registers are reset
  *          - Value different from 0: Number of the first Backup register
  *            not reset
  */
uint32_t IsBackupRegReset(void)
{
  uint32_t index = 0;

  for (index = 0; index < RTC_BKP_DR_NUMBER; index++)
  {
     /* Read from bkp Data Register */
    if (RTC_ReadBackupRegister(RTC_BKP_DR[index]) != 0x0)
    {
      return (index + 1);
    }
  }
  return 0;  
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
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
