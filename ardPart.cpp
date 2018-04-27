void setup() {
 pinMode( 5, OUTPUT );
 pinMode( 4, OUTPUT );
 pinMode( 6, OUTPUT );
 pinMode( 7, OUTPUT );

 Serial.begin(9600);
}

char message[4];
int counter = 0;

void loop()
{
 if ( Serial.available() )
 {
   char curr = Serial.read();

   message[counter] = curr;
   counter ++;
 }

 if ( counter == 4 )
 {
   analogWrite( message[0], message[1] );
   digitalWrite( message[2], message[3] );
  
   counter = 0;
 }
}
