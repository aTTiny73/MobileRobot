#include "delay.h"

volatile uint32_t g_systimer = 0;

//---> Blocking delay, not needed --->//
// void delay_ms(uint32_t delay)/*{{{*/
// {
//   RCC->APB1ENR |= RCC_APB1ENR_TIM3EN; // enable clock for TIM3 (72MHz)
//   TIM3->CR1 |= TIM_CR1_ARPE;   // Enable auto-reload register
//   TIM3->PSC = 72 - 1; // output clock will be 1 MHz
//   TIM3->ARR = 1000; // over flow will accure every ms
//   TIM3->EGR |= TIM_EGR_UG;
//   TIM3->CR1 |= TIM_CR1_CEN;
//   while (delay)
//   {
//     while(!(TIM3->SR & TIM_SR_UIF)) // wait for overflow
//     {
//     }
//     TIM3->SR &= ~(TIM_SR_UIF);
//     --delay;
//   }
//   TIM3->CR1 &= ~(TIM_CR1_CEN);
//   return;
// }/*}}}*/
// void delay_us(uint32_t delay)/*{{{*/
// {
//   RCC->APB1ENR |= RCC_APB1ENR_TIM3EN; // enable clock for TIM3 (72MHz)
//   TIM3->CR1 |= TIM_CR1_ARPE;   // Enable auto-reload register
//   TIM3->PSC = 1 - 1; // output clock will be 72 MHz
//   TIM3->ARR = 72; // over flow will accure every us
//   TIM3->EGR |= TIM_EGR_UG;
//   TIM3->CR1 |= TIM_CR1_CEN;
//   while (delay)
//   {
//     while(!(TIM3->SR & TIM_SR_UIF)) // wait for overflow
//     {
//     }
//     TIM3->SR &= ~(TIM_SR_UIF);
//     --delay;
//   }
//   TIM3->CR1 &= ~(TIM_CR1_CEN);
//   return;
// }/*}}}*/


void systimer_init(void)/*{{{*/
{
  RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; // enable TIM2 (16bit)
  TIM2->PSC = 72 - 1; // scale timer clock to 1Mhz
  TIM2->ARR = 1000;
  TIM2->CR1 = TIM_CR1_ARPE | TIM_CR1_URS; //  upcounter,autoreload on overflow
  TIM2->CR2 = 0x0000;
  TIM2->CNT = 0x00000000;
	TIM2->DIER = TIM_DIER_UIE;												// enable 
  TIM2->EGR |= TIM_EGR_UG;
  TIM2->CR1 |= TIM_CR1_CEN;
	NVIC_SetPriority(TIM2_IRQn, 0);
	NVIC_EnableIRQ(TIM2_IRQn);
}/*}}}*/
void TIM2_IRQHandler(void)/*{{{*/
{
	if(TIM2->SR & 0x0001)
	{
		g_systimer++;
		TIM2->SR = 0x0000;
	}
}
/*}}}*/
uint32_t systimer_get(void)/*{{{*/
{
  return g_systimer;
}/*}}}*/
uint8_t systimer_timeout_flag(uint32_t current_time, uint32_t period)/*{{{*/
{
  uint32_t time = g_systimer;
  uint8_t systimer_status = 0x00;
  if(time >= current_time)
  {
    if(time >= (current_time + period))
    {
      systimer_status = SYSTIMER_TIMEOUT;
    }
    else
    {
      systimer_status = SYSTIMER_KEEP_ALIVE;
    }
  }
  else
  {
    uint32_t utmp_32 = 0xffffffff - current_time;
    if((time + utmp_32) >= period)
    {
      systimer_status = SYSTIMER_TIMEOUT;
    }
    else
    {
      systimer_status = SYSTIMER_KEEP_ALIVE;
    }
  }
  return systimer_status;
}/*}}}*/
