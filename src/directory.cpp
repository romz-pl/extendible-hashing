#include "directory.h"
#include <cassert>
#include <stdexcept>

//
//
//
Directory::Directory()
    : m_globalDepth( 0 )
{

}

//
//
//
Data Directory::Get( const Key& key ) const
{
    if( m_dir.size() == 0 )
    {
        throw std::runtime_error( "The Key not found. The directory is empty." );
    }

    const std::size_t id = GetEntryId( key );
    const Bucket* b = m_dir[ id ];
    if( !b )
    {
        throw std::runtime_error( "The Key not found. Empty bucket." );
    }
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
