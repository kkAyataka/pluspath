// Copyright 2019 kkAyataka
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#import "pluspath/detail/pluspath-mac.h"

#include <Foundation/Foundation.h>

static int NSString_to_cbuffer(NSString * str, char * path_buf, unsigned long * path_buf_size) {
    if (!str) {
        return 0;
    }

    const unsigned long str_size = strlen([str UTF8String]) + 1;

    if (path_buf == 0 && path_buf_size) {
        *path_buf_size = strlen([str UTF8String]) + 1;
        return 1;
    } else if (path_buf && path_buf_size && *path_buf_size >= str_size) {
        strcpy(path_buf, [str UTF8String]);
        return 1;
    } else {
        return 0;
    }
}

static NSString * get_special_dir(const NSSearchPathDirectory dir_key, const NSSearchPathDomainMask domain) {
    NSArray<NSURL *> * urls = [[NSFileManager defaultManager] URLsForDirectory:dir_key inDomains: domain];
    if (urls && [urls count] > 0) {
        return [[urls objectAtIndex: 0] path];
    }

    return @"";
}

int pluspath_get_executable_dir(char * path_buf, unsigned long int * path_buf_size) {
    @autoreleasepool {
        NSString * path = [[[NSBundle mainBundle] executablePath] stringByDeletingLastPathComponent];
        return NSString_to_cbuffer(path, path_buf, path_buf_size);
    }
}

int pluspath_get_app_bundle_dir(char * path_buf, unsigned long int * path_buf_size) {
    @autoreleasepool {
        NSString * path = [[NSBundle mainBundle] bundlePath];
        if ([[path pathExtension] isEqualToString: @"app"]) {
            path = [path stringByDeletingLastPathComponent];
        }
        return NSString_to_cbuffer(path, path_buf, path_buf_size);
    }
}

int pluspath_get_home_dir(char * path_buf, unsigned long int * path_buf_size) {
    @autoreleasepool {
        NSString * path = NSHomeDirectory();
        return NSString_to_cbuffer(path, path_buf, path_buf_size);
    }
}

int pluspath_get_tmp_dir(char * path_buf, unsigned long int * path_buf_size) {
    @autoreleasepool {
        NSString * path = NSTemporaryDirectory();
        return NSString_to_cbuffer(path, path_buf, path_buf_size);
    }
}

int pluspath_get_desktop_dir(char * path_buf, unsigned long * path_buf_size) {
    @autoreleasepool {
        NSString * path = get_special_dir(NSDesktopDirectory, NSUserDomainMask);
        return NSString_to_cbuffer(path, path_buf, path_buf_size);
    }
}

int pluspath_get_user_app_data_dir(char * path_buf, unsigned long * path_buf_size) {
    @autoreleasepool {
        NSString * path = get_special_dir(NSApplicationSupportDirectory, NSUserDomainMask);
        return NSString_to_cbuffer(path, path_buf, path_buf_size);
    }
}

int pluspath_get_common_app_data_dir(char * path_buf, unsigned long * path_buf_size) {
    @autoreleasepool {
        NSString * path = get_special_dir(NSApplicationSupportDirectory, NSLocalDomainMask);
        return NSString_to_cbuffer(path, path_buf, path_buf_size);
    }
}
