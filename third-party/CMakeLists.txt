# ScriptX & QuickJs

# set(CMAKE_CXX_STANDARD 17)
set(SCRIPTX_BACKEND QuickJs)
set(CMAKE_BUILD_TYPE Release)

# 添加 QuickJS 库
add_library(quickjs STATIC IMPORTED)
set_target_properties(quickjs PROPERTIES
    IMPORTED_LOCATION "${CMAKE_CURRENT_LIST_DIR}/quickjs/lib/quickjs.lib"
    IMPORTED_LOCATION_DEBUG "${CMAKE_CURRENT_LIST_DIR}/quickjs/lib/quickjs.lib"
    IMPORTED_LOCATION_RELEASE "${CMAKE_CURRENT_LIST_DIR}/quickjs/lib/quickjs.lib"
)

# 包含 ScriptX
include(${CMAKE_CURRENT_LIST_DIR}/scriptx/CMakeLists.txt)

# 设置包含目录
target_include_directories(ScriptX PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/quickjs/include
    ${CMAKE_CURRENT_LIST_DIR}/scriptx/src/include
)

# 链接 QuickJS 库到 ScriptX
target_link_libraries(ScriptX PRIVATE quickjs)