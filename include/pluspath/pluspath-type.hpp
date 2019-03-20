// Copyright 2019 kkAyataka
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef PLUSPATH_TYPE_HPP__
#define PLUSPATH_TYPE_HPP__

#include <string>
#include <vector>

namespace pluspath {

/**
 * List mode
 */
typedef enum {
    kListModeRecursive = -1,
    kListModeNonRecursive = 0,
} ListMode;

/**
 * Paths type, string vector
 */
typedef std::vector<std::string> StringVec;

} // namespace pluspath

#endif // PLUSPATH_TYPE_HPP__
