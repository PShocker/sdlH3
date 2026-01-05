cmake_minimum_required(VERSION 3.28)
project(sdlH3)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add compile information for LSP
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        # 去掉调试符号
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s")
        # 启用lto -flto=auto
        # 对本机cpu生成特定优化代码,可能存在兼容性问题
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -flto=auto")
    endif()
endif()

add_subdirectory(3rdparty/zlib EXCLUDE_FROM_ALL)
add_subdirectory(3rdparty/freetype EXCLUDE_FROM_ALL)

# set(SDL_SHARED FALSE)
# set(SDL_SHARED TRUE)
# set(SDL_STATIC TRUE)
# add_subdirectory(3rdparty/SDL EXCLUDE_FROM_ALL)

add_subdirectory(sdlH3)
