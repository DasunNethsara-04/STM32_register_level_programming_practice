#include "main.h"
#include "stm32f411xe.h"

void EXTI9_5_IRQHandler() {
  if (EXTI->PR & EXTI_PR_PR5) {
    GPIOB->ODR ^= GPIO_ODR_OD5;
    EXTI->PR = EXTI_PR_PR5;
  }
}

int main(void) {
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
  RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

  // set the pin mode
  // input: A5
  GPIOA->MODER &= ~GPIO_MODER_MODER5;
  // output: B5
  GPIOB->MODER |= GPIO_MODER_MODER5_0;
  GPIOB->MODER &= ~GPIO_MODER_MODER5_1;

  // set the output type as push-pull
  GPIOB->OTYPER &= ~GPIO_OTYPER_OT_5;

  // set the output speed as low speed
  GPIOB->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED5;

  // set the pull-up, pull-down as no pull-up/ pull-down
  GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD5;
  GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD5;

  // set up the external interrupts for pin A5
  SYSCFG->EXTICR[1] &= ~SYSCFG_EXTICR2_EXTI5;

  // detect the raising edge
  EXTI->RTSR |= EXTI_RTSR_TR5;

  EXTI->IMR |= EXTI_IMR_IM5;

  NVIC_EnableIRQ(EXTI9_5_IRQn);

  while (1) {
  }
}