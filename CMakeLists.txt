cmake_minimum_required(VERSION 3.0.0)
project(main VERSION 0.1.0)

add_subdirectory(src)
add_executable(main main.cpp glad.c)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -v -framework CoreFoundation -framework NetWork -framework Security  -framework CoreGraphics -framework IOKit  -framework AppKit")

target_link_directories(main PUBLIC "${PROJECT_SOURCE_DIR}/lib/libffmpeg/lib"  "${PROJECT_SOURCE_DIR}/lib/glfw/lib")
target_link_libraries(main PUBLIC avutil avcodec avformat swresample swscale bz2 iconv z glfw3 veplayer pthread)

target_include_directories(main PUBLIC "${CMAKE_SOURCE_DIR}/lib/libffmpeg/include" "${CMAKE_SOURCE_DIR}/lib/glfw/include"  "${CMAKE_SOURCE_DIR}/lib/glad/include")
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)


