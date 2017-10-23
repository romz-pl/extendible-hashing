#ifndef HASHEX_BUCKET_H
#define HASHEX_BUCKET_H

#include <map>
#include <string>
#include <cstdint>
#include "key.h"

class Bucket
{
public:
    Bucket( uint32_t depth, uint32_t size );
    void insert( const Key& key, std::string value );
    void remove( const Key& key );
    void update( const Key& key, std::string value );
    std::string search( const Key &key ) const;
    bool isFull() const;
    bool isEmpty() const;
    uint32_t getDepth() const;
    uint32_t increaseDepth();
    uint32_t decreaseDepth();
    std::map< Key, std::string> copy() const;
    void clear();
    void display() const;
    bool hasKey( const Key& key ) const;

private:
    uint32_t m_depth;
    const uint32_t m_maxAllowedSize;
    std::map< Key, std::string > m_values;

};



#endif
