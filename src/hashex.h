#ifndef HASHEX_HASHEX_H
#define HASHEX_HASHEX_H

#include <string>

using Data = std::string;

#include "key.h"

class HashEx
{
public:
    HashEx() = default;
    ~HashEx() = default;

    Data Get( const Key& key ) const;
    void Put( const Key& key, const Data& data );
    void Delete( const Key& key );

};


#endif
