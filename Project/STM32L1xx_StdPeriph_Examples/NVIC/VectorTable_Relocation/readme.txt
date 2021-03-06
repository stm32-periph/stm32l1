/**
  @page NVIC_VectorTable_Relocation NVIC Vector Table Relocation example
  
  @verbatim
  ******************** (C) COPYRIGHT 2015 STMicroelectronics *******************
  * @file    NVIC/VectorTable_Relocation/readme.txt 
  * @author  MCD Application Team
  * @version V1.2.2
  * @date    17-November-2021
  * @brief   Description of the NVIC Vector Table Relocation example.
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
   @endverbatim

@par Example Description 

This example describes how to set the CortexM3 vector table in a specific 
address other than default using the NVIC_SetVectorTable function from the 
misc.h/.c driver.

This can be used to build program which will be loaded into Flash memory by an
application previously programmed from the Flash memory base address. 
Such application can be In-Application Programming (IAP, through USART) or
Device Firmware Upgrade (DFU, through USB).

These applications are available for download from the ST microcontrollers 
website: <a href="http://www.st.com/internet/mcu/family/141.jsp">  ST Microcontrollers </a>/stm32l

The associated program implements a "Delay" function based on SysTick end of count
interrupt, and toggles four leds with timing defined by the "Delay" function.

When using the IAP or DFU to load your porgram, the vector table must be
relocated at address 0x08003000.


@par Directory contents 

  - NVIC/VectorTable_Relocation/stm32l1xx_conf.h    Library Configuration file
  - NVIC/VectorTable_Relocation/stm32l1xx_it.c      Interrupt handlers
  - NVIC/VectorTable_Relocation/stm32l1xx_it.h      Interrupt handlers header file
  - NVIC/VectorTable_Relocation/main.c              Main program
  - NVIC/VectorTable_Relocation/system_stm32l1xx.c  STM32L1xx system source file

@note The "system_stm32l1xx.c" is generated by an automatic clock configuration 
      system and can be easily customized to your own configuration. 
      To select different clock setup, use the "STM32L1xx_Clock_Configuration_V1.1.0.xls" 
      provided with the AN3309 package available on <a href="http://www.st.com/internet/mcu/family/141.jsp">  ST Microcontrollers </a>

@par Hardware and Software environment

  - This example runs on STM32L1xx Ultra Low Power High-, Medium-Density and Medium-Density Plus Devices.
  
  - This example has been tested with STMicroelectronics STM32L152D-EVAL (STM32L1xx 
    Ultra Low Power High-Density) and STM32L152-EVAL (STM32L1xx Ultra Low 
    Power Medium-Density) evaluation board and can be easily tailored to any 
    other supported device and development board.

  - STM32L152-EVAL Set-up
    - Use LD1, LD2, LD3 and LD4 leds connected respectively to PD.00, PD.01, 
      PD.04 and PD.05 pins

  - STM32L152-EVAL Set-up
    - Use LD1, LD2, LD3 and LD4 leds connected respectively to PD.03, PD.07, PG.14
      and PG.15 pins

@par How to use it ? 

In order to make the program work, you must do the following :
 - Copy all source files from this example folder to the template folder under
   Project\STM32L1xx_StdPeriph_Templates
 - Open your preferred toolchain and setup your project configuration as follows
 - If the used device is STM32L1XX_MD choose "STM32L1XX_MD(STM32L1xxxBxx)" workspace
    - Add the following files to the project source list
       - Utilities\STM32_EVAL\STM32L152_EVAL\stm32l152_eval.c
 - If the used device is STM32L1XX_HD choose "STM32L1XX_HD(STM32L1xxxDxx)" workspace
    - Add the following files to the project source list
       - Utilities\STM32_EVAL\STM32L152D_EVAL\stm32l152d_eval.c 
<ul>
    <li> MDK-ARM
         - In the project option menu, select 'Target' window and enter 0x08003000 
           as IROM start address
         - In the project option menu, select 'Linker' window and enter 0x08003000 
           as R/O base address

    <li> EWARM
         - Use "stm32l1xx_flash_offset.icf" as linker file

    <li> TrueSTUDIO 
         - In the project properties window, select C/C++ Build->settings node then 
           the C Linker->General node and use "stm32l1xx_flash_offset.ld" as Script File.
           This linker is configured for Ultra Low Power Medium-density devices. 
           To use it with other STM32 devices, this linker should be updated. 
          
</ul> 

 - Rebuild all files and load your image into target memory
 - Run the example


@note
- Ultra Low Power Medium-density devices: - STM32L151x6xx, STM32L151x8xx, STM32L151xBxx, STM32L152x6xx,
                                            STM32L152x8xx, STM32L152xBxx, STM32L151x6xxA, STM32L151x8xxA,
                                            STM32L151xBxxA, STM32L152x6xxA, STM32L152x8xxA and STM32L152xBxxA
                                          - STM32L100x6xx, STM32L100x8xx and STM32L100xBxx
- Ultra Low Power Medium-density Plus devices: - STM32L151xCxx, STM32L152xCxx and STM32L162xCxx 
                                               - STM32L100xCxx
- Ultra Low Power High-density devices: STM32L151xDxx, STM32L152xDxx and STM32L162xDxx
- Ultra Low Power XL-density devices: STM32L151xExx, STM32L152xExx and STM32L162xExx
    

 */


