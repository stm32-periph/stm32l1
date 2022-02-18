/**
  ******************************************************************************
  * @file    RTC/TimeStamp/main.c
  * @author  MCD Application Team
  * @version V1.2.2
  * @date    17-November-2021
  * @brief   Main program body
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

  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "stm32l1xx.h"
#include <stdio.h>

#ifdef USE_STM32L152D_EVAL 
  #include "stm32l152d_eval.h"
  #include "stm32l152d_eval_glass_lcd.h"
#elif defined USE_STM32L152_EVAL 
  #include "stm32l152_eval.h"
  #include "stm32l152_eval_glass_lcd.h"
#endif 


/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void RTC_Config(void);
void RTC_TimeRegulate(void);
void RTC_TimeShow(void);
void RTC_DateShow(void);
void RTC_TimeStampShow(void);
uint8_t USART_Scanf(uint32_t MinValue, uint32_t MaxValue);


#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

#endif /* __MAIN_H */

