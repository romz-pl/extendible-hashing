#ifndef HASHEX_BUCKET_H
#define HASHEX_BUCKET_H

#include <map>
#include <string>
#include <cstdint>
#include "key.h"
#include "data.h"

class Bucket
{
public:
    Bucket( uint32_t depth, uint32_t maxAllowedSize );
    ~Bucket() = default;

    Bucket( const Bucket & ) = default;
    Bucket& operator=( const Bucket & ) = default;

    Bucket( Bucket && ) = default;
    Bucket& operator=( Bucket && ) = default;


    void insert( const Key& key, const Data& value );
    void remove( const Key& key );
    void update( const Key& key, const Data& value );
    Data search( const Key &key ) const;
    bool is_full() const;
    bool is_empty() const;
    uint32_t get_depth() const;
    uint32_t increase_depth();
    uint32_t decrease_depth();
    std::map< Key, Data > copy() const;
    void clear();
    void display() const;
    bool hasKey( const Key& key ) const;

    uint32_t get_index_diff() const;
    uint32_t get_pair_index( uint32_t idx ) const;

    std::string get_id_as_string( uint32_t n ) const;

private:
    uint32_t m_depth;
    const uint32_t m_maxAllowedSize;
    std::map< Key, Data > m_values;

};



#endif
