import serial
from serial import Serial
import time

from arduino import Arduino
from arduino import mode

bot = Arduino("COM5")

bot.pinMode(6, mode.OUT)
bot.pinMode(7, mode.OUT)

_in = ''

while _in != 'q':
    _in = input()

    if _in == 'w':
        bot.analogWrite(6, 50)
        bot.digitalWrite(7, 0)

    if _in == 'd':
        bot.analogWrite(6, 50)
        bot.digitalWrite(7, 1)

    if _in == 's':
        bot.analogWrite(6, 0)
        bot.digitalWrite(7, 0)

    if _in == 'u':
        print(bot.sonicRead(10, 8))
        print(bot.sonicRead(10, 8))
        print(bot.sonicRead(10, 8))
