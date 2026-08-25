#include "stm32f411xe.h"
#include "stm32f4xx_hal.h"

void EXTI4_IRQHandler(void) {
  // check for pending register
  if (EXTI->PR & EXTI_PR_PR4) {
    // toggle the LED
    GPIOB->ODR ^= GPIO_ODR_OD4;

    // clear the pending register
    EXTI->PR = EXTI_PR_PR4;
  }
}

int main(void) {
  HAL_Init();

  // input -> PA4 -> A4
  // output -> PB4 -> B4

  // enable clock for peripherals: GPIOA, GPIOB and SYSCFG
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
  RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

  // pin modes for input (A4) and output (B4)
  // input
  GPIOA->MODER &= ~GPIO_MODER_MODE4;
  // output
  GPIOB->MODER |= GPIO_MODER_MODE4_0;
  GPIOB->MODER &= ~GPIO_MODER_MODE4_1;

  // set the output type
  GPIOB->OTYPER &= ~GPIO_OTYPER_OT_4;

  // set the output speed
  GPIOB->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED4;

  // setup the pull up/ pull down
  GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD4;
  GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD4;

  // setup interrupt
  SYSCFG->EXTICR[1] &= ~SYSCFG_EXTICR2_EXTI4;

  // enable raising trigger for input line 4
  EXTI->RTSR |= EXTI_RTSR_TR4;

  // mask interrupt request from line 4
  EXTI->IMR |= EXTI_IMR_IM4;

  NVIC_EnableIRQ(EXTI4_IRQn);

  while (1) {
    // I'm freeeeee
    // yeeee
  }
}