/**
  @page TIM_OnePulse TIM One Pulse example
  
  @verbatim
  ******************** (C) COPYRIGHT 2015 STMicroelectronics *******************
  * @file    TIM/OnePulse/readme.txt 
  * @author  MCD Application Team
  * @version V1.2.2
  * @date    17-November-2021
  * @brief   Description of the TIM One Pulse example.
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

This example shows how to use the TIM peripheral to generate a One pulse Mode 
after a Rising edge of an external signal is received in Timer Input pin.

TIM3CLK = SystemCoreClock, we want to get TIM3 counter clock at 16 MHz:
  - Prescaler = (TIM3CLK / TIM3 counter clock) - 1
SystemCoreClock is set to 32 MHz for Ultra Low Power Medium-Density High-Density
Devices.

The Autoreload value is 65535 (TIM3->ARR), so the maximum frequency value to 
trigger the TIM3 input is 16000000/65535 = 244.144 Hz.

The TIM3 is configured as follows: 
The One Pulse mode is used, the external signal is connected to TIM3 CH2 pin (PA.07), 
the rising edge is used as active edge, the One Pulse signal is output 
on TIM3_CH1 (PA.06).

The TIM_Pulse defines the delay value, the delay value is fixed to:
delay =  CCR1/TIM3 counter clock = 16383 / 16000000 = 1.023ms. 
The (TIM_Period - TIM_Pulse) defines the One Pulse value, the pulse value is fixed to:
One Pulse value = (TIM_Period - TIM_Pulse)/TIM3 counter clock 
                = (65535 - 16383) / 16000000 = 3.072 ms.

@par Directory contents 

  - TIM/OnePulse/stm32l1xx_conf.h    Library Configuration file
  - TIM/OnePulse/stm32l1xx_it.c      Interrupt handlers
  - TIM/OnePulse/stm32l1xx_it.h      Interrupt handlers header file
  - TIM/OnePulse/main.c              Main program
  - TIM/OnePulse/system_stm32l1xx.c  STM32L1xx system source file

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

  - STM32L152-EVAL and STM32L152D-EVAL Set-up 
    - Connect the external signal to the TIM3_CH2 pin (PA.07)
    - Connect the TIM3_CH1 (PA.06) pin to an oscilloscope to monitor the waveform. 

@par How to use it ? 

In order to make the program work, you must do the following:
 - Copy all source files from this example folder to the template folder under
   Project\STM32L1xx_StdPeriph_Templates
 - Open your preferred toolchain
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


