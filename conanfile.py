from conan import ConanFile
from conan.tools.cmake import CMake, CMakeDeps, CMakeToolchain, cmake_layout
from conan.tools.build import check_min_cppstd
from conan.errors import ConanInvalidConfiguration
from conans.model.version import Version

class JsEngineRecipe(ConanFile):
    # generators = "CMakeDeps"
    name = "js_engine"
    version = "1.0.0"
    
    # Binary configuration
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "fPIC": [True, False]}
    default_options = {
        "shared": True,  # DLL需要
        "fPIC": True,
        "boost/*:header_only": True,
    }

    exports_sources = "CMakeLists.txt", "src/*", "third-party/*"

    def validate(self):
        check_min_cppstd(self, "20")
        
        if self.settings.os == "Linux":
            if self.settings.compiler != "clang":
                raise ConanInvalidConfiguration("Linux requires Clang compiler")
            if self.settings.compiler.libcxx != "libc++":
                raise ConanInvalidConfiguration("Linux requires libc++")

    def requirements(self):
        # 添加你用到的依赖
        self.requires("fmt/[~10.0]")
        self.requires("expected-lite/0.8.0")
        self.requires("entt/3.14.0")
        self.requires("ms-gsl/4.0.0")
        self.requires("nlohmann_json/3.11.3")
        self.requires("boost/1.85.0")
        self.requires("glm/1.0.1")
        self.requires("concurrentqueue/1.0.4")
        self.requires("magic_enum/0.9.7")
        
        if self.settings.os == "Linux":
            self.requires("libelf/0.8.13")

    def config_options(self):
        if self.settings.os == "Windows":
            self.options.rm_safe("fPIC")

    def configure(self):
        if self.options.shared:
            self.options.rm_safe("fPIC")

    def source(self):
        # 复制 endstone 头文件到构建目录
        endstone_include = os.path.join(self.source_folder, "build/_deps/endstone/include")
        if os.path.exists(endstone_include):
            self.copy("*", dst="include", src=endstone_include)

    def layout(self):
        cmake_layout(self)
        # 设置构建输出目录为项目目录
        self.cpp.build.bindirs = ["bin"]
        self.cpp.build.libdirs = ["lib"] 
        self.cpp.source.includedirs = ["include"]

    def generate(self):
        tc = CMakeToolchain(self)
        
        # 定义
        tc.preprocessor_definitions["NOMINMAX"] = "1"
        tc.preprocessor_definitions["UNICODE"] = "1"
        tc.preprocessor_definitions["_AMD64_"] = "1"
        tc.preprocessor_definitions["ENTT_SPARSE_PAGE"] = "2048"
        tc.preprocessor_definitions["ENTT_PACKED_PAGE"] = "128"
        tc.preprocessor_definitions["SCRIPTX_BACKEND_QUICKJS"] = "1"
        tc.preprocessor_definitions["SCRIPTX_BACKEND_TRAIT_PREFIX"] = "../third-party/scriptx/backend/QuickJs/trait/Trait"
        
        if self.settings.build_type == "Debug":
            tc.preprocessor_definitions["DEBUG"] = "1"

        # Windows 特定配置
        if self.settings.os == "Windows":
            tc.variables["CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS"] = True
            tc.variables["USE_MSVC_RUNTIME_LIBRARY_DLL"] = True  # MD运行时

        tc.generate()

        deps = CMakeDeps(self)
        deps.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.libs = ["js_engine"]