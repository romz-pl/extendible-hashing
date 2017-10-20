#ifndef HASHEX_DIRECTORY_H
#define HASHEX_DIRECTORY_H

#include "entry.h"
#include <vector>

class Directory
{
public:
    Directory() = default;
    ~Directory() = default;

private:
    std::vector< Entry > m_dir;

};

#endif
