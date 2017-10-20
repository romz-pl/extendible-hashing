#include "bucket.h"

//
//
//
Bucket::Bucket()
    : m_localDepth( 0 )
{

}


//
//
//
Data Bucket::Get( ) const
{
    return m_data;
}
