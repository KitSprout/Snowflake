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
#include "stm32f0xx.h"

/** @addtogroup STM32_Program
  * @{
  */

/* Private typedef -------------------------------------------------------------------------*/
/* Private define --------------------------------------------------------------------------*/
#define NOTE TIM14->ARR
uint16_t note = 0;


#define T   1000000
#define DSO (5000 - T/392)   //  392 Hz, 2551
#define DO  (5000 - T/523)   //  523 Hz
#define RE  (5000 - T/587)   //  587 Hz
#define MI  (5000 - T/659)   //  659 Hz
#define FA  (5000 - T/698)   //  698 Hz
#define SO  (5000 - T/784)   //  784 Hz
#define LA  (5000 - T/880)   //  880 Hz
#define SI  (5000 - T/988)   //  988 Hz
#define UDO (5000 - T/1046)  // 1046 Hz, 956
#define NP  (0)               // ¥ð¤î²Å
#define NP2 (1)               // ¥ð¤î²Å
#define NP4 (2)               // ¥ð¤î²Å

/* Private macro ---------------------------------------------------------------------------*/
/* Private variables -----------------------------------------------------------------------*/
/* Private function prototypes -------------------------------------------------------------*/
/* Private functions -----------------------------------------------------------------------*/

void BSP_TIM_PWM_Config( void )
{
  NVIC_InitTypeDef NVIC_InitStruct;
  GPIO_InitTypeDef GPIO_InitStruct;
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14, ENABLE);

  NVIC_InitStruct.NVIC_IRQChannel = TIM14_IRQn;
  NVIC_InitStruct.NVIC_IRQChannelPriority = 0;
  NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStruct);

  GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_OUT;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_UP;
  GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_7;
  GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* TIM14 Time Base */
  TIM_TimeBaseStruct.TIM_Prescaler         = (uint16_t)(48 - 1);
  TIM_TimeBaseStruct.TIM_Period            = (uint16_t)(5000 - 1);
  TIM_TimeBaseStruct.TIM_ClockDivision     = TIM_CKD_DIV1;
  TIM_TimeBaseStruct.TIM_CounterMode       = TIM_CounterMode_Up;    // Count Up
  TIM_TimeBaseStruct.TIM_RepetitionCounter = 0;
  TIM_TimeBaseInit(TIM14, &TIM_TimeBaseStruct);

  /* Enable */
  TIM_ClearFlag(TIM14, TIM_FLAG_Update);
  TIM_ITConfig(TIM14, TIM_IT_Update, ENABLE);
//  TIM_Cmd(TIM14, ENABLE);
}

void TIMx_EventCallback( void )
{
	TIM_SetCounter(TIM14, note);
	TIM_ClearFlag(TIM14, TIM_FLAG_Update);
  if ((note == NP) || (note == NP2) || (note == NP4)) {
    __GPIO_RST(GPIOA, GPIO_Pin_7);
	}
  else {
		LED_1_Toggle();
		LED_2_Toggle();
		LED_3_Toggle();
		LED_4_Toggle();
		LED_5_Toggle();
		LED_6_Toggle();
    __GPIO_TOG(GPIOA, GPIO_Pin_7);
	}
}

//									 1   2   3   4   5   6   7   8
uint16_t PLAY[8] = {DO, RE, MI, FA, SO, LA, SI, UDO};

#define LENS 90
uint16_t BELL[LENS] = {
	MI, MI, MI, NP, MI, MI, MI, NP, MI, SO, DO, RE, MI, NP, NP,     // 15
	FA, FA, FA, FA, FA, MI, MI, NP, MI, RE, RE, MI, RE, NP, SO, NP, // 16
	MI, MI, MI, NP, MI, MI, MI, NP, MI, SO, DO, RE, MI, NP, NP,			// 15
	FA, FA, FA, FA, FA, MI, MI, NP, SO, SO, FA, RE, DO, NP, NP, NP,	// 16
	DSO, SI, LA, SO, DSO, NP, NP, DSO, SI, LA, SO, DO, NP, NP, DO, FA, MI, RE, LA, LA, LA, NP,	// 22
	UDO, LA, FA, RE, DO, NP	//5
};

/*
  333 333 35123
  444 4433 3332232 5
  333 333 35123
  444 4433 3355421
  53215 5553216 64327 55423 53215 5553216 6432555 565421 5 333 333 35123 444 4433 3332232 5 333 333 35123 444 4433 3355671
*/
void playMusicScale( unsigned int scale, unsigned int time )
{
  note = scale;
  if (note == NP) {
		TIM_ClearFlag(TIM14, TIM_FLAG_Update);
		TIM_Cmd(TIM14, DISABLE);
		delay_ms(time);
  }
	else if (note == NP2) {
		TIM_ClearFlag(TIM14, TIM_FLAG_Update);
		TIM_Cmd(TIM14, DISABLE);
		delay_ms(time >> 1);
  }
	else if (note == NP4) {
		TIM_ClearFlag(TIM14, TIM_FLAG_Update);
		TIM_Cmd(TIM14, DISABLE);
		delay_ms(time >> 2);
  }
  else {
		TIM_SetCounter(TIM14, note);
		TIM_ClearFlag(TIM14, TIM_FLAG_Update);
		TIM_Cmd(TIM14, ENABLE);
		delay_ms(time);
  }
}

int main( void )
{
  HAL_InitTick();
  BSP_GPIO_Config();
	BSP_TIM_PWM_Config();

//	NOTE = DO;

  while (1) {
		for (uint8_t i = 0; i < LENS; i++) {
			
			playMusicScale(BELL[i], 200);
		}
		playMusicScale(NP, 2000);
  }
}

/*************************************** END OF FILE ****************************************/
