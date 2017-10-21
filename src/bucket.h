#ifndef HASHEX_BUCKET_H
#define HASHEX_BUCKET_H

#include <map>
#include <string>
#include <cstdint>

class Bucket
{
public:
    Bucket( uint32_t depth, uint32_t size );
    int insert( uint32_t key, std::string value );
    void remove( uint32_t key );
    int update( uint32_t key, std::string value );
    std::string search( uint32_t key ) const;
    bool isFull() const;
    bool isEmpty() const;
    uint32_t getDepth() const;
    uint32_t increaseDepth();
    uint32_t decreaseDepth();
    std::map< uint32_t, std::string > copy() const;
    void clear();
    void display() const;

private:
    uint32_t m_depth;
    const uint32_t m_size;
    std::map< uint32_t, std::string > m_values;

};



#endif
