#include "data.h"

//
//
//
Data::Data()
{

}

//
//
//
Data::Data( const std::string& v )
    : m_data( v )
{

}

//
//
//
bool Data::operator==( const Data& v ) const
{
    return m_data == v.m_data;
}

//
//
//
bool Data::operator<( const Data& v ) const
{
    return m_data < v.m_data;
}

//
//
//
bool Data::operator!=( const Data& v ) const
{
    return !( *this == v );
}

//
//
//
bool Data::operator<=( const Data& v ) const
{
   return !( v < *this );
}

//
//
//
bool Data::operator>( const Data& v ) const
{
    return ( v < *this );
}

//
//
//
bool Data::operator>=( const Data& v ) const
{
    return !( *this < v );
} 

//
//
//
std::string Data::ToString() const
{
    return m_data;
}
