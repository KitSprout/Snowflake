/**
 *       __            ____
 *      / /__ _  __   / __/                      __  
 *     / //_/(_)/ /_ / /  ___   ____ ___  __ __ / /_ 
 *    / ,<  / // __/_\ \ / _ \ / __// _ \/ // // __/ 
 *   /_/|_|/_/ \__//___// .__//_/   \___/\_,_/ \__/  
 *                     /_/   github.com/KitSprout    
 *  
 *  @file    ws2812b.h
 *  @author  KitSprout
 *  @date    28-Nov-2017
 *  @brief   
 * 
 */

/* Define to prevent recursive inclusion ---------------------------------------------------*/
#ifndef __WS2812B_H
#define __WS2812B_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes --------------------------------------------------------------------------------*/
#include "core_cm0.h"

/* Exported types --------------------------------------------------------------------------*/
/* Exported constants ----------------------------------------------------------------------*/
#define WS2812B_COLS    (6)
#define	WS2812B_ROWS    (5)
#define WS2812B_LENS    (31)

/* Exported functions ----------------------------------------------------------------------*/  
void WS2812B_Config( void );

void WS2812B_sendPixel( uint16_t led, uint8_t r, uint8_t g, uint8_t b );
void WS2812B_sendData( uint16_t led_start, uint16_t led_end );
void WS2812B_clearAll( uint8_t r, uint8_t g, uint8_t b );

void WS2812B_testRainbow( void );
void WS2812B_testBreath( uint32_t speed );
void WS2812B_DEMO( void );

inline void WS2812B_setRGB( uint16_t led, uint8_t r, uint8_t g, uint8_t b );

extern uint8_t  WS2812B_rgb[WS2812B_LENS][3];

#ifdef __cplusplus
}
#endif

#endif

/*************************************** END OF FILE ****************************************/
