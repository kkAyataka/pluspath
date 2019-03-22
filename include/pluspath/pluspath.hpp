// Copyright 2019 kkAyataka
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef PLUSPATH_HPP_
#define PLUSPATH_HPP_

#include "pluspath-type.hpp"

#include <vector>

#ifdef _MSC_VER
    #include "detail\pluspath-win.hpp"
#elif __APPLE__
    #include "detail/pluspath-mac.h"
    #include "detail/pluspath-unix.hpp"
#else
#endif

namespace pluspath {
namespace detail {

typedef int (*get_dir_f)(char *, unsigned long*);
inline std::string get_dir(get_dir_f f) {
    unsigned long size = 0;
    if (f(0, &size)) {
        std::vector<char> buf(size);
        if (f(&buf[0], &size)) {
            return &buf[0];
        }
    }

    return "";
}

} // namespace pluspath::detail

/**
 * List file paths
 * @param [in] target_path listing target path
 * @param [in] mode List recursivery or not
 * @return Listed paths array
 */
inline StringVec list_paths(const std::string& target_path, const ListMode mode) {
    return detail::list_paths(target_path, mode);
}

inline std::string get_executable_dir() {
    return detail::get_dir(pluspath_get_executable_dir);
}

inline std::string get_app_bundle_dir() {
    return detail::get_dir(pluspath_get_app_bundle_dir);
}

inline std::string get_home_dir() {
    return detail::get_dir(pluspath_get_home_dir);
}

inline std::string get_tmp_dir() {
    return detail::get_dir(pluspath_get_tmp_dir);
}

inline std::string get_desktop_dir() {
    return detail::get_dir(pluspath_get_desktop_dir);
}

inline std::string get_user_app_data_dir() {
    return detail::get_dir(pluspath_get_user_app_data_dir);
}

inline std::string get_common_app_data_dir() {
    return detail::get_dir(pluspath_get_common_app_data_dir);
}

inline std::string get_download_dir() {
    return detail::get_dir(pluspath_get_download_dir);
}

inline std::string get_user_documents_dir() {
    return detail::get_dir(pluspath_get_user_documents_dir);
}

inline std::string get_user_music_dir() {
    return detail::get_dir(pluspath_get_user_music_dir);
}

inline std::string get_user_pictures_dir() {
    return detail::get_dir(pluspath_get_user_pictures_dir);
}

inline std::string get_user_movies_dir() {
    return detail::get_dir(pluspath_get_user_movies_dir);
}

} // namespace pluspath

#endif // PLUSPATH_HPP_
