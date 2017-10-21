#ifndef HASHEX_DIRECTORY_H
#define HASHEX_DIRECTORY_H

#include <vector>
#include "bucket.h"

class Directory
{
public:
    Directory( uint32_t depth, uint32_t bucket_size );
    void insert( uint32_t key, std::string value, bool reinserted );
    void remove( uint32_t key, int mode );
    void update( uint32_t key, std::string value );
    std::string search( uint32_t key );
    void display( bool duplicates );

private:
    uint32_t global_depth;
    uint32_t bucket_size;
    std::vector< Bucket* > buckets;
    uint32_t hash( uint32_t n );
    int pairIndex( uint32_t bucket_no, uint32_t depth );
    void grow();
    void shrink();
    void split( uint32_t bucket_no );
    void merge( uint32_t bucket_no );
    std::string bucket_id( uint32_t n );

};

#endif
