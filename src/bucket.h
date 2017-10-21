#ifndef HASHEX_BUCKET_H
#define HASHEX_BUCKET_H

#include "data.h"
#include "key.h"

class Bucket
{
public:
    Bucket( std::uint32_t localDepth );
    Bucket( const Key& key, const Data& data, std::uint32_t localDepth );
    ~Bucket() = default;

    Data Get( const Key &key ) const;
    void Put( const Key& key, const Data& data );

    Key GetKey( ) const;

    bool IsFull() const;

    std::uint32_t GetLocalDepth() const;
    void IncLocalDepth();

    void SetEmpty();

    void Print() const;

private:
    bool m_empty;

    std::uint32_t m_localDepth;

    Key m_key;

    Data m_data;
};

#endif
