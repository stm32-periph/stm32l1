/**
  ******************************************************************************
  * @file    PWR/BOR/main.c 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    31-December-2010
  * @brief   Main program body
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
#include "stm32l1xx.h"
#include "stm32_eval.h"

/** @addtogroup STM32L1xx_StdPeriph_Examples
  * @{
  */

/** @addtogroup PWR_BOR
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Uncomment this line to modify the BOR Level */
#define BOR_MODIFY
/* Select the BOR level */
#ifdef BOR_MODIFY
//#define BOR_LEVEL OB_BOR_OFF  /*!< BOR is disabled at power down, the reset is asserted when the VDD power supply reachs the PDR(Power Down Reset) threshold (1.5V) */
#define BOR_LEVEL OB_BOR_LEVEL1  /*!< BOR Reset threshold levels for 1.7V - 1.8V VDD power supply */
//#define BOR_LEVEL OB_BOR_LEVEL2  /*!< BOR Reset threshold levels for 1.9V - 2.0V VDD power supply */
//#define BOR_LEVEL OB_BOR_LEVEL3  /*!< BOR Reset threshold levels for 2.3V - 2.4V VDD power supply */
//#define BOR_LEVEL OB_BOR_LEVEL4  /*!< BOR Reset threshold levels for 2.55V - 2.65V VDD power supply */
//#define BOR_LEVEL OB_BOR_LEVEL5  /*!< BOR Reset threshold levels for 2.8V - 2.9V VDD power supply */
#endif

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
__IO uint32_t i = 0, BOROptionBytes = 0;

/* Private function prototypes -----------------------------------------------*/


/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_stm32l1xx_md.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32l1xx.c file
     */     
       
  /* Initialize LED1 on STM32L152-EVAL board */
  STM_EVAL_LEDInit(LED1);
  
  /* Get BOR Option Bytes */
  BOROptionBytes = FLASH_OB_GetBOR();

  
#ifdef BOR_MODIFY
  if((BOROptionBytes & 0x0F) != BOR_LEVEL) 
  {
    /* Unlocks the option bytes block access */
    FLASH_OB_Unlock();

    /* Clears the FLASH pending flags */
    FLASH_ClearFlag(FLASH_FLAG_EOP|FLASH_FLAG_WRPERR | FLASH_FLAG_PGAERR
                  | FLASH_FLAG_SIZERR | FLASH_FLAG_OPTVERR);

    /* Select the desired V(BOR) Level ---------------------------------------*/
    FLASH_OB_BORConfig(BOR_LEVEL); 

    /* Launch the option byte loading */
    FLASH_OB_Launch();  
  }
#endif
     
  while (1)
  {
    /* Toggle The LED1 */
    STM_EVAL_LEDToggle(LED1);

    /* Inserted Delay */
    for(i = 0; i < 0x5FFFF; i++);
  }
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

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/