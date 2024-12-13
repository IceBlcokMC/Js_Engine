add_rules("mode.debug", "mode.release")

add_repositories("levilamina https://github.com/LiteLDev/xmake-repo.git")

add_requires(
    "fmt >=10.0.0 <11.0.0",
    "expected-lite 0.8.0",
    "entt 3.14.0",
    "microsoft-gsl 4.0.0",
    "nlohmann_json 3.11.3",
    "boost 1.85.0",
    "glm 1.0.1",
    "concurrentqueue 1.0.4"
)
add_requires("magic_enum 0.9.7")

if is_plat("windows") then
    if not has_config("vs_runtime") then
        set_runtimes("MD")
    end
end

target("Js_Engine")
    add_defines(
        "NOMINMAX",
        "UNICODE",
        "_AMD64_"
    )
    add_files("src/**.cc")
    add_includedirs(
        "build/_deps/endstone-src/include", -- 使用 CMake 构建拉取的 EndStone
        "src"
    )
    add_packages(
        "fmt",
        "expected-lite",
        "entt",
        "microsoft-gsl",
        "nlohmann_json",
        "boost",
        "glm",
        "concurrentqueue"
    )
    add_packages("magic_enum")
    set_kind("shared")
    set_languages("cxx20")
    set_symbols("debug")
    -- set_exceptions("none") -- 不使用异常处理

    -- EndStone Entt
    add_defines("ENTT_SPARSE_PAGE=2048")
    add_defines("ENTT_PACKED_PAGE=128")

    -- ScriptX & QuickJs
    add_includedirs("third-party/scriptx/src/include")
    add_files(
        "third-party/scriptx/src/**.cc",
        "third-party/scriptx/backend/QuickJs/**.cc"
    )
    add_defines(
        "SCRIPTX_BACKEND_QUICKJS",
        "SCRIPTX_BACKEND_TRAIT_PREFIX=../third-party/scriptx/backend/QuickJs/trait/Trait"
    )

    -- QuickJs & Platform
    if is_plat("windows") then
        add_includedirs("./third-party/quickjs/win/include")
        add_links("./third-party/quickjs/win/lib/quickjs.lib")

        add_cxflags(
            "/EHa",
            "/utf-8",
            -- "/W4", -- 开启警告
            "/sdl"
        )
    elseif is_plat("linux") then
        add_includedirs("./third-party/quickjs/linux/include")
        add_links("./third-party/quickjs/linux/lib/quickjs.a")

        add_cxflags(
            "-fPIC",
            "-stdlib=libc++",
            "-std=c++20"
        )
        add_ldflags(
            "-stdlib=libc++"
        )
        add_links("c++", "c++abi")
    else 
        printf("${bright red}Platform %s is not supported", os.host())
    end 


    if is_mode("debug") then
        add_defines("DEBUG")
    end

    set_basename("js_engine")
    after_build(function(target)
        local output_dir = path.join(os.projectdir(), "bin")

        os.cp(target:targetfile(), path.join(output_dir, target:name() .. ".dll"))

        local pdb_path = path.join(output_dir, target:name() .. ".pdb")
        if os.isfile(target:symbolfile()) then 
            os.cp(target:symbolfile(), pdb_path) 
        end

        cprint("${bright green}[plugin Packer]: ${reset}plugin already generated to " .. output_dir)
    end)