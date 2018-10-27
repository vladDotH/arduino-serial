import serial
from serial import Serial
import time

from arduino import Arduino

bot = Arduino("COM5")

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