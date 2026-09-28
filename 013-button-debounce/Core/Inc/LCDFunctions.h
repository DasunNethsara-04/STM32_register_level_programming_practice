/*
 * LCDFunctions.h
 *
 *  Created on: Sep 26, 2026
 *      Author: Dasun Nethsara
 */

#ifndef INC_LCDFUNCTIONS_H_
#define INC_LCDFUNCTIONS_H_

#include "main.h"

// function prototypes
void InitializePins();
void EnableClockForThePort(GPIO_TypeDef *port);
void SetupPinsAndPortsForOutput(GPIO_TypeDef *port, uint8_t pin);
void SendBitToThePin(GPIO_TypeDef *port, uint8_t pin, uint8_t bitState);
void SendCharToLCDDataPins(char character);

#endif /* INC_LCDFUNCTIONS_H_ */
