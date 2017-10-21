#include "bucket.h"
#include <stdexcept>

//
//
//
Bucket::Bucket()
    : m_localDepth( 0 )
{

}

//
//
//
Bucket::Bucket( const Key& key, const Data& data )
    : m_localDepth( 0 )
    , m_key( key )
{
    m_data.push_front( data );
}


//
//
//
Data Bucket::Get( const Key& key ) const
{
    if( m_data.empty() )
    {
        throw std::runtime_error( "Bucket::Get: Empty bucket." );
    }

    if( key != m_key )
    {
        throw std::runtime_error( "Bucket::Get: Key not found." );
    }
    return m_data.front();
}

//
//
//
Key Bucket::GetKey( ) const
{
    return m_key;
}
