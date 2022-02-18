/**
  @page TrueSTUDIO_STM32L152 TrueSTUDIO Project Template for STM32L1xx Ultra Low Power Medium-density devices
 
  @verbatim
  ******************** (C) COPYRIGHT 2010 STMicroelectronics *******************
  * @file    readme.txt
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    31-December-2010
  * @brief   This sub-directory contains all the user-modifiable files needed to 
  *          create a new project linked with the STM32L1xx Standard Peripheral 
  *          Library and working with Atollic for STM32 TrueSTUDIO software 
  *          toolchain (Version 1.4.0 and later)
  ******************************************************************************
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  ******************************************************************************
  @endverbatim
 
 @par Directory contents
 
 - project .cproject/.project: A pre-configured project file with the provided 
                               library structure that produces an executable 
                               image with TrueSTUDIO.

 - stm32_flash.ld: 			       This file is the TrueSTUDIO linker script used to 
                               place program code (readonly) in internal FLASH 
                               and data (readwrite, Stack and Heap)in internal 
                               SRAM. 
                               You can customize this file to your need.
                           
 @par How to use it ?

 - Open the TrueSTUDIO toolchain.
 - Click on File->Switch Workspace->Other and browse to TrueSTUDIO workspace 
   directory.
 - Click on File->Import, select General->'Existing Projects into Workspace' 
   and then click "Next". 
 - Browse to the TrueSTUDIO workspace directory and select the project: 
   - STM32L152-EVAL: to configure the project for STM32L Ultra Low Power 
     Medium-density devices
     @note The needed define symbols for this config are already declared in the
           preprocessor section: USE_STDPERIPH_DRIVER, STM32L1XX_MD, USE_STM32L152_EVAL     
 - Under Windows->Preferences->General->Workspace->Linked Resources, add 
   a variable path named "CurPath" which points to the folder containing
   "Libraries", "Project" and "Utilities" folders.
 - Rebuild all project files: Select the project in the "Project explorer" 
   window then click on Project->build project menu.
 - Run program: Select the project in the "Project explorer" window then click 
   Run->Debug (F11)

@note
 - Ultra Low Power Medium Density-devices are STM32L151xx and STM32L152xx 
   microcontrollers where the Flash memory density ranges between 64 and 128 Kbytes.

 * <h3><center>&copy; COPYRIGHT 2010 STMicroelectronics</center></h3>
 */
