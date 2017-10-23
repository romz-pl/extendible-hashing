#ifndef HASHEX_DATA_H
#define HASHEX_DATA_H

//
// 1. This represent data in hash table.
//
// 2. The current implementation stores std::string.
//
// 3. If you need other type, just change std::string to your type D,
//    and make sure comparision operators are available for type D.
//

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

