#include <gtest/gtest.h>
#include "hashex.h"
#include <random>
#include <algorithm>
#include <limits>
#include "GetRandomString.h"

//
//
//
TEST(data, Compare)
{

    std::random_device rd;
    std::mt19937 g( rd() );

    const std::size_t stringMaxLength = 8000;
    std::uniform_int_distribution< std::size_t > pick( 0, stringMaxLength );

    for( size_t i = 0; i < 100; i++ )
    {
        const std::string v1 = GetRandomString( pick ( g ) );
        const std::string v2 = GetRandomString( pick ( g ) );
        
        EXPECT_TRUE( Data( v1 ) == Data( v1 ) );
        EXPECT_TRUE( Data( v2 ) == Data( v2 ) );
        
        if( v1 != v2 )
        {
            EXPECT_TRUE( Data( v1 ) != Data( v2 ) );
        }
        
        if( v1 < v2 )
        {
            EXPECT_TRUE( Data( v1 ) < Data( v2 ) );
        }
        
        if( v1 <= v2 )
        {
            EXPECT_TRUE( Data( v1 ) <= Data( v2 ) );
        }
        
        if( v1 > v2 )
        {
            EXPECT_TRUE( Data( v1 ) > Data( v2 ) );
        }
        
        if( v1 >= v2 )
        {
            EXPECT_TRUE( Data( v1 ) >= Data( v2 ) );
        }
        
    }
}

//
//
//
TEST(data, ToString)
{
    std::random_device rd;
    std::mt19937 g( rd() );

    const std::size_t stringMaxLength = 8000;
    std::uniform_int_distribution< std::size_t > pick( 0, stringMaxLength );

    for( size_t i = 0; i < 100; i++ )
    {
        const std::string v = GetRandomString( pick ( g ) );

        const Data data( v );
        EXPECT_TRUE( data.to_string() == v );
    }
}

