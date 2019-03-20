// Copyright 2019 kkAyataka
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef PLUSPATH_UNIX_H__
#define PLUSPATH_UNIX_H__

#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>

#include "../pluspath-type.hpp"

namespace pluspath {
namespace detail {

/**
 * @private
 * Implement list_paths function for Mac anc Linux
 */
inline StringVec list_paths(const std::string &target_path, const ListMode mode) {
    const std::string dot = ".";
    const std::string dotdot = "..";

    std::string base = target_path;
    if (target_path.size() > 0 && target_path[target_path.size() - 1] != '/') {
        base += "/";
    }

    StringVec paths;
    DIR *dir = opendir(target_path.c_str());
    if (dir) {
        struct dirent *dent = 0;
        while ((dent = readdir(dir)) != NULL) {
            // ignore "." and ".." file
            if (dot != dent->d_name && dotdot != dent->d_name) {
                const std::string path = base + dent->d_name;
                
                paths.push_back(path);

                // list recursively
                if (dent->d_type == DT_DIR && mode == kListModeRecursive) {
                    const StringVec sub_paths = list_paths(path, mode);
                    paths.insert(paths.end(), sub_paths.begin(), sub_paths.end());
                }
            }
        }
        closedir(dir);
    }

    return paths;
}

}} // namespace pluspath::detail

#endif // PLUSPATH_UNIX_H__
