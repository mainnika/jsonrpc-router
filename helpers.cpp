#include "helpers.h"

namespace tbb {

    size_t tbb_hash_compare<boost::uuids::uuid>::hash(const boost::uuids::uuid& a) {
        return tbb_hash_compare<boost::uuids::uuid>::uuid_hasher(a);
    }

    bool tbb_hash_compare<boost::uuids::uuid>::equal(const boost::uuids::uuid& a, const boost::uuids::uuid& b) {
        return a == b;
    }
    
    boost::hash<boost::uuids::uuid> tbb_hash_compare<boost::uuids::uuid>::uuid_hasher;
}