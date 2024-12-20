cd ..

git clone --dept=1 https://github.com/EndstoneMC/endstone.git build/_deps/endstone-src

cd build/_deps/endstone-src

git apply ../../../patch/cxx20.patch

pause