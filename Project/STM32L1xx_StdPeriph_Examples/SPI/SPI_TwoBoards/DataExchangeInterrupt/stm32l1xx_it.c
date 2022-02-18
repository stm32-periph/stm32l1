/**
  ******************************************************************************
  * @file    SPI/SPI_TwoBoards/DataExchangeInterrupt/stm32l1xx_it.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    31-December-2010
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and peripherals
  *          interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2010 STMicroelectronics</center></h2>
  ******************************************************************************  
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32l1xx_it.h"
#include "main.h"

/** @addtogroup STM32L1xx_StdPeriph_Examples
  * @{
  */

/** @addtogroup SPI_DataExchangeInterrupt
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern uint8_t TxBuffer[];
extern  uint8_t RxBuffer[];
extern __IO uint8_t Rx_Idx;
extern __IO uint8_t Tx_Idx;

extern __IO uint8_t CmdTransmitted;
extern __IO uint8_t CmdReceived;
extern __IO uint8_t CmdStatus;

__IO uint8_t Counter = 0x00;
extern __IO uint32_t TimeOut;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{}

/**
  * @brief  This function handles PendSV_Handler exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
  /* Decrement the timeout value */
  if (TimeOut != 0x0)
  {
    TimeOut--;
  }
    
  if (Counter < 10)
  {
    Counter++;
  }
  else
  {
    Counter = 0x00;
    STM_EVAL_LEDToggle(LED1);
  }
}

/******************************************************************************/
/*            STM32L1xx Peripherals Interrupt Handlers                        */
/******************************************************************************/
/**
  * @brief  This function handles SPI interrupt request.
  * @param  None
  * @retval None
  */
void SPIx_IRQHANDLER(void)
{
#if defined (SPI_SLAVE)

  /* SPI in Slave Tramitter mode--------------------------------------- */
  if (SPI_I2S_GetITStatus(SPIx, SPI_I2S_IT_TXE) == SET)
  {
    SPI_I2S_SendData(SPIx, TxBuffer[Tx_Idx++]);
  }

  /* SPI in Slave Receiver mode--------------------------------------- */
  if (SPI_I2S_GetITStatus(SPIx, SPI_I2S_IT_RXNE) == SET)
  {
    if (CmdReceived == 0x00)
    {
      CmdReceived = SPI_I2S_ReceiveData(SPIx);
      CmdStatus = 0x01;
    }
    else
    {
      RxBuffer[Rx_Idx++] = SPI_I2S_ReceiveData(SPIx);
    }
  }

  /* SPI Error interrupt--------------------------------------- */
  if (SPI_I2S_GetITStatus(SPIx, SPI_I2S_IT_OVR) == SET)
  {
    SPI_I2S_ReceiveData(SPIx);
    SPI_I2S_GetITStatus(SPIx, SPI_I2S_IT_OVR);
  }

#endif /* SPI_SLAVE*/

#if defined (SPI_MASTER)

  /* SPI in Master Tramitter mode--------------------------------------- */
  if (SPI_I2S_GetITStatus(SPIx, SPI_I2S_IT_TXE) == SET)
  {
    if (CmdStatus == 0x00)
    {
      SPI_I2S_SendData(SPIx, CmdTransmitted);
      CmdStatus = 0x01;
    }
    else
    {
      SPI_I2S_SendData(SPIx, TxBuffer[Tx_Idx++]);
      if (Tx_Idx == GetVar_NbrOfData())
      {
        /* Disable the Tx buffer empty interrupt */
        SPI_I2S_ITConfig(SPIx, SPI_I2S_IT_TXE, DISABLE);
      }
    }
  }

  /* SPI in Master Receiver mode--------------------------------------- */
  if (SPI_I2S_GetITStatus(SPIx, SPI_I2S_IT_RXNE) == SET)
  {
    if (CmdReceived == 0x00)
    {
      CmdReceived = SPI_I2S_ReceiveData(SPIx);
      Rx_Idx = 0x00;
    }
    else
    {
      RxBuffer[Rx_Idx++] = SPI_I2S_ReceiveData(SPIx);
    }
  }

  /* SPI Error interrupt--------------------------------------- */
  if (SPI_I2S_GetITStatus(SPIx, SPI_I2S_IT_OVR) == SET)
  {
    SPI_I2S_ReceiveData(SPIx);
    SPI_I2S_GetITStatus(SPIx, SPI_I2S_IT_OVR);
  }

#endif /* SPI_MASTER*/
}

/******************************************************************************/
/*                 STM32L1xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32l1xx_md.s).                                            */
/******************************************************************************/
/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
