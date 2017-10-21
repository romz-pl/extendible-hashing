#ifndef HASHEX_KEY_H
#define HASHEX_KEY_H

#include <cstdint>

class Key
{
public:
    Key();
    Key( uint32_t value );
    ~Key() = default;

    std::size_t GetHash() const;

    bool operator== (const Key& key ) const;
    bool operator!= (const Key& key ) const;

    // bool operator< (const Key& key ) const;

private:
    static std::uint64_t Hash64( std::uint64_t x );

public:
//private:
    uint32_t m_value;
};

#endif
