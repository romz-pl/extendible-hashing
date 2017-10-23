#include "bucket.h"
#include <iostream>
#include <sstream>
#include <cassert>

//
//
//
Bucket::Bucket( uint32_t depth, uint32_t size )
    : m_depth( depth )
    , m_maxAllowedSize( size )
{
    if( size < 1 )
    {
        throw std::runtime_error( "The maximum allowed size of bucket must be at least one." );
    }
}

//
//
//
void Bucket::insert(const Key& key, const Data &value )
{
    assert( m_values.find( key ) == m_values.end() );
    assert( !isFull() );

    m_values[ key ] = value;
}

//
//
//
void Bucket::remove( const Key& key )
{
    const auto it = m_values.find( key );
    if( it == m_values.end() )
    {
        std::stringstream buffer;
        buffer << "Cannot remove. Key '" << key.ToString() << "' does not exists.";
        throw std::runtime_error( buffer.str() );
    }

    m_values.erase( it );
}

//
//
//
void Bucket::update(const Key &key, const Data &value )
{
    const auto it = m_values.find( key );
    if( it == m_values.end() )
    {
        std::stringstream buffer;
        buffer << "Cannot update. Key '" << key.ToString() << "' does not exists.";
        throw std::runtime_error( buffer.str() );
    }

    m_values[ key ] = value;
}

//
//
//
Data Bucket::search( const Key& key ) const
{
    const auto it = m_values.find( key );
    if( it == m_values.end() )
    {
        std::stringstream buffer;
        buffer << "Not found. Key '" << key.ToString() << "' does not exists.";
        throw std::runtime_error( buffer.str() );
    }

    return it->second;
}

//
//
//
bool Bucket::isFull() const
{
    return ( m_values.size() == m_maxAllowedSize );
}

//
//
//
bool Bucket::isEmpty() const
{
    return m_values.empty();
}

//
//
//
uint32_t Bucket::getDepth() const
{
    return m_depth;
}

//
//
//
uint32_t Bucket::increaseDepth()
{
    m_depth++;
    return m_depth;
}

//
//
//
uint32_t Bucket::decreaseDepth()
{
    m_depth--;
    return m_depth;
}

//
//
//
std::map< Key, Data > Bucket::copy() const
{
    return m_values;
}

//
//
//
void Bucket::clear()
{
    m_values.clear();
}

//
//
//
void Bucket::display() const
{
    for( const auto& v : m_values )
        std::cout << v.first.ToString() << " ";

    std::cout << std::endl;
}

//
//
//
bool Bucket::hasKey( const Key &key ) const
{
    return ( m_values.find( key ) != m_values.end() );
}
