#ifndef HASHEX_INDEX_H
#define HASHEX_INDEX_H

#include <cstdint>

class Key;


class Index
{
public:
    static uint32_t get( const Key& key, uint32_t depth );

private:
    static uint32_t get_mask( uint32_t depth );
};


#endif

