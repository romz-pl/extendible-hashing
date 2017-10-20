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

private:
    std::size_t GetEntryId( const Key &key ) const;

private:
    std::uint32_t m_globalDepth;

    std::vector< Bucket* > m_dir;

};

#endif
