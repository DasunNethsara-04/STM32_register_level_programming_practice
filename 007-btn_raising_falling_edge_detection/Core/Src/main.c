#include "stm32f411xe.h"
#include "stm32f4xx_hal.h"
#include <stdint.h>

int main(void) {
  // inputs -> A4, A5
  // outputs -> B4, B5

  HAL_Init();

  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

  // set GPIO A4 and A5 as inputs
  GPIOA->MODER &= ~GPIO_MODER_MODE4;
  GPIOA->MODER &= ~GPIO_MODER_MODE5;

  // set GPIO B4 and B5 as outputs
  GPIOB->MODER |= GPIO_MODER_MODER4_0;
  GPIOB->MODER &= ~GPIO_MODER_MODER4_1;
  GPIOB->MODER |= GPIO_MODER_MODER5_0;
  GPIOB->MODER &= ~GPIO_MODER_MODER5_1;

  // set the output type
  GPIOB->OTYPER &= ~GPIO_OTYPER_OT_4;
  GPIOB->OTYPER &= ~GPIO_OTYPER_OT_5;

  // set the output speed
  GPIOB->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED4;
  GPIOB->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED5;

  // set the pull up/ pull down
  GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD4;
  GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD5;
  GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD4;
  GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD5;

  uint32_t btn1PreviousState = !!(GPIOA->IDR & GPIO_IDR_ID4);
  uint32_t btn1CurrentState;
  uint32_t btn2PreviousState = !!(GPIOA->IDR & GPIO_IDR_ID5);
  uint32_t btn2CurrentState;

  while (1) {
    // raising edge detection for button 1
    btn1CurrentState = !!(GPIOA->IDR & GPIO_IDR_ID4);
    if (btn1CurrentState == 1 && btn1PreviousState == 0) {
      HAL_Delay(50);
      btn1CurrentState = !!(GPIOA->IDR & GPIO_IDR_ID4);
      if (btn1CurrentState) {
        // toggle the LED 1
        GPIOB->ODR ^= GPIO_ODR_OD4;
      }
    }
    btn1PreviousState = btn1CurrentState;

    // falling edge detection for button 2
    btn2CurrentState = !!(GPIOA->IDR & GPIO_IDR_ID5);
    if (btn2PreviousState == 1 && btn2CurrentState == 0) {
      HAL_Delay(50);
      btn2CurrentState = !!(GPIOA->IDR & GPIO_IDR_ID5);
      if (btn2CurrentState == 0) {
        // toggle the LED 2
        GPIOB->ODR ^= GPIO_ODR_OD5;
      }
    }
    btn2PreviousState = btn2CurrentState;
  }
}