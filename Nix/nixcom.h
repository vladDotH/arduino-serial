#ifndef NIXCOM_H_INCLUDED
#define NIXCOM_H_INCLUDED

#include <sys/types.h>    /// linux libraries
#include <fcntl.h>
#include <termios.h>
#include <errno.h>
#include <unistd.h>       ///

#include <string>
#include <stdio.h>
#include <iostream>
#include <sstream>

#include "motor.h"

using namespace std;

class nixCom {
private:
    int portHandle;
    string port;

public:
    nixCom () = default;
    ~nixCom () { close( portHandle ); }

    nixCom ( int port );

    void defPort ( int port );

    void send( string message );
};

class nixController {
private:
    motor *Lmotor,
          *Rmotor;

    nixCom controlPort;

public:
    nixController ( int port );
    ~nixController () = default;

    void setLR ( motor *Lmotor, motor *Rmotor );
    void ride ( int Lval, int Rval );
    void motorStart ( motor &currentMotor, int val );
};

#endif // NIXCOM_H_INCLUDED
