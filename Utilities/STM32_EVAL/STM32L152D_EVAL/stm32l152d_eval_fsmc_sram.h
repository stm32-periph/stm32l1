/**
  ******************************************************************************
  * @file    stm32l152d_eval_fsmc_sram.h
  * @author  MCD Application Team
  * @version V1.0.2
  * @date    17-November-2021
  * @brief   This file contains all the functions prototypes for the 
  *          stm32l152d_eval_fsmc_sram firmware driver.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2012 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32L152D_EVAL_FSMC_SRAM_H
#define __STM32L152D_EVAL_FSMC_SRAM_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l152d_eval.h"

/** @addtogroup Utilities
  * @{
  */
  
/** @addtogroup STM32_EVAL
  * @{
  */ 

/** @addtogroup STM32L152D_EVAL
  * @{
  */
  
/** @addtogroup STM32L152D_EVAL_FSMC_SRAM
  * @{
  */  

/** @defgroup STM32L152D_EVAL_FSMC_SRAM_Exported_Types
  * @{
  */
/**
  * @}
  */
  
/** @defgroup STM32L152D_EVAL_FSMC_SRAM_Exported_Constants
  * @{
  */ 
/**
  * @}
  */ 
  
/** @defgroup STM32L152D_EVAL_FSMC_SRAM_Exported_Macros
  * @{
  */ 
/**
  * @}
  */ 

/** @defgroup STM32L152D_EVAL_FSMC_SRAM_Exported_Functions
  * @{
  */      

void SRAM_Init(void);
void SRAM_WriteBuffer(uint16_t* pBuffer, uint32_t WriteAddr, uint32_t NumHalfwordToWrite);
void SRAM_ReadBuffer(uint16_t* pBuffer, uint32_t ReadAddr, uint32_t NumHalfwordToRead);

#ifdef __cplusplus
}
#endif

#endif /* __STM32L152D_EVAL_FSMC_SRAM_H */
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */ 

/**
  * @}
  */ 


