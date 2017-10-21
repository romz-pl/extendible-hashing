#include "hashex.h"
#include <cassert>

//
//
//
HashEx::HashEx()
{

}

//
//
//
Data HashEx::Get( const Key& key ) const
{
    return m_dir.Get( key );
}

//
//
//
void HashEx::Put( const Key& key, const Data& data )
{
    m_dir.Put( key, data );
}

//
//
//
void HashEx::Delete( const Key& /*key*/ )
{
    assert( 0 );
}

//
//
//
void HashEx::Print() const
{
    m_dir.Print();
}
