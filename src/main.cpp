//
//
// 1. Implementation of extendible hashing in C++
//
// 2. This is the refactored, simpyfied and  improved https://github.com/nitish6174/extendible-hashing project
//
// 3. The implemenation is based on the book:
//    R. Ramakrishnan, J. Gehrke "DATABASE MANAGEMENT SYSTEMS" (third edition)
//    Chapter 11.2 "EXTENDIBLE HASHING"
//
// 4. Extendible hashing was proposed in the following paper:
//    R. Fagin, J. Nievergelt, N. Pippenger, and H. Strong, "Extendible Hashing - a fast access
//    method for dynamic files",  ACM Transactions on Database Systems,
//    vol. 4, No. 3, pp. 315-344, 1979.
//
// 5. Abstract from the original paper:
//    Extendible hashing is a new access technique, in which the user is guaranteed no more than
//    two page faults to locate the data associated with a given unique identifier, or key.
//    Unlike conventional hashing, extendible hashing has a dynamic structure that grows and shrinks gracefully
//    as the database grows and shrinks. This approach simultaneously solves the problem of making
//    hash tables that are extendible and of making radix search trees that are balanced. We study,
//    by analysis and simulation, the performance of extendible hashing. The results indicate that extendible
//    hashing provides an attractive alternative to other access methods, such as balanced trees.
//
// 6. G.D. Knott "Expandable open addressing hash table storage and retrieval", Proc. ACM SIGFIDET
//    Workshop on Data Description, Access, and Control, pp. 186-206, 1971,
//
// 7. P. Larson "Dynamic hashing", BIT vol. 18, pp. 184-201, 1978.
//
// 8. The algorithm is implemented in clas HashEx
//
// 9. The main functions calls the check function, checking the correcctness the implemented algorithms.
//
// Authr: Zbigniew Romanowski
// e-mail: romz@wp.pl
//


#include <iostream>
#include "hashex.h"
#include <cassert>
#include <random>
#include <algorithm>
#include <unordered_map>

void Check();
std::string GetRandomString();
std::vector< Key > GenerateKeys();
HashEx CreateHashEx();

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

    std::cout << "All test passed!\n" << std::flush;
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
    std::unordered_map< Key, Data > stlMap;
    HashEx hashEx = CreateHashEx();
    std::vector< Key > key = GenerateKeys();

    // Insert keys
    for( Key k : key )
    {
        const Data data = Data( GetRandomString() );
        hashEx.Put( k, data );
        // hashEx.Print( true );
        stlMap.insert( std::make_pair( k, data ) );
    }

    // Make key randomly distributed other then inserted
    std::shuffle( key.begin(), key.end(), std::mt19937{ std::random_device{}() } );

    // Check if keys are in hash table
    for( Key k : key )
    {
        const Data dataA = hashEx.Get( k );
        const Data dataB = stlMap.at( k );

        if( dataA != dataB )
        {
            throw std::runtime_error( "Insert Error" );
        }
    }
    if( hashEx.Count() != stlMap.size() )
    {
        throw std::runtime_error( "Insert Error: Not equal size" );
    }

    // Make key randomly distributed other then inserted
    std::shuffle( key.begin(), key.end(), std::mt19937{ std::random_device{}() } );

    // Delete keys in random order
    for( Key k : key )
    {
        hashEx.Delete( k );
        stlMap.erase( k );
    }

    if( hashEx.Count() != stlMap.size() )
    {
        throw std::runtime_error( "Delete Error: Not equal size" );
    }
}

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
// Generate keys
//
std::vector< Key > GenerateKeys()
{
    // Number of tested keys.
    // Chenge this value, if needed!
    const std::size_t eltNo = 1400;

    std::vector< Key > key;
    key.reserve( eltNo );
    for( std::size_t i = 0; i < eltNo; i++ )
        key.push_back( Key( i ) );

    // Make key randomly distributed
    std::shuffle( key.begin(), key.end(), std::mt19937{ std::random_device{}() } );

    return key;

}


//
// Returns randomply generated string.
// The length of the string is random, and not longer then the length of he alphabet.
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




