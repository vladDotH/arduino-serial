#include "nixcom.h"

using namespace std;

int main ()
{
    nixController ard( "/dev/ttyACM0" );
    ard.setLR( &A, &B );

    char key;

    while( key != 'q' )
    {
        cin >> key;

        if ( key == 'w' )
            ard.ride( 100, -100 );
        else if ( key == 's' )
            ard.ride( -100, 100 );
        else if ( key == 'a' )
            ard.ride( -100, -100 );
        else if ( key == 'd' )
            ard.ride( 100, 100 );

        else ard.ride(0,0);
    }
}