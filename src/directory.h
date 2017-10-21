#ifndef HASHEX_DIRECTORY_H
#define HASHEX_DIRECTORY_H

#include <vector>
#include "bucket.h"

class Directory
{
public:
    Directory(int depth, int bucket_size);
    void insert(int key,std::string value,bool reinserted);
    void remove(int key,int mode);
    void update(int key, std::string value);
    void search(int key);
    void display(bool duplicates);

private:
    int global_depth, bucket_size;
    std::vector<Bucket*> buckets;
    int hash(int n);
    int pairIndex(int bucket_no, int depth);
    void grow(void);
    void shrink(void);
    void split(int bucket_no);
    void merge(int bucket_no);
    std::string bucket_id(int n);

};

#endif
