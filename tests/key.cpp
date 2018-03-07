#include <gtest/gtest.h>
#include "hashex.h"
#include <random>
#include <algorithm>
#include <limits>

//
//
//
TEST(key, Compare)
{

    std::random_device rd;
    std::mt19937 g( rd() );

    std::uniform_int_distribution< uint32_t > pick( 0, std::numeric_limits<uint32_t>::max() );

    for( size_t i = 0; i < 10000; i++ )
    {
        const uint32_t v1 = pick( g );
        const uint32_t v2 = pick( g );
        
        EXPECT_TRUE( Key( v1 ) == Key( v1 ) );
        EXPECT_TRUE( Key( v2 ) == Key( v2 ) );
        
        if( v1 != v2 )
        {
            EXPECT_TRUE( Key( v1 ) != Key( v2 ) );
        }
        
        if( v1 < v2 )
        {
            EXPECT_TRUE( Key( v1 ) < Key( v2 ) );
        }
        
        if( v1 <= v2 )
        {
            EXPECT_TRUE( Key( v1 ) <= Key( v2 ) );
        }
        
        if( v1 > v2 )
        {
            EXPECT_TRUE( Key( v1 ) > Key( v2 ) );
        }
        
        if( v1 >= v2 )
        {
            EXPECT_TRUE( Key( v1 ) >= Key( v2 ) );
        }
        
    }
}

//
//
//
TEST(key, ToString)
{
    std::random_device rd;
    std::mt19937 g( rd() );

    std::uniform_int_distribution< uint32_t > pick( 0, std::numeric_limits<uint32_t>::max() );

    for( size_t i = 0; i < 10000; i++ )
    {
        const uint32_t v = pick( g );
        const Key key( v );
        EXPECT_TRUE( !key.ToString().empty() );
    }
}

//
//
//
TEST(key, GetHash)
{
    std::random_device rd;
    std::mt19937 g( rd() );

    std::uniform_int_distribution< uint32_t > pick( 0, std::numeric_limits<uint32_t>::max() );

    for( size_t i = 0; i < 10000; i++ )
    {
        const uint32_t v = pick( g );
        const Key key( v );
        EXPECT_NO_THROW( key.GetHash() );
    }
}

