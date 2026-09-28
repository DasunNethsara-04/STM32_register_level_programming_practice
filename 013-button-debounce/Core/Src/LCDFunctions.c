/*
 * LCDFunctions.c
 *
 *  Created on: Sep 26, 2026
 *      Author: Dasun Nethsara
 */

#include "main.h"

#define LCDPIN1 1
#define LCDPIN1PORT GPIOA
#define LCDPIN2 2
#define LCDPIN2PORT GPIOA
#define LCDPIN3 3
#define LCDPIN3PORT GPIOA
#define LCDPIN4 4
#define LCDPIN4PORT GPIOA
#define LCDPIN5 5
#define LCDPIN5PORT GPIOA
#define LCDPIN6 6
#define LCDPIN6PORT GPIOA
#define LCDPIN7 7
#define LCDPIN7PORT GPIOA
#define LCDPIN8 8
#define LCDPIN8PORT GPIOA

void EnableClockForThePort(GPIO_TypeDef *port) {
	if (port == GPIOA)
		RCC->AHB1ENR |= (1UL << 0);
	if (port == GPIOB)
		RCC->AHB1ENR |= (1UL << 1);
	if (port == GPIOC)
		RCC->AHB1ENR |= (1UL << 2);
	if (port == GPIOD)
		RCC->AHB1ENR |= (1UL << 3);
	if (port == GPIOE)
		RCC->AHB1ENR |= (1UL << 4);
	if (port == GPIOH)
		RCC->AHB1ENR |= (1UL << 7);
}

void SetupPinsAndPortsForOutput(GPIO_TypeDef *port, uint8_t pin) {
	// then configure the pins as output
	// pin mode as output
	port->MODER &= ~(3UL << (2 * pin));
	port->MODER |= (1UL << (2 * pin));

	// set the output type as open close
	port->OTYPER &= ~(1UL << pin);

	// set the output speed as high speed -> 11
	port->OSPEEDR |= (3UL << (2 * pin));

	// set the pulll-up/ pull-down as NO  -> 00
	port->PUPDR &= ~(3UL << (2 * pin));
}

void InitializePins() {
	SetupPinsAndPortsForOutput(LCDPIN1PORT, LCDPIN1);
	SetupPinsAndPortsForOutput(LCDPIN2PORT, LCDPIN2);
	SetupPinsAndPortsForOutput(LCDPIN3PORT, LCDPIN3);
	SetupPinsAndPortsForOutput(LCDPIN4PORT, LCDPIN4);
	SetupPinsAndPortsForOutput(LCDPIN5PORT, LCDPIN5);
	SetupPinsAndPortsForOutput(LCDPIN6PORT, LCDPIN6);
	SetupPinsAndPortsForOutput(LCDPIN7PORT, LCDPIN7);
	SetupPinsAndPortsForOutput(LCDPIN8PORT, LCDPIN8);
}

void SendBitToThePin(GPIO_TypeDef *port, uint8_t pin, uint8_t bitState) {
	if (bitState)
		port->ODR |= (1UL << pin);
	else
		port->ODR &= ~(1UL << pin);
}

void SendCharToLCDDataPins(char character) {
	SendBitToThePin(LCDPIN1PORT, LCDPIN1, character & 0b00000001);
	SendBitToThePin(LCDPIN2PORT, LCDPIN2, character & 0b00000010);
	SendBitToThePin(LCDPIN3PORT, LCDPIN3, character & 0b00000100);
	SendBitToThePin(LCDPIN4PORT, LCDPIN4, character & 0b00001000);
	SendBitToThePin(LCDPIN5PORT, LCDPIN5, character & 0b00010000);
	SendBitToThePin(LCDPIN6PORT, LCDPIN6, character & 0b00100000);
	SendBitToThePin(LCDPIN7PORT, LCDPIN7, character & 0b01000000);
	SendBitToThePin(LCDPIN8PORT, LCDPIN8, character & 0b10000000);
}
