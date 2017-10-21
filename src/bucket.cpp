#include "bucket.h"
#include <iostream>

/* Bucket class functions */

Bucket::Bucket(int depth, int size)
{
    this->depth = depth;
    this->size = size;
}

int Bucket::insert(int key, string value)
{
    std::map<int,string>::iterator it;
    it = values.find(key);
    if(it!=values.end())
        return -1;
    if(isFull())
        return 0;
    values[key] = value;
    return 1;
}

int Bucket::remove(int key)
{
    std::map<int,string>::iterator it;
    it = values.find(key);
    if(it!=values.end())
    {
        values.erase(it);
        return 1;
    }
    else
    {
        cout<<"Cannot remove : This key does not exists"<<endl;
        return 0;
    }
}

int Bucket::update(int key, string value)
{
    std::map<int,string>::iterator it;
    it = values.find(key);
    if(it!=values.end())
    {
        values[key] = value;
        cout<<"Value updated"<<endl;
        return 1;
    }
    else
    {
        cout<<"Cannot update : This key does not exists"<<endl;
        return 0;
    }
}

void Bucket::search(int key)
{
    std::map<int,string>::iterator it;
    it = values.find(key);
    if(it!=values.end())
    {
        cout<<"Value = "<<it->second<<endl;
    }
    else
    {
        cout<<"This key does not exists"<<endl;
    }
}

int Bucket::isFull(void)
{
    if(values.size()==size)
        return 1;
    else
        return 0;
}

int Bucket::isEmpty(void)
{
    if(values.size()==0)
        return 1;
    else
        return 0;
}

int Bucket::getDepth(void)
{
    return depth;
}

int Bucket::increaseDepth(void)
{
    depth++;
    return depth;
}

int Bucket::decreaseDepth(void)
{
    depth--;
    return depth;
}

std::map<int, string> Bucket::copy(void)
{
    std::map<int, string> temp(values.begin(),values.end());
    return temp;
}

void Bucket::clear(void)
{
    values.clear();
}

void Bucket::display()
{
    std::map<int,string>::iterator it;
    for(it=values.begin();it!=values.end();it++)
        cout<<it->first<<" ";
    cout<<endl;
}
