cmake_minimum_required(VERSION 3.15)

project(js_engine CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
    endstone
    GIT_REPOSITORY https://github.com/EndstoneMC/endstone.git
    GIT_TAG main
)
FetchContent_MakeAvailable(endstone)

# 先包含 third-party
include(third-party/CMakeLists.txt)

# 然后添加插件并链接 ScriptX
endstone_add_plugin(${PROJECT_NAME} src/Entry.cc)
target_link_libraries(${PROJECT_NAME} PRIVATE ScriptX)

# cmake -B build -S .
# cmake --build ./build
