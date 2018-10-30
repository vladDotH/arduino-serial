#include <Windows.h>
#include "Arduino.h"

#define KEY_DOWN(key) (GetAsyncKeyState(key) & 0x8000)

int main()
{
	Arduino bot;
	bot.connect(5);

	while (!KEY_DOWN(VK_SPACE))
	{
		if (KEY_DOWN('W'))
		{
			bot.analogWrite(6, 255);
			bot.digitalWrite(7, Arduino::Mode::HIGH);
		}
	
		else if (KEY_DOWN('S'))
		{
			bot.analogWrite(6, 255);
			bot.digitalWrite(7, Arduino::Mode::LOW);
		}

		else if (KEY_DOWN('A'))
		{
			bot.analogWrite(6, 50);
			bot.digitalWrite(7, Arduino::Mode::HIGH);
		}

		else if (KEY_DOWN('D'))
		{
			bot.analogWrite(6, 128);
			bot.digitalWrite(7, Arduino::Mode::LOW);
		}

		else if (KEY_DOWN('Q'))
			break;

		else
		{
			bot.analogWrite(6, 0);
			bot.digitalWrite(7, Arduino::Mode::LOW);
		}
	}
	
	bot.close();
}