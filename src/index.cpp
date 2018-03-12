#include "index.h"
#include "key.h"

//
// Returns index of key in the hash table, when the depth of hash table is "depth".
//  
uint32_t Index::get( const Key& key, uint32_t depth )
{
    const uint32_t hash = key.GetHash();
    const uint32_t mask = get_mask( depth );
    return ( hash & mask );
}

//
// Returns depth number of 1 on the lest significant bits
//
uint32_t Index::get_mask( uint32_t depth )
{
    const uint32_t zero = 0;
    
    return ~(  ~zero << depth );
}


