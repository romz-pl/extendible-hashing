#include <iostream>
#include <set>
#include <cassert>
#include <sstream>
#include "directory.h"
#include "index.h"

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
    const uint32_t ss = get_dir_size();
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
//
//
void Directory::grow()
{
    const uint32_t ss = get_dir_size();
    assert( ss == static_cast< uint32_t >( m_bucket.size() ) );

    m_bucket.reserve( 2 * ss );
    for( uint32_t i = 0 ; i < ss ; i++ )
        m_bucket.push_back( m_bucket[ i ] );

    m_global_depth++;
    //std::cout << "get_dir_size=" << get_dir_size() << "\n";
}

//
//
//
void Directory::shrink()
{
    for( size_t i = 0 ; i < m_bucket.size() ; i++ )
    {
        if( m_bucket[ i ]->get_depth() == m_global_depth )
        {
            return;
        }
    }
    m_global_depth--;
    const uint32_t ss = get_dir_size();
    for( uint32_t i = 0 ; i < ss; i++ )
        m_bucket.pop_back();
}

//
//
//
void Directory::split( uint32_t idx )
{
    const uint32_t local_depth = m_bucket[ idx ]->increase_depth();
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
    const int32_t pair_index = m_bucket[ idx ]->get_pair_index( idx );

    const int32_t index_diff = m_bucket[ idx ]->get_index_diff();
    const int32_t dir_size = get_dir_size();

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
    Bucket *b = m_bucket[ idx ];

    const int32_t pair_index = b->get_pair_index( idx );
    const int32_t index_diff = b->get_index_diff();

    Bucket *bp = m_bucket[ pair_index ];

    if( bp->get_depth() == b->get_depth() )
    {
        bp->decrease_depth();

        delete b;

        // Assign values to siblings buckets
        m_bucket[ idx ] = bp;

        for( int32_t i = idx - index_diff ; i >= 0 ; i -= index_diff )
            m_bucket[ i ] = bp;

        const int32_t dir_size = get_dir_size();
        for( int32_t i = idx + index_diff ; i < dir_size ; i += index_diff )
            m_bucket[ i ] = bp;
    }
}


//
//
//
void Directory::insert( const Key &key, const Data &value, bool reinserted )
{
    const uint32_t idx = Index::get( key, m_global_depth );

    Bucket* b = m_bucket[ idx ];
    if( b->has_key( key ) )
    {
        std::stringstream buffer;
        buffer << "Key " << key.to_string() << " already exists in bucket " << b->get_id_as_string( idx );
        throw std::runtime_error( buffer.str() );
    }

    if( b->is_full() )
    {
        split( idx );
        insert( key, value, reinserted );
        return;
    }

    b->insert( key, value );
    if( !reinserted )
    {
        m_count++;
        LOGGER( std::cout << "Inserted key " << key.to_string() << " in bucket " << b->get_id_as_string( idx ) << std::endl; )
    }
    else
    {
        LOGGER( std::cout << "Moved key " << key.to_string() << " to bucket " << b->get_id_as_string( idx ) << std::endl; )
    }

}

//
//
//
void Directory::remove( const Key& key, int mode )
{
    const uint32_t idx = Index::get( key, m_global_depth );
    Bucket *b = m_bucket[ idx ];
    b->remove( key );
    m_count--;

    LOGGER( std::cout << "Deleted key " << key.to_string() << " from bucket " << b->get_id_as_string( idx ) << std::endl; )

    if( mode > 0 )
    {
        if( b->is_empty() && b->get_depth() > 1 )
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
    const uint32_t idx = Index::get( key, m_global_depth );
    m_bucket[ idx ]->update( key, value );

    LOGGER( std::cout << "Value updated" << std::endl; )
}

//
//
//
Data Directory::search( const Key& key ) const
{
    const uint32_t idx = Index::get( key, m_global_depth );

    LOGGER( std::cout << "Searching key " << key.to_string() << " in bucket " << m_bucket[ idx ]->get_id_as_string( idx ) << std::endl; )

    const Data value = m_bucket[ idx ]->search( key );
    LOGGER( std::cout << "Value = " << value.to_string() << std::endl; )

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
        const uint32_t d = m_bucket[ i ]->get_depth();
        const std::string s = m_bucket[ i ]->get_id_as_string( i );
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

//
// Returns current size of the directory
//
uint32_t Directory::get_dir_size() const
{
    return ( 1U << m_global_depth );
}

