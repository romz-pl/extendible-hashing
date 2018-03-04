#include <gtest/gtest.h>
#include "hashex.h"


//
//
//
TEST(hashex, insert_colision)
{
    const int initial_global_depth = 2;
    const int bucket_size = 3;
    HashEx hashEx( initial_global_depth, bucket_size );
    
    EXPECT_NO_THROW( hashEx.Put( Key( 1 ), Data( "aa" ) ) );
    EXPECT_NO_THROW( hashEx.Put( Key( 2 ), Data( "bb" ) ) );
    EXPECT_ANY_THROW( hashEx.Put( Key( 2 ), Data( "cc" ) ) );
}

