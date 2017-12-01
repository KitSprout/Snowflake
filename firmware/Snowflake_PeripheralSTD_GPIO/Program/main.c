/**
 *       __            ____
 *      / /__ _  __   / __/                      __  
 *     / //_/(_)/ /_ / /  ___   ____ ___  __ __ / /_ 
 *    / ,<  / // __/_\ \ / _ \ / __// _ \/ // // __/ 
 *   /_/|_|/_/ \__//___// .__//_/   \___/\_,_/ \__/  
 *                     /_/   github.com/KitSprout    
 *  
 *  @file    main.c
 *  @author  KitSprout
 *  @date    28-Nov-2017
 *  @brief   
 * 
 */

/* Includes --------------------------------------------------------------------------------*/
#include "drivers\stm32f0_system.h"
#include "stm32f0xx_bsp.h"

/** @addtogroup STM32_Program
  * @{
  */

/* Private typedef -------------------------------------------------------------------------*/
/* Private define --------------------------------------------------------------------------*/
/* Private macro ---------------------------------------------------------------------------*/
/* Private variables -----------------------------------------------------------------------*/
/* Private function prototypes -------------------------------------------------------------*/
/* Private functions -----------------------------------------------------------------------*/

int main( void )
{
  HAL_InitTick();
  BSP_GPIO_Config();

  while (1) {
    LED_1_Set();
    LED_2_Set();
    LED_3_Set();
    LED_4_Set();
    LED_5_Set();
    LED_6_Set();
    delay_ms(50);
    LED_1_Reset();
    LED_2_Reset();
    LED_3_Reset();
    LED_4_Reset();
    LED_5_Reset();
    LED_6_Reset();
    delay_ms(2450);

    while (KEY_Read()) {
      LED_1_Set();
      delay_ms(50);
      LED_1_Reset();
      LED_2_Set();
      delay_ms(50);
      LED_2_Reset();
      LED_3_Set();
      delay_ms(50);
      LED_3_Reset();
      LED_4_Set();
      delay_ms(50);
      LED_4_Reset();
      LED_5_Set();
      delay_ms(50);
      LED_5_Reset();
      LED_6_Set();
      delay_ms(50);
      LED_6_Reset();
    }
  }
}

/*************************************** END OF FILE ****************************************/
