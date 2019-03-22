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
 * Gets current directory path
 * @return Current directory path
 */
inline std::string get_current_dir() {
    return detail::get_current_dir();
}

/**
 * Set/Changes current directory
 * @param [in] dir_path New current directory psth
 * @return true is succeeded, false is failed.
 */
inline bool set_current_dir(const std::string & dir_path) {
    return detail::set_current_dir(dir_path);
}

/**
 * List file paths
 * @param [in] target_path listing target path
 * @param [in] mode List recursivery or not
 * @return Listed paths array
 */
inline StringVec list_paths(const std::string& target_path, const ListMode mode) {
    return detail::list_paths(target_path, mode);
}

/**
 * Gets directory path that the executable file exists
 * @return Directory path
 *  - Mac: If this function is called from app bundle,
 *      this function returns MyApp.app/Contents/MacOS
 * @see get_app_bundle_dir
 */
inline std::string get_executable_dir() {
    return detail::get_dir(pluspath_get_executable_dir);
}

/**
 * Gets directory path that the app bundle file exists
 * @return Directory path
 *  - Windows and Linux: This function returns the path same as get_executable_dir
 * @see get_executable_dir
 */
inline std::string get_app_bundle_dir() {
    return detail::get_dir(pluspath_get_app_bundle_dir);
}

/**
 * Gets home directory path
 * @return
 *  - Windows: e.g. C:¥Users¥UserName
 *  - Mac: e.g. /Users/username
 *  = Linux: e.g. /home/username
 */
inline std::string get_home_dir() {
    return detail::get_dir(pluspath_get_home_dir);
}

/**
 * Gets tem@porary directory
 * @return
 *  - Windows: e.g.
 *  - Mac: e.g. /var/folders/xx/xx_random?string/T
 *  = Linux: e.g. /tmp or ${PLUSPATH_TMP} environment variable
 */
inline std::string get_tmp_dir() {
    return detail::get_dir(pluspath_get_tmp_dir);
}

/**
 * Gets desktop directory path
 * @return
 * - Windows: e.g. C:\Users/{user_name}/Desktop
 * - Mac: e.g. /Users/{user_name}/Desktop
 * - Linux: ~/.config/user-dirs.dirs file is considered. e.g. /home/{user_name}/Desktop
 */
inline std::string get_desktop_dir() {
    return detail::get_dir(pluspath_get_desktop_dir);
}

/**
 * Gets user applicatino data desktop directory path
 * @return
 * - Windows: e.g. C:\Users\{user_name}\AppData\Roaming
 * - Mac: e.g. /Users/{user_name}/Library/Application Support
 * - Linux: e.g. /home/{user_name}/.var/opt or ${PLUSPATH_USER_APP_DATA} environment variable
 */
inline std::string get_user_app_data_dir() {
    return detail::get_dir(pluspath_get_user_app_data_dir);
}

/**
 * Gets common applicatino data desktop directory path
 * @return
 * - Windows: e.g. C:\ProgramData
 * - Mac: e.g. /Library/Application Support
 * - Linux: e.g. /var/opt or ${PLUSPATH_COMMON_APP_DATA} environment variable
 */
inline std::string get_common_app_data_dir() {
    return detail::get_dir(pluspath_get_common_app_data_dir);
}

/**
 * Gets download directory path
 * @return
 * - Windows: e.g. C:\Users\{user_name}\Downloads
 * - Mac: e.g. /Users/{user_name}/Downloads
 * - Linux: ~/.config/user-dirs.dirs file is considered. e.g. /home/{user_name}/Downloads
 */
inline std::string get_download_dir() {
    return detail::get_dir(pluspath_get_download_dir);
}

/**
 * Gets user documents directory path
 * @return
 * - Windows: e.g. C:\Users\{user_name}\Documents
 * - Mac: e.g. /Users/{user_name}/Documents
 * - Linux: ~/.config/user-dirs.dirs file is considered. e.g. /home/{user_name}/Documents
 */
inline std::string get_user_documents_dir() {
    return detail::get_dir(pluspath_get_user_documents_dir);
}

/**
 * Gets user music directory path
 * @return
 * - Windows: e.g. C:\Users\{user_name}\Music
 * - Mac: e.g. /Users/{user_name}/Music
 * - Linux: ~/.config/user-dirs.dirs file is considered. e.g. /home/{user_name}/Music
 */
inline std::string get_user_music_dir() {
    return detail::get_dir(pluspath_get_user_music_dir);
}

/**
 * Gets user pictures directory path
 * @return
 * - Windows: e.g. C:\Users\{user_name}\Pictures
 * - Mac: e.g. /Users/{user_name}/Pictures
 * - Linux: ~/.config/user-dirs.dirs file is considered. e.g. /home/{user_name}/Pictures
 */
inline std::string get_user_pictures_dir() {
    return detail::get_dir(pluspath_get_user_pictures_dir);
}

/**
 * Gets user movies/videos directory path
 * @return
 * - Windows: e.g. C:\Users\{user_name}\Movies
 * - Mac: e.g. /Users/{user_name}/Movies
 * - Linux: ~/.config/user-dirs.dirs file is considered. e.g. /home/{user_name}/Videos
 */
inline std::string get_user_movies_dir() {
    return detail::get_dir(pluspath_get_user_movies_dir);
}
#define get_user_movies_dir get_user_videos_dir ///< videos version

} // namespace pluspath

#endif // PLUSPATH_HPP_
