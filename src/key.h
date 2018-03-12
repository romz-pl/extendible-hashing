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
#include <vector>

class Key
{
public:
    explicit Key( uint32_t value );
    Key( const void* buf, uint32_t count );
    ~Key() = default;

    Key( const Key & ) = default;
    Key& operator=( const Key & ) = default;

    Key( Key && ) = default;
    Key& operator=( Key && ) = default;

    uint32_t get_hash() const;

    bool operator==( const Key& key ) const;
    bool operator!=( const Key& key ) const;

    bool operator< ( const Key& key ) const;
    bool operator<=( const Key& key ) const;
    bool operator> ( const Key& key ) const;
    bool operator>=( const Key& key ) const; 

    std::string to_string() const;

private:
    std::vector< uint8_t > m_blob;
};

#endif
