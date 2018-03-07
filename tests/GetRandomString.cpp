#include <random>
#include <algorithm>

//
//
//
std::string GetRandomString( std::size_t maxLength )
{
    const std::string alphabet( "0123456789"
                                "abcdefghijklmnopqrstuvwxyz"
                                "ABCDEFGHIJKLMNOPQRSTUVWXYZ" );

    std::random_device rd;
    std::mt19937 g( rd() );
    std::uniform_int_distribution< std::string::size_type > pick( 0, alphabet.size() );
    std::uniform_int_distribution< std::string::size_type > pickLength( 1, maxLength );

    std::string::size_type length = pickLength( g );
    std::string s;
    s.reserve( length );

    while( length-- )
    {
        const char c = alphabet[ pick( g ) ];
        s += c;
    }
    return s;
}

