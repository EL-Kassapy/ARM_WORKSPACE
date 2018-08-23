
#include "stm32f4xx.h"


int main(void)
{
    // Setting for the GPIO FOR PWM Output Channel
    RCC  ->  AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    GPIOA -> MODER |= GPIO_MODER_MODER8_0;   // ALTERNATE Function MODE
    GPIOA -> MODER &= ~(GPIO_MODER_MODER8_1);
    // you need to specify which Alternate function you want to use (see Data Sheet )
    GPIOA -> AFR[1] |= GPIO_AF_TIM1; // set the alternate function as timer 1


    // Setting for the TIMER
    RCC  -> APB2ENR |= RCC_APB2ENR_TIM1EN; // Enable the Clock for Timer1
    TIM1 -> CR1 |= TIM_CR1_CEN; // Enable Timer

    TIM1 -> PSC =  0;	// PRESALLER Value
    TIM1 -> ARR =  2000;	// DEtermine Frequency
    TIM1 -> CCR1 = 2000;	// Determine duty cycle NOTE: 100/200 =0.5 so duty Cycle 50%

    TIM1 -> CCMR1 |= TIM_CCMR1_OC1M_0 | TIM_CCMR1_OC1M_1; // SET TO PWM Mode 1
    TIM1 -> CCMR1 |= TIM_CCMR1_OC1PE ; // Enable Corresponding pre-load Register
    TIM1 -> CCER  |= TIM_CCER_CC1E; // Enable OUTPUT of the PWM on channel 1 needs moe enabled in next line
    TIM1 -> BDTR  |= TIM_BDTR_MOE ; // Enable general output
    TIM1 -> EGR   |= TIM_EGR_UG; // Enable UG BIT (REQUIRED)

    while (1)
  {




  }


}
