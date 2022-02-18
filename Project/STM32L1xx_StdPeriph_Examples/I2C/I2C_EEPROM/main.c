/**
  ******************************************************************************
  * @file    I2C/I2C_EEPROM/main.c 
  * @author  MCD Application Team
  * @version V1.2.2
  * @date    17-November-2021
  * @brief   Main program body
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
#ifdef USE_STM32L152D_EVAL
#include "stm32l152d_eval_i2c_ee.h"
#include "stm32l152d_eval_lcd.h"
#else
#include "stm32l152_eval_i2c_ee.h"
#include "stm32l152_eval_lcd.h"
#endif

/** @addtogroup STM32L1xx_StdPeriph_Examples
  * @{
  */

/** @addtogroup I2C_EEPROM
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;

/* Private define ------------------------------------------------------------*/
/* Uncomment the following line to enable using LCD screen for messages display */
#define ENABLE_LCD_MSG_DISPLAY

#define sEE_WRITE_ADDRESS1        0x50
#define sEE_READ_ADDRESS1         0x50
#define BUFFER_SIZE1             (countof(Tx1_Buffer)-1)
#define BUFFER_SIZE2             (countof(Tx2_Buffer)-1)
#define sEE_WRITE_ADDRESS2       (sEE_WRITE_ADDRESS1 + BUFFER_SIZE1)
#define sEE_READ_ADDRESS2        (sEE_READ_ADDRESS1 + BUFFER_SIZE1)

/* Private macro -------------------------------------------------------------*/
#define countof(a) (sizeof(a) / sizeof(*(a)))

/* Private variables ---------------------------------------------------------*/
uint8_t Tx1_Buffer[] = "/* STM32L1xx I2C Firmware Library EEPROM driver example: \
                        This firmware provides a basic example of how to use the I2C firmware library and\
                        an associate I2C EEPROM driver to communicate with an I2C EEPROM device \
                        I2C peripheral is configured in Master transmitter during write operation and in\
                        Master receiver during read operation from I2C EEPROM.*/";

uint8_t Tx2_Buffer[] = "/* STM32F1xx I2C Firmware Library EEPROM driver example : \
                        I2C1 interfacing with M24LR64 EEPROM */";

uint8_t Rx1_Buffer[BUFFER_SIZE1], Rx2_Buffer[BUFFER_SIZE2]; 
volatile TestStatus TransferStatus1 = FAILED, TransferStatus2 = FAILED;
volatile uint16_t NumDataRead = 0;

/* Private functions ---------------------------------------------------------*/
TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength);

/**
  * @brief   Main program
  * @param  None
  * @retval None
*/
int main(void)
{
  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_stm32l1xx_xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32l1xx.c file
     */    

#ifdef ENABLE_LCD_MSG_DISPLAY
  /* Initialize the LCD screen for information display */
#ifdef USE_STM32L152D_EVAL
  STM32L152D_LCD_Init();
#else
  STM32L152_LCD_Init();
#endif 
  LCD_Clear(LCD_COLOR_BLUE);  
  LCD_SetBackColor(LCD_COLOR_BLUE);
  LCD_SetTextColor(LCD_COLOR_WHITE);
  LCD_DisplayStringLine(LCD_LINE_0, "SMT32L1xx FW Library");
  LCD_DisplayStringLine(LCD_LINE_1, "   EEPROM Example   ");
#endif /* ENABLE_LCD_MSG_DISPLAY */  
  
  /* Initialize the I2C EEPROM driver ----------------------------------------*/
  sEE_Init();  

  /* First write in the memory followed by a read of the written data --------*/
  /* Write on I2C EEPROM from sEE_WRITE_ADDRESS1 */
  sEE_WriteBuffer(Tx1_Buffer, sEE_WRITE_ADDRESS1, BUFFER_SIZE1); 

  /* Wait for EEPROM standby state */
  sEE_WaitEepromStandbyState();  
  
  /* Set the Number of data to be read */
  NumDataRead = BUFFER_SIZE1;
  
  /* Read from I2C EEPROM from sEE_READ_ADDRESS1 */
  sEE_ReadBuffer(Rx1_Buffer, sEE_READ_ADDRESS1, (uint16_t *)(&NumDataRead)); 


  /* Starting from this point, if the requested number of data is higher than 1, 
     then only the DMA is managing the data transfer. Meanwhile, CPU is free to 
     perform other tasks:
  
    // Add your code here: 
    //...
    //...

     For simplicity reasons, this example is just waiting till the end of the 
     transfer. */
 
#ifdef ENABLE_LCD_MSG_DISPLAY  
  LCD_DisplayStringLine(LCD_LINE_3, " Transfer 1 Ongoing ");
#endif /* ENABLE_LCD_MSG_DISPLAY */ 
  
  /* Wait till DMA transfer is compelete (Tranfer complete interrupt handler 
    resets the variable holding the number of data to be read) */
  while (NumDataRead > 0)
  {}  
  
  /* Check if the data written to the memory is read correctly */
  TransferStatus1 = Buffercmp(Tx1_Buffer, Rx1_Buffer, BUFFER_SIZE1);
  /* TransferStatus1 = PASSED, if the transmitted and received data 
     to/from the EEPROM are the same */
  /* TransferStatus1 = FAILED, if the transmitted and received data 
     to/from the EEPROM are different */
#ifdef ENABLE_LCD_MSG_DISPLAY  
  if (TransferStatus1 == PASSED)
  {
    LCD_DisplayStringLine(LCD_LINE_3, " Transfer 1 PASSED  ");
  }
  else
  {
    LCD_DisplayStringLine(LCD_LINE_3, " Transfer 1 FAILED  ");
  }  
#endif /* ENABLE_LCD_MSG_DISPLAY */  

  /* Second write in the memory followed by a read of the written data -------*/
  /* Write on I2C EEPROM from sEE_WRITE_ADDRESS2 */
  sEE_WriteBuffer(Tx2_Buffer, sEE_WRITE_ADDRESS2, BUFFER_SIZE2); 

  /* Wait for EEPROM standby state */
  sEE_WaitEepromStandbyState();  
  
  /* Set the Number of data to be read */
  NumDataRead = BUFFER_SIZE2;  
  
  /* Read from I2C EEPROM from sEE_READ_ADDRESS2 */
  sEE_ReadBuffer(Rx2_Buffer, sEE_READ_ADDRESS2, (uint16_t *)(&NumDataRead));


  /* Starting from this point, if the requested number of data is higher than 1, 
     then only the DMA is managing the data transfer. Meanwhile, CPU is free to 
     perform other tasks:
     
    // Add your code here: 
    //...
    //...

     For simplicity reasons, this example is just waiting till the end of the 
     transfer. */

#ifdef ENABLE_LCD_MSG_DISPLAY   
  LCD_DisplayStringLine(LCD_LINE_5, " Transfer 2 Ongoing ");
#endif /* ENABLE_LCD_MSG_DISPLAY */  
  
  /* Wait till DMA transfer is compelete (Tranfer complete interrupt handler 
    resets the variable holding the number of data to be read) */
  while (NumDataRead > 0)
  {}
  
  /* Check if the data written to the memory is read correctly */
  TransferStatus2 = Buffercmp(Tx2_Buffer, Rx2_Buffer, BUFFER_SIZE2);
  /* TransferStatus2 = PASSED, if the transmitted and received data 
     to/from the EEPROM are the same */
  /* TransferStatus2 = FAILED, if the transmitted and received data 
     to/from the EEPROM are different */
#ifdef ENABLE_LCD_MSG_DISPLAY   
  if (TransferStatus2 == PASSED)
  {
    LCD_DisplayStringLine(LCD_LINE_5, " Transfer 2 PASSED  ");
  }
  else
  {
    LCD_DisplayStringLine(LCD_LINE_5, " Transfer 2 FAILED  ");
  }  
#endif /* ENABLE_LCD_MSG_DISPLAY */
  
  /* Free all used resources */
  sEE_DeInit();

  while (1)
  {
  }
}

#ifndef USE_DEFAULT_TIMEOUT_CALLBACK
/**
  * @brief  Example of timeout situation management.
  * @param  None.
  * @retval None.
  */
uint32_t sEE_TIMEOUT_UserCallback(void)
{
  /* Use application may try to recover the communication by resetting I2C
    peripheral (calling the function I2C_SoftwareResetCmd()) then re-start
    the transmission/reception from a previously stored recover point.
    For simplicity reasons, this example only shows a basic way for errors 
    managements which consists of stopping all the process and requiring system
    reset. */
  
#ifdef ENABLE_LCD_MSG_DISPLAY   
  /* Display error message on screen */
  LCD_Clear(LCD_COLOR_RED);  
  LCD_DisplayStringLine(LCD_LINE_4, "Communication ERROR!");
  LCD_DisplayStringLine(LCD_LINE_5, "Try again after res-");
  LCD_DisplayStringLine(LCD_LINE_6, "  etting the Board  ");
#endif /* ENABLE_LCD_MSG_DISPLAY */
  
  /* Block communication and all processes */
  while (1)
  {   
  }  
}
#endif /* USE_DEFAULT_TIMEOUT_CALLBACK */

/**
  * @brief  Compares two buffers.
  * @param  pBuffer1, pBuffer2: buffers to be compared.
  * @param  BufferLength: buffer's length
  * @retval PASSED: pBuffer1 identical to pBuffer2
  *         FAILED: pBuffer1 differs from pBuffer2
  */
TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength)
{
  while(BufferLength--)
  {
    if(*pBuffer1 != *pBuffer2)
    {
      return FAILED;
    }
    
    pBuffer1++;
    pBuffer2++;
  }

  return PASSED;  
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */ 

/**
  * @}
  */ 

