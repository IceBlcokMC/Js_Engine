add_rules("mode.debug", "mode.release")

add_repositories("levilamina https://github.com/LiteLDev/xmake-repo.git")
add_repositories("iceblcokmc https://github.com/IceBlcokMC/xmake-repo.git")

add_requires("nodejs 23.5.0") -- iceblockmc
add_requires(
    "endstone 0.5.7.1",
    "expected-lite 0.8.0",
    "entt 3.14.0",
    "microsoft-gsl 4.0.0",
    "nlohmann_json 3.11.3",
    "boost 1.85.0",
    "glm 1.0.1",
    "concurrentqueue 1.0.4",
    "magic_enum 0.9.7"
)

local fmt_version = "fmt >=10.0.0 <11.0.0";
if is_plat("windows") then
    add_requires(fmt_version)
elseif is_plat("linux") then
    set_toolchains("clang")
    add_requires("libelf 0.8.13")
    add_requires(fmt_version, {configs = {header_only = true}})
end

if is_plat("windows") then
    if not has_config("vs_runtime") then
        set_runtimes("MD")
    end
end


target("Js_Engine")
    set_license("GPL-3.0")
    add_defines(
        "NOMINMAX",
        "UNICODE",
        "_AMD64_"
    )
    add_files("src/**.cc")
    add_includedirs("src")
    add_packages("nodejs")
    add_packages(
        "fmt",
        "expected-lite",
        "entt",
        "microsoft-gsl",
        "nlohmann_json",
        "boost",
        "glm",
        "concurrentqueue",
        "endstone",
        "magic_enum"
    )
    set_kind("shared")
    set_languages("cxx20")
    set_symbols("debug")
    -- set_exceptions("none")

    -- EndStone Entt
    add_defines("ENTT_SPARSE_PAGE=2048")
    add_defines("ENTT_PACKED_PAGE=128")

    if is_plat("windows") then
        add_cxxflags("/Zc:__cplusplus")
        add_cxflags(
            "/EHa",
            "/utf-8",
            -- "/W4",
            "/sdl"
        )
    elseif is_plat("linux") then
        add_rpathdirs("$ORIGIN/../")
        add_cxflags(
            "-fPIC",
            "-stdlib=libc++",
            "-fdeclspec",
            {force = true}
        )
        add_ldflags(
            "-stdlib=libc++",
            {force = true}
        )
        add_packages("libelf")
        add_syslinks("dl", "pthread", "c++", "c++abi")
    end

    -- ScriptX
    add_includedirs("third-party/scriptx/src/include")
    add_files(
        "third-party/scriptx/src/**.cc",
        "third-party/scriptx/backend/V8/**.cc"
    )
    add_defines(
        "SCRIPTX_BACKEND_V8",
        "SCRIPTX_BACKEND_TRAIT_PREFIX=../third-party/scriptx/backend/V8/trait/Trait"
    )

    if is_mode("debug") then
        add_defines("DEBUG")
    end

    set_basename("js_engine")
    after_build(function(target)
        local output_dir = path.join(os.projectdir(), "bin")
        local ext = ".dll";
        if (is_plat("linux")) then
            ext = ".so";
        end

        os.cp(target:targetfile(), path.join(output_dir, target:basename() .. ext))

        os.cp(path.join(os.projectdir(), "lib/*"), path.join(os.projectdir(), "bin", "js_engine"))

        local pdb_path = path.join(output_dir, target:basename() .. ".pdb")
        if os.isfile(target:symbolfile()) then 
            os.cp(target:symbolfile(), pdb_path) 
        end

        cprint("${bright green}[plugin Packer]: ${reset}plugin already generated to " .. output_dir)
    end)