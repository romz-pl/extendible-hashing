#include <gtest/gtest.h>
#include "hashex.h"
#include <cassert>
#include <random>
#include <algorithm>

//
//
//
HashEx CreateHashEx()
{
    const int initial_global_depth = 2;
    const int bucket_size = 3;
    HashEx hashEx( initial_global_depth, bucket_size );
    return hashEx;
}


//
// Generate unique keys
//
std::vector< Key > GenerateKeys()
{
    // Number of tested keys.
    // Chenge this value, if needed!
    const std::size_t eltNo = 14000;

    std::vector< Key > key;
    key.reserve( eltNo );
    for( std::size_t i = 0; i < eltNo; i++ )
        key.push_back( Key( i ) );

    // Make key randomly distributed
    std::shuffle( key.begin(), key.end(), std::mt19937{ std::random_device{}() } );

    return key;

}

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

//
// Insert keys
//
void Insert( std::map< Key, Data >& stlMap, HashEx& hashEx, const std::vector< Key >& key )
{
    const std::size_t maxLength = 50;

    for( Key k : key )
    {
        const Data data = Data( GetRandomString( maxLength ) );
        EXPECT_NO_THROW( hashEx.Put( k, data ) );
        // hashEx.Print( true );
        stlMap.insert( std::make_pair( k, data ) );
    }

    EXPECT_TRUE( hashEx.Count() == stlMap.size() );

    for( auto v : stlMap )
    {
        EXPECT_ANY_THROW( hashEx.Put( v.first, v.second ) );
    }

}

//
// Find keys
//
void Find( const std::map< Key, Data >& stlMap, const HashEx& hashEx, std::vector< Key >& key )
{
    // Make key randomly distributed other then inserted
    std::shuffle( key.begin(), key.end(), std::mt19937{ std::random_device{}() } );

    // Check if keys are in hash table
    for( Key k : key )
    {
        const Data dataA = hashEx.Get( k );
        const Data dataB = stlMap.at( k );

        EXPECT_TRUE( dataA == dataB );
    }
}

//
// Delete keys
//
void Delete( std::map< Key, Data >& stlMap, HashEx& hashEx, std::vector< Key >& key )
{
    // Make key randomly distributed other then inserted
    std::shuffle( key.begin(), key.end(), std::mt19937{ std::random_device{}() } );

    // Delete keys in random order
    for( Key k : key )
    {
        EXPECT_NO_THROW( hashEx.Delete( k ) );
        EXPECT_ANY_THROW( hashEx.Delete( k ) );
        EXPECT_ANY_THROW( hashEx.Get( k ) );
        stlMap.erase( k );
    }

    EXPECT_TRUE( hashEx.Count() == 0 );
    EXPECT_TRUE( hashEx.Count() == stlMap.size() );
}


//
//
//
TEST(hashex, insert)
{
    
    std::map< Key, Data > stlMap;
    HashEx hashEx = CreateHashEx();
    std::vector< Key > key = GenerateKeys();

    Insert( stlMap, hashEx, key );

    Find( stlMap, hashEx, key );
    
    Delete( stlMap, hashEx, key );


}

