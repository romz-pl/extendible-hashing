#include "key.h"


//
//
//
Key::Key( uint32_t value )
    : m_value( value )
{

}

//
//
//
std::size_t Key::GetHash() const
{
    // return Hash64( m_value );
    return Hash32( m_value );
}

//
//
//
uint32_t Key::Hash32( uint32_t x )
{
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    return x;
}

//
//
//
uint64_t Key::Hash64( uint64_t x )
{
    x = (x ^ (x >> 30)) * UINT64_C(0xbf58476d1ce4e5b9);
    x = (x ^ (x >> 27)) * UINT64_C(0x94d049bb133111eb);
    x = x ^ (x >> 31);
    return x;
}

//
//
//
bool Key::operator==( const Key& key ) const
{
    return m_value == key.m_value;
}

//
//
//
bool Key::operator!=( const Key& key ) const
{
    return !( m_value == key.m_value );
}


//
//
//
bool Key::operator<( const Key& key ) const
{
    return m_value < key.m_value;
}

//
//
//
std::string Key::ToString() const
{
    return std::to_string( m_value );
}

