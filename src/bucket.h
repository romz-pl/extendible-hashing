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
    int remove( uint32_t key );
    int update( uint32_t key, std::string value );
    std::string search( uint32_t key );
    int isFull();
    int isEmpty();
    uint32_t getDepth();
    uint32_t increaseDepth();
    uint32_t decreaseDepth();
    std::map< uint32_t, std::string > copy();
    void clear();
    void display();

private:
    uint32_t depth;
    uint32_t size;
    std::map< uint32_t, std::string > values;

};



#endif
