#include "key.h"
#include <functional>

Key::Key( std::uint32_t value )
    : m_value( value )
{

}

//
//
//
std::size_t Key::GetHash() const
{
    const std::hash< std::uint32_t > fun;
    const std::size_t ret = fun( m_value );
    return ret;
}

//
//
//
bool Key::operator== (const Key& key ) const
{
    return m_value == key.m_value;
}

//
//
//
bool Key::operator< (const Key& key ) const
{
    return m_value < key.m_value;
}
