#include <gtest/gtest.h>
#include "hashex.h"
#include <random>
#include <algorithm>
#include <limits>

//
//
//
TEST(bucket, Insert)
{
    const uint32_t depth = 2;
    const uint32_t maxAllowedSize = 3;

    Bucket bucket( depth, maxAllowedSize );
    
    EXPECT_NO_THROW( bucket.insert( Key( 0U ), Data( "a" ) ) );
    
    // Duplication
    EXPECT_ANY_THROW( bucket.insert( Key( 0U ), Data( "a" ) ) );
    
    for( uint32_t i = 1; i < maxAllowedSize; i++ )
    {
        EXPECT_NO_THROW( bucket.insert( Key( i ), Data( "a" ) ) );
    }
    
    // Bucket is full
    EXPECT_ANY_THROW( bucket.insert( Key( maxAllowedSize ), Data( "a" ) ) );
}


//
//
//
TEST(bucket, Remove)
{
    const uint32_t depth = 2;
    const uint32_t maxAllowedSize = 3;

    Bucket bucket( depth, maxAllowedSize );
    
    const Key key( 1 );
    EXPECT_NO_THROW( bucket.insert( key, Data( "a" ) ) );
    EXPECT_NO_THROW( bucket.remove( key ) );
    EXPECT_ANY_THROW( bucket.remove( key ) );
}

//
//
//
TEST(bucket, Update)
{
    const uint32_t depth = 2;
    const uint32_t maxAllowedSize = 3;

    Bucket bucket( depth, maxAllowedSize );
    
    const Key key( 1 );
    EXPECT_NO_THROW( bucket.insert( key, Data( "a" ) ) );
    
    const Data data( "b" );
    EXPECT_NO_THROW( bucket.update( key, data ) );
    EXPECT_TRUE( bucket.search( key ) == data );
    
    EXPECT_NO_THROW( bucket.remove( key ) );
    // Key does not exist
    EXPECT_ANY_THROW( bucket.update( key, data ) );
}

//
//
//
TEST(bucket, Search)
{
    const uint32_t depth = 2;
    const uint32_t maxAllowedSize = 3;

    Bucket bucket( depth, maxAllowedSize );
    
    const Key key( 1 );
    EXPECT_ANY_THROW( bucket.search( key ) );
    
    const Data data( "b" );
    EXPECT_NO_THROW( bucket.insert( key, data ) );
    EXPECT_TRUE( bucket.search( key ) == data );
    
    EXPECT_NO_THROW( bucket.remove( key ) );
    EXPECT_ANY_THROW( bucket.search( key ) );
}

//
//
//
TEST(bucket, full_empty)
{
    const uint32_t depth = 2;
    const uint32_t maxAllowedSize = 3;

    Bucket bucket( depth, maxAllowedSize );
    
    EXPECT_TRUE( !bucket.is_full( ) );
    EXPECT_TRUE( bucket.is_empty( ) );
    
    for( uint32_t i = 0; i < maxAllowedSize; i++ )
    {
        EXPECT_NO_THROW( bucket.insert( Key( i ), Data( "a" ) ) );
    }
    EXPECT_TRUE( bucket.is_full( ) );
    EXPECT_TRUE( !bucket.is_empty( ) );
}

//
//
//
TEST(bucket, depth)
{
    const uint32_t depth = 2;
    const uint32_t maxAllowedSize = 3;

    Bucket bucket( depth, maxAllowedSize );
    
    EXPECT_TRUE( bucket.get_depth() == depth );
    
    for( uint32_t i = 0; i < depth; i++ )
    {
        EXPECT_NO_THROW( bucket.decrease_depth() );
        EXPECT_TRUE( bucket.get_depth() == depth - i - 1 );
    }
    
    EXPECT_ANY_THROW( bucket.decrease_depth() );
    
    EXPECT_NO_THROW( bucket.increase_depth() );
    EXPECT_TRUE( bucket.get_depth() == 1 );
}

//
//
//
TEST(bucket, copy)
{
    const uint32_t depth = 2;
    const uint32_t maxAllowedSize = 10;

    Bucket bucket( depth, maxAllowedSize );
    
    const std::vector< Key > key{ Key( 1 ), Key( 2 ), Key( 3 ) };
    
    for( auto k : key )
    {
        EXPECT_NO_THROW( bucket.insert( k, Data( "a" + k.to_string() ) ) );
    }
    
    std::map< Key, Data >  cp = bucket.copy();
    
    for( auto k : key )
    {
        EXPECT_TRUE( cp.at( k ) == bucket.search( k ) );
    }
}

//
//
//
TEST(bucket, clear)
{
    const uint32_t depth = 2;
    const uint32_t maxAllowedSize = 10;

    Bucket bucket( depth, maxAllowedSize );
    
    EXPECT_TRUE( bucket.is_empty( ) );
    for( size_t i = 0; i < 4; i++ )
    {
        const Data data( "a" + std::to_string( i ) );
        EXPECT_NO_THROW( bucket.insert( Key( i ), data ) );
        EXPECT_TRUE( !bucket.is_empty( ) );
    }
    
    EXPECT_NO_THROW( bucket.clear() );
    EXPECT_TRUE( bucket.is_empty( ) );
}


//
//
//
TEST(bucket, hasKey)
{
    const uint32_t depth = 2;
    const uint32_t maxAllowedSize = 10;

    Bucket bucket( depth, maxAllowedSize );
    
    for( size_t i = 0; i < 4; i++ )
    {
        const Key key( i );
        const Data data( "a" + std::to_string( i ) );
        EXPECT_NO_THROW( bucket.insert( key, data ) );
        EXPECT_TRUE( bucket.has_key( key ) ); 
    }
}

//
//
//
TEST(bucket, display)
{
    const uint32_t depth = 2;
    const uint32_t maxAllowedSize = 10;

    Bucket bucket( depth, maxAllowedSize );
    
    const std::vector< Key > key{ Key( 1 ), Key( 2 ), Key( 3 ) };
    
    for( auto k : key )
    {
        EXPECT_NO_THROW( bucket.insert( k, Data( "a" + k.to_string() ) ) );
    }
    
    bucket.display();
}

