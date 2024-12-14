cmake_minimum_required(VERSION 3.15)
project(js_engine CXX)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS True)

# 查找依赖包
find_package(fmt REQUIRED)
find_package(expected-lite REQUIRED)
find_package(EnTT REQUIRED)
find_package(Microsoft.GSL REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(Boost REQUIRED)
find_package(glm REQUIRED)
find_package(concurrentqueue REQUIRED)
find_package(magic_enum REQUIRED)

if(UNIX)
    find_package(libelf REQUIRED)
endif()

# 创建库目标
add_library(js_engine)

# 源文件
file(GLOB_RECURSE SOURCES 
    "src/*.cc"
    "third-party/scriptx/src/*.cc"
    "third-party/scriptx/backend/QuickJs/*.cc"
)
target_sources(js_engine PRIVATE ${SOURCES})

# 包含目录
target_include_directories(js_engine PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
    "${CMAKE_CURRENT_SOURCE_DIR}/third-party/scriptx/src/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/build/_deps/endstone/include"   # endstone 头文件目录
)

if(WIN32)
    target_include_directories(js_engine PRIVATE "third-party/quickjs/win/include")
    target_link_libraries(js_engine PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/third-party/quickjs/win/lib/quickjs.lib")
else()
    target_include_directories(js_engine PRIVATE "third-party/quickjs/linux/include")
    target_link_libraries(js_engine PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/third-party/quickjs/linux/lib/quickjs.a")

    target_compile_options(js_engine PRIVATE
        -frelaxed-template-template-args  # 放宽模板参数检查
        -fdelayed-template-parsing        # 延迟模板解析
    )   
endif()

# 链接依赖
target_link_libraries(js_engine PRIVATE
    fmt::fmt
    nonstd::expected-lite 
    EnTT::EnTT
    Microsoft.GSL::GSL
    nlohmann_json::nlohmann_json
    Boost::boost
    glm::glm
    concurrentqueue::concurrentqueue
    magic_enum::magic_enum
)

if(UNIX)
    target_link_libraries(js_engine PRIVATE libelf::libelf dl pthread)
endif()

# 编译选项
if(WIN32)
    target_compile_options(js_engine PRIVATE 
        /EHa
        /utf-8
        /sdl
    )
else()
    target_compile_options(js_engine PRIVATE
        -fPIC
        -stdlib=libc++
        -fexceptions
        -frtti
    )
    target_link_options(js_engine PRIVATE
        -stdlib=libc++
        "-Wl,-rpath=/usr/lib/llvm-15/lib"
    )
endif()

# 安装规则
install(TARGETS js_engine
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)