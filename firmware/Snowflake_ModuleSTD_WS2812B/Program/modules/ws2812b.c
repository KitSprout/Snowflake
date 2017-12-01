/**
 *       __            ____
 *      / /__ _  __   / __/                      __  
 *     / //_/(_)/ /_ / /  ___   ____ ___  __ __ / /_ 
 *    / ,<  / // __/_\ \ / _ \ / __// _ \/ // // __/ 
 *   /_/|_|/_/ \__//___// .__//_/   \___/\_,_/ \__/  
 *                     /_/   github.com/KitSprout    
 *  
 *  @file    stm32f0_delay.c
 *  @author  KitSprout
 *  @date    28-Nov-2017
 *  @brief   
 * 
 */

/* Includes --------------------------------------------------------------------------------*/
#include "drivers\stm32f0_system.h"
#include "modules\ws2812b.h"

/* Private typedef -------------------------------------------------------------------------*/
/* Private define --------------------------------------------------------------------------*/
/* Private macro ---------------------------------------------------------------------------*/
//#define TIMx                              TIM3
//#define TIMx_CLK()                        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE)
//#define TIMx_CCRx                         TIM3->CCR1
//#define TIM_OCxInit(_TIMx, _OCx)          TIM_OC1Init(_TIMx, _OCx)
//#define TIM_OCxPreloadConfig(_TIMx, _EN)  TIM_OC1PreloadConfig(_TIMx, _EN)

//#define TIMx_SIG_PIN                      GPIO_Pin_6
//#define TIMx_SIG_GPIO_PORT                GPIOA

//#define TIMx_DMA                          DMA1_Channel4
//#define TIMx_DMA_CCx                      TIM_DMA_CC1
//#define TIMx_DMA_CLK()                    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE)
//#define TIMx_DMA_FLAG_TCx                 DMA1_FLAG_TC4

#define PWM_H_WIDTH                       (17)  // logical 1
#define PWM_L_WIDTH                       (9)   // logical 0
#define WS2812B_LOGIC(_DATA)              (((_DATA) & 0x80) ? (PWM_H_WIDTH) : (PWM_L_WIDTH))
#define WS2812B_BUF_LENS                  (24 * WS2812B_LENS + 42)

/* Private variables -----------------------------------------------------------------------*/
uint8_t WS2812B_rgb[WS2812B_LENS][3] = {0};
static uint16_t WS2812B_dmaBuf[WS2812B_BUF_LENS] = {0};

/* Private function prototypes -------------------------------------------------------------*/
/* Private functions -----------------------------------------------------------------------*/

void WS2812B_Config( void )
{
  GPIO_InitTypeDef GPIO_Struct;
  DMA_InitTypeDef DMA_InitStruct;
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;
  TIM_OCInitTypeDef TIM_OCInitStruct;

  /* TIM Clk *******************************************************************/
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

  GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_1);

  /* TIM GPIO ******************************************************************/
  GPIO_Struct.GPIO_Pin   = GPIO_Pin_6;
  GPIO_Struct.GPIO_Mode  = GPIO_Mode_AF;
  GPIO_Struct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Struct.GPIO_OType = GPIO_OType_PP;
  GPIO_Struct.GPIO_PuPd  = GPIO_PuPd_UP;
  GPIO_Init(GPIOA, &GPIO_Struct);

  /* TIM TimeBase **************************************************************/
  TIM_TimeBaseStruct.TIM_Prescaler     = (uint16_t)(2 - 1);     // 24MHz
  TIM_TimeBaseStruct.TIM_Period        = (uint16_t)(30 - 1);    // 800KHz
  TIM_TimeBaseStruct.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStruct.TIM_CounterMode   = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStruct);
  TIM_ARRPreloadConfig(TIM3, DISABLE);

  /* TIM PWM Output ************************************************************/
  TIM_OCInitStruct.TIM_OCMode       = TIM_OCMode_PWM1;
  TIM_OCInitStruct.TIM_OutputState  = TIM_OutputState_Enable;
  TIM_OCInitStruct.TIM_OCPolarity   = TIM_OCPolarity_High;
  TIM_OCInitStruct.TIM_Pulse        = 0;
  TIM_OC1Init(TIM3, &TIM_OCInitStruct);
  TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);

  /* TIM DMA ******************************************************************/
  DMA_DeInit(DMA1_Channel4);
  DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)&(TIM3->CCR1);
  DMA_InitStruct.DMA_MemoryBaseAddr     = (uint32_t)&WS2812B_dmaBuf;
  DMA_InitStruct.DMA_DIR                = DMA_DIR_PeripheralDST;
  DMA_InitStruct.DMA_BufferSize         = WS2812B_BUF_LENS;
  DMA_InitStruct.DMA_PeripheralInc      = DMA_PeripheralInc_Disable;
  DMA_InitStruct.DMA_MemoryInc          = DMA_MemoryInc_Enable;
  DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  DMA_InitStruct.DMA_MemoryDataSize     = DMA_MemoryDataSize_HalfWord;
  DMA_InitStruct.DMA_Mode               = DMA_Mode_Normal;
  DMA_InitStruct.DMA_Priority           = DMA_Priority_High;
  DMA_InitStruct.DMA_M2M                = DMA_M2M_Disable;
  DMA_Init(DMA1_Channel4, &DMA_InitStruct);
  TIM_DMACmd(TIM3, TIM_DMA_CC1, ENABLE);
}
FlagStatus getFlag( void )
{
  return ((DMA1->ISR & DMA1_FLAG_TC4) != (uint32_t)RESET) ? SET : RESET;
}
static void WS2812B_DMA_SEND( void )
{
  DMA_SetCurrDataCounter(DMA1_Channel4, WS2812B_BUF_LENS);
  DMA_Cmd(DMA1_Channel4, ENABLE);
  TIM_Cmd(TIM3, ENABLE);
  while (!getFlag());
//  while (!DMA_GetFlagStatus(DMA1_FLAG_TC4));
  TIM_Cmd(TIM3, DISABLE);
  DMA_Cmd(DMA1_Channel4, DISABLE);
  DMA_ClearFlag(DMA1_FLAG_TC4);
}

//static void WS2812B_setDmaBuf( uint16_t led_start, uint16_t led_end )
//{
//  uint8_t tmpData = 0;
//  uint16_t memAddr = 24 * led_start;

//  do {
//    for(uint8_t i = 0; i < 3; i++) {
//      tmpData = WS2812B_rgb[led_start][i];
//      for(uint8_t j = 0; j < 8; j++) {
//        WS2812B_dmaBuf[memAddr++] = WS2812B_LOGIC(tmpData);
//        tmpData = tmpData << 1;
//      }
//    }
//  } while(led_start++ < led_end);
//}

inline void WS2812B_setRGB( uint16_t led, uint8_t r, uint8_t g, uint8_t b )
{
  WS2812B_rgb[led][0] = g;
  WS2812B_rgb[led][1] = r;
  WS2812B_rgb[led][2] = b;
}

void WS2812B_sendPixel( uint16_t led, uint8_t r, uint8_t g, uint8_t b )
{
  uint8_t tmpData = 0;
  uint16_t memAddr = 24 * led;

  WS2812B_rgb[led][0] = g;
  WS2812B_rgb[led][1] = r;
  WS2812B_rgb[led][2] = b;

  for(uint8_t i = 0; i < 3; i++) {
    tmpData = WS2812B_rgb[led][i];
    for(uint8_t j = 0; j < 8; j++) {
      WS2812B_dmaBuf[memAddr++] = WS2812B_LOGIC(tmpData);
      tmpData = tmpData << 1;
    }
	}

  WS2812B_DMA_SEND();
}

void WS2812B_sendData( uint16_t led_start, uint16_t led_end )
{
  uint8_t tmpData = 0;
  uint16_t memAddr = 24 * led_start;

  do {
    for(uint8_t i = 0; i < 3; i++) {
      tmpData = WS2812B_rgb[led_start][i];
      for(uint8_t j = 0; j < 8; j++) {
        WS2812B_dmaBuf[memAddr++] = WS2812B_LOGIC(tmpData);
        tmpData = tmpData << 1;
      }
    }
  } while(led_start++ < led_end);

  WS2812B_DMA_SEND();
}

void WS2812B_clearAll( uint8_t r, uint8_t g, uint8_t b )
{
  for (uint8_t i = 0; i < WS2812B_LENS; i++) {
    WS2812B_rgb[i][0] = g;
    WS2812B_rgb[i][1] = r;
    WS2812B_rgb[i][2] = b;
  }
  WS2812B_sendData(0, WS2812B_LENS - 1);
}

#define TLIG_R 16
void WS2812B_testRainbow( void )
{
  uint8_t intStageNum = 0;
  uint8_t r = TLIG_R, g = 0, b = 0;

  for(uint16_t i = 0; i < TLIG_R * 6; i++) {
    switch(intStageNum) {
      case 0: { g++; if(g == TLIG_R) { intStageNum = 1;}  break; }
      case 1: { r--; if(r == 0)      { intStageNum = 2;}  break; }
      case 2: { b++; if(b == TLIG_R) { intStageNum = 3;}  break; }
      case 3: { g--; if(g == 0)      { intStageNum = 4;}  break; }
      case 4: { r++; if(r == TLIG_R) { intStageNum = 5;}  break; }
      case 5: { b--; if(b == 0)      { intStageNum = 0;}  break; }
    }
    for(uint8_t j = 0; j < WS2812B_LENS; j++) {
      WS2812B_rgb[j][0] = g;
      WS2812B_rgb[j][1] = r;
      WS2812B_rgb[j][2] = b;
    }

    WS2812B_sendData(0, WS2812B_LENS - 1);
    delay_ms(100);
  }
}

#define TLIG_B 24
void WS2812B_testBreath( uint32_t speed )
{
  uint8_t state = 1;
  uint8_t color = 0;

  for(uint16_t i = 0; i < TLIG_B * 2; i++) {
    color = (state == 1) ? (color + 1) : (color - 1);
    WS2812B_clearAll(color, color, color);
    delay_ms(speed);

    if(color == TLIG_B)
      state = 0;
    else if (color == 0) {
      state = 1;
    }
  }
}

void WS2812B_DEMO( void )
{
  WS2812B_clearAll(0, 0, 0);
  delay_ms(100);

  WS2812B_testBreath(40);
  WS2812B_testBreath(40);
  delay_ms(100);
  for(uint8_t i = 0; i < TLIG_R; i++) {
    WS2812B_clearAll(i, 0, 0);
    delay_ms(100);
  }

  while(1) {
    WS2812B_testRainbow();
  }
}

/*************************************** END OF FILE ****************************************/
