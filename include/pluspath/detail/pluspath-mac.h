// Copyright 2019 kkAyataka
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

int pluspath_get_executable_dir(char * path_buf, unsigned long * path_buf_size);
int pluspath_get_app_bundle_dir(char * path_buf, unsigned long * path_buf_size);
int pluspath_get_home_dir(char * path_buf, unsigned long * path_buf_size);
int pluspath_get_tmp_dir(char * path_buf, unsigned long * path_buf_size);
int pluspath_get_desktop_dir(char * path_buf, unsigned long * path_buf_size);
int pluspath_get_user_app_data_dir(char * path_buf, unsigned long * path_buf_size);


#ifdef __cplusplus
}
#endif // __cplusplus
