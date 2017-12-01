/**
 *       __            ____
 *      / /__ _  __   / __/                      __  
 *     / //_/(_)/ /_ / /  ___   ____ ___  __ __ / /_ 
 *    / ,<  / // __/_\ \ / _ \ / __// _ \/ // // __/ 
 *   /_/|_|/_/ \__//___// .__//_/   \___/\_,_/ \__/  
 *                     /_/   github.com/KitSprout    
 *  
 *  @file    stm32f0xx_bsp.c
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

void BSP_GPIO_Config( void )
{
  GPIO_InitTypeDef GPIO_InitStruct;

  /* Enable all GPIO Clk *******************************************************/
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);

  /* GPIO all analog input *****************************************************/
  GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_All;
  GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_AN;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOB, &GPIO_InitStruct);
  GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_All & (~(GPIO_Pin_13 | GPIO_Pin_14));
  GPIO_Init(GPIOA, &GPIO_InitStruct);

  GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_OUT;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_NOPULL;

  GPIO_InitStruct.GPIO_Pin   = LED_1_PIN;
  GPIO_Init(LED_1_GPIO_PORT, &GPIO_InitStruct);
  GPIO_InitStruct.GPIO_Pin   = LED_2_PIN;
  GPIO_Init(LED_2_GPIO_PORT, &GPIO_InitStruct);
  GPIO_InitStruct.GPIO_Pin   = LED_3_PIN;
  GPIO_Init(LED_3_GPIO_PORT, &GPIO_InitStruct);
  GPIO_InitStruct.GPIO_Pin   = LED_4_PIN;
  GPIO_Init(LED_4_GPIO_PORT, &GPIO_InitStruct);
  GPIO_InitStruct.GPIO_Pin   = LED_5_PIN;
  GPIO_Init(LED_5_GPIO_PORT, &GPIO_InitStruct);
  GPIO_InitStruct.GPIO_Pin   = LED_6_PIN;
  GPIO_Init(LED_6_GPIO_PORT, &GPIO_InitStruct);

  LED_1_Reset();
  LED_2_Reset();
  LED_3_Reset();
  LED_4_Reset();
  LED_5_Reset();
  LED_6_Reset();

  GPIO_InitStruct.GPIO_Pin   = KEY_PIN;
  GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_IN;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_UP;
  GPIO_Init(KEY_GPIO_PORT, &GPIO_InitStruct);
}

/*************************************** END OF FILE ****************************************/
