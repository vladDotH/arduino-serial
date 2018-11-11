#include <NewPing.h>

enum Mode {
  DIGITAL = 2,
  ANALOG,

  PinMode = 4,
  OUT = 0,
  IN = 1,

  UltraSonicGet = 255
};

void setup() {
  Serial.begin(9600);
}

byte msg [3];
int byteCount = 0;

void loop() {
  if ( Serial.available() ) {
    msg[byteCount] = Serial.read();
    byteCount ++;
  }

  if ( byteCount == 3 ) {

    if ( msg[0] == DIGITAL ) {
      digitalWrite( msg[1], msg[2] );
    }

    if ( msg[0] == ANALOG ) {
      analogWrite( msg[1], msg[2] );
    }

    if ( msg[0] == UltraSonicGet ) {
      NewPing sonar(msg[1], msg[2], 200);
      int range = sonar.ping_cm();
      Serial.write( (byte)range );
    }

    if ( msg[0] == PinMode ) {
      if ( msg[2] == OUT ){
        pinMode( msg[1], OUTPUT );
      }

      if ( msg[2] == IN )
        pinMode( msg[1], INPUT );
    }

    byteCount = 0;
  }
}
