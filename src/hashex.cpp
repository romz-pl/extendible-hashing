#include "hashex.h"
#include <cassert>

//
//
//
HashEx::HashEx( uint32_t depth, uint32_t bucket_size )
    : m_dir( depth, bucket_size )
{

}

//
//
//
Data HashEx::Get( const Key& key ) const
{
    return m_dir.search( key );
}

//
//
//
void HashEx::Put( const Key& key, const Data& data )
{
    m_dir.insert( key, data, false );
}

//
//
//
void HashEx::Delete( const Key& key )
{
    m_dir.remove( key, 2 );
}

//
//
//
void HashEx::Print() const
{
    m_dir.display( true );
}

//
//
//
size_t HashEx::Count() const
{
    return m_dir.count();
}
