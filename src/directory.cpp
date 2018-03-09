#include "directory.h"
#include <iostream>
#include <set>
#include <cassert>
#include <sstream>

//
//
//
#ifdef NOLOGGING
#  define LOGGER(x)
#else
#  define LOGGER(x) x
#endif


//
//
//
Directory::Directory( uint32_t depth, uint32_t max_bucket_size )
    : m_global_depth( depth)
    , m_max_bucket_size( max_bucket_size )
    , m_count( 0 )
{
    const uint32_t ss = 1U << m_global_depth;
    m_bucket.reserve( ss );
    for( size_t i = 0 ; i < ss ; i++ )
    {
        m_bucket.push_back( new Bucket( depth, max_bucket_size ) );
    }
}

//
//
//
Directory::~Directory()
{
    const size_t ss = m_bucket.size();
    for( size_t i = 0; i < ss; i++ )
    {
        Bucket *b =  m_bucket[ i ];
        if( !b )
            continue;

        for( size_t k = i + 1; k < ss; k++ )
        {
            if( b == m_bucket[ k ] )
            {
                m_bucket[ k ] = nullptr;
            }
        }
        delete b;
        m_bucket[ i ] = nullptr;
    }
}

//
// Extracts least significant m_global_depth bits from key's hash.
// Returns index of the bucket for given "key".
//
uint32_t Directory::get_index( const Key& key ) const
{
    const uint32_t n = key.GetHash();
    // const uint32_t ss = ( 1U << m_global_depth );
    // const uint32_t v = n & ( ss - 1 );
    const uint32_t v = n & ~( (~0) << m_global_depth );
    return v;
}

//
// Flips "depth-1" bit in "idx".
// Return the resulting value.
//
uint32_t Directory::get_pair_index( uint32_t idx, uint32_t depth )
{
    assert( depth > 0 );
    const uint32_t ss = 1U << ( depth - 1U );
    const uint32_t v = idx ^ ss; 
    return v;
}

//
//
//
void Directory::grow()
{
    const size_t ss = m_bucket.size();
    assert( ss == 1U << m_global_depth );

    m_bucket.reserve( 2 * ss );
    for( size_t i = 0 ; i < ss ; i++ )
        m_bucket.push_back( m_bucket[ i ] );

    m_global_depth++;
}

//
//
//
void Directory::shrink()
{
    for( size_t i = 0 ; i < m_bucket.size() ; i++ )
    {
        if( m_bucket[ i ]->getDepth() == m_global_depth )
        {
            return;
        }
    }
    m_global_depth--;
    const uint32_t ss = 1U << m_global_depth;
    for( uint32_t i = 0 ; i < ss; i++ )
        m_bucket.pop_back();
}

//
//
//
void Directory::split( uint32_t idx )
{
    const uint32_t local_depth = m_bucket[ idx ]->increaseDepth();
    if( local_depth > m_global_depth )
        grow();

    const auto temp = m_bucket[ idx ]->copy();
    m_bucket[ idx ]->clear();

    Bucket *bp = new Bucket( local_depth, m_max_bucket_size );
    assign_to_siblings( idx, bp );

    for( const auto v : temp )
        insert( v.first, v.second, true );
}

//
// Assign the pointer "bp" to all sibling of the bucket with index "idx" 
//
void Directory::assign_to_siblings( uint32_t idx, Bucket* bp )
{
    const uint32_t local_depth = m_bucket[ idx ]->getDepth();
    const int32_t pair_index = get_pair_index( idx, local_depth );

    const int32_t index_diff = 1 << local_depth;
    const int32_t dir_size = 1 << m_global_depth;

    m_bucket[ pair_index ] = bp;

    for( int32_t i = pair_index - index_diff ; i >= 0 ; i -= index_diff )
        m_bucket[ i ] = bp;
    
    for( int32_t i = pair_index + index_diff ; i < dir_size ; i += index_diff )
        m_bucket[ i ] = bp;

}

//
//
//
void Directory::merge( uint32_t idx )
{
    const uint32_t local_depth = m_bucket[ idx ]->getDepth();
    const int32_t pair_index = get_pair_index( idx, local_depth );

    const int32_t index_diff = 1 << local_depth;
    const int32_t dir_size = 1 << m_global_depth;

    Bucket *bp = m_bucket[ pair_index ];

    if( bp->getDepth() == local_depth )
    {
        bp->decreaseDepth();

        delete m_bucket[ idx ];
        m_bucket[ idx ] = bp;

        for( int32_t i = idx - index_diff ; i >= 0 ; i -= index_diff )
            m_bucket[ i ] = bp;

        for( int32_t i = idx + index_diff ; i < dir_size ; i += index_diff )
            m_bucket[ i ] = bp;
    }
}

//
//
//
std::string Directory::bucket_id( uint32_t n ) const
{
    std::string s;
    uint32_t d = m_bucket[ n ]->getDepth();

    while( n > 0 && d > 0 )
    {
        s = ( n % 2 == 0 ? "0" : "1" ) + s;
        n /= 2;
        d--;
    }

    while( d > 0 )
    {
        s = "0" + s;
        d--;
    }

    return s;
}

//
//
//
void Directory::insert( const Key &key, const Data &value, bool reinserted )
{
    const uint32_t idx = get_index( key );

    Bucket* b = m_bucket[ idx ];
    if( b->hasKey( key ) )
    {
        std::stringstream buffer;
        buffer << "Key " << key.ToString() << " already exists in bucket " << bucket_id( idx );
        throw std::runtime_error( buffer.str() );
    }

    if( b->isFull() )
    {
        split( idx );
        insert( key, value, reinserted );
        return;
    }

    b->insert( key, value );
    if( !reinserted )
    {
        m_count++;
        LOGGER( std::cout << "Inserted key " << key.ToString() << " in bucket " << bucket_id( idx ) << std::endl; )
    }
    else
    {
        LOGGER( std::cout << "Moved key " << key.ToString() << " to bucket " << bucket_id( idx ) << std::endl; )
    }

}

//
//
//
void Directory::remove( const Key& key, int mode )
{
    const uint32_t idx = get_index( key );
    Bucket *b = m_bucket[ idx ];
    b->remove( key );
    m_count--;

    LOGGER( std::cout << "Deleted key " << key.ToString() << " from bucket " << bucket_id( idx ) << std::endl; )

    if( mode > 0 )
    {
        if( b->isEmpty() && b->getDepth() > 1 )
            merge( idx );
    }
    if( mode > 1 )
    {
        shrink();
    }
}

//
//
//
void Directory::update( const Key &key, const Data &value )
{
    const uint32_t idx = get_index( key );
    m_bucket[ idx ]->update( key, value );

    LOGGER( std::cout << "Value updated" << std::endl; )
}

//
//
//
Data Directory::search( const Key& key ) const
{
    const uint32_t idx = get_index( key );

    LOGGER( std::cout << "Searching key " << key.ToString() << " in bucket " << bucket_id( idx ) << std::endl; )

    const Data value = m_bucket[ idx ]->search( key );
    LOGGER( std::cout << "Value = " << value.ToString() << std::endl; )

    return value;
}

//
//
//
void Directory::display( bool duplicates ) const
{
    std::set< std::string>  shown;
    std::cout << "Global depth : " << m_global_depth << std::endl;

    for( std::size_t i = 0; i < m_bucket.size(); i++ )
    {
        const uint32_t d = m_bucket[ i ]->getDepth();
        const std::string s = bucket_id( i );
        if( duplicates || shown.find( s ) == shown.end() )
        {
            shown.insert( s );
            for( uint32_t j = d; j <= m_global_depth; j++ )
                std::cout << " ";
            std::cout << s << " => ";
            m_bucket[ i ]->display();
        }
    }
}

//
//
//
size_t Directory::count() const
{
    return m_count;
}
