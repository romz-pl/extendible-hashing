#include "directory.h"
#include <cassert>

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
    std::size_t id = GetEntryId( key );
    return m_dir[ id ].Get( key );
}

//
//
//
std::size_t Directory::GetEntryId( const Key& key ) const
{
    std::uint32_t mask = 0;
    for( std::uint32_t i = 0; i < m_globalDepth; i++ )
        mask |= ( 1 << i );

    std::uint32_t hv = key.GetHash();

    std::size_t ret = hv & mask;
    assert( ret < m_dir.size() );
    return ret;
}
