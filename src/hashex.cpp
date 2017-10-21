#include "hashex.h"
#include <cassert>

//
//
//
HashEx::HashEx( int depth, int bucket_size )
    : m_dir( depth, bucket_size )
{

}

//
//
//
Data HashEx::Get( const Key& /*key*/ ) const
{
    return Data();
    // return m_dir.search( key );
}

//
//
//
void HashEx::Put( const Key& /*key*/, const Data& /*data*/ )
{
    // m_dir.insert( key.m, data, false );
}

//
//
//
void HashEx::Delete( const Key& /*key*/ )
{
    // m_dir.remove( key, 2 );
}

//
//
//
void HashEx::Print() const
{
    // m_dir.display( true );
}
