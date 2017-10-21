#ifndef HASHEX_DATA_H
#define HASHEX_DATA_H

#include <string>

class Data
{
public:
    Data();
    Data( const std::string& v );
    ~Data() = default;

private:
    std::string m_data;
};


#endif

