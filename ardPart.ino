enum Mode {
  DIGITAL = 2,
  ANALOG
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
    
    byteCount = 0;
  }
}
