#include <NewPing.h>

enum Mode {
  DIGITAL = 2,
  ANALOG,

  UltraSonicGet = 255
};

void setup() {
  Serial.begin(9600);

  pinMode( 4, OUTPUT );
  pinMode( 5, OUTPUT );
  pinMode( 6, OUTPUT );
  pinMode( 7, OUTPUT );
}

byte msg [3];
int byteCount = 0;

//#define TRIGGER_PIN 10
//#define ECHO_PIN 8
//#define MAX_DISTANCE 50
//NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void loop() {
  if ( Serial.available() ) {
    msg[byteCount] = Serial.read();   
    byteCount ++;
  }

  if ( byteCount == 3 ) {
    
    if( msg[0] == DIGITAL ){
      digitalWrite( msg[1], msg[2] );
    }

    if( msg[0] == ANALOG ){
      analogWrite( msg[1], msg[2] );
    }

    if( msg[0] == UltraSonicGet ){
      NewPing sonar(msg[1], msg[2], 200);
      int range = sonar.ping_cm();
      Serial.write( (byte)range );
    }
    
    byteCount = 0;
  }
}
