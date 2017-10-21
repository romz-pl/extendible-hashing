#ifndef HASHEX_HASHEX_H
#define HASHEX_HASHEX_H

//
//
// Exerpts from the book:
// R. Ramakrishnan, J. Gehrke "DATABASE MANAGEMENT SYSTEMS" (third edition)
// Chapter 11.2 "EXTENDIBLE HASHING"
//
//
// 1. We observe that the basic technique used in Extendible Hashing is to treat the
//    result of applying a hash function $h $as a binary number and interpret the last $d$
//    bits (where $d$ depends on the size of the directory) as an offset into the directory.
//
// 2. When distributing entries across a bucket and its split image, we should do so
//    on the basis of the $d$-th bit.
//
// 3. The number $d$ is called the global depth.
//
// 4. To determine whether a directory doubling is needed, we maintain a local depth
//    for each bucket.
//
// 5. If a bucket whose local depth is equal to the global depth is split,
//    the directory must be doubled.
//
// 6. Initially, all local depths are equal to the global depth (which is the number of
//    bits needed to express the total number of buckets).
//
// 7. We increment the global depth by 1 each time the directory doubles.
//
// 8. Whenever a bucket is split (whether or not the split leads to a directory doubling),
//    we increment by 1 the local depth of the split bucket and assign this same (incremented)
//    local depth to its (newly created) split image.
//
// 9. If a bucket has local depth $l$, the hash values of data entries in it agree on the last $l$ bits;
//    further, no data entry in any other bucket of the file has a hash value with the same last $l$ bits.
//    A total of $2^{d-l}$ directory elements point to a bucket with local depth $l$;
//    if d = l, exactly one directory element points to the bucket and splitting such a
//    bucket requires directory doubling.
//
// 10. In summary:
//     1) A data entry can be located by computing its hash value, taking
//        the last $d$ bits, and looking in the bucket pointed to by this directory element.
//     2) For inserts, the data entry is placed in the bucket to which it belongs and the
//        bucket is split if necessary to make space. A bucket split leads to an increase in
//        the local depth and, if the local depth becomes greater than the global depth
//        as a result, to a directory doubling (and an increase in the global depth) as well.
//
//
// 11. For deletes, the data entry is located and removed. If the delete leaves the
//     bucket empty, it can be merged with its split image, although this step is
//     often omitted in practice. Merging buckets decreases the local depth. If each
//     directory element points to the same bucket as its split image, we can halve the
//     directory and reduce the global depth, although this step is not necessary for correctness.
//

#include "data.h"
#include "key.h"
#include "directory.h"

class HashEx
{
public:
    HashEx();
    ~HashEx() = default;

    Data Get( const Key& key ) const;
    void Put( const Key& key, const Data& data );
    void Delete( const Key& key );

    void Print() const;

private:
    Directory m_dir;

};


#endif
