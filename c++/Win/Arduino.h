#pragma once
#include "Connecter.h"

class Arduino :
	public Connecter
{
public:
	enum class Mode {
		LOW = 0,
		HIGH,
		DIGITAL,
		ANALOG
	};

	Arduino();
	~Arduino();

	void digitalWrite(int pin, Mode mode);
	void analogWrite(int pin, int val);
	
};

