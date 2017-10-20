#ifndef HASHEX_KEY_H
#define HASHEX_KEY_H

#include <cstdint>

class Key
{
public:
    Key() = default;
    ~Key() = default;

private:
    std::uint32_t m_key;
};

#endif
