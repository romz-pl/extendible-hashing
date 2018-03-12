#include <cstring>
#include "key.h"


//
//
//
Key::Key( uint32_t value ) :
    Key( &value, sizeof( value ) )
{

}

//
// count - number of bytes to copy
//
Key::Key( const void* buf, uint32_t count )
{
    m_blob.resize( count );

    std::memcpy( m_blob.data(), buf, count );
}

//
// jenkins_one_at_a_time_hash
//
uint32_t Key::get_hash() const
{
    size_t i = 0;
    uint32_t hash = 0;
    while( i != m_blob.size() )
    {
        hash += m_blob[ i++ ];
        hash += hash << 10;
        hash ^= hash >> 6;
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;

    return hash;
}

//
//
//
bool Key::operator==( const Key& key ) const
{
//    return ( m_blob.size() == key.m_blob.size() &&
//             std::memcmp( m_blob.data(), key.m_blob.data(), m_blob.size() ) == 0 );

    return get_hash() == key.get_hash();
}

//
//
//
bool Key::operator<( const Key& key ) const
{
/*
    const size_t s = std::min( m_blob.size(), key.m_blob.size() );
    const int ret = std::memcmp( m_blob.data(), key.m_blob.data(), s );

    if( ret < 0 )
        return true;

    if( ret > 0 )
        return false;

    return ( m_blob.size() < key.m_blob.size() ); */

    return get_hash() < key.get_hash();
}

//
//
//
bool Key::operator!=( const Key& key ) const
{
    return !( *this == key );
}

//
//
//
bool Key::operator<=( const Key& key ) const
{
   return !( key < *this );
}

//
//
//
bool Key::operator>( const Key& key ) const
{
    return ( key < *this );
}

//
//
//
bool Key::operator>=( const Key& key ) const
{
    return !( *this < key );
} 

//
//
//
std::string Key::to_string() const
{
    return std::to_string( get_hash() );
}

