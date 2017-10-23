#include <iostream>
#include "hashex.h"
#include <cassert>
#include <random>
#include <algorithm>
#include <unordered_map>

void Check();
std::string GetRandomString();

int main()
{
    try
    {
        Check();
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
// Hashing function for STL unordered_map
//
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
void Check()
{


    const int initial_global_depth = 2;
    const int bucket_size = 3;
    Directory dir( initial_global_depth, bucket_size );
    std::unordered_map< Key, Data > stlMap;

    const std::size_t eltNo = 1400;
    std::vector< Key > key;
    key.reserve( eltNo );
    for( std::size_t i = 0; i < eltNo; i++ )
        key.push_back( Key( i ) );

     std::shuffle( key.begin(), key.end(), std::mt19937{ std::random_device{}() } );

     for( Key k : key )
     {
         const Data data = Data( GetRandomString() );

         dir.insert( k, data, 0);
         // dir.display( true );

         stlMap.insert( std::make_pair( k, data ) );
     }

     std::shuffle( key.begin(), key.end(), std::mt19937{ std::random_device{}() } );

     for( Key k : key )
     {
         const Data dataA = dir.search( k );
         const Data dataB = stlMap.at( k );

         if( dataA != dataB )
         {
             throw std::runtime_error( "Insert Error" );
         }
     }
     if( dir.count() != stlMap.size() )
     {
         throw std::runtime_error( "Insert Error 2" );
     }

     std::shuffle( key.begin(), key.end(), std::mt19937{ std::random_device{}() } );

     for( Key k : key )
     {
         dir.remove( k, 1 );
         stlMap.erase( k );
     }

     if( dir.count() != stlMap.size() )
     {
         throw std::runtime_error( "Delete Error" );
     }
}


//
//
//
std::string GetRandomString()
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
    return s;
}




