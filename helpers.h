#pragma once

#include <boost/functional/hash.hpp>
#include <boost/uuid/uuid.hpp>

#include <tbb/tbb_stddef.h>
#include <tbb/internal/_tbb_hash_compare_impl.h>

namespace tbb {

    template<>
    struct tbb_hash_compare<boost::uuids::uuid> {
        static boost::hash<boost::uuids::uuid> uuid_hasher;
        static size_t hash(const boost::uuids::uuid& a);
        static bool equal(const boost::uuids::uuid& a, const boost::uuids::uuid& b);
    };
}