#include "hashex.h"
#include <cassert>

//
//
//
HashEx::HashEx()
    : m_globalDepth( 0 )
{

}

//
//
//
Data HashEx::Get( const Key& /*key*/ ) const
{
    assert( 0 );
    return Data();
}

//
//
//
void HashEx::Put( const Key& /*key*/, const Data& /*data*/ )
{
    assert( 0 );
}

//
//
//
void HashEx::Delete( const Key& /*key*/ )
{
    assert( 0 );
}
