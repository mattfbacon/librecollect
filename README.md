# librecollect

A memcached library for C++, that wraps libmemcached. Uses modern C++ and OOP techniques to make using the library a little nicer.

## Build and test

```bash
make debug # or release
./dist/Debug/test # or Release
```

## Use it in a project

```cmake
# do you want to build it dynamically?
# probably not if you're vendoring it
set(RECOLLECT_BUILD_DYNAMIC False)
include(path/to/librecollect/CMakeLists.txt)

target_link_libraries(your_project PRIVATE recollect)
```
