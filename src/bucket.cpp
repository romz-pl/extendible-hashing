#include "bucket.h"
#include <iostream>


Bucket::Bucket( uint32_t depth, uint32_t size )
{
    this->depth = depth;
    this->size = size;
}

int Bucket::insert( uint32_t key, std::string value )
{
    std::map< uint32_t, std::string >::iterator it;
    it = values.find(key);
    if(it!=values.end())
        return -1;
    if(isFull())
        return 0;
    values[key] = value;
    return 1;
}

int Bucket::remove( uint32_t key )
{
    std::map< uint32_t, std::string >::iterator it;
    it = values.find(key);
    if(it!=values.end())
    {
        values.erase(it);
        return 1;
    }
    else
    {
        std::cout<<"Cannot remove : This key does not exists"<<std::endl;
        return 0;
    }
}

int Bucket::update( uint32_t key, std::string value )
{
    std::map< uint32_t, std::string >::iterator it;
    it = values.find(key);
    if(it!=values.end())
    {
        values[key] = value;
        std::cout<<"Value updated"<<std::endl;
        return 1;
    }
    else
    {
        std::cout<<"Cannot update : This key does not exists"<<std::endl;
        return 0;
    }
}

std::string Bucket::search( uint32_t key ) const
{
    const auto it = values.find( key );
    if( it != values.end() )
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
    return ( values.size() == size );
}

bool Bucket::isEmpty() const
{
    return ( values.size() == 0 );
}

uint32_t Bucket::getDepth() const
{
    return depth;
}

uint32_t Bucket::increaseDepth()
{
    depth++;
    return depth;
}

uint32_t Bucket::decreaseDepth()
{
    depth--;
    return depth;
}

std::map< uint32_t, std::string > Bucket::copy() const
{
    return values;
}

void Bucket::clear()
{
    values.clear();
}

void Bucket::display() const
{
    for( const auto& v : values )
        std::cout << v.first << " ";

    std::cout << std::endl;
}
