#ifndef HASHEX_HASHEX_H
#define HASHEX_HASHEX_H


#include "data.h"
#include "key.h"
#include "directory.h"

class HashEx
{
public:
    HashEx();
    ~HashEx() = default;

    Data Get( const Key& key ) const;
    void Put( const Key& key, const Data& data );
    void Delete( const Key& key );

private:
    Directory m_dir;

};


#endif
