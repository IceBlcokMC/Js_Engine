add_rules("mode.debug", "mode.release")

add_requires("endstone main")
add_requires("fmt")
add_requires("expected-lite")
add_requires("nlohmann_json")

if not has_config("vs_runtime") then
    set_runtimes("MD")
end

package("endstone")
    set_homepage("https://github.com/EndstoneMC/endstone")
    set_description("Endstone SDK for plugins")
    
    add_urls("https://github.com/EndstoneMC/endstone.git")
    
    -- 添加所有必要的依赖，参考 CMake 配置
    add_deps("fmt", "expected-lite", "nlohmann_json")
    add_deps("microsoft-gsl", {alias = "ms-gsl"})
    add_deps("boost")
    add_deps("entt")
    add_deps("magic_enum")
    add_deps("spdlog")
    add_deps("toml++")
    add_deps("glm")
    add_deps("libbase64 0.5.2")
    
    -- 仅支持Windows MSVC和Linux Clang
    if is_plat("windows") then
        add_configs("runtimes", {description = "Set vs runtime", default = "MD", values = {"MT", "MD", "MTd", "MDd"}})
    end

    on_load(function (package)
        -- 设置编译器要求
        if package:is_plat("windows") and not package:is_plat("mingw") then
            package:set("runtimes", package:config("runtimes"))
        end

        -- 添加头文件搜索路径
        package:add("includedirs", "include")
        package:add("sysincludedirs", "include")
    end)

    on_install(function (package)
        -- 检查编译器
        if package:is_plat("windows") then
            if not is_host("windows") then
                raise("Endstone: MSVC is required on Windows.")
            end
        elseif package:is_plat("linux") then
            if not package:has_tool("cc", "clang") then
                raise("Endstone: Clang is required on Linux.")
            end
        else
            raise("Endstone: This platform is not supported")
        end

        -- 设置编译选项
        if package:is_plat("windows") then
            -- 设置_ITERATOR_DEBUG_LEVEL=0
            package:add("cxflags", "/D_ITERATOR_DEBUG_LEVEL=0")
        elseif package:is_plat("linux") then
            -- 使用libc++
            package:add("cxflags", "-stdlib=libc++")
            package:add("cxflags", "-fPIC")
        end

        -- 创建临时的xmake.lua文件用于构建
        local xmake_content = string.format([[
            add_requires("fmt", "expected-lite", "nlohmann_json")
            add_requires("microsoft-gsl", {alias = "ms-gsl"})
            add_requires("boost")
            add_requires("entt")
            add_requires("magic_enum")
            add_requires("spdlog")
            add_requires("toml++")
            add_requires("glm")
            add_requires("libbase64 0.5.2")
            add_rules("mode.debug", "mode.release")
            
            target("endstone")
                set_kind("static")
                set_languages("c++17")
                add_files("src/endstone_core/*.cpp")
                add_includedirs("include")
                add_packages("fmt", "expected-lite", "nlohmann_json")
                add_packages("ms-gsl")
                add_packages("boost")
                add_packages("entt")
                add_packages("magic_enum")
                add_packages("spdlog")
                add_packages("toml++")
                add_packages("glm")
                add_packages("libbase64")
                
                -- 添加编译定义
                add_defines("PYBIND11_DETAILED_ERROR_MESSAGES")
                add_defines("ENTT_SPARSE_PAGE=2048")
                add_defines("ENTT_PACKED_PAGE=128")
                
                if is_plat("windows") then
                    add_cxflags("/D_ITERATOR_DEBUG_LEVEL=0")
                    set_runtimes("%s")
                elseif is_plat("linux") then
                    add_cxflags("-stdlib=libc++", "-fPIC")
                end
        ]], package:config("runtimes") or "MD")
        
        io.writefile("xmake.lua", xmake_content)

        -- 构建项目
        local configs = {}
        if package:is_plat("windows") then
            configs.runtimes = package:config("runtimes")
        end
        import("package.tools.xmake").install(package, configs)

        -- 安装头文件，保持目录结构
        os.cp("include/endstone", path.join(package:installdir(), "include", "endstone"))
    end)

package("libbase64")
    set_homepage("https://github.com/aklomp/base64")
    set_description("Fast Base64 stream encoder/decoder")
    set_license("CC0")

    add_urls("https://github.com/aklomp/base64/archive/refs/tags/v$(version).zip",
             "https://github.com/aklomp/base64.git")
    add_versions("0.5.2", "b3bde7849cc25f9e271df782ac3ca9f09aeaa0d4f68062df414aed0d94da01fb")

    if is_plat("windows") then
        add_configs("shared", {description = "Build shared library.", default = false, type = "boolean"})
        add_configs("runtimes", {description = "Set vs runtime", default = "MD", values = {"MT", "MD", "MTd", "MDd"}})
    end

    add_configs("openmp", {description = "Enable OpenMP support", default = false, type = "boolean"})
    add_configs("simd", {description = "Enable SIMD support", default = true, type = "boolean"})

    on_load(function (package)
        if package:is_plat("windows") and not package:is_plat("mingw") then
            package:set("runtimes", package:config("runtimes"))
        end
    end)

    on_install(function (package)
        -- 检测架构
        local is_x86 = false
        local is_arm = false
        if package:is_arch("x86", "x64", "x86_64") then
            is_x86 = true
        elseif package:is_arch("arm", "arm64", "arm64-v8a") then
            is_arm = true
        end

        -- 生成 config.h
        local config = {}
        if package:config("simd") then
            if is_x86 then
                config.BASE64_WITH_SSSE3 = 1
                config.BASE64_WITH_SSE41 = 1
                config.BASE64_WITH_SSE42 = 1
                config.BASE64_WITH_AVX = 1
                config.BASE64_WITH_AVX2 = 1
                config.BASE64_WITH_AVX512 = 1
            elseif is_arm then
                if package:is_arch("arm") then
                    config.BASE64_WITH_NEON32 = 1
                else
                    config.BASE64_WITH_NEON64 = 1
                end
            end
        end

        local config_content = ""
        config_content = config_content .. "#ifndef BASE64_CONFIG_H\n"
        config_content = config_content .. "#define BASE64_CONFIG_H\n\n"
        
        for k, v in pairs(config) do
            config_content = config_content .. string.format("#define %s %d\n", k, v)
            if k:startswith("BASE64_WITH_") then
                local feature = k:sub(12)
                config_content = config_content .. string.format("#define HAVE_%s %s\n", feature, k)
            end
        end
        
        config_content = config_content .. "\n#endif // BASE64_CONFIG_H\n"
        io.writefile("config.h", config_content)

        -- 创建 xmake.lua
        local xmake_content = string.format([[
            add_rules("mode.debug", "mode.release")
            
            target("base64")
                set_kind("%s")
                set_languages("c99")
                
                -- 基础源文件
                add_files("lib/lib.c")
                add_files("lib/codec_choose.c")
                add_files("lib/tables/tables.c")
                add_files("lib/arch/generic/codec.c")
                
                -- SIMD 支持
                if is_arch("x86", "x64", "x86_64") then
                    add_files("lib/arch/ssse3/codec.c")
                    add_files("lib/arch/sse41/codec.c")
                    add_files("lib/arch/sse42/codec.c")
                    add_files("lib/arch/avx/codec.c")
                    add_files("lib/arch/avx2/codec.c")
                    add_files("lib/arch/avx512/codec.c")
                elseif is_arch("arm", "arm64", "arm64-v8a") then
                    if is_arch("arm") then
                        add_files("lib/arch/neon32/codec.c")
                    else
                        add_files("lib/arch/neon64/codec.c")
                    end
                end
                
                add_includedirs("include")
                add_includedirs(".")
                
                if is_plat("windows") then
                    add_defines("_SCL_SECURE_NO_WARNINGS")
                    set_runtimes("%s")
                    if not is_kind("shared") then
                        add_defines("BASE64_STATIC_DEFINE")
                    end
                end
                
                add_headerfiles("include/*.h")
        ]], package:config("shared") and "shared" or "static",
            package:config("runtimes") or "MD")
        
        io.writefile("xmake.lua", xmake_content)

        -- 构建配置
        local configs = {}
        if package:is_plat("windows") then
            configs.shared = package:config("shared")
            configs.runtimes = package:config("runtimes")
        end

        import("package.tools.xmake").install(package, configs)
        
        -- 安装头文件
        os.cp("include/*.h", package:installdir("include"))
    end)

    on_test(function (package)
        assert(package:has_cfuncs("base64_encode", {includes = "libbase64.h"}))
    end)


target("js_engine")
    set_kind("shared")
    set_version("0.0.1")
    add_cxflags("/utf-8")
    add_defines("UNICODE")
    add_files("src/**.cc")
    add_includedirs("src")
    set_languages("cxx20")
    set_symbols("debug")

    set_prefixname("endstone_")
    add_packages("endstone", "fmt", "expected-lite")

    add_defines(
        "SCRIPTX_BACKEND_QUICKJS",
        "SCRIPTX_BACKEND_TRAIT_PREFIX=../third-party/scriptx/backend/QuickJs/trait/Trait"
    )
    add_files(
        "third-party/scriptx/backend/QuickJs/**.cc",
        "third-party/scriptx/src/**.cc"
    )
    add_includedirs(
        "third-party/scriptx/src/include",
        "third-party/quickjs/include"
    )
    add_links("third-party/quickjs/lib/quickjs.lib")

    if is_mode("debug") then
        add_defines("DEBUG")
    end

    after_build(function (target)
        local bin = path.join(os.projectdir(), "bin")
    end)


