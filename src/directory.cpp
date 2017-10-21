#include "directory.h"
#include <cassert>
#include <stdexcept>

//
//
//
Directory::Directory()
    : m_globalDepth( 1 )
{
    const std::size_t size = ( 1 << m_globalDepth );
    m_dir.resize( size, nullptr );

    for( Bucket*&b : m_dir )
        b = NewBucket( m_globalDepth );

}

//
//
//
Directory::~Directory()
{
    for( auto b : m_pool )
        delete b;
}

//
//
//
Data Directory::Get( const Key& key ) const
{
    assert( m_dir.size() != 0 );

    const std::size_t id = GetEntryId( key );
    const Bucket* b = m_dir[ id ];
    assert( b );
    return b->Get( key );
}

//
//
//
std::size_t Directory::GetEntryId( const Key& key ) const
{
    std::size_t mask = 0;
    for( std::uint32_t i = 0; i < m_globalDepth; i++ )
        mask |= ( 1 << i );

    std::size_t hv = key.GetHash();

    std::size_t ret = hv & mask;
    assert( ret < m_dir.size() );
    return ret;
}

//
//
//
void Directory::Put( const Key& key, const Data& data )
{
    std::size_t id = GetEntryId( key );

    if( !m_dir[ id ]->IsFull() )
    {
        m_dir[ id ]->Put( key, data );
        return;
    }

    if( m_dir[ id ]->GetKey() == key )
    {
        throw std::runtime_error( "Key already inserted" );
    }



    // Double the directory
    if( m_globalDepth == m_dir[ id ]->GetLocalDepth() )
    {
        m_globalDepth++;
        const std::vector< Bucket* > tmp = m_dir;
        m_dir.insert( m_dir.end(), tmp.begin(), tmp.end() );
    }

    // Split the Bucket
    Bucket* w = m_dir[ id ];
    w->IncLocalDepth();
    id = GetEntryId( m_dir[ id ]->GetKey() );
    m_dir[ id ] = w;

    const std::size_t idNew = GetEntryId( key );
    if( id != idNew )
    {
        m_dir[ idNew ] = NewBucket( key, data, w->GetLocalDepth() );
        return;
    }

    Put( key, data );



}

//
//
//
Bucket* Directory::NewBucket( std::uint32_t depth )
{
    Bucket* b = new Bucket( depth );
    m_pool.push_back( b );
    return b;
}

//
//
//
Bucket* Directory::NewBucket( const Key& key, const Data& data, std::uint32_t depth )
{
    Bucket* b = new Bucket( key, data, depth );
    m_pool.push_back( b );
    return b;
}
