// Copyright 2019 kkAyataka
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include "gtest/gtest.h"

#include "pluspath/pluspath.hpp"
#include "pluspath/detail/pluspath-mac.h"

TEST(pluspath, check_paths) {
    std::cout << "current dir: " << pluspath::get_current_dir() << std::endl;
    std::cout << "executable dir: " << pluspath::get_executable_dir() << std::endl;
    std::cout << "app bundle dir: " << pluspath::get_app_bundle_dir() << std::endl;
    std::cout << "home dir: " << pluspath::get_home_dir() << std::endl;
    std::cout << "tmp dir: " << pluspath::get_tmp_dir() << std::endl;
    std::cout << "desktop dir: " << pluspath::get_desktop_dir() << std::endl;
    std::cout << "user app data dir: " << pluspath::get_user_app_data_dir() << std::endl;
    std::cout << "common app data dir: " << pluspath::get_common_app_data_dir() << std::endl;
    std::cout << "download dir: " << pluspath::get_download_dir() << std::endl;
    std::cout << "use documents dir: " << pluspath::get_user_documents_dir() << std::endl;
    std::cout << "use muxic dir: " << pluspath::get_user_music_dir() << std::endl;
    std::cout << "use pictures dir: " << pluspath::get_user_pictures_dir() << std::endl;
    std::cout << "use movies dir: " << pluspath::get_user_movies_dir() << std::endl;
}

TEST(pluspath, list_paths) {
    pluspath::set_current_dir("/");
    const pluspath::StringVec paths = list_paths("./", pluspath::kListModeNonRecursive);
    for (auto i = paths.begin(); i != paths.end(); ++i) {
        std::cout << *i << std::endl;
    }
}
