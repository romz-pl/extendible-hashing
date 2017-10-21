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
        b = new Bucket();

}

//
//
//
Directory::~Directory()
{
    for( auto b : m_dir )
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

    if( m_dir[ id ]->GetKey() == key )
    {
        throw std::runtime_error( "Key already inserted" );
    }

    if( !m_dir[ id ]->IsFull() )
    {
        m_dir[ id ]->Put( key, data );
        return;

    }

    // Split the Bucket or double the directory

    Bucket* p = m_dir[ id ];
    m_dir[ id ] = nullptr;

    m_globalDepth++;
    const std::vector< Bucket* > tmp = m_dir;
    m_dir.insert( m_dir.end(), tmp.begin(), tmp.end() );
    id = GetEntryId( p->GetKey() );
    m_dir[ id ] = p;

    Put( key, data );



}
