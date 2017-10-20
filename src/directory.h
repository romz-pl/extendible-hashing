#ifndef HASHEX_DIRECTORY_H
#define HASHEX_DIRECTORY_H

#include "bucket.h"
#include <vector>

class Directory
{
public:
    Directory() = default;
    ~Directory() = default;

private:
    std::vector< Bucket* > m_dir;

};

#endif
