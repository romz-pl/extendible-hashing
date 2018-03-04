#include <gtest/gtest.h>
#include "hashex.h"


//
//
//
TEST(hashex, update)
{
    const int initial_global_depth = 4;
    const int bucket_size = 5;
    HashEx hashEx( initial_global_depth, bucket_size );

    std::string txt;
    const std::size_t eltNo = 2000;
    for( std::size_t i = 0; i < eltNo; i++ )
    {
        txt = "aa" + std::to_string( i );
        EXPECT_NO_THROW( hashEx.Put( Key( i ), Data( txt ) ) );
    }
    
    for( std::size_t i = 0; i < eltNo; i++ )
    {
        txt = "bb" + std::to_string( i );
        EXPECT_NO_THROW( hashEx.Update( Key( i ), Data( txt ) ) );
    }
    
    for( std::size_t i = 0; i < eltNo; i++ )
    {
        txt = "bb" + std::to_string( i );
        const Data data = hashEx.Get( Key( i ) );
        EXPECT_TRUE( data == Data( txt ) );
        
    }

}

