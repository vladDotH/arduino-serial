#include "Arduino.h"



Arduino::Arduino()
{
	
}


Arduino::~Arduino()
{
}

void Arduino::digitalWrite(int pin, Mode mode)
{
	string message;
	message += (char)Mode::DIGITAL;
	message += (char)pin;
	message += (char)mode;

	write(message);
}

void Arduino::analogWrite(int pin, int val)
{
	string message;
	message += (char)Mode::ANALOG;
	message += (char)pin;
	message += (char)val;

	write(message);
}
