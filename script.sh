#!/bin/sh
# zlib-1.2.5.sh by Dan Peori (danpeori@oopo.net)
#newlib doesn't define endian.h that is needed by SDL

if [ ! -f $PS3DEV/ppu/ppu/include/machine/endian.h ]; then
  cat > $PS3DEV/ppu/ppu/include/machine/endian.h << EOF
#ifndef __MACHINE_ENDIAN_H__

#include <sys/config.h>

#ifndef BIG_ENDIAN
#define BIG_ENDIAN 4321
#endif
#ifndef LITTLE_ENDIAN
#define LITTLE_ENDIAN 1234
#endif

#ifndef BYTE_ORDER
#if defined(__IEEE_LITTLE_ENDIAN) || defined(__IEEE_BYTES_LITTLE_ENDIAN)
#define BYTE_ORDER LITTLE_ENDIAN
#else
#define BYTE_ORDER BIG_ENDIAN
#endif
#endif

#endif /* __MACHINE_ENDIAN_H__ */
EOF
fi

if [ -f Makefile ]; then
  make clean
fi

./autogen.sh

## Configure the build.
AR="ppu-ar" \
CC="ppu-gcc" \
RANLIB="ppu-ranlib" \
CFLAGS="-O2 -Wall -I$PSL1GHT/ppu/include -I$PS3DEV/portlibs/ppu/include" \
LDFLAGS="-L$PSL1GHT/ppu/lib -L$PS3DEV/portlibs/ppu/lib -lrt -llv2" \
PKG_CONFIG_PATH="$PS3DEV/portlibs/ppu/lib/pkgconfig" \
./configure \
  --prefix="$PS3DEV/portlibs/ppu" \
  --host=ppu \
  --includedir="$PS3DEV/portlibs/ppu/include" \
  --libdir="$PS3DEV/portlibs/ppu/lib" \
  --enable-atomic=yes \
  --enable-video-psl1ght=yes \
  --enable-joystick=yes \
  --enable-audio=yes \
  || { exit 1; }

## Compile and install.
#make -j4 && make install || { exit 1; }

