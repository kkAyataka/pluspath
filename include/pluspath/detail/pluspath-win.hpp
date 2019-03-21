// Copyright 2019 kkAyataka
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef PLUSPATH_DETAIL_PLUSPATH_WIN_HPP__
#define PLUSPATH_DETAIL_PLUSPATH_WIN_HPP__

#include "../pluspath-type.hpp"

#include <Windows.h>
#include <PathCch.h>
#include <ShlObj.h>

#include <vector>

#pragma comment(lib, "Pathcch")

namespace pluspath {
namespace detail {

inline std::string remove_last_element(const std::string & path) {
    std::vector<char> buf(path.size());
    const int size = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, path.c_str(), -1, 0, 0);
    if (size) {
        std::vector<wchar_t> wbuf(size);
        MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, path.c_str(), -1, &wbuf[0], size);

        PathCchRemoveFileSpec(&wbuf[0], wbuf.size());

        std::fill(buf.begin(), buf.end(), 0);
        WideCharToMultiByte(CP_ACP, 0, &wbuf[0], -1, &buf[0], static_cast<int>(buf.size()), NULL, NULL);
        return &buf[0];
    }
    else {
        return path;
    }
}

inline std::string wstr_to_str(const std::wstring & wstr) {
    const int size = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, 0, 0, NULL, NULL);
    if (size) {
        std::vector<char> buf(size);
        WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, &buf[0], static_cast<int>(buf.size()), NULL, NULL);
        return &buf[0];
    }
    else {
        return "";
    }
}

inline int store_to_buf(const std::string & path, char * buf, unsigned long * buf_size) {
    if (buf == 0 && buf_size) {
        *buf_size = static_cast<int>(path.size()) + 1;
        return 1;
    }
    else if (buf && buf_size && *buf_size > path.size()) {
        strcpy_s(buf, *buf_size, path.c_str());
        return 1;
    }
    else {
        return 0;
    }
}

inline int get_known_dir(const KNOWNFOLDERID id, char * buf, unsigned long * buf_size) {
    wchar_t * wbuf = 0;
    if (SHGetKnownFolderPath(id, KF_FLAG_DEFAULT, NULL, &wbuf) == S_OK) {
        const auto path = pluspath::detail::wstr_to_str(wbuf);
        CoTaskMemFree(wbuf);
        return store_to_buf(path, buf, buf_size);
    }
    else {
        return 0;
    }
}

inline StringVec list_paths(const std::string & target_path, const ListMode mode) {
    const std::string dot = ".";
    const std::string dotdot = "..";

    StringVec paths;

    std::string base_path = target_path;
    if (base_path.back() != '\\') {
        base_path += '\\';
    }

    WIN32_FIND_DATAA fd = {};
    HANDLE fh = FindFirstFileExA((base_path + '*').c_str(), FindExInfoBasic, &fd, FindExSearchNameMatch, NULL, 0);
    if (fh != INVALID_HANDLE_VALUE) {
        while (FindNextFileA(fh, &fd)) {
            // ignore . and .. file
            if (dot != fd.cFileName && dotdot != fd.cFileName) {
                const auto path = base_path + fd.cFileName;
                paths.push_back(path);

                if ((fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && mode == kListModeRecursive) {
                    const auto sub_paths = detail::list_paths(path, mode);
                    paths.insert(paths.end(), sub_paths.begin(), sub_paths.end());
                }
            }
        }

        FindClose(fh);
    }

    return paths;
}

}} // namespcae pluspath::detail

inline int pluspath_get_executable_dir(char * buf, unsigned long * buf_size) {
    std::vector<char> tbuf(1024);
    for (int i = 0; GetModuleFileNameA(NULL, &tbuf[0], static_cast<int>(tbuf.size())) == tbuf.size() || i < 6; ++i) {
        tbuf.resize(tbuf.size() * 2);
    }

    const std::string path = pluspath::detail::remove_last_element(&tbuf[0]);
    return pluspath::detail::store_to_buf(path, buf, buf_size);
}

inline int pluspath_get_app_bundle_dir(char * buf, unsigned long * buf_size) {
    return pluspath_get_executable_dir(buf, buf_size);
}

inline int pluspath_get_home_dir(char * buf, unsigned long * buf_size) {
    return pluspath::detail::get_known_dir(FOLDERID_Profile, buf, buf_size);
}

inline int pluspath_get_tmp_dir(char * buf, unsigned long * buf_size) {
    char path[MAX_PATH + 1] = {};
    const auto copyed = GetTempPathA(sizeof(path), path);
    return pluspath::detail::store_to_buf(path, buf, buf_size);
}

inline int pluspath_get_desktop_dir(char * buf, unsigned long * buf_size) {
    return pluspath::detail::get_known_dir(FOLDERID_Desktop, buf, buf_size);
}

#endif // PLUSPATH_DETAIL_PLUSPATH_WIN_HPP__
