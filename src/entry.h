#ifndef HASHEX_ENTRY_H
#define HASHEX_ENTRY_H

#include "key.h"
#include "bucket.h"

class Entry
{
public:
    Entry() = default;
    ~Entry() = default;

private:
    Key m_key;

    Bucket m_bucket;
};


#endif
