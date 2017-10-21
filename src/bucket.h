#ifndef HASHEX_BUCKET_H
#define HASHEX_BUCKET_H

#include "data.h"
#include "key.h"
#include <forward_list>

class Bucket
{
public:
    Bucket();
    Bucket( const Key& key, const Data& data );
    ~Bucket() = default;

    Data Get( const Key &key ) const;
    void Put( const Key& key, const Data& data );

    Key GetKey( ) const;

    bool IsFull() const;

private:
    std::uint32_t m_localDepth;

    Key m_key;

    // Here should be:
    // std::optional< Data > m_data;
    std::forward_list< Data > m_data;
};

#endif
