#include "bucket.h"
#include <iostream>
#include <sstream>
#include <cassert>


Bucket::Bucket( uint32_t depth, uint32_t size )
    : m_depth( depth )
    , m_size( size )
{

}

void Bucket::insert( uint32_t key, std::string value )
{
    assert( m_values.find( key ) == m_values.end() );
    assert( !isFull() );

    m_values[ key ] = value;
}

void Bucket::remove( uint32_t key )
{
    const auto it = m_values.find( key );
    if( it != m_values.end() )
    {
        m_values.erase( it );
    }
    else
    {
        std::stringstream buffer;
        buffer << "Cannot remove. Key '" << key << "' does not exists.";
        throw std::runtime_error( buffer.str() );
    }
}

int Bucket::update( uint32_t key, std::string value )
{
    const auto it = m_values.find( key );
    if( it != m_values.end() )
    {
        m_values[ key ] = value;
        std::cout << "Value updated" << std::endl;
        return 1;
    }
    else
    {
        std::cout << "Cannot update : This key does not exists" << std::endl;
        return 0;
    }
}

std::string Bucket::search( uint32_t key ) const
{
    const auto it = m_values.find( key );
    if( it != m_values.end() )
    {
        std::cout << "Value = " << it->second << std::endl;
        return it->second;
    }
    else
    {
        throw std::runtime_error( "This key does not exists" );
    }
}

bool Bucket::isFull() const
{
    return ( m_values.size() == m_size );
}

bool Bucket::isEmpty() const
{
    return m_values.empty();
}

uint32_t Bucket::getDepth() const
{
    return m_depth;
}

uint32_t Bucket::increaseDepth()
{
    m_depth++;
    return m_depth;
}

uint32_t Bucket::decreaseDepth()
{
    m_depth--;
    return m_depth;
}

std::map< uint32_t, std::string > Bucket::copy() const
{
    return m_values;
}

void Bucket::clear()
{
    m_values.clear();
}

void Bucket::display() const
{
    for( const auto& v : m_values )
        std::cout << v.first << " ";

    std::cout << std::endl;
}

bool Bucket::hasKey( uint32_t key ) const
{
    return ( m_values.find( key ) != m_values.end() );
}
