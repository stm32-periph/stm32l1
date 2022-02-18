/**
  ******************************************************************************
  * @file    RTC/RTC_Timer/main.h 
  * @author  MCD Application Team
  * @version V1.2.2
  * @date    17-November-2021
  * @brief   Header for main.c module
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
#include "stm32l152d_eval.h"
#include "stm32l152d_eval_lcd.h"
#include <stdio.h>

/* Exported types ------------------------------------------------------------*/
typedef struct {
  uint8_t tab[12];
} Table_TypeDef;

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void RTC_Config(void);
void RTC_AlarmConfig(void);
void Delay(__IO uint32_t nTime);


#endif /* __MAIN_H */

