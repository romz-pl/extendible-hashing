#ifndef HASHEX_KEY_H
#define HASHEX_KEY_H

#include <cstdint>
#include <string>

class Key
{
public:
    explicit Key( uint32_t value );
    ~Key() = default;

    std::size_t GetHash() const;

    bool operator==( const Key& key ) const;
    bool operator!=( const Key& key ) const;

    bool operator<( const Key& key ) const;

    std::string ToString() const;

private:
    static uint64_t Hash64( uint64_t x );
    static uint32_t Hash32( uint32_t x );

private:
    uint32_t m_value;
};

#endif
