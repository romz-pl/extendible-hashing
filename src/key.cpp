#include "key.h"


//
//
//
std::uint32_t Key::GetHash() const
{
    return m_value;
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
