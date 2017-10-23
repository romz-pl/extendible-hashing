#ifndef HASHEX_DIRECTORY_H
#define HASHEX_DIRECTORY_H

#include <vector>
#include "bucket.h"

class Directory
{
public:
    Directory( uint32_t depth, uint32_t bucket_size );
    void insert( const Key& key, std::string value, bool reinserted );
    void remove( const Key &key, int mode );
    void update( const Key& key, std::string value );
    std::string search( const Key &key ) const;
    void display( bool duplicates ) const;
    size_t count() const;

private:
    static uint32_t pairIndex( uint32_t bucket_no, uint32_t depth );

    uint32_t hash( const Key &key ) const;
    void grow();
    void shrink();
    void split( uint32_t bucket_no );
    void merge( uint32_t bucket_no );
    std::string bucket_id( uint32_t n ) const;


private:
    uint32_t m_global_depth;
    const uint32_t m_bucket_size;
    std::vector< Bucket* > m_buckets;
    size_t m_count;


};

#endif
