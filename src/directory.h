#ifndef HASHEX_DIRECTORY_H
#define HASHEX_DIRECTORY_H

#include "entry.h"
#include <vector>
#include "data.h"

class Directory
{
public:
    Directory();
    ~Directory() = default;

    Data Get( const Key& key ) const;

private:
    std::size_t GetEntryId( const Key &key ) const;

private:
    std::uint32_t m_globalDepth;

    std::vector< Entry > m_dir;

};

#endif
