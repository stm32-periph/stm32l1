/**
  ******************************************************************************
  * @file    RTC/TimeStamp/main.c 
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
#include "stm32l1xx.h"
#include "stm32_eval.h"
#include "stm32l152_eval_glass_lcd.h"

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
RTC_InitTypeDef   RTC_InitStructure;
RTC_TimeTypeDef   RTC_TimeStructure;
RTC_DateTypeDef   RTC_DateStructure;
__IO uint32_t DisplayTimeDate = 0;
__IO uint32_t DisplayTimeDateStamp = 0;

/* Private function prototypes -----------------------------------------------*/
void RTC_Config(void);
void LCD_ShowTimeCalendar(uint32_t DisplayTimeDate);
void LCD_ShowDateCalendar(uint32_t DisplayTimeDate);

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
       
  /* RTC configuration -------------------------------------------------------*/
  RTC_Config();
  
  /* LCD GLASS Initialization ------------------------------------------------*/
  LCD_GLASS_Init();
  
  /* Clear the LCD GLASS -----------------------------------------------------*/
  LCD_GLASS_Clear();

  /* Configure STM32L152-EVAL LED1 as Output push-pull */
  STM_EVAL_LEDInit(LED1);
  STM_EVAL_LEDInit(LED2);
  STM_EVAL_LEDInit(LED3);
  STM_EVAL_LEDInit(LED4);
  
  /* Initialize JoyStick Buttons */
  STM_EVAL_PBInit(Button_SEL,  Mode_EXTI);
  STM_EVAL_PBInit(Button_UP,   Mode_EXTI);
  STM_EVAL_PBInit(Button_DOWN, Mode_EXTI);
  STM_EVAL_PBInit(Button_KEY,  Mode_EXTI);
  STM_EVAL_PBInit(Button_LEFT, Mode_EXTI);
  STM_EVAL_PBInit(Button_RIGHT,Mode_EXTI);

  while (1)
  {
    /* Display Time and Date from TimeStamp */
    if(DisplayTimeDateStamp == 1)
    {
      if(DisplayTimeDate == 0)
      {
        /* Display Time Stamp */
        LCD_ShowTimeCalendar(DisplayTimeDateStamp);
      }
      else
      {
        /* Display Date  */
        LCD_ShowDateCalendar(DisplayTimeDateStamp);
      }
    }
    /* Display Time and Date */
    else 
    {
      if(DisplayTimeDate == 0)
      {
        /* Display Time */
        LCD_ShowTimeCalendar(DisplayTimeDateStamp);   
      }
      else 
      {
        /* Display Date */
        LCD_ShowDateCalendar(DisplayTimeDateStamp);
      }
    }
  }
}

/**
  * @brief  Configures the RTC clock source.
  * @param  None
  * @retval None
  */
void RTC_Config(void)
{
  /* Enable The PWR Register */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);

  /* Allow access to RTC */
  PWR_RTCAccessCmd(ENABLE);

  /* Reset RTC Domain */
  RCC_RTCResetCmd(ENABLE);
  RCC_RTCResetCmd(DISABLE);

  /*!< LSE Enable */
  RCC_LSEConfig(RCC_LSE_ON);

  /*!< Wait till LSE is ready */
  while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)
  {}

  /*!< LCD Clock Source Selection */
  RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);

  /* Enable the RTC Clock */
  RCC_RTCCLKCmd(ENABLE);

  /* Wait for RTC APB registers synchronisation */
  RTC_WaitForSynchro();
  
  /* Set the Time */
  RTC_TimeStructure.RTC_Hours   = 0x08;
  RTC_TimeStructure.RTC_Minutes = 0x00;
  RTC_TimeStructure.RTC_Seconds = 0x57;
	
  /* Set the Date */
  RTC_DateStructure.RTC_Month = RTC_Month_December;
  RTC_DateStructure.RTC_Date = 0x12;  
  RTC_DateStructure.RTC_Year = 0x10; 
  RTC_DateStructure.RTC_WeekDay = RTC_Weekday_Friday; 
		
  /* Calendar Configuration */
  RTC_InitStructure.RTC_AsynchPrediv = 0x7F;
  RTC_InitStructure.RTC_SynchPrediv	=  0xFF;
  RTC_InitStructure.RTC_HourFormat = RTC_HourFormat_24;
  RTC_Init(&RTC_InitStructure);

  /* Set Time with BCD Format */
  RTC_SetTime(RTC_Format_BCD, &RTC_TimeStructure);  
  
  /* Set Date with Bcd Format */
  RTC_SetDate(RTC_Format_BCD, &RTC_DateStructure);  
  
  /* Enable The TimeStamp */
  RTC_TimeStampCmd(RTC_TimeStampEdge_Falling, ENABLE);  
}

/**
  * @brief  Prints the Time Calendar in the GLASS LCD.
  * @param  None
  * @retval None
  */

void LCD_ShowTimeCalendar(uint32_t DisplayTimeDate)
{
  uint8_t tmp = 0;
  
  if(DisplayTimeDateStamp == 0)
  {
    /* Get the current Time*/
    RTC_GetTime(RTC_Format_BCD, &RTC_TimeStructure);
  }
  else
  {
    RTC_GetTimeStamp(RTC_Format_BCD, &RTC_TimeStructure, &RTC_DateStructure);
  }	

  /*!< Wait Until the last LCD RAM update finish */
  while(LCD_GetFlagStatus(LCD_FLAG_UDR) != RESET)
  {
  }

  tmp = (char)(((uint8_t)(RTC_TimeStructure.RTC_Hours & 0xF0) >> 0x04) + 0x30);
  LCD_GLASS_WriteChar(&tmp, POINT_OFF, APOSTROPHE_OFF, 0);

  tmp = (char)(((uint8_t)(RTC_TimeStructure.RTC_Hours & 0x0F))+ 0x30);
  LCD_GLASS_WriteChar(&tmp, POINT_OFF, APOSTROPHE_OFF, 1);

  tmp = (char)(((uint8_t)(RTC_TimeStructure.RTC_Minutes & 0xF0) >> 0x04) + 0x30);
  LCD_GLASS_WriteChar(&tmp, POINT_OFF, APOSTROPHE_OFF, 3);

  tmp = (char)(((uint8_t)(RTC_TimeStructure.RTC_Minutes & 0x0F))+ (uint8_t)0x30);
  LCD_GLASS_WriteChar(&tmp, POINT_OFF, APOSTROPHE_OFF, 4);

  tmp = (char)(((uint8_t)(RTC_TimeStructure.RTC_Seconds & 0xF0) >> 0x04)+ 0x30);
  LCD_GLASS_WriteChar(&tmp, POINT_OFF, APOSTROPHE_OFF, 6);

  tmp = (char)(((uint8_t)(RTC_TimeStructure.RTC_Seconds & 0x0F)) + 0x30);
  LCD_GLASS_WriteChar(&tmp, POINT_OFF, APOSTROPHE_OFF, 7); 

  /*!< Requesy LCD RAM update */
  LCD_UpdateDisplayRequest();
}

/**
  * @brief  Prints the Date Calendar in the LCD.
  * @param  None
  * @retval None
  */
void LCD_ShowDateCalendar(uint32_t DisplayTimeDate)
{
  uint8_t tmp = 0;
  
  if(DisplayTimeDateStamp == 0)
  {
    /* Get the current Date */
    RTC_GetDate(RTC_Format_BCD, &RTC_DateStructure);
  }
  else
  {
   /* Get the current Date */
   RTC_GetTimeStamp(RTC_Format_BCD, &RTC_TimeStructure, &RTC_DateStructure);
  }

  /*!< Wait Until the last LCD RAM update finish */
  while(LCD_GetFlagStatus(LCD_FLAG_UDR) != RESET)
  {
  }

  tmp = (char)(((uint8_t)(RTC_DateStructure.RTC_Month & 0xF0) >> 4) + 0x30);
  LCD_GLASS_WriteChar(&tmp, POINT_OFF, APOSTROPHE_OFF, 0);

  tmp = (char)(((uint8_t)(RTC_DateStructure.RTC_Month & 0x0F)) + 0x30);
  LCD_GLASS_WriteChar(&tmp, POINT_OFF, APOSTROPHE_OFF, 1);

  tmp = (char)(((uint8_t)(RTC_DateStructure.RTC_Date & 0xF0) >> 0x04) + 0x30);
  LCD_GLASS_WriteChar(&tmp, POINT_OFF, APOSTROPHE_OFF, 3);

  tmp = (char)(((uint8_t)(RTC_DateStructure.RTC_Date & 0x0F)) + (uint8_t)0x30);
  LCD_GLASS_WriteChar(&tmp, POINT_OFF, APOSTROPHE_OFF, 4);

  tmp = (char)(((uint8_t)(RTC_DateStructure.RTC_Year & 0xF0) >> 4) + 0x30);
  LCD_GLASS_WriteChar(&tmp, POINT_OFF, APOSTROPHE_OFF, 6);

  /* The RTC_Year member in the TimeStamp Date is always 00 (no years in the RTC_TSDR register) */ 
  tmp = (char)(((uint8_t)(RTC_DateStructure.RTC_Year & 0x0F)) + 0x30);
  LCD_GLASS_WriteChar(&tmp, POINT_OFF, APOSTROPHE_OFF, 7); 

  /*!< Requesy LCD RAM update */
  LCD_UpdateDisplayRequest();

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
