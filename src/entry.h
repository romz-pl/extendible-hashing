#ifndef HASHEX_ENTRY_H
#define HASHEX_ENTRY_H

#include "key.h"
#include "bucket.h"
#include "data.h"

class Entry
{
public:
    Entry();
    ~Entry() = default;

    Data Get( const Key& key ) const;

private:
    Key m_key;

    Bucket *m_bucket;
};


#endif
