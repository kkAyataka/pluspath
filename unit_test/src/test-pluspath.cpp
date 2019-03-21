// Copyright 2019 kkAyataka
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include "gtest/gtest.h"

#include "pluspath/pluspath.hpp"
#include "pluspath/detail/pluspath-mac.h"

TEST(pluspath, check_paths) {
    std::cout << "executable dir: " << pluspath::get_executable_dir() << std::endl;
    std::cout << "app bundle dir: " << pluspath::get_app_bundle_dir() << std::endl;
    std::cout << "home dir: " << pluspath::get_home_dir() << std::endl;
    std::cout << "tmp dir: " << pluspath::get_tmp_dir() << std::endl;
    std::cout << "desktop dir: " << pluspath::get_desktop_dir() << std::endl;
    std::cout << "user app data dir: " << pluspath::get_user_app_data_dir() << std::endl;
    std::cout << "common app data dir: " << pluspath::get_common_app_data_dir() << std::endl;
}

TEST(pluspath, list_paths) {
    /*
    const pluspath::StringVec paths = list_paths("../../../", pluspath::kListModeRecursive);
    for (auto i = paths.begin(); i != paths.end(); ++i) {
        std::cout << *i << std::endl;
    }
    */
}
