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
#include "modules\ws2812b.h"

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
//  while(1) {
//    LED_1_Toggle();
//    LED_2_Toggle();
//    LED_3_Toggle();
//    LED_4_Toggle();
//    LED_5_Toggle();
//    LED_6_Toggle();
//    delay_ms(50);
//    LED_1_Toggle();
//    LED_2_Toggle();
//    LED_3_Toggle();
//    LED_4_Toggle();
//    LED_5_Toggle();
//    LED_6_Toggle();
//    delay_ms(1450);
//  }
  WS2812B_Config();
  while(1) {
    LED_1_Toggle();
//    LED_2_Toggle();
//    LED_3_Toggle();
//    LED_4_Toggle();
//    LED_5_Toggle();
//    LED_6_Toggle();
    WS2812B_testBreath(50);
  }
//  uint8_t i = 0;
  
//    i++;
//    WS2812B_sendPixel(0, i, 128, 255);
//    LED_1_Toggle();
//    delay_ms(50);
//  }
}

/*************************************** END OF FILE ****************************************/
