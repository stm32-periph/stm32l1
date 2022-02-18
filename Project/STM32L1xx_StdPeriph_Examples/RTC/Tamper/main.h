/**
  ******************************************************************************
  * @file    RTC/Tamper/main.h 
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

#ifdef USE_STM32L152D_EVAL 
  #include "stm32l152d_eval.h"
#elif defined USE_STM32L152_EVAL 
  #include "stm32l152_eval.h"
#endif 

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
uint32_t IsBackupRegReset(void);

#endif /* __MAIN_H */

