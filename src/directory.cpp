#include "directory.h"
#include <cassert>
#include <stdexcept>
#include <iostream>

//
//
//
Directory::Directory()
    : m_globalDepth( 1 )
{
    const std::size_t size = ( 1 << m_globalDepth );
    m_dir.resize( size, nullptr );

    for( Bucket*&b : m_dir )
        b = NewBucket( m_globalDepth );

}

//
//
//
Directory::~Directory()
{
    for( auto b : m_pool )
        delete b;
}

//
//
//
Data Directory::Get( const Key& key ) const
{
    assert( m_dir.size() != 0 );

    const std::size_t id = GetEntryId( key );
    const Bucket* b = m_dir[ id ];
    assert( b );
    return b->Get( key );
}

//
//
//
std::size_t Directory::GetEntryId( const Key& key ) const
{
    std::size_t mask = 0;
    for( std::uint32_t i = 0; i < m_globalDepth; i++ )
        mask |= ( 1 << i );

    std::size_t hv = key.GetHash();

    std::size_t ret = hv & mask;
    assert( ret < m_dir.size() );
    return ret;
}

//
//
//
void Directory::Put( const Key& key, const Data& data )
{
    const std::size_t id = GetEntryId( key );

    if( !m_dir[ id ]->IsFull() )
    {
        m_dir[ id ]->Put( key, data );
        return;
    }

    if( m_dir[ id ]->GetKey() == key )
    {
        throw std::runtime_error( "Key already inserted" );
    }



    bool force = false;
    std::size_t idA = 0, idB = 0;
    do
    {
        // Double the directory
        if( force || m_globalDepth == m_dir[ id ]->GetLocalDepth() )
        {
            m_globalDepth++;
            std::cout << "Global-Depth=" << m_globalDepth << std::endl;
            const std::vector< Bucket* > tmp = m_dir;
            m_dir.insert( m_dir.end(), tmp.begin(), tmp.end() );
        }

        // Split the Bucket

        idA = GetEntryId( m_dir[ id ]->GetKey() );

        idB = GetEntryId( key );

        if( idA == idB )
        {
            force = true;
        }

    } while( idA == idB );


    const std::size_t v = m_dir[ id ]->GetLocalDepth();

    const Key oldKey = m_dir[ id ]->GetKey();
    const Data oldData = m_dir[ id ]->GetData();
    *(m_dir[ idA ]) = Bucket( oldKey, oldData, v + 1 );

    m_dir[ idB ] = NewBucket( key, data, v + 1 );




}

//
//
//
Bucket* Directory::NewBucket( std::uint32_t depth )
{
    Bucket* b = new Bucket( depth );
    m_pool.push_back( b );
    return b;
}

//
//
//
Bucket* Directory::NewBucket( const Key& key, const Data& data, std::uint32_t depth )
{
    Bucket* b = new Bucket( key, data, depth );
    m_pool.push_back( b );
    return b;
}

//
//
//
void Directory::Print() const
{
    std::cout << "Global Depth: " << m_globalDepth << std::endl;

    for( auto b : m_dir )
        b->Print();
}
