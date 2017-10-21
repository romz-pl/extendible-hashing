#ifndef HASHEX_DIRECTORY_H
#define HASHEX_DIRECTORY_H

#include "bucket.h"
#include <vector>
#include "data.h"

class Directory
{
public:
    Directory();
    ~Directory();

    Data Get( const Key& key ) const;
    void Put( const Key& key, const Data& data );

    void Print() const;

private:
    std::size_t GetEntryId( const Key &key ) const;

    Bucket* NewBucket( std::uint32_t depth );
    Bucket* NewBucket( const Key& key, const Data& data, std::uint32_t depth );

private:
    std::uint32_t m_globalDepth;

    std::vector< Bucket* > m_dir;

    std::vector< Bucket* > m_pool;

};

#endif
