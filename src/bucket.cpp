#include "bucket.h"
#include <iostream>
#include <sstream>
#include <cassert>

//
//
//
Bucket::Bucket( uint32_t depth, uint32_t maxAllowedSize )
    : m_depth( depth )
    , m_maxAllowedSize( std::max( maxAllowedSize, 1U ) )
{

}

//
//
//
void Bucket::insert( const Key& key, const Data &value )
{
    if( m_values.find( key ) != m_values.end() )
    {
        std::stringstream buffer;
        buffer << "Cannot insert. Key '" << key.ToString() << "' already exists.";
        throw std::runtime_error( buffer.str() );    
    }

    if( isFull() )
    {
        throw std::runtime_error( "Cannot insert key into the bucket. The bucket is full." );
    }

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
void Bucket::update( const Key &key, const Data &value )
{
    const auto it = m_values.find( key );
    if( it == m_values.end() )
    {
        std::stringstream buffer;
        buffer << "Cannot update. Key '" << key.ToString() << "' does not exist.";
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
    if( m_depth == 0 )
    {
        throw std::runtime_error( "Cannot decrease the bucket's depth. The depth is zero." );
    }
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
    std::string txt;
    for( const auto& v : m_values )
    {
        txt = "(" + v.first.ToString() + ";" + v.second.ToString() + ")";
        std::cout << txt << " ";
    }

    std::cout << std::endl;
}

//
//
//
bool Bucket::hasKey( const Key &key ) const
{
    return ( m_values.find( key ) != m_values.end() );
}

//
// Returns the size of directory when the Bucket was inserted into the directry.
// This value is equal the distance between siblings into the directory, hence the name.
//
uint32_t Bucket::get_index_diff() const
{
    return ( 1U << m_depth );
}

