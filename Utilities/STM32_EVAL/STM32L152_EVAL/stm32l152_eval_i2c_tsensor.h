/**
  ******************************************************************************
  * @file    stm32l152_eval_i2c_tsensor.h
  * @author  MCD Application Team
  * @version V5.0.3
  * @date    17-November-2021
  * @brief   This file contains all the functions prototypes for the 
  *          stm32l152_eval_i2c_tsensor firmware driver.
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
#ifndef __STM32L152_EVAL_I2C_TSENSOR_H
#define __STM32L152_EVAL_I2C_TSENSOR_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l152_eval.h"

/** @addtogroup Utilities
  * @{
  */
  
/** @addtogroup STM32_EVAL
  * @{
  */ 

/** @addtogroup STM32L152_EVAL
  * @{
  */
  
/** @addtogroup STM32L152_EVAL_I2C_TSENSOR
  * @{
  */  

/** @defgroup STM32L152_EVAL_I2C_TSENSOR_Exported_Types
  * @{
  */
   
 /** 
  * @brief  IOE DMA Direction  
  */ 
typedef enum
{
  LM75_DMA_TX = 0,
  LM75_DMA_RX = 1
}LM75_DMADirection_TypeDef;

/** 
  * @brief  TSENSOR Status  
  */ 
typedef enum
{
  LM75_OK = 0,
  LM75_FAIL
}LM75_Status_TypDef;

/**
  * @}
  */
  
/** @defgroup STM32L152_EVAL_I2C_TSENSOR_Exported_Constants
  * @{
  */ 
    
/* Uncomment the following line to use Timeout_User_Callback LM75_TimeoutUserCallback(). 
   If This Callback is enabled, it should be implemented by user in main function .
   LM75_TimeoutUserCallback() function is called whenever a timeout condition 
   occure during communication (waiting on an event that doesn't occur, bus 
   errors, busy devices ...). */   
/* #define USE_TIMEOUT_USER_CALLBACK */    
    
/* Maximum Timeout values for flags and events waiting loops. These timeouts are
   not based on accurate values, they just guarantee that the application will 
   not remain stuck if the I2C communication is corrupted.
   You may modify these timeout values depending on CPU frequency and application
   conditions (interrupts routines ...). */   
#define LM75_FLAG_TIMEOUT         ((uint32_t)0x1000)
#define LM75_LONG_TIMEOUT         ((uint32_t)(10 * LM75_FLAG_TIMEOUT))    
    

/**
  * @brief  Block Size
  */
#define LM75_REG_TEMP       0x00  /*!< Temperature Register of LM75 */
#define LM75_REG_CONF       0x01  /*!< Configuration Register of LM75 */
#define LM75_REG_THYS       0x02  /*!< Temperature Register of LM75 */
#define LM75_REG_TOS        0x03  /*!< Over-temp Shutdown threshold Register of LM75 */
#define I2C_TIMEOUT         ((uint32_t)0x3FFFF) /*!< I2C Time out */
#define LM75_ADDR           0x90   /*!< LM75 address */
#define LM75_I2C_SPEED      100000 /*!< I2C Speed */
  
   

/**
  * @}
  */

/** @defgroup STM32L152_EVAL_I2C_TSENSOR_Exported_Macros
  * @{
  */ 
/**
  * @}
  */ 

/** @defgroup STM32L152_EVAL_I2C_TSENSOR_Exported_Functions
  * @{
  */ 
void LM75_DeInit(void);
void LM75_Init(void);
ErrorStatus LM75_GetStatus(void);
uint16_t LM75_ReadTemp(void);
uint16_t LM75_ReadReg(uint8_t RegName);
uint8_t LM75_WriteReg(uint8_t RegName, uint16_t RegValue);
uint8_t LM75_ReadConfReg(void);
uint8_t LM75_WriteConfReg(uint8_t RegValue);
uint8_t LM75_ShutDown(FunctionalState NewState);

/** 
  * @brief  Timeout user callback function. This function is called when a timeout
  *         condition occurs during communication with IO Expander. Only protoype
  *         of this function is decalred in IO Expander driver. Its implementation
  *         may be done into user application. This function may typically stop
  *         current operations and reset the I2C peripheral and IO Expander.
  *         To enable this function use uncomment the define USE_TIMEOUT_USER_CALLBACK
  *         at the top of this file.          
  */
#ifdef USE_TIMEOUT_USER_CALLBACK 
 uint8_t LM75_TIMEOUT_UserCallback(void);
#else
 #define LM75_TIMEOUT_UserCallback()  LM75_FAIL
#endif /* USE_TIMEOUT_USER_CALLBACK */
 
#ifdef __cplusplus
}
#endif

#endif /* __STM32L152_EVAL_I2C_TSENSOR_H */
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


