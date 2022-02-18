/**
  ******************************************************************************
  * @file    FLASH/Dual_Boot//main.h 
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
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void TimingDelay_Decrement(void);
void Delay(__IO uint32_t nTime);

#endif /* __MAIN_H */

