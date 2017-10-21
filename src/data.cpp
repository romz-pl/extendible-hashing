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
bool Data::operator == ( const Data& v ) const
{
    return m_data == v.m_data;
}
