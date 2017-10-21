#include <iostream>
#include "hashex.h"
#include <cassert>
#include <random>
#include <algorithm>
#include <unordered_map>

void TestGet();
void TestPut();
void TestPutSmall();
Data GetRandomData();

int main()
{
    try
    {
        // TestGet();
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
Data GetRandomData()
{
    const std::string alphabet( "0123456789"
                                "abcdefghijklmnopqrstuvwxyz"
                                "ABCDEFGHIJKLMNOPQRSTUVWXYZ" );

    std::random_device rd;
    std::mt19937 g( rd() );
    std::uniform_int_distribution< std::string::size_type > pick( 0, alphabet.size() );

    std::string::size_type length = pick( g );
    std::string s;
    s.reserve( length );

    while( length-- )
    {
        const char c = alphabet[ pick( g ) ];
        s += c;
    }
    return Data( s );
}

namespace std
{
    template<> struct hash< Key >
    {
        typedef Key argument_type;
        typedef std::size_t result_type;
        result_type operator()( argument_type const& k ) const noexcept
        {
            return k.GetHash();
        }
    };
}

//
//
//
void TestPut()
{
    HashEx he;
    std::unordered_map< Key, Data > stlMap;

    const std::size_t eltNo = 40;
    std::vector< Key > key;
    key.reserve( eltNo );
    for( std::size_t i = 0; i < eltNo; i++ )
        key.push_back( Key( i ) );

     std::shuffle( key.begin(), key.end(), std::mt19937{ std::random_device{}() } );

     int jj = 0;
     for( const Key& k : key )
     {
         const Data data = GetRandomData();

         std::cout << jj << ": " << k.m_value << " " << data.m_data << std::endl << std::flush;

         he.Put( k, data );

         // he.Print();



         stlMap.insert( std::make_pair( k, data ) );
         jj++;
     }

     std::shuffle( key.begin(), key.end(), std::mt19937{ std::random_device{}() } );

     for( const Key& k : key )
     {
         const Data dataA = he.Get( k );
         const Data dataB = stlMap.at( k );

         if( dataA != dataB )
         {
             throw std::runtime_error( "Error" );
         }
     }
}

//
//
//
void TestPutSmall()
{
    HashEx he;
    Key keyA( 1 );
    Data dataA( "abc-1" );
    he.Put( keyA, dataA );
    assert( he.Get( keyA ) == dataA );

    Key keyB = Key( 3 );
    Data dataB = Data( "abc-3" );
    he.Put( keyB, dataB );
    assert( he.Get( keyA ) == dataA );
    assert( he.Get( keyB ) == dataB );

    // he.Put( key, data );
}
