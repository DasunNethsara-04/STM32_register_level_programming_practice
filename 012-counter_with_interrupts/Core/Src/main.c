#include "stm32f411xe.h"
#include <stdbool.h>
#include <stdint.h>

volatile uint8_t count = 0;

// prototypes
void EXTI9_5_IRQHandler(void);
void clearLEDs(void);

int main(void) {
  // input: A5
  // outputs: B3, B4, B5, B6

  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
  RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

  // set pin modes
  // input -> A5
  GPIOA->MODER &= ~GPIO_MODER_MODER5;
  // outputs -> B3
  GPIOB->MODER |= GPIO_MODER_MODER3_0;
  GPIOB->MODER &= ~GPIO_MODER_MODER3_1;
  // outputs -> B4
  GPIOB->MODER |= GPIO_MODER_MODER4_0;
  GPIOB->MODER &= ~GPIO_MODER_MODER4_1;
  // outputs -> B5
  GPIOB->MODER |= GPIO_MODER_MODER5_0;
  GPIOB->MODER &= ~GPIO_MODER_MODER5_1;
  // outputs -> B6
  GPIOB->MODER |= GPIO_MODER_MODER6_0;
  GPIOB->MODER &= ~GPIO_MODER_MODER6_1;

  // set all output pins' type as push-pull
  GPIOB->OTYPER &= ~GPIO_OTYPER_OT3;
  GPIOB->OTYPER &= ~GPIO_OTYPER_OT4;
  GPIOB->OTYPER &= ~GPIO_OTYPER_OT5;
  GPIOB->OTYPER &= ~GPIO_OTYPER_OT6;

  // set the speed as low speed for all the outputs
  GPIOB->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR3;
  GPIOB->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR4;
  GPIOB->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR5;
  GPIOB->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR6;

  // set the pull-up/ pull-down as No pull-up/down for all the input and outputs
  GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD5;
  GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD3;
  GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD4;
  GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD5;
  GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD6;

  // external interrupts
  SYSCFG->EXTICR[1] &= ~SYSCFG_EXTICR2_EXTI5;

  EXTI->RTSR |= EXTI_RTSR_TR5;
  EXTI->IMR |= EXTI_IMR_IM5;

  NVIC_EnableIRQ(EXTI9_5_IRQn);

  while (true) {
    switch (count) {
    case 0:
      clearLEDs();
      break;
    case 1:
      clearLEDs();
      // turn on B3, others off
      GPIOB->ODR |= GPIO_ODR_OD3;
      break;
    case 2:
      clearLEDs();
      // turn on B4, others off
      GPIOB->ODR |= GPIO_ODR_OD4;
      break;
    case 3:
      clearLEDs();
      // turn on B3 and B4, others off
      GPIOB->ODR |= GPIO_ODR_OD3;
      GPIOB->ODR |= GPIO_ODR_OD4;
      break;
    case 4:
      clearLEDs();
      // turn on B5, others off
      GPIOB->ODR |= GPIO_ODR_OD5;
      break;
    case 5:
      clearLEDs();
      // turn on B5 and B3, others off
      GPIOB->ODR |= GPIO_ODR_OD5;
      GPIOB->ODR |= GPIO_ODR_OD3;
      break;
    case 6:
      clearLEDs();
      // turn on B5 and B4, others off
      GPIOB->ODR |= GPIO_ODR_OD5;
      GPIOB->ODR |= GPIO_ODR_OD4;
      break;
    case 7:
      clearLEDs();
      // turn on B3, B4, B5, others off
      GPIOB->ODR |= GPIO_ODR_OD3;
      GPIOB->ODR |= GPIO_ODR_OD4;
      GPIOB->ODR |= GPIO_ODR_OD5;
      break;
    case 8:
      clearLEDs();
      // turn on B6, others off
      GPIOB->ODR |= GPIO_ODR_OD6;
      break;
    case 9:
      clearLEDs();
      // turn on B3 and B6, others off
      GPIOB->ODR |= GPIO_ODR_OD3;
      GPIOB->ODR |= GPIO_ODR_OD6;
      break;
    case 10:
      clearLEDs();
      // turn on B4 and B6 others off
      GPIOB->ODR |= GPIO_ODR_OD4;
      GPIOB->ODR |= GPIO_ODR_OD6;
      break;
    case 11:
      clearLEDs();
      // turn on B3, B4 and B6 others off
      GPIOB->ODR |= GPIO_ODR_OD3;
      GPIOB->ODR |= GPIO_ODR_OD4;
      GPIOB->ODR |= GPIO_ODR_OD6;
      break;
    case 12:
      clearLEDs();
      // turn on B5 and B6 others off
      GPIOB->ODR |= GPIO_ODR_OD5;
      GPIOB->ODR |= GPIO_ODR_OD6;
      break;
    case 13:
      clearLEDs();
      // turn on B3, B5 and B6 others off
      GPIOB->ODR |= GPIO_ODR_OD3;
      GPIOB->ODR |= GPIO_ODR_OD5;
      GPIOB->ODR |= GPIO_ODR_OD6;
      break;
    case 14:
      clearLEDs();
      // turn on B4, B5 and B6 others off
      GPIOB->ODR |= GPIO_ODR_OD4;
      GPIOB->ODR |= GPIO_ODR_OD5;
      GPIOB->ODR |= GPIO_ODR_OD6;
      break;
    case 15:
      clearLEDs();
      // turn on all LEDs
      GPIOB->ODR |= GPIO_ODR_OD3;
      GPIOB->ODR |= GPIO_ODR_OD4;
      GPIOB->ODR |= GPIO_ODR_OD5;
      GPIOB->ODR |= GPIO_ODR_OD6;
      break;
    default:
      clearLEDs();
      count = 0;
    }
  }
}

void EXTI9_5_IRQHandler(void) {
  if (EXTI->PR & EXTI_PR_PR5) {
    // increment the counter variable
    count++;

    // clear the PR
    EXTI->PR = EXTI_PR_PR5;
  }
}

void clearLEDs(void) {
  GPIOB->ODR &= ~GPIO_ODR_OD3;
  GPIOB->ODR &= ~GPIO_ODR_OD4;
  GPIOB->ODR &= ~GPIO_ODR_OD5;
  GPIOB->ODR &= ~GPIO_ODR_OD6;
}