#ifndef HASHEX_BUCKET_H
#define HASHEX_BUCKET_H

#include "data.h"
#include "key.h"

class Bucket
{
public:
    Bucket( const Key& key, const Data& data );
    ~Bucket() = default;

    Data Get( const Key &key ) const;

    Key GetKey( ) const;

private:
    std::uint32_t m_localDepth;

    Key m_key;

    Data m_data;
};

#endif
