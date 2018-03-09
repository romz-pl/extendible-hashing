#ifndef HASHEX_DIRECTORY_H
#define HASHEX_DIRECTORY_H

#include <vector>
#include "bucket.h"

class Directory
{
public:
    Directory( uint32_t depth, uint32_t max_bucket_size );
    ~Directory();

    Directory( const Directory & ) = delete;
    Directory& operator=( const Directory & ) = delete;

    Directory( Directory && ) = delete;
    Directory& operator=( Directory && ) = delete;


    void insert( const Key& key, const Data& value, bool reinserted );
    void remove( const Key &key, int mode );
    void update( const Key& key, const Data& value );
    Data search( const Key &key ) const;
    void display( bool duplicates ) const;
    size_t count() const;

private:
    static uint32_t get_pair_index( uint32_t idx, uint32_t depth );

    uint32_t get_index( const Key &key ) const;
    void grow();
    void shrink();
    void split( uint32_t idx );
    void merge( uint32_t idx );
    std::string bucket_id( uint32_t n ) const;

    void assign_to_siblings( uint32_t idx, Bucket* bp );

private:
    uint32_t m_global_depth;
    const uint32_t m_max_bucket_size;
    std::vector< Bucket* > m_bucket;
    size_t m_count;


};

#endif
