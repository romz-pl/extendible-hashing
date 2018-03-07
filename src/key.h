#ifndef HASHEX_KEY_H
#define HASHEX_KEY_H

//
// 1. This represents key in hash table.
//
// 2. Current implemenation is specific for type "uint32_t".
//
// 3. If you want other type, just change "uint32_t" to your required type T,
//    and make sure the compariosion operator are available for type T.
//

#include <cstdint>
#include <string>

class Key
{
public:
    explicit Key( uint32_t value );
    ~Key() = default;

    Key( const Key & ) = default;
    Key& operator=( const Key & ) = default;

    uint32_t GetHash() const;

    bool operator==( const Key& key ) const;
    bool operator!=( const Key& key ) const;

    bool operator< ( const Key& key ) const;
    bool operator<=( const Key& key ) const;
    bool operator> ( const Key& key ) const;
    bool operator>=( const Key& key ) const; 

    std::string ToString() const;

private:
//    static uint64_t Hash64( uint64_t x );
    static uint32_t Hash32( uint32_t x );

private:
    uint32_t m_value;
};

#endif
