#!/bin/bash
ENDSTONE_SDK_PATH="build/_deps/endstone"


echo "[Script] check deps"
python --version
cmake --version
conan --version
ninja --version

echo "[Script] mkdir must floader"
mkdir build
mkdir build/_deps
mkdir $ENDSTONE_SDK_PATH


echo "[Script] Clone endstone repo..."
git clone --depth=1 https://github.com/EndstoneMC/endstone.git $ENDSTONE_SDK_PATH


# 编译项目
echo "[Script] Build with Conan..."
conan install . --output-folder=build --build=missing \
    -s compiler=clang \
    -s compiler.version=15 \
    -s compiler.libcxx=libc++ \
    -s compiler.cppstd=20 \
    -s build_type=RelWithDebInfo \
    -c tools.cmake.cmaketoolchain:generator=Ninja

cd build

echo "[Script] Configure CMake..."
cmake .. \
    -DCMAKE_TOOLCHAIN_FILE=build/RelWithDebInfo/generators/conan_toolchain.cmake \
    -DCMAKE_BUILD_TYPE=RelWithDebInfo \
    -G Ninja

echo "[Script] Build..."
cmake --build . --config RelWithDebInfo


