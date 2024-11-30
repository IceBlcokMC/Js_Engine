cmake_minimum_required(VERSION 3.15)

project(js_engine CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_BUILD_TYPE Release)


# 定义补丁相关的变量
set(LOGGER_ORIGINAL "${CMAKE_BINARY_DIR}/_deps/endstone-src/include/endstone/logger.h")
set(LOGGER_BACKUP "${LOGGER_ORIGINAL}.bak")
set(LOGGER_PATCH "${CMAKE_CURRENT_SOURCE_DIR}/patch/logger.h")

# 创建补丁目标
add_custom_target(patch_logger
    COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/_deps/endstone-src/include/endstone"
    COMMAND ${CMAKE_COMMAND} -E echo "Checking logger patch..."
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${LOGGER_ORIGINAL}" "${LOGGER_BACKUP}"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${LOGGER_PATCH}" "${LOGGER_ORIGINAL}"
    COMMENT "Patching logger.h"
)

# 获取 endstone
include(FetchContent)
FetchContent_Declare(
    endstone
    GIT_REPOSITORY https://github.com/EndstoneMC/endstone.git
    GIT_TAG main
)
FetchContent_MakeAvailable(endstone)

# 包含 third-party
include(third-party/CMakeLists.txt)

# 确保输出目录存在
file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# 创建插件目标并设置依赖
endstone_add_plugin(${PROJECT_NAME} src/Entry.cc)
target_link_libraries(${PROJECT_NAME} PRIVATE ScriptX)

# 设置 PDB 生成选项
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /Zi)  # 生成完整的调试信息
    set_target_properties(${PROJECT_NAME} PROPERTIES 
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
        RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/bin
        RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/bin
        PDB_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
        PDB_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/bin
        PDB_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/bin
    )
endif()

# 在插件目标创建后添加补丁依赖
add_dependencies(${PROJECT_NAME} patch_logger)
