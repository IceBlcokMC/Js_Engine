add_rules("mode.debug", "mode.release")

add_repositories("levilamina https://github.com/LiteLDev/xmake-repo.git")
package("endstone")
    set_kind("library", {headeronly = true})
    set_homepage("https://github.com/EndstoneMC/endstone")
    set_description("Endstone - High-level Plugin API for Bedrock Dedicated Servers (BDS), in both Python and C++")
    set_license("Apache-2.0")

    add_urls("https://github.com/EndstoneMC/endstone/archive/refs/tags/$(version).tar.gz","https://github.com/EndstoneMC/endstone.git")
    add_versions("v0.5.6","b6a78473aef733d02aa99fe960ea3ffee6e52486")
    add_patches("v0.5.6", "https://github.com/engsr6982/Js_Engine/raw/refs/heads/develop/patch/cxx20.patch",
                        "547ae3d325b8deb68747179b6bc3aa8772ba4efe36263bf31f34be7a3aac2ceb")
    on_install("windows", "linux", function (package)
        os.cp("include", package:installdir())
    end)
package_end()
add_requires(
    "fmt >=10.0.0 <11.0.0",
    "expected-lite 0.8.0",
    "entt 3.14.0",
    "microsoft-gsl 4.0.0",
    "nlohmann_json 3.11.3",
    "boost 1.85.0",
    "glm 1.0.1",
    "concurrentqueue 1.0.4",
    "endstone v0.5.6"
)
add_requires("magic_enum 0.9.7")

if not has_config("vs_runtime") then
    set_runtimes("MD")
end

target("Js_Engine")
    add_cxflags(
        "/EHa",
        "/utf-8",
        -- "/W4", -- 开启警告
        "/sdl"
    )
    add_defines(
        "NOMINMAX",
        "UNICODE",
        "_AMD64_"
    )
    add_files("src/**.cc")
    add_includedirs("src")
    add_packages(
        "fmt",
        "expected-lite",
        "entt",
        "microsoft-gsl",
        "nlohmann_json",
        "boost",
        "glm",
        "concurrentqueue",
        "endstone"
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
    elseif is_plat("linux") then
        -- TODO: Build QuickJs for Linux
    end 


    if is_mode("debug") then
        add_defines("DEBUG")
    end

    set_basename("js_engine")
    after_build(function(target)
        local output_dir = path.join(os.projectdir(), "bin")

        os.cp(target:targetfile(), path.join(output_dir, target:name() .. ".dll"))

        os.cp(path.join(os.projectdir(), "types"), path.join(os.projectdir(), "bin", "js_engine", "dts"))

        local pdb_path = path.join(output_dir, target:name() .. ".pdb")
        if os.isfile(target:symbolfile()) then 
            os.cp(target:symbolfile(), pdb_path) 
        end

        cprint("${bright green}[plugin Packer]: ${reset}plugin already generated to " .. output_dir)
    end)