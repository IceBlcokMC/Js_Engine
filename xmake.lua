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

target("Js_Engine")
    add_cxflags(
        "/EHs",
        "/utf-8",
        "/W4",
        "/w44265",
        "/w44289",
        "/w44296",
        "/w45263",
        "/w44738",
        "/w45204"
    )
    add_files("src/**.cc")
    add_includedirs(
        "EndStone-SDK/include",
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
    set_kind("shared")
    set_languages("cxx20")
    add_linkdirs("EndStone-SDK/lib")
    set_symbols("debug")

    -- entt EndStone-SDK
    add_defines("ENTT_SPARSE_PAGE=2048")
    add_defines("ENTT_PACKED_PAGE=128")

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
    add_links("ucrt", "vcruntime", "msvcrt", "legacy_stdio_definitions") -- QuickJs C运行时库

    if is_mode("debug") then
        add_defines("DEBUG")
    end

    after_build(function(target)
        local output_dir = path.join(os.projectdir(), "bin")

        -- 清理输出目录
        -- if os.isdir(output_dir) then os.rm(output_dir) end

        -- dll复制
        os.cp(target:targetfile(), path.join(output_dir, target:name() .. ".dll"))

        -- pdb复制
        local pdb_path = path.join(output_dir, target:name() .. ".pdb")
        if os.isfile(target:symbolfile()) then 
            os.cp(target:symbolfile(), pdb_path) 
        end

        -- 输出信息
        cprint("${bright green}[plugin Packer]: ${reset}plugin already generated to " .. output_dir)
    end)