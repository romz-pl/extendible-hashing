#ifndef HASHEX_KEY_H
#define HASHEX_KEY_H

#include <cstdint>

class Key
{
public:
    Key() = default;
    ~Key() = default;

    std::uint32_t GetHash() const;

    bool operator== (const Key& key ) const;
    bool operator< (const Key& key ) const;

private:
    std::uint32_t m_value;
};

#endif
