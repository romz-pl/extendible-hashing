#ifndef HASHEX_DATA_H
#define HASHEX_DATA_H

#include <string>

class Data
{
public:
    Data();
    explicit Data( const std::string& v );
    ~Data() = default;

    bool operator == ( const Data& v ) const;
    bool operator != ( const Data& v ) const;

    std::string ToString() const;

private:
    std::string m_data;
};


#endif

