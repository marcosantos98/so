set -e

BIN_UTILS=2.39
GCC=12.2.0

mkdir -p toolchain
mkdir -p toolchain/cross
mkdir -p toolchain/build/
mkdir -p toolchain/build/binutils
mkdir -p toolchain/build/gcc

wget https://ftp.gnu.org/gnu/binutils/binutils-$BIN_UTILS.tar.xz -O ./toolchain/build/binutils-$BIN_UTILS.tar.xz
wget https://ftp.gnu.org/gnu/gcc/gcc-12.2.0/gcc-$GCC.tar.xz -O ./toolchain/build/gcc-$GCC.tar.xz

export PREFIX="$PWD/toolchain/cross"
export TARGET=i686-elf
export PATH="$PREFIX/bin:$PATH"

cd toolchain/build

tar xf binutils-$BIN_UTILS.tar.xz
tar xf gcc-$GCC.tar.xz

cd binutils
../binutils-$BIN_UTILS/configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror
make -j 4
echo "Install Bin Utils"
sudo make install

which -- $TARGET-as || echo $TARGET-as is not in the PATH

cd ../gcc
../gcc-$GCC/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers
make all-gcc
make all-target-libgcc
echo "Install GCC"
sudo make install-gcc
sudo make install-target-libgcc

cd ..
cd ..
cd ..

