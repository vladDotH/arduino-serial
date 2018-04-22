#include "wincom.h"

using namespace std;

winController ard( 3 );


#define KEY_DOWN(key) (GetAsyncKeyState(key) & 0x8000)

int main()
{
    ard.setLR( &A, &B );

    while ( !KEY_DOWN( VK_SPACE ) )
    {
        if ( KEY_DOWN( 'W' ) )
        {
//            ard.motorStart( B, 100 );
            ard.ride( 100, -100 );
        }

        else if ( KEY_DOWN( 'S' ) )
        {
            ard.ride( -100, 100 );
        }

        else if ( KEY_DOWN( 'A' ) )
        {
            ard.ride( -100, -100 );
        }

        else if ( KEY_DOWN( 'D' ) )
        {
            ard.ride( 100, 100 );
        }

        else
        {
//            ard.motorStart( B, 0 );
            ard.ride( 0, 0 );
        }
    }
}
