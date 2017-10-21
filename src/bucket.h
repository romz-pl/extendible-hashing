#ifndef HASHEX_BUCKET_H
#define HASHEX_BUCKET_H

#include <map>
#include <string>

class Bucket
{
        int depth,size;
        std::map<int, std::string> values;
    public:
        Bucket(int depth, int size);
        int insert(int key, std::string value);
        int remove(int key);
        int update(int key, std::string value);
        void search(int key);
        int isFull(void);
        int isEmpty(void);
        int getDepth(void);
        int increaseDepth(void);
        int decreaseDepth(void);
        std::map<int, std::string> copy(void);
        void clear(void);
        void display(void);
};



#endif
