#include <stdint.h>
#include "LCDFunctions.h"

int main(void) {
	char letter = 'W';

	// enable clock for the port A (GPIOA)
	EnableClockForThePort(GPIOA);
	// initialize the pins
	InitializePins();

	SendCharToLCDDataPins(letter);

	while (1) {
		// never stops
	}
}
