#ifndef HASHEX_BUCKET_H
#define HASHEX_BUCKET_H

#include <map>
#include <string>

class Bucket
{
public:
    Bucket( int depth, int size );
    int insert( int key, std::string value );
    int remove( int key );
    int update( int key, std::string value );
    void search( int key );
    int isFull();
    int isEmpty();
    int getDepth();
    int increaseDepth();
    int decreaseDepth();
    std::map< int, std::string > copy();
    void clear();
    void display();

private:
    int depth;
    int size;
    std::map< int, std::string > values;

};



#endif
