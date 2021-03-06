/**
  @page NVIC_IRQ_Mask NVIC IRQ Channels Mask example
  
  @verbatim
  ******************** (C) COPYRIGHT 2015 STMicroelectronics *******************
  * @file    NVIC/IRQ_Mask/readme.txt 
  * @author  MCD Application Team
  * @version V1.2.2
  * @date    17-November-2021
  * @brief   Description of the NVIC IRQ Channels Mask example.
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

This example demontrates the use of the Nested Vectored Interrupt Controller (NVIC)
IRQ Channels configuration and how to mask/activate different IRQs: 

- Configuration of 3 TIM (TIM2..TIM4)timers to generate an interrupt on each 
  counter update event.

- The three timers are linked to their correspondant Update IRQ channel.

- Assignment of a ascendant IRQ priority for each IRQ channel :
     - TIM2 has a preemption priority of 0
     - TIM3 has a preemption priority of 1
     - TIM4 has a preemption priority of 2
- In each interrupt routine: 
   - TIM2 toggles a LED1 each 1s 
   - TIM3 toggles a LED2 each 2s 
   - TIM4 toggles a LED3 each 3s 

- The KEY and SEL buttons are used to boost the execution priority as follows:

  - The KEY button is used in GPIO mode and at each KEY button press, the execution 
    priority is raised to 0 and turn LED4 ON. This prevents all exceptions with 
    configurable priority from activating, other than through the HardFault fault 
    escalation mechanism. As consequence, all LEDs stop toggling as TIM2, TIM3 
    and TIM4 IRQs are prevented from activation. 
    
    Pressing again the KEY button will release the priority boosting, turn LED4 
    OFF and will allow all exceptions with configurable priority to be activated 
    and TIM2, TIM3 and TIM4 can be generated again and the LEDs restart toggling.
    
    This execution priority is made using the CMSIS functions "__disable_irq()" 
    and "__enable_irq()". 
    These two functions are managing the Cortex-M3 PRIMASK special register.

  - The SEL button is used in EXTI mode and at each SEL button press, the execution 
    priority is masked to 0x40 using the BASEPRI register. 
    A non-zero value will act as a priority mask, affecting the execution priority 
    when the priority defined by BASEPRI is the same or higher than the current 
    executing priority. 
    As consequence, LED2 and LED3 stop toggling as TIM3 and TIM4 IRQs are 
    prevented from activation. 
    Pressing again the SEL button will configure the BASEPRI register to 0, 
    thus it has no effect on the current priority and TIM3 and TIM4 can be 
    generated again and LED2 and LED3 restart toggling.
    
    This execution priority is made using the CMSIS functions "__set_BASEPRI()". 
    This function is managing the Cortex-M3 BASEPRI special register.
    Setting the BASEPRI register has no effect when the execution priority is
    raised to 0 using the "__disable_irq()" function.

@note These mechanisms only affect the group priority. They have no effect on 
      the sub-priority. The sub-priority is only used to sort pending exception 
      priorities, and does not affect active exceptions.
      
@par Directory contents 

  - NVIC/IRQ_Mask/stm32l1xx_conf.h    Library Configuration file
  - NVIC/IRQ_Mask/stm32l1xx_it.c      Interrupt handlers
  - NVIC/IRQ_Mask/stm32l1xx_it.h      Interrupt handlers header file
  - NVIC/IRQ_Mask/main.c              Main program
  - NVIC/IRQ_Mask/system_stm32l1xx.c  STM32L1xx system source file
  
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
    - Use LED1, LED2, LED3 and LED4 leds connected respectively to PD.00, PD.01, PD04 and PD.05 pins.
    - Make sure that JP18 Jumper is closed.

  - STM32L152D-EVAL Set-up
    - Use LED1, LED2, LED3 and LED4 leds connected respectively to PD.03, PD.07, PG.14 and PG.15 pins.
      
@par How to use it ? 

In order to make the program work, you must do the following:
 - Copy all source files from this example folder to the template folder under
   Project\STM32L1xx_StdPeriph_Templates
 - Open your preferred toolchain
 - If the used device is STM32L1XX_MD choose "STM32L1XX_MD(STM32L1xxxBxx)" workspace
    - Add the following files to the project source list
       - Utilities\STM32_EVAL\STM32L152_EVAL\stm32l152_eval.c
 - If the used device is STM32L1XX_HD choose "STM32L1XX_HD(STM32L1xxxDxx)" workspace
    - Add the following files to the project source list
       - Utilities\STM32_EVAL\STM32L152D_EVAL\stm32l152d_eval.c 
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


