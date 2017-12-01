/**
 *       __            ____
 *      / /__ _  __   / __/                      __  
 *     / //_/(_)/ /_ / /  ___   ____ ___  __ __ / /_ 
 *    / ,<  / // __/_\ \ / _ \ / __// _ \/ // // __/ 
 *   /_/|_|/_/ \__//___// .__//_/   \___/\_,_/ \__/  
 *                     /_/   github.com/KitSprout    
 *  
 *  @file    stm32f0xx_it.c
 *  @author  KitSprout
 *  @date    28-Nov-2017
 *  @brief   
 * 
 */

/* Includes --------------------------------------------------------------------------------*/
#include "drivers\stm32f0_system.h"

/** @addtogroup STM32_Interrupt
  * @{
  */

/* Private variables -----------------------------------------------------------------------*/
/* Private functions -----------------------------------------------------------------------*/

void NMI_Handler( void ) { while(1); }
void HardFault_Handler( void ) { while(1); }
void SVC_Handler( void ) { while(1); }
void PendSV_Handler( void ) { while(1); }
void SysTick_Handler( void ) { HAL_IncTick(); }

//void WWDG_IRQHandler( void )
//void RTC_IRQHandler( void )
//void FLASH_IRQHandler( void )
//void RCC_IRQHandler( void )
//void EXTI0_1_IRQHandler( void )
//void EXTI2_3_IRQHandler( void )
//void EXTI4_15_IRQHandler( void )
//void DMA1_Channel1_IRQHandler( void )
//void DMA1_Channel2_3_IRQHandler( void )
//void DMA1_Channel4_5_IRQHandler( void )
//void ADC1_IRQHandler( void )
//void TIM1_BRK_UP_TRG_COM_IRQHandler( void )
//void TIM1_CC_IRQHandler( void )
//void TIM3_IRQHandler( void )
//void TIM14_IRQHandler( void )
//void TIM15_IRQHandler( void )
//void TIM16_IRQHandler( void )
//void TIM17_IRQHandler( void )
//void I2C1_IRQHandler( void )
//void I2C2_IRQHandler( void )
//void SPI1_IRQHandler( void )
//void SPI2_IRQHandler( void )
//void USART1_IRQHandler( void )
//void USART2_IRQHandler( void )

/*************************************** END OF FILE ****************************************/
