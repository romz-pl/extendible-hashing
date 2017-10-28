[![Build Status](https://travis-ci.org/romz-pl/extendible-hashing.svg?branch=master)](https://travis-ci.org/romz-pl/extendible-hashing)

# Memory based extendible hashing

1. Implementation of extendible hashing in C++

2. This is the refactored, simpyfied and  improved https://github.com/nitish6174/extendible-hashing project

3. The implemenation is based on the book:
R. Ramakrishnan, J. Gehrke "DATABASE MANAGEMENT SYSTEMS" (third edition)
Chapter 11.2 "EXTENDIBLE HASHING"

4. Extendible hashing was proposed in the following paper:
R. Fagin, J. Nievergelt, N. Pippenger, and H. Strong, "Extendible Hashing -·a fast access
method for dynamic files",  ACM Transactions on Database Systems, 
vol. 4, No. 3, pp. 315-344, 1979.

5. Abstract from the original paper:
Extendible hashing is a new access technique, in which the user is guaranteed no more than two page faults to locate the data associated with a given unique identifier, or key. Unlike conventional hashing, extendible hashing has a dynamic structure that grows and shrinks gracefully as the database grows and shrinks. This approach simultaneously solves the problem of making hash tables that are extendible and of making radix search trees that are balanced. We study, by analysis and simulation, the performance of extendible hashing. The results indicate that extendible hashing provides an attractive alternative to other access methods, such as balanced trees.

6. G.D. Knott "Expandable open addressing hash table storage and retrieval", Proc. ACM SIGFIDET
Workshop on Data Description, Access, and Control, pp. 186-206, 1971,

7. P. Larson "Dynamic hashing", BIT vol. 18, pp. 184-201, 1978.
