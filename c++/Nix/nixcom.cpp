#include "nixcom.h"
#include <string.h>
#include <stdio.h>

nixCom::nixCom( string port )
{
    this -> defPort( port );
}

nixCom::~nixCom()
{
    close( portHandle );
}

void nixCom::defPort( string port )
{
    this -> port = port;

    portHandle = open( port.c_str(), O_RDWR| O_NONBLOCK | O_NDELAY );

    if ( portHandle < 0 )
    {
        cout << "Error " << errno << " opening " << port.c_str() << ": " << endl;
    }

    struct termios tty;
    struct termios tty_old;
    memset (&tty, 0, sizeof tty);

    /* Error Handling */
    if ( tcgetattr ( portHandle, &tty ) != 0 )
    {
        cout << "Error " << errno << " from tcgetattr: " << endl;
        return;
    }

    /* Save old tty parameters */
    tty_old = tty;

    /* Set Baud Rate */
    cfsetospeed ( &tty, (speed_t)B9600 );
    cfsetispeed ( &tty, (speed_t)B9600 );

    /* Setting other Port Stuff */
    tty.c_cflag     &=  ~PARENB;            // Make 8n1
    tty.c_cflag     &=  ~CSTOPB;
    tty.c_cflag     &=  ~CSIZE;
    tty.c_cflag     |=  CS8;

    tty.c_cflag     &=  ~CRTSCTS;           // no flow control
    tty.c_cc[VMIN]   =  1;                  // read doesn't block
    tty.c_cc[VTIME]  =  5;                  // 0.5 seconds read timeout
    tty.c_cflag     |=  CREAD | CLOCAL;     // turn on READ & ignore ctrl lines

    /* Make raw */
    cfmakeraw( &tty );

    /* Flush Port, then applies attributes */
    tcflush( portHandle, TCIFLUSH );

    if ( tcsetattr( portHandle, TCSANOW, &tty ) != 0 )
    {
        std::cout << "Error " << errno << " from tcsetattr" << std::endl;
        return;
    }
}

void nixCom::send ( string message )
{
    int out = write( portHandle, message.c_str(), message.size() );

    if ( !out )
    {
        cout << "Write error \n";
    }
}

/**                                              **/

nixController::nixController( string port )
{
    controlPort.defPort( port );
}

nixController::~nixController()
{
    ride( 0, 0 );
}

void nixController::setLR( motor *Lmotor, motor *Rmotor )
{
    this -> Lmotor = Lmotor;
    this -> Rmotor = Rmotor;
}

void nixController::ride( int Lval, int Rval )
{
    motorStart( *Lmotor, Lval );
    motorStart( *Rmotor, Rval );
}

void nixController::motorStart ( motor &currentMotor, int val )
{
   if ( val > 127 ) val = 127;

   if ( val < -127 ) val = -127;

   if ( currentMotor.currentSpeed == val )
        return;

    currentMotor.currentSpeed = val;

    string message;

    cout << (int)(signed char)val << " to " << currentMotor.mainPin << endl;

    message += (char) ( currentMotor.mainPin << 4 ) | currentMotor.reversePin ;
    message += (char) val;

    controlPort.send( message );
}
