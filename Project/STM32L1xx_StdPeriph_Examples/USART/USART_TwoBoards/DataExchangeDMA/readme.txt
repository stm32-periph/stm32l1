/**
  @page USART_DataExchangeDMA USART Communication Boards Data Exchange using DMA example
  
  @verbatim
  ******************** (C) COPYRIGHT 2010 STMicroelectronics *******************
  * @file    USART/USART_TwoBoards/DataExchangeDMA/readme.txt 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    31-December-2010
  * @brief   Description of the USART Communication Boards Data Exchange using 
  *          DMA example.
  ******************************************************************************
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  ******************************************************************************
   @endverbatim

@par Example Description 

This example provides a small application in which joystick buttons are used 
to trigger USART communications using DMA and though using USART firmware library.

- Hardware Description

To use this example, you need to load it on two STM32 boards (let's call them 
Board A and Board B) then connect these two boards through USART lines and GND.

@verbatim
*------------------------------------------------------------------------------*
|                BOARD A                                BOARD B                |
|         ____________________                   ____________________          |
|        |                    |                 |                    |         |
|        |                    |                 |                    |         | 
|        |     __________     |                 |     __________     |         |
|        |    |   USART  |____|TX_____________RX|____|   USART  |    |         |
|        |    |  Device1 |____|RX_____________TX|____|  Device2 |    |         |
|        |    |__________|    |                 |    |__________|    |         |
|        |                    |                 |                    |         |
|        |  O LD1             |                 |  O LD1             |         |
|        |  O LD2    Joystick |                 |  O LD2    Joystick |         |
|        |  O LD3        _    |                 |  O LD3        _    |         |
|        |  O LD4       |_|   |                 |  O LD4       |_|   |         |
|        |                    |                 |                    |         |
|        |             GND O--|-----------------|--O GND             |         |
|        |____________________|                 |____________________|         |
|                                                                              |
|                                                                              |
*------------------------------------------------------------------------------*
@endverbatim

@note
- The connection between the pins should use a common Ground.

- Software Description

On Board A, at each joystick buttons press:
- The USART Board A sends the specific command to the USART Board B (the command 
  contains the transaction code (CMD_RIGHT, CMD_LEFT, CMD_UP, CMD_DOWN or CMD_SEL)
  followed by the number of data to be transmitted (CMD_RIGHT_SIZE, CMD_LEFT_SIZE, 
  CMD_UP_SIZE, CMD_DOWN_SIZE or CMD_SEL_SIZE)

- The USART Board B receives the command and sends the CMD_ACK command to the USART board A

- The USART Board A receives the CMD_ACK command and sends the number of bytes 
  from TxBuffer to the USART Board B.
  
- The USART Board B compares the number of bytes received with the defined ones into
  his TxBuffer.
  
  Received data correctness is signaled by LED lightening and though as follow:
   - Joystick RIGHT and data correctly received ==> LD2, LD3 ON and LD4 OFF 
   - Joystick LEFT and data correctly received  ==> LD4 ON, LD2 and LD3 are OFF
   - Joystick UP and data correctly received    ==> LD2 ON, LD3 and LD4 are OFF
   - Joystick DOWN and data correctly received  ==> LD3 ON, LD2 and LD4 are OFF
   - Joystick SEL and data correctly received   ==> LD2, LD3 and LD4 are ON

The steps described above can be also initiated and ensured by Board B. 

In both boards(Board A or Board B), the data transfers is managed using the USART 
Tx/Rx channels DMA requests.

The SysTick is configured to generate interrupt each 10ms. A dedicated counter 
inside the SysTick ISR is used to toggle the LD1 each 100ms indicating that the 
firmware is running.

A defined communication timeout is insuring that the application will not remain 
stuck if the USART communication is corrupted.
You can adjust this timeout through the USER_TIMEOUT  define inside main.h file
depending on CPU frequency and application conditions (interrupts routines, 
number of data to transfer, baudrate, CPU frequency...).

These operations can be repeated infinitely.
   
@par Directory contents 

  - USART/USART_TwoBoards/DataExchangeDMA/stm32l1xx_conf.h    Library Configuration file
  - USART/USART_TwoBoards/DataExchangeDMA/stm32l1xx_it.c      Interrupt handlers
  - USART/USART_TwoBoards/DataExchangeDMA/stm32l1xx_it.h      Interrupt handlers header file
  - USART/USART_TwoBoards/DataExchangeDMA/main.c              Main program
  - USART/USART_TwoBoards/DataExchangeDMA/main.h              Main program header file
  - USART/USART_TwoBoards/DataExchangeDMA/system_stm32l1xx.c  STM32L1xx system source file
  
@note The "system_stm32l1xx.c" is generated by an automatic clock configuration 
      system and can be easily customized to your own configuration. 
      To select different clock setup, use the "STM32L1xx_Clock_Configuration_V1.0.0.xls" 
      provided with the AN3309 package available on <a href="http://www.st.com/internet/mcu/family/141.jsp">  ST Microcontrollers </a>
         
@par Hardware and Software environment

  - This example runs on STM32L1xx Ultra Low Power Medium-Density Devices.
  
  - This example has been tested with STMicroelectronics STM32L152-EVAL (STM32L1xx 
    Ultra Low Power Medium-Density) evaluation board and can be easily tailored 
    to any other supported device and development board.

  - STM32L152-EVAL Set-up
    - Use LED1, LED2, LED3 and LED4 connected respectively to PD.00, PD.01, PD.04 
      and PD.05 pins for each eval boards.
    - Use The Joystick Push Button 
       - DOWN[PE.10]
       - UP[PE.09]
       - LEFT[PE.12]
       - RIGHT[PE.11] 
       - SEL[PE.08]
    - Connect USART1 TX pin (PA.09) to USART1 RX pin (PA.10)
    - Connect USART1 RX pin (PA.10) to USART1 TX pin (PA.09)
  
@par How to use it ? 

In order to make the program work, you must do the following :
 - Copy all source files from this example folder to the template folder under
   Project\STM32L1xx_StdPeriph_Template
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example

@note
- Ultra Low Power Medium-density devices are STM32L151xx and STM32L152xx 
  microcontrollers where the Flash memory density ranges between 64 and 128 Kbytes.
    
 * <h3><center>&copy; COPYRIGHT 2010 STMicroelectronics</center></h3>
 */