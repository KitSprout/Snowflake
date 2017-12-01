/**
 *       __            ____
 *      / /__ _  __   / __/                      __  
 *     / //_/(_)/ /_ / /  ___   ____ ___  __ __ / /_ 
 *    / ,<  / // __/_\ \ / _ \ / __// _ \/ // // __/ 
 *   /_/|_|/_/ \__//___// .__//_/   \___/\_,_/ \__/  
 *                     /_/   github.com/KitSprout    
 *  
 *  @file    boardConfig.h
 *  @author  KitSprout
 *  @date    28-Nov-2017
 *  @brief   
 * 
 */

/* Define to prevent recursive inclusion ---------------------------------------------------*/
#ifndef __BOARDCONFIG_H
#define __BOARDCONFIG_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes --------------------------------------------------------------------------------*/
/* Exported types --------------------------------------------------------------------------*/
/* Exported constants ----------------------------------------------------------------------*/

#define KS_HW_BOARD_NAME              "Snowflake"
#define KS_HW_MCU_NAME                "STM32F030F4"

#define KS_HW_USE_CLOCK_SOUCE_HSI     (0U)
#define KS_HW_USE_CLOCK_SOUCE_HSE     (1U)
#define KS_HW_CLOCK_SOUCE             KS_HW_USE_CLOCK_SOUCE_HSE

#define KS_FW_UART_HAL_LIBRARY        (0U)
#define KS_FW_SPI_HAL_LIBRARY         (0U)
#define KS_FW_I2C_HAL_LIBRARY         (0U)

#define KS_SYSCLK                     SystemCoreClock


/* -------- LED and KEY */

#define LED_1_PIN                     GPIO_Pin_4
#define LED_1_GPIO_PORT               GPIOA
#define LED_1_Set()                   __GPIO_SET(LED_1_GPIO_PORT, LED_1_PIN)
#define LED_1_Reset()                 __GPIO_RST(LED_1_GPIO_PORT, LED_1_PIN)
#define LED_1_Toggle()                __GPIO_TOG(LED_1_GPIO_PORT, LED_1_PIN)

#define LED_2_PIN                     GPIO_Pin_5
#define LED_2_GPIO_PORT               GPIOA
#define LED_2_Set()                   __GPIO_SET(LED_2_GPIO_PORT, LED_2_PIN)
#define LED_2_Reset()                 __GPIO_RST(LED_2_GPIO_PORT, LED_2_PIN)
#define LED_2_Toggle()                __GPIO_TOG(LED_2_GPIO_PORT, LED_2_PIN)

#define LED_3_PIN                     GPIO_Pin_0
#define LED_3_GPIO_PORT               GPIOA
#define LED_3_Set()                   __GPIO_SET(LED_3_GPIO_PORT, LED_3_PIN)
#define LED_3_Reset()                 __GPIO_RST(LED_3_GPIO_PORT, LED_3_PIN)
#define LED_3_Toggle()                __GPIO_TOG(LED_3_GPIO_PORT, LED_3_PIN)

#define LED_4_PIN                     GPIO_Pin_1
#define LED_4_GPIO_PORT               GPIOA
#define LED_4_Set()                   __GPIO_SET(LED_4_GPIO_PORT, LED_4_PIN)
#define LED_4_Reset()                 __GPIO_RST(LED_4_GPIO_PORT, LED_4_PIN)
#define LED_4_Toggle()                __GPIO_TOG(LED_4_GPIO_PORT, LED_4_PIN)

#define LED_5_PIN                     GPIO_Pin_2
#define LED_5_GPIO_PORT               GPIOA
#define LED_5_Set()                   __GPIO_SET(LED_5_GPIO_PORT, LED_5_PIN)
#define LED_5_Reset()                 __GPIO_RST(LED_5_GPIO_PORT, LED_5_PIN)
#define LED_5_Toggle()                __GPIO_TOG(LED_5_GPIO_PORT, LED_5_PIN)

#define LED_6_PIN                     GPIO_Pin_3
#define LED_6_GPIO_PORT               GPIOA
#define LED_6_Set()                   __GPIO_SET(LED_6_GPIO_PORT, LED_6_PIN)
#define LED_6_Reset()                 __GPIO_RST(LED_6_GPIO_PORT, LED_6_PIN)
#define LED_6_Toggle()                __GPIO_TOG(LED_6_GPIO_PORT, LED_6_PIN)

#define KEY_PIN                       GPIO_Pin_1
#define KEY_GPIO_PORT                 GPIOB
#define KEY_Read()                    (__GPIO_READ(KEY_GPIO_PORT, KEY_PIN) != KEY_PIN)


/* Exported functions ----------------------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif

/*************************************** END OF FILE ****************************************/
