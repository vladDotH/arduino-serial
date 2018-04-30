void setup() {
  pinMode( 5, OUTPUT );
  pinMode( 4, OUTPUT );
  pinMode( 6, OUTPUT );
  pinMode( 7, OUTPUT );

  Serial.begin(9600);
}

char message[2];
int counter = 0;

void loop()
{
  if ( Serial.available() )
  {
    char curr = Serial.read();

    message[counter] = curr;
    counter ++;
  }

  if ( counter == 2 )
  {
    counter = 0;

    digitalWrite( message[0] & 15, message[1] < 0 );

    message[1] = 2 * abs( message[1] );

    analogWrite( message[0] >> 4, message[1]  );
  }
}

