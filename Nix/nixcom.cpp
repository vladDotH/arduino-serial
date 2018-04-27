#include "nixcom.h"
#include <string.h>
#include <stdio.h>

nixCom::nixCom( int port )
{
    this -> defPort( port );
}

void nixCom::defPort( int port )
{
    stringstream sstr;
    sstr << port;
    sstr >> this -> port;

    string sPortName = "/dev/ttyACM";     
    sPortName += this -> port;

    portHandle = open( sPortName.c_str(), O_RDWR| O_NONBLOCK | O_NDELAY );

    if ( portHandle < 0 )
    {
        cout << "Error " << errno << " opening " << sPortName.c_str() << ": " << endl;
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

nixController::nixController( int port )
{
    controlPort.defPort( port );
}

void nixController::setLR ( motor *Lmotor, motor *Rmotor )
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
   if ( currentMotor.currentSpeed == val )
        return;

    currentMotor.currentSpeed = val;

    string message;

    val = abs( val );
    val = ( val > 254 ) ? 254 : val;

    message += (char) currentMotor.mainPin;
    message += (char) val;
    message += (char) currentMotor.reversePin;
    message += (char) ( currentMotor.currentSpeed < 0 ? 1 : 0 );

    controlPort.send( message );

    //Sleep( 20 );
}
