#include "stat.h"

using namespace shim;

#ifndef __APPLE__

void bionic::from_host(struct ::stat64 const &info, stat &result) {
    result.st_dev = info.st_dev;
#ifndef __LP64__
    result.__st_ino = info.__st_ino;
#endif
    result.st_mode = info.st_mode;
    result.st_nlink = info.st_nlink;
    result.st_uid = info.st_uid;
    result.st_gid = info.st_gid;
    result.st_rdev = info.st_rdev;
    result.st_size = info.st_size;
    result.st_blksize = (unsigned long) info.st_blksize;
    result.st_blocks = (unsigned long long) info.st_blocks;
    result.st_atim = info.st_atim;
    result.st_mtim = info.st_mtim;
    result.st_ctim = info.st_ctim;
    result.st_ino = info.st_ino;
}

int shim::stat(const char *path, bionic::stat *s) {
    struct ::stat64 tmp = {};
    int ret = ::stat64(path, &tmp);
    bionic::from_host(tmp, *s);
    return ret;
}

int shim::fstat(int fd, shim::bionic::stat *s) {
    struct ::stat64 tmp = {};
    int ret = ::fstat64(fd, &tmp);
    bionic::from_host(tmp, *s);
    return ret;
}

#else

void bionic::from_host(struct ::stat const &info, stat &result) {
    result.st_dev = info.st_dev;
#ifndef __LP64__
    result.__st_ino = info.st_ino;
#endif
    result.st_mode = info.st_mode;
    result.st_nlink = info.st_nlink;
    result.st_uid = info.st_uid;
    result.st_gid = info.st_gid;
    result.st_rdev = info.st_rdev;
    result.st_size = info.st_size;
    result.st_blksize = (unsigned long) info.st_blksize;
    result.st_blocks = (unsigned long long) info.st_blocks;
    result.st_atim = info.st_atimespec;
    result.st_mtim = info.st_mtimespec;
    result.st_ctim = info.st_ctimespec;
    result.st_ino = info.st_ino;
}

int shim::stat(const char *path, bionic::stat *s) {
    struct ::stat tmp = {};
    int ret = ::stat(path, &tmp);
    bionic::from_host(tmp, *s);
    return ret;
}

int shim::fstat(int fd, shim::bionic::stat *s) {
    struct ::stat tmp = {};
    int ret = ::fstat(fd, &tmp);
    bionic::from_host(tmp, *s);
    return ret;
}

#endif

void shim::add_stat_shimmed_symbols(std::vector<shimmed_symbol> &list) {
    list.insert(list.end(), {
        {"stat", stat},
        {"fstat", fstat},
        {"stat64", stat},
        {"fstat64", fstat},
        {"chmod", ::chmod},
        {"fchmod", ::fchmod},
        {"umask", ::umask},
        {"mkdir", ::mkdir},
    });
}