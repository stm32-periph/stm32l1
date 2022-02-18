/**
  ******************************************************************************
  * @file    ADC/ADC1_Freeze/main.c 
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

/** @addtogroup ADC1_Freeze
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define RV3_VOLTAGE                 ADC_Channel_18
#define IDD_VOLTAGE                 ADC_Channel_5
#define ADC_RATIO                   ((uint16_t) 806) /*ADC_RATIO = ( 3.3 * 1000 * 1000)/4095 */
#define ASCII_NUM_0                 0x30
#define EVAL_RESISTOR_R36      130    /* value of resistor R36 is 1.3 Ohm 
                                         EVAL_RESISTOR_RATIO * 1.3 = 130  */
#define EVAL_RESISTOR_RATIO    100    /* R36 is multiplied by 100 */
#define EVAL_MAX9938_GAIN      50     /* Ampli-op gain = 50 */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
ADC_InitTypeDef           ADC_InitStructure;
GPIO_InitTypeDef          GPIO_InitStructure;
TIM_TimeBaseInitTypeDef   TIM_TimeBaseStructure;
NVIC_InitTypeDef          NVIC_InitStructure;

/* Private function prototypes -----------------------------------------------*/
void ADC_Config(void);
void LCD_Glass_Config(void);
void TIM2_Config(void);

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

  /* LCD GLASS Configuration */
  LCD_Glass_Config();

  /* TIM2 Configuration */
  TIM2_Config();

  /* ADC1 configuration: channel18 and channel5 */
  ADC_Config();

  /* Configure the STM32L152-EVAL KEY Push button */
  STM_EVAL_PBInit(BUTTON_KEY, BUTTON_MODE_EXTI); 

  while (1)
  {   
  }
}

/**
  * @brief  Configures the ADC1: channel5 and channel18.
  * @param  None
  * @retval None
  */
void ADC_Config(void)
{
  /* Enable The HSI (16Mhz) */
  RCC_HSICmd(ENABLE);

  /* Enable the GPIOB Clock */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
  /* Configure PB.12 (ADC Channel18) in analog mode */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  /* Check that HSI oscillator is ready */
  while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET);

  /* Enable the GPIOA Clock */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
  /* Configure PA.5 (ADC Channel5) in analog mode */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* ADC1 Configuration ------------------------------------------------------*/
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
  /* ADC1 DeInit */  
  ADC_DeInit(ADC1);
  /* ADC1 Configuration of channel18 and channel5 : continuous mode, external trigger (TIM2) */
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
  ADC_InitStructure.ADC_ScanConvMode = ENABLE;
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_Falling;
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T2_TRGO;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NbrOfConversion = 2;
  ADC_Init(ADC1, &ADC_InitStructure);
  
  /* ADC1 Regular Channel Config */
  ADC_RegularChannelConfig(ADC1, IDD_VOLTAGE, 1, ADC_SampleTime_4Cycles);
  ADC_RegularChannelConfig(ADC1, RV3_VOLTAGE, 2, ADC_SampleTime_4Cycles);

  /* Enables the ADC1 Power Down during Delay */ 
  ADC_PowerDownCmd(ADC1, ADC_PowerDown_Idle_Delay, ENABLE);
  
  /* Delay until the converted data has been read */
  ADC_DelaySelectionConfig(ADC1, ADC_DelayLength_Freeze);

  /* Enable ADC1 */
  ADC_Cmd(ADC1, ENABLE);     
  
  /* Wait until the ADC1 is ready */
  while(ADC_GetFlagStatus(ADC1, ADC_FLAG_ADONS) == RESET)
  {
  }
}

/**
  * @brief  Configures the LCD Glass.
  * @param  None
  * @retval None
  */
void LCD_Glass_Config(void)
{  
  /* Enable PWR clock */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);

  /* Allow access to the RTC */
  PWR_RTCAccessCmd(ENABLE);

  /* Reset Backup Domain */
  RCC_RTCResetCmd(ENABLE);
  RCC_RTCResetCmd(DISABLE);

  /* LSE Enable */
  RCC_LSEConfig(RCC_LSE_ON);

  /*Wait till LSE is ready */
  while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)
  {}
  
  /* LCD Clock Source Selection */
  RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);

  /* Init LCD Glass */
  LCD_GLASS_Init();
}

/**
  * @brief  Configures TIM2.
  * @param  None
  * @retval None
  */
void TIM2_Config(void)
{
  /* Enable TIM2 clock */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

  TIM_DeInit(TIM2);
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
  /* Time base configuration */
  TIM_TimeBaseStructure.TIM_Period = 0xFF;         
  TIM_TimeBaseStructure.TIM_Prescaler = 0x1;       
  TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;    
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

  /* TIM2 TRGO selection */
  TIM_SelectOutputTrigger(TIM2, TIM_TRGOSource_Update);

  /* Enable TIM2 Update Interrupt*/ 
  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  /* Enable TIM2 */       
  TIM_Cmd(TIM2,ENABLE);
}

/**
  * @brief  Display the ADC converted Values on the LCD Glass.
  * @param  data1: VDD voltage.
  * @param  data2: RV3 voltage.
  * @retval None
  */
void DisplayOnLCD(uint16_t data1, uint16_t data2) 
{
  uint16_t rv3voltage=0;
  uint32_t iddrun = 0;
  uint8_t digit1 = 0, digit2 = 0;
  uint8_t LCDString[8]="00MA 00V";


  /* Calculate the current consumption */
  iddrun = (uint32_t) ((uint32_t)(((data1 * 1000 * EVAL_RESISTOR_RATIO) / EVAL_MAX9938_GAIN))\
                           / (uint32_t)(EVAL_RESISTOR_R36));

  /* Calculate RV3 voltage value*/
  rv3voltage = (uint16_t)((uint32_t)((uint32_t)data2 * (uint32_t)ADC_RATIO) / (uint32_t)1000);

  /* digit1 value*/
  digit1 = (uint8_t)(iddrun / 1000);
  /* digit2 value */
  digit2 = (uint8_t)((iddrun % 1000) / 100);

  /* Fill the LCDString fields with the current Voltage */
  LCDString[0] = (uint8_t)((uint8_t)(digit1) + ASCII_NUM_0);
  LCDString[1] = (uint8_t)((uint8_t)(digit2) + ASCII_NUM_0);

  /* digit1 value*/
  digit1 = (uint8_t)(rv3voltage / 1000);
  /* digit2 value */
  digit2 = (uint8_t)((rv3voltage % 1000) / 100);


  /* Fill the LCDString fields with the current Voltage */
  LCDString[5] = (uint8_t)((uint8_t)(digit1) + ASCII_NUM_0);
  LCDString[6] = (uint8_t)((uint8_t)(digit2) + ASCII_NUM_0);

 
  /*!< Wait Until the last LCD RAM update finish */
  while(LCD_GetFlagStatus(LCD_FLAG_UDR) != RESET)
  {
  }
  /* Display one character on LCD */
  LCD_GLASS_WriteChar(&LCDString[0], POINT_ON, APOSTROPHE_OFF, 0);
  
  /* Display one character on LCD */
  LCD_GLASS_WriteChar(&LCDString[1], POINT_OFF, APOSTROPHE_OFF, 1);
  
  /* Display one character on LCD */
  LCD_GLASS_WriteChar(&LCDString[2], POINT_OFF, APOSTROPHE_OFF, 2);
  
  /* Display one character on LCD */
  LCD_GLASS_WriteChar(&LCDString[3], POINT_OFF, APOSTROPHE_OFF, 3);
  
  /* Display one character on LCD */
  LCD_GLASS_WriteChar(&LCDString[4], POINT_OFF, APOSTROPHE_OFF , 4);
  
  /* Display one character on LCD */
  LCD_GLASS_WriteChar(&LCDString[5], POINT_ON, APOSTROPHE_OFF, 5);
  
  /* Display one character on LCD */
  LCD_GLASS_WriteChar(&LCDString[6], POINT_OFF, APOSTROPHE_OFF, 6);
  
  /* Display one character on LCD */
  LCD_GLASS_WriteChar(&LCDString[7], POINT_OFF, APOSTROPHE_OFF, 7);
  
  /* Request LCD RAM update */
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
