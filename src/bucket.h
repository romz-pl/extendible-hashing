#ifndef HASHEX_BUCKET_H
#define HASHEX_BUCKET_H

#include "data.h"

class Bucket
{
public:
    Bucket();
    ~Bucket() = default;

    Data Get( ) const;

private:
    std::uint32_t m_localDepth;

    Data m_data;
};

#endif
