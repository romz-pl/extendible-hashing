#include "directory.h"
#include <iostream>
#include <set>
#include <cassert>
#include <sstream>


Directory::Directory( uint32_t depth, uint32_t bucket_size )
    : m_global_depth( depth)
    , m_bucket_size( bucket_size )
    , m_count( 0 )
{
    const uint32_t ss = ( 1U << m_global_depth );
    m_buckets.reserve( ss );
    for( size_t i = 0 ; i < ss ; i++ )
    {
        m_buckets.push_back( new Bucket( depth, bucket_size ) );
    }
}

uint32_t Directory::hash( const Key& key ) const
{
    const size_t n = key.GetHash();
    return n & ( ( 1 << m_global_depth ) - 1 );
}

uint32_t Directory::pairIndex( uint32_t bucket_no, uint32_t depth )
{
    return bucket_no ^ ( 1 << ( depth - 1 ) );
}

void Directory::grow()
{
    const size_t ss = m_buckets.size();
    assert( ss == ( 1U << m_global_depth ) );

    m_buckets.reserve( 2 * ss );
    for( size_t i = 0 ; i < ss ; i++ )
        m_buckets.push_back( m_buckets[ i ] );

    m_global_depth++;
}

void Directory::shrink()
{
    for( size_t i = 0 ; i < m_buckets.size() ; i++ )
    {
        if( m_buckets[ i ]->getDepth() == m_global_depth )
        {
            return;
        }
    }
    m_global_depth--;
    for( uint32_t i = 0 ; i < 1U << m_global_depth; i++ )
        m_buckets.pop_back();
}

void Directory::split( uint32_t bucket_no )
{
    const uint32_t local_depth = m_buckets[ bucket_no ]->increaseDepth();
    if( local_depth > m_global_depth )
        grow();

    const int32_t pair_index = pairIndex( bucket_no, local_depth );
    m_buckets[ pair_index ] = new Bucket( local_depth, m_bucket_size );

    const std::map< Key, std::string > temp = m_buckets[ bucket_no ]->copy();
    m_buckets[ bucket_no ]->clear();
    const int32_t index_diff = 1 << local_depth;
    const int32_t dir_size = 1 << m_global_depth;

    for( int32_t i = pair_index - index_diff ; i >= 0 ; i -= index_diff )
        m_buckets[ i ] = m_buckets[pair_index];

    for( int32_t i = pair_index + index_diff ; i < dir_size ; i += index_diff )
        m_buckets[ i ] = m_buckets[ pair_index ];

    for( const auto v : temp )
        insert( v.first, v.second, 1 );
}

void Directory::merge( uint32_t bucket_no )
{
    const uint32_t local_depth = m_buckets[ bucket_no ]->getDepth();
    const int32_t pair_index = pairIndex( bucket_no, local_depth );
    const int32_t index_diff = 1 << local_depth;
    const int32_t dir_size = 1 << m_global_depth;

    if( m_buckets[ pair_index ]->getDepth() == local_depth )
    {
        m_buckets[ pair_index ]->decreaseDepth();
        delete( m_buckets[ bucket_no ] );
        m_buckets[ bucket_no ] = m_buckets[ pair_index ];

        for( int32_t i = bucket_no - index_diff ; i >= 0 ; i -= index_diff )
            m_buckets[ i ] = m_buckets[ pair_index ];

        for( int32_t i = bucket_no + index_diff ; i < dir_size ; i += index_diff )
            m_buckets[ i ] = m_buckets[ pair_index ];
    }
}

std::string Directory::bucket_id( uint32_t n ) const
{
    std::string s;
    uint32_t d = m_buckets[ n ]->getDepth();

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

void Directory::insert( const Key &key, std::string value, bool reinserted )
{
    const uint32_t bucket_no = hash( key );

    Bucket* b = m_buckets[ bucket_no ];
    if( b->hasKey( key ) )
    {
        std::stringstream buffer;
        buffer << "Key " << key.ToString() << " already exists in bucket " << bucket_id( bucket_no );
        throw std::runtime_error( buffer.str() );
    }

    if( b->isFull() )
    {
        split( bucket_no );
        insert( key, value, reinserted );
        return;
    }

    b->insert( key, value );
    if( !reinserted )
    {
        m_count++;
        std::cout << "Inserted key " << key.ToString() << " in bucket " << bucket_id( bucket_no ) << std::endl;
    }
    else
    {
        std::cout << "Moved key " << key.ToString() << " to bucket " << bucket_id( bucket_no ) << std::endl;
    }

}

void Directory::remove( const Key& key, int mode )
{
    const uint32_t bucket_no = hash( key );
    m_buckets[ bucket_no ]->remove( key );
    m_count--;
    std::cout << "Deleted key " << key.ToString() << " from bucket " << bucket_id( bucket_no ) << std::endl;

    if( mode > 0 )
    {
        if( m_buckets[ bucket_no ]->isEmpty() && m_buckets[ bucket_no ]->getDepth() > 1 )
            merge( bucket_no );
    }
    if( mode > 1 )
    {
        shrink();
    }
}

void Directory::update( const Key &key, std::string value )
{
    const uint32_t bucket_no = hash( key );
    m_buckets[ bucket_no ]->update( key, value );
    std::cout << "Value updated" << std::endl;
}

std::string Directory::search( const Key& key ) const
{
    const uint32_t bucket_no = hash( key );
    std::cout << "Searching key " << key.ToString() << " in bucket " << bucket_id( bucket_no ) << std::endl;

    const std::string value = m_buckets[ bucket_no ]->search( key );
    std::cout << "Value = " << value << std::endl;
    return value;
}

void Directory::display( bool duplicates ) const
{
    std::set< std::string>  shown;
    std::cout << "Global depth : " << m_global_depth << std::endl;

    for( std::size_t i = 0; i < m_buckets.size(); i++ )
    {
        const uint32_t d = m_buckets[ i ]->getDepth();
        const std::string s = bucket_id( i );
        if( duplicates || shown.find( s ) == shown.end() )
        {
            shown.insert( s );
            for( uint32_t j = d; j <= m_global_depth; j++ )
                std::cout << " ";
            std::cout << s << " => ";
            m_buckets[ i ]->display();
        }
    }
}

size_t Directory::count() const
{
    return m_count;
}
