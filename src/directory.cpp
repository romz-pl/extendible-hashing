#include "directory.h"
#include <iostream>
#include <set>


Directory::Directory( uint32_t depth, uint32_t bucket_size )
{
    this->global_depth = depth;
    this->bucket_size = bucket_size;
    for(int i = 0 ; i < 1<<depth ; i++ )
    {
        buckets.push_back(new Bucket(depth,bucket_size));
    }
}

uint32_t Directory::hash( uint32_t n )
{
    return n&((1<<global_depth)-1);
}

int Directory::pairIndex( uint32_t bucket_no, uint32_t depth )
{
    return bucket_no^(1<<(depth-1));
}

void Directory::grow()
{
    for(int i = 0 ; i < 1<<global_depth ; i++ )
        buckets.push_back(buckets[i]);
    global_depth++;
}

void Directory::shrink()
{
    for( std::size_t i=0 ; i<buckets.size() ; i++ )
    {
        if(buckets[i]->getDepth()==global_depth)
        {
            return;
        }
    }
    global_depth--;
    for( uint32_t i = 0 ; i < 1U << global_depth; i++ )
        buckets.pop_back();
}

void Directory::split( uint32_t bucket_no )
{
    int pair_index,index_diff,dir_size,i;
    std::map< uint32_t, std::string > temp;
    std::map< uint32_t, std::string >::iterator it;

    const uint32_t local_depth = buckets[bucket_no]->increaseDepth();
    if(local_depth>global_depth)
        grow();
    pair_index = pairIndex(bucket_no,local_depth);
    buckets[pair_index] = new Bucket(local_depth,bucket_size);
    temp = buckets[bucket_no]->copy();
    buckets[bucket_no]->clear();
    index_diff = 1<<local_depth;
    dir_size = 1<<global_depth;
    for( i=pair_index-index_diff ; i>=0 ; i-=index_diff )
        buckets[i] = buckets[pair_index];
    for( i=pair_index+index_diff ; i<dir_size ; i+=index_diff )
        buckets[i] = buckets[pair_index];
    for(it=temp.begin();it!=temp.end();it++)
        insert((*it).first,(*it).second,1);
}

void Directory::merge( uint32_t bucket_no )
{
    int pair_index,index_diff,dir_size,i;

    const uint32_t local_depth = buckets[bucket_no]->getDepth();
    pair_index = pairIndex(bucket_no,local_depth);
    index_diff = 1<<local_depth;
    dir_size = 1<<global_depth;

    if( buckets[pair_index]->getDepth() == local_depth )
    {
        buckets[pair_index]->decreaseDepth();
        delete(buckets[bucket_no]);
        buckets[bucket_no] = buckets[pair_index];
        for( i=bucket_no-index_diff ; i>=0 ; i-=index_diff )
            buckets[i] = buckets[pair_index];
        for( i=bucket_no+index_diff ; i<dir_size ; i+=index_diff )
            buckets[i] = buckets[pair_index];
    }
}

std::string Directory::bucket_id( uint32_t n )
{
    int d;
    std::string s;
    d = buckets[n]->getDepth();
    s = "";
    while(n>0 && d>0)
    {
        s = (n%2==0?"0":"1")+s;
        n/=2;
        d--;
    }
    while(d>0)
    {
        s = "0"+s;
        d--;
    }
    return s;
}

void Directory::insert( uint32_t key, std::string value, bool reinserted )
{
    uint32_t bucket_no = hash(key);
    int status = buckets[bucket_no]->insert(key,value);
    if(status==1)
    {
        if(!reinserted)
            std::cout<<"Inserted key "<<key<<" in bucket "<<bucket_id(bucket_no)<<std::endl;
        else
            std::cout<<"Moved key "<<key<<" to bucket "<<bucket_id(bucket_no)<<std::endl;
    }
    else if(status==0)
    {
        split(bucket_no);
        insert(key,value,reinserted);
    }
    else
    {
        std::cout<<"Key "<<key<<" already exists in bucket "<<bucket_id(bucket_no)<<std::endl;
    }
}

void Directory::remove( uint32_t key, int mode )
{
    int bucket_no = hash(key);
    if(buckets[bucket_no]->remove(key))
        std::cout<<"Deleted key "<<key<<" from bucket "<<bucket_id(bucket_no)<<std::endl;
    if(mode>0)
    {
        if(buckets[bucket_no]->isEmpty() && buckets[bucket_no]->getDepth()>1)
            merge(bucket_no);
    }
    if(mode>1)
    {
        shrink();
    }
}

void Directory::update( uint32_t key, std::string value )
{
    int bucket_no = hash(key);
    buckets[bucket_no]->update(key,value);
}

std::string Directory::search( uint32_t key )
{
    int bucket_no = hash(key);
    std::cout<<"Searching key "<<key<<" in bucket "<<bucket_id(bucket_no)<<std::endl;
    return buckets[bucket_no]->search(key);
}

void Directory::display( bool duplicates )
{
    std::string s;
    std::set<std::string> shown;
    std::cout<<"Global depth : "<<global_depth<<std::endl;
    for( std::size_t i=0;i<buckets.size();i++)
    {
        const uint32_t d = buckets[i]->getDepth();
        s = bucket_id(i);
        if(duplicates || shown.find(s)==shown.end())
        {
            shown.insert(s);
            for(uint32_t j = d; j <= global_depth; j++)
                std::cout<<" ";
            std::cout<<s<<" => ";
            buckets[i]->display();
        }
    }
}
