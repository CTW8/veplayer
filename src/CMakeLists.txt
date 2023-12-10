file(GLOB player_source "*.cpp")

file(GLOB player_source_header "*.h")

# 将子目录1的源文件添加到库中
add_library(veplayer ${player_source})

include_directories(veplayer PUBLIC "${CMAKE_SOURCE_DIR}/lib/libffmpeg/include" "${CMAKE_SOURCE_DIR}/lib/glfw/include"  "${CMAKE_SOURCE_DIR}/lib/glad/include" "${player_source_header}")
