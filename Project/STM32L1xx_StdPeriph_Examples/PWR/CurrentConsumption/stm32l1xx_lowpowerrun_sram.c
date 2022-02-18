/**
  ******************************************************************************
  * @file    PWR/CurrentConsumption/stm32l1xx_lowpowerrun_sram.c 
  * @author  MCD Application Team
  * @version V1.2.2
  * @date    17-November-2021
  * @brief   This file provides firmware functions to manage the STM32L1xx 
  *          Low Power Run Mode from Internal SRAM.
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

/* Includes ------------------------------------------------------------------*/
#include "stm32l1xx.h"

/** @addtogroup STM32L1xx_StdPeriph_Examples
  * @{
  */

/** @addtogroup CurrentConsumption
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  This function configures the system to enter Low Power Run mode for
  *         current consumption measurement purpose. The code is running from 
  *         Internal SRAM.
  *         The maximum clock when the system is in Low Power Run mode is ~128KHz.
  *         This mode can only be entered when Voltage Range 2 is selected.    
  * @param  None
  * @retval None
  */
#if defined ( __CC_ARM   )
/* With ARM Compiler, RAM functions are defined using the toolchain options. 
   For more details please refer to your toolchain documentation. */
  void

#elif defined ( __ICCARM__ )
 __ramfunc void

#elif defined   (  __GNUC__  )
void __attribute__((section(".data")))
#elif defined   (  __TASKING__  )
#pragma section_code_init on
#endif

LowPowerRunModeSRAM_Measure(void)
{

  /* This function should be called when the program is running from internal SRAM. */
  FLASH_RUNPowerDownCmd(ENABLE);

  /* Wait Until Key button pressed */
  while(((*(__IO uint32_t *)0x40020010) & 0x0001) == 0)
  {
  }

  /* Wait Until Key button pressed */
  while(((*(__IO uint32_t *)0x40020010) & 0x0001) != 0)
  {
  }

  /* This function should be called when the program is running from internal SRAM. */
  FLASH_RUNPowerDownCmd(DISABLE);  
}

#if defined (  __TASKING__  )
#pragma section_code_init restore
#endif


/**
  * @}
  */ 

/**
  * @}
  */ 

