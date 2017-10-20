#include <iostream>
#include "hashex.h"

void TestGet();

int main()
{
    try
    {
        TestGet();
    }
    catch( std::exception& e )
    {
        std::cout << e.what() << std::endl << std::flush;
        return 1;
    }

    std::cout << "OK\n" << std::flush;
    return 0;
}

//
//
//
void TestGet()
{
    HashEx he;
    Key key( 1 );
    Data data = he.Get( key );
}

