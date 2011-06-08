#!/bin/sh
# SDL 1.2

if [ -f Makefile ]; then
  make clean
fi

./autogen.sh

## Configure the build.
AR="ppu-ar" \
CC="ppu-gcc" \
CFLAGS="-O2 -Wall -I$PSL1GHT/ppu/include -I$PS3DEV/portlibs/ppu/include" \
LDFLAGS="-L$PSL1GHT/ppu/lib -L$PS3DEV/portlibs/ppu/lib -lrt -llv2" \
RANLIB="ppu-ranlib" \
PKG_CONFIG_PATH="$PS3DEV/portlibs/ppu/lib/pkgconfig" \
./configure \
  --prefix="$PS3DEV/portlibs/ppu" \
  --host=ppu-pls1ght \
  --includedir="$PS3DEV/portlibs/ppu/include" \
  --libdir="$PS3DEV/portlibs/ppu/lib" \
  --enable-atomic=yes \
  --enable-video-psl1ght=yes \
  --enable-joystick=yes \
  --enable-audio=yes \
  || { exit 1; }

## Compile and install.
#make -j4 && make install || { exit 1; }

