/**
  ******************************************************************************
  * @file    LCD/LCD_Contrast_Control/main.c 
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
#include "stm32l1xx_it.h"
#include "stm32l152_eval_glass_lcd.h"
#include "stm32_eval.h"

/** @addtogroup STM32L1xx_StdPeriph_Examples
  * @{
  */

/** @addtogroup LCD_Contrast_Control
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define ADC1_DR_Address    ((uint32_t)0x40012458)
#define ADC_StepValue       512  /* Eight intervals with ADC_StepValue range */

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
__IO uint16_t ADC_ConvertedValue;
__IO uint8_t Contrast_Range = 0;
__I uint32_t LCDContrastArray[8]= {LCD_Contrast_Level_0, LCD_Contrast_Level_1, 
                                   LCD_Contrast_Level_2, LCD_Contrast_Level_3, 
                                   LCD_Contrast_Level_4, LCD_Contrast_Level_5,
                                   LCD_Contrast_Level_6, LCD_Contrast_Level_7};

/* Private function prototypes -----------------------------------------------*/
void RCC_Config(void);
void ADC_Config(void);
void LCD_GLASS_DisplayContrast(__IO uint8_t value);

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
       
  /* System clocks configuration ---------------------------------------------*/
  RCC_Config();
  
  /* GPIO configuration ------------------------------------------------------*/
  ADC_Config();
    
  /* LCD GLASS Initialization */
  LCD_GLASS_Init();

  /* Infinite loop */
  while (1)
  { 
    /* Calculate the Contrast range value */  
    Contrast_Range = (uint8_t) (ADC_ConvertedValue / ADC_StepValue);
   
    /* Configure the LCD Contrast and Display message on the LCD Glass */
    LCD_GLASS_DisplayContrast(Contrast_Range);
  }
}

/**
  * @brief  Configures the different system and peripherals clocks.
  * @param  None
  * @retval None
  */
void RCC_Config(void)
{   
  /* Enable PWR clocks */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);

  /* Allow access to the RTC */
  PWR_RTCAccessCmd(ENABLE);

  /* Reset Backup Domain */
  RCC_RTCResetCmd(ENABLE);
  RCC_RTCResetCmd(DISABLE);

  /*!< LSE Enable */
  RCC_LSEConfig(RCC_LSE_ON);

  /*!< Wait till LSE is ready */
  while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)
  {}
  /*!< LCD Clock Source Selection */
  RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
}

/**
  * @brief  Configures the different ADC resources (Clock, GPIO ports...).
  * @param  None
  * @retval None
  */
void ADC_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  ADC_InitTypeDef ADC_InitStructure;
  DMA_InitTypeDef DMA_InitStructure;
  
  /* Enable DMA1 and GPIOB clock */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1 | RCC_AHBPeriph_GPIOB , ENABLE);

  /* Enable ADC1 clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

  /* Enable the HSI */
  RCC_HSICmd(ENABLE);
    
  /* Configure PB.12 (ADC Channel18) as analog input -------------------------*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  /* DMA1 channel1 configuration ----------------------------------------------*/
  DMA_DeInit(DMA1_Channel1);
  DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address;
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&ADC_ConvertedValue;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
  DMA_InitStructure.DMA_BufferSize = 1;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
  DMA_Init(DMA1_Channel1, &DMA_InitStructure);
  
  /* Enable DMA1 channel1 */
  DMA_Cmd(DMA1_Channel1, ENABLE);
     
  /* ADC1 configuration ------------------------------------------------------*/
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
  ADC_InitStructure.ADC_ScanConvMode = ENABLE;
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConvEdge_None;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NbrOfConversion = 1;
  ADC_Init(ADC1, &ADC_InitStructure);

  /* ADC1 regular channel18 configuration */ 
  ADC_RegularChannelConfig(ADC1, ADC_Channel_18, 1, ADC_SampleTime_4Cycles);

  /* Enable the request after last transfer for DMA Circular mode */
  ADC_DMARequestAfterLastTransferCmd(ADC1, ENABLE);
  
  /* Enable ADC1 DMA */
  ADC_DMACmd(ADC1, ENABLE);
  
  /* Enable ADC1 */
  ADC_Cmd(ADC1, ENABLE);

  /* Start ADC1 Software Conversion */ 
  ADC_SoftwareStartConv(ADC1);  
}

/**
  * @brief  Configures the LCD Contrast and Display Message on the LCD GLASS.
  * @param  value: LCD CONTRAST range. 
  * @retval None
  */
void  LCD_GLASS_DisplayContrast(__IO uint8_t value)
{
  /* Configures the LCD Contrast Maximum Voltage according to the value variable */
  LCD_ContrastConfig(LCDContrastArray[value]);
  
  switch (value)
  {
    case 0 :
      /* Display the "CONTR2V6" message on the LCD GLASS */
      LCD_GLASS_DisplayString("CONTR2V6");
      break;
    case 1 :
      /* Display the "CONTR2V7" message on the LCD GLASS */
      LCD_GLASS_DisplayString("CONTR2V7");
      break;
    case 2 :
      /* Display the "CONTR2V8" message on the LCD GLASS */
      LCD_GLASS_DisplayString("CONTR2V8");
      break;
    case 3 :
      /* Display the "CONTR3V0" message on the LCD GLASS */
      LCD_GLASS_DisplayString("CONTR3V0");
      break;
    case 4 :
      /* Display the "CONTR3V1" message on the LCD GLASS */
      LCD_GLASS_DisplayString("CONTR3V1");
      break;
    case 5 :
      /* Display the "CONTR3V2" message on the LCD GLASS */
      LCD_GLASS_DisplayString("CONTR3V2");
      break;
    case 6 :
      /* Display the "CONTR3V4" message on the LCD GLASS */
      LCD_GLASS_DisplayString("CONTR3V4");
      break;
    default :
      /* Display the "CONTR3V5" message on the LCD GLASS */
      LCD_GLASS_DisplayString("CONTR3V5");
      break;
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
