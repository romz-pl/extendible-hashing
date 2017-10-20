#include <iostream>
#include "hashex.h"

void TestGet();
void TestPut();

int main()
{
    try
    {
        TestPut();
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

//
//
//
void TestPut()
{
    HashEx he;
    Key key( 1 );
    Data data( "abc-1" );
    he.Put( key, data );

    key = Key( 3 );
    data = Data( "abc-3" );
    he.Put( key, data );

    // he.Put( key, data );
}
