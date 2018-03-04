#include <gtest/gtest.h>
#include "hashex.h"


//
//
//
TEST(hashex, print)
{
    const int initial_global_depth = 2;
    const int bucket_size = 2;
    HashEx hashEx( initial_global_depth, bucket_size );

    std::string txt;
    const std::size_t eltNo = 7;
    for( std::size_t i = 0; i < eltNo; i++ )
    {
        txt = "aa" + std::to_string( i );
        EXPECT_NO_THROW( hashEx.Put( Key( i ), Data( txt ) ) );
    }

    EXPECT_NO_THROW( hashEx.Print() );
}

