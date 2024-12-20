LLVM_VERSION=15

sudo apt-get -y update
sudo apt-get -y upgrade

echo "[Script] Install LLVM、Clang、libc++"
sudo apt-get update -y -q
sudo apt-get install -y -q lsb-release wget software-properties-common gnupg
sudo wget https://apt.llvm.org/llvm.sh
sudo chmod +x llvm.sh
sudo ./llvm.sh $LLVM_VERSION
sudo apt-get install -y -q libc++-$LLVM_VERSION-dev libc++abi-$LLVM_VERSION-dev
sudo update-alternatives --install /usr/bin/cc cc /usr/bin/clang-$LLVM_VERSION 100
sudo update-alternatives --install /usr/bin/c++ c++ /usr/bin/clang++-$LLVM_VERSION 100
sudo update-alternatives --install /usr/bin/clang clang /usr/bin/clang-$LLVM_VERSION 100
sudo update-alternatives --install /usr/bin/clang++ clang++ /usr/bin/clang++-$LLVM_VERSION 100
sudo update-alternatives --install /usr/bin/llvm-cov llvm-cov /usr/bin/llvm-cov-$LLVM_VERSION 100
sudo update-alternatives --install /usr/bin/ld ld /usr/bin/ld.lld-$LLVM_VERSION 100

echo "[Script] Install git"
sudo apt install -y git

echo "[Script] Install Python3.11 with pip"
sudo add-apt-repository ppa:deadsnakes/ppa
sudo apt install python3.11
sudo python3.11 --version
sudo apt install python3.11-full
sudo apt install python3-pip
which python3.11
sudo update-alternatives --install /usr/bin/python python /usr/bin/python3.11 9
sudo update-alternatives --config python
python --version
