#include "bucket.h"
#include <stdexcept>
#include <cassert>
#include <iostream>

//
//
//
Bucket::Bucket( uint32_t localDepth )
    : m_empty( true )
    , m_localDepth( localDepth )
{

}

//
//
//
Bucket::Bucket( const Key& key, const Data& data, uint32_t localDepth )
    : m_empty( false )
    , m_localDepth( localDepth )
    , m_key( key )
{
    m_data = data;
}


//
//
//
Data Bucket::Get( const Key& key ) const
{
    if( m_empty )
    {
        throw std::runtime_error( "Bucket::Get: Empty bucket." );
    }

    if( key != m_key )
    {
        throw std::runtime_error( "Bucket::Get: Key not found." );
    }
    return m_data;
}

//
//
//
Key Bucket::GetKey( ) const
{
    assert( !m_empty );
    return m_key;
}

//
//
//
Data Bucket::GetData( ) const
{
    assert( !m_empty );
    return m_data;
}

//
//
//
bool Bucket::IsFull() const
{
    return !m_empty;
}

//
//
//
void Bucket::Put( const Key& key, const Data& data )
{
    assert( m_empty );

    m_key = key;
    m_data = data;
    m_empty = false;
}

//
//
//
std::uint32_t Bucket::GetLocalDepth() const
{
    return m_localDepth;
}

//
//
//
void Bucket::SetLocalDepth( std::uint32_t depth )
{
    m_localDepth = depth;
}

//
//
//
void Bucket::SetEmpty()
{
    m_empty = true;
}

//
//
//
void Bucket::Print() const
{
    std::cout << std::boolalpha << m_empty << "; ";
    std::cout << "Local-Depth=" << m_localDepth << "; ";
    std::cout << "Key=" << m_key.m_value << "; ";
    std::cout << std::flush << std::endl;
}
