/* f3d_timer4.c --- 
 * 
 * Filename: f3d_timer4.c
 * Description: 
 * Author: Bryce Himebaugh
 * Maintainer: 
 * Created: Tue Feb 18 09:31:16 2014
 * Last-Updated: 
 *           By: 
 *     Update #: 0
 * Keywords: 
 * Compatibility: 
 * 
 */

/* Commentary: 
 * 
 * 
 * 
 */

/* Change log:
 * 
 * 
 */

/* Copyright (c) 2004-2007 The Trustees of Indiana University and 
 * Indiana University Research and Technology Corporation.  
 * 
 * All rights reserved. 
 * 
 * Additional copyrights may follow 
 */

/* Code: */

// Pins PD12 
#include <f3d_timer4.h>
#include <f3d_led.h>
#include <stdio.h>

TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
TIM_OCInitTypeDef TIM_OCInitStructure;
TIM_ICInitTypeDef TIM_ICInitStructure;
NVIC_InitTypeDef NVIC_InitStructure;
uint32_t pulse_width = 0;	

static void f3d_timer4_pins(void) {
  GPIO_InitTypeDef GPIO_InitStructure;
  TIM_OCInitTypeDef TIM_OCInitStructure;
  uint16_t TimerPeriod = 0;
  uint16_t Channel1Pulse = 0;
  // Pin Initializations

  // Enable the clock to Port D
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOD, ENABLE);

  // Configure PD12 as an output
  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
  GPIO_Init(GPIOD, &GPIO_InitStructure);

  // Configure PD13 as an Inputs
  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
  GPIO_Init(GPIOD, &GPIO_InitStructure);

  GPIO_PinAFConfig(GPIOD, GPIO_PinSource12, GPIO_AF_2);
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource13, GPIO_AF_2);
  /* GPIO_PinAFConfig(GPIOD, GPIO_PinSource14, GPIO_AF_2); */
  /* GPIO_PinAFConfig(GPIOD, GPIO_PinSource15, GPIO_AF_2);	 */
}

void f3d_timer4_init(void) {

  // Configure the PortD 12-15 and assign to timer4
  f3d_timer4_pins();	

  // Enable the clock to Timer4 
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

  /* // Setup the timebase. 2khz/40 to give a 50Hz period */
  /* TIM_TimeBaseStructInit(&TIM_TimeBaseStructure); */
  /* TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; */
  /* TIM_TimeBaseStructure.TIM_Period = (SystemCoreClock / 2000) - 1; */
  /* TIM_TimeBaseStructure.TIM_ClockDivision = 0; */
  /* TIM_TimeBaseStructure.TIM_Prescaler = 39;	 */
  /* TIM_TimeBaseStructure.TIM_RepetitionCounter = 0; */
  /* TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); */

  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_Period = (SystemCoreClock / 2000) - 1;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_Prescaler = 0;	
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

  // Setup PWM Output Channel
  TIM_OCStructInit(&TIM_OCInitStructure);
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Toggle;
  /* TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; */
  /* TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable; */
  /* TIM_OCInitStructure.TIM_Pulse = (uint16_t) (27000); // 1.5mS high time initially.  */
  /* TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; */
  /* TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High; */
  /* TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set; */
  /* TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset; */
  TIM_OC1Init(TIM4, &TIM_OCInitStructure);

  /* // Setup PWM Output Channel */
  /* TIM_OCStructInit(&TIM_OCInitStructure); */
  /* TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; */
  /* TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; */
  /* TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable; */
  /* TIM_OCInitStructure.TIM_Pulse = (uint16_t) (2700); // 1.5mS high time initially.  */
  /* TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; */
  /* TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High; */
  /* TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set; */
  /* TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset; */
  /* TIM_OC1Init(TIM4, &TIM_OCInitStructure); */

  // Enable PWM Channel
  TIM_CCxCmd(TIM4,TIM_Channel_1,TIM_CCx_Enable);

  // Setup Input Compare Channel
  TIM_ICStructInit(&TIM_ICInitStructure);
  TIM_ICInitStructure.TIM_Channel=TIM_Channel_2;
  TIM_ICInitStructure.TIM_ICPolarity=TIM_ICPolarity_Rising;
  TIM_ICInitStructure.TIM_ICSelection=TIM_ICSelection_DirectTI;
  TIM_ICInitStructure.TIM_ICPrescaler=TIM_ICPSC_DIV1;
  TIM_ICInitStructure.TIM_ICFilter=0;
  TIM_ICInit(TIM4,&TIM_ICInitStructure);

  // Setup the NVIC priority and subpriority
  NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x08;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x08;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  // Setup Interrupt for Capture Channel 2
  TIM_ITConfig(TIM4,TIM_IT_CC2,ENABLE);

  // Enable the timer
  TIM_Cmd(TIM4, ENABLE);
}

void f3d_frequency(uint32_t freq) {
  uint32_t period, prescale;
  if (freq) {
    freq<<=1; // multiply by 2 because both a high and low transition are needed in one period
    period = (SystemCoreClock / freq) - 1;  
    prescale = 1;
    while (period>0xFFFF) {
      period = ((SystemCoreClock/++prescale)/freq)-1;
      if (prescale>=0xFFFF) {
	break;
      }
    }
    TIM_TimeBaseStructure.TIM_Prescaler = prescale-1; 
    //  TIM_TimeBaseStructure.TIM_Period = (SystemCoreClock / freq) - 1;  
    TIM_TimeBaseStructure.TIM_Period = period;
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
    TIM_CCxCmd(TIM4,TIM_Channel_1,TIM_CCx_Enable);
  }
  else {
    TIM_CCxCmd(TIM4,TIM_Channel_1,TIM_CCx_Disable);
  }
}


void f3d_hightime_oc1_uS(uint32_t time_uS) {
  uint32_t time_nS = time_uS * 1000;
  time_nS /= 555; 
  TIM_SetCompare1(TIM4,time_nS);
}

void TIM4_IRQHandler(void) {
  enum {RISING,FALLING};
  static uint32_t cc2_rising;
  static uint32_t cc2_falling;
  static led_state = 0;
  static cc2_capture_status = RISING;

  if (TIM_GetITStatus(TIM4,TIM_IT_CC2)==SET) {
    // Timer 2 Stuff
    // TIM_ClearFlag(TIM4,TIM_FLAG_CC2);
    // TIM_ClearITPendingBit(TIM4,TIM_IT_CC2);
    switch (cc2_capture_status) {
    case RISING:
      // setup for falling edge
      cc2_rising = TIM_GetCapture2(TIM4);	
      TIM_ICInitStructure.TIM_ICPolarity=TIM_ICPolarity_Falling;
      TIM_ICInit(TIM4,&TIM_ICInitStructure);
      cc2_capture_status=FALLING;
      f3d_led_on(0);				
      break;
    case FALLING:
      cc2_falling = TIM_GetCapture2(TIM4);
      TIM_ICInitStructure.TIM_ICPolarity=TIM_ICPolarity_Rising;
      TIM_ICInit(TIM4,&TIM_ICInitStructure);
      cc2_capture_status=RISING;
      pulse_width = cc2_falling - cc2_rising;
      f3d_led_off(0);	
      break;
    }
  }
}



/* f3d_timer4.c ends here */
