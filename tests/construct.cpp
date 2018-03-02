#include <gtest/gtest.h>
#include "hashex.h"


//
//
//
TEST(hashex, construct)
{
    for( uint32_t initial_global_depth = 2; initial_global_depth < 10; initial_global_depth++ )
    {
        for( uint32_t bucket_size = 0; bucket_size < 100; bucket_size++ )
        {
            EXPECT_NO_THROW( HashEx( initial_global_depth, bucket_size ) );
        }
    }
}

