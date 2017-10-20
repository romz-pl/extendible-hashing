#include "entry.h"
#include <stdexcept>
#include <utility>

//
//
//
Entry::Entry( const Key& key )
    : m_key ( key )
    , m_bucket( nullptr )
{

}

//
//
//
Data Entry::Get( const Key& key ) const
{
    using namespace std::rel_ops;

    if( key != m_key || !m_bucket )
    {
        throw std::runtime_error( "Key is not found" );
    }

    return m_bucket->Get();

}
