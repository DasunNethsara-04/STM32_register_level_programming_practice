#include "main.h"
#include "stm32f411xe.h"

int main(void) {
  // inputs -> A4, A5
  // outputs -> B4, B5

  // enable clock for port A and B
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

  // set the pin modes
  // input -> A4
  GPIOA->MODER &= ~GPIO_MODER_MODER4_0;
  GPIOA->MODER &= ~GPIO_MODER_MODER4_1;

  // input -> A5
  GPIOA->MODER &= ~GPIO_MODER_MODER5_0;
  GPIOA->MODER &= ~GPIO_MODER_MODER5_1;

  // output -> B4
  GPIOB->MODER |= GPIO_MODER_MODER4_0;
  GPIOB->MODER &= ~GPIO_MODER_MODER4_1;

  // output -> B5
  GPIOB->MODER |= GPIO_MODER_MODER5_0;
  GPIOB->MODER &= ~GPIO_MODER_MODER5_1;

  // output type for B4 and B5
  GPIOB->OTYPER &= ~GPIO_OTYPER_OT_4;
  GPIOB->OTYPER &= ~GPIO_OTYPER_OT_5;

  // output speed for B4
  GPIOB->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED4_0;
  GPIOB->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED4_1;

  // output speed for B5
  GPIOB->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED5_0;
  GPIOB->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED5_1;

  // set pull up/ pull down for inputs -> No Pull Up/ Pull down (already done it
  // using external resisters)
  GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD4_0;
  GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD4_1;
  GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD5_0;
  GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD5_1;

  // set pull up/ pull down for outputs -> No Pull Up/ Pull down
  GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD4_0;
  GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD4_1;
  GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD5_0;
  GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD5_1;

  while (1) {
    // check if the button 1 in PA4 is pressed
    if (GPIOA->IDR & GPIO_IDR_ID4) {
      // turn on the LED in B4
      GPIOB->ODR |= GPIO_ODR_OD4;
    } else {
      // turn the LED off
      GPIOB->ODR &= ~GPIO_ODR_OD4;
    }

    // check if the button 2 in PA5 is pressed
    if (GPIOA->IDR & GPIO_IDR_ID5) {
      // turn on the LED in B5
      GPIOB->ODR |= GPIO_ODR_OD5;
    } else {
      // turn the LED off
      GPIOB->ODR &= ~GPIO_ODR_OD5;
    }
  }
}