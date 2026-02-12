cmake_minimum_required(VERSION 3.28)
project(main)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}")
include_directories("${CMAKE_SOURCE_DIR}/3rdparty/zlib")
include_directories("${CMAKE_SOURCE_DIR}/3rdparty/entt/src")

include_directories("C:/SDL3-3.4.0/include")
link_directories("C:/SDL3-3.4.0/lib/x64")

# ffmpeg
include_directories("C:/ffmpeg-master-latest-win64-gpl-shared/include")
link_directories("C:/ffmpeg-master-latest-win64-gpl-shared/lib")

# include_directories("C:/FFMPEG-WEB/include")
# link_directories("C:/FFMPEG-WEB/lib")

file(GLOB_RECURSE ALL_CPP_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
add_executable(main ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp ${ALL_CPP_FILES})

target_link_libraries(main PRIVATE zlibstatic)
target_link_libraries(main PRIVATE SDL3)
# target_link_libraries(main PRIVATE SDL3::SDL3)
target_link_libraries(main PRIVATE freetype)

target_link_libraries(main PRIVATE avcodec avformat avutil swscale swresample)

if (MSVC)
    add_compile_options(/WX)  # MSVC 的 "警告视为错误"
else()
    add_compile_options(-Werror)  # GCC/Clang 的选项
endif()

if(WIN32)
        if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
                set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /utf-8")
                set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /bigobj")
                add_definitions(-DNOMINMAX)
        endif()

        set_target_properties(main PROPERTIES
                RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
endif()

if(APPLE)
        set_target_properties(main PROPERTIES
                RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
        )
endif()

# 设置 Emscripten 编译选项
if(EMSCRIPTEN)

        set(CMAKE_EXECUTABLE_SUFFIX ".html")

        set_target_properties(main PROPERTIES LINK_FLAGS 
        "--preload-file ${CMAKE_SOURCE_DIR}/build/Data/@Data/ --preload-file ${CMAKE_SOURCE_DIR}/build/Maps/@Maps/"
        )
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -sALLOW_MEMORY_GROWTH -sUSE_ZLIB -sSTACK_SIZE=64MB")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -sINITIAL_MEMORY=128MB")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -sMAXIMUM_MEMORY=4GB")

        # set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -O3 -flto")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -g4 -sNO_DISABLE_EXCEPTION_CATCHING=1")

        set_target_properties(main PROPERTIES
                RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
        )
endif()
