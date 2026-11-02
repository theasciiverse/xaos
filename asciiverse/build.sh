#!/bin/sh
# Builds XaoS with its text-mode driver (AAlib on curses) as ./xaos.
#
# Upstream's configure looks for a system AAlib and wants gettext; here
# everything the program needs is built from source into av-build/ and
# linked in statically, so one script serves every target:
#   - zlib and libpng, for saving images and rendering animations
#   - GSL, whose complex functions the user formula parser (sffe) uses
#   - AAlib from aalib/ (1.4rc5 with Debian's patches), compiled with only
#     its curses drivers, from asciiverse/include/aalib/config.h
# XaoS itself is compiled the same way, from asciiverse/include/xaos/
# (aconfig.h and version.h in place of configure's), text driver only and
# without gettext (its menus are English; the tutorials keep their own
# translations in catalogs/).
#
#   docker run --rm -v "$PWD":/src -w /src alpine:3.22 sh asciiverse/build.sh
#       Linux: static musl, needs nothing on the system but terminfo
#   CC_ARCH=arm64 sh asciiverse/build.sh     (or x86_64)
#       macOS, on the runner: the system's ncurses
set -eu
ZLIB=1.3.2
LIBPNG=1.6.59
GSL=2.8
GSL_SHA256=6a99eeed15632c6354895b1dd542ed5a855c0f15d9ad1326c6fe2b2c9e423190

if [ -f /etc/alpine-release ] && [ "$(id -u)" = 0 ]; then
  apk add --no-cache build-base curl git ncurses-dev ncurses-static >/dev/null
fi

root=$(cd "$(dirname "$0")/.." && pwd)
deps="$root/av-build"
prefix="$deps/prefix"
mkdir -p "$deps" "$prefix"
jobs=$(getconf _NPROCESSORS_ONLN 2>/dev/null || echo 4)
cflags="-O2${CC_ARCH:+ -arch $CC_ARCH}"
host=""
if [ "$(uname)" = Darwin ]; then
  case "${CC_ARCH:-$(uname -m)}" in
    arm64) host=aarch64-apple-darwin ;;
    *) host=x86_64-apple-darwin ;;
  esac
fi

if [ ! -f "$prefix/lib/libz.a" ]; then
  [ -d "$deps/zlib" ] || git clone -q --depth 1 -b "v$ZLIB" https://github.com/madler/zlib "$deps/zlib"
  (cd "$deps/zlib" && CFLAGS="$cflags" ./configure --static --prefix="$prefix" >/dev/null &&
     make -j "$jobs" >/dev/null && make install >/dev/null)
fi

if [ ! -f "$prefix/lib/libpng.a" ]; then
  [ -d "$deps/libpng" ] || git clone -q --depth 1 -b "v$LIBPNG" https://github.com/pnggroup/libpng "$deps/libpng"
  (cd "$deps/libpng" && CFLAGS="$cflags" CPPFLAGS="-I$prefix/include" LDFLAGS="-L$prefix/lib" \
     ./configure --disable-shared --prefix="$prefix" ${host:+--host=$host} >/dev/null &&
     make -j "$jobs" >/dev/null && make install >/dev/null)
fi

if [ ! -f "$prefix/lib/libgsl.a" ]; then
  if [ ! -d "$deps/gsl-$GSL" ]; then
    curl -sfL -o "$deps/gsl.tar.gz" "https://ftp.gnu.org/gnu/gsl/gsl-$GSL.tar.gz"
    if command -v sha256sum >/dev/null; then sum=$(sha256sum "$deps/gsl.tar.gz"); else sum=$(shasum -a 256 "$deps/gsl.tar.gz"); fi
    [ "${sum%% *}" = "$GSL_SHA256" ] || { echo "gsl-$GSL.tar.gz: wrong sha256" >&2; exit 1; }
    tar -xzf "$deps/gsl.tar.gz" -C "$deps"
  fi
  (cd "$deps/gsl-$GSL" && CFLAGS="$cflags" ./configure --disable-shared --prefix="$prefix" \
     ${host:+--host=$host} >/dev/null && make -j "$jobs" >/dev/null && make install >/dev/null)
fi

if [ "$(uname)" = Darwin ]; then
  curses="-lncurses"
else
  curses="-lncursesw"
fi

# AAlib: the library's sources minus the drivers for X11, S-Lang, GPM, the
# Linux console, DOS and OS/2
if [ ! -f "$prefix/lib/libaa.a" ] || [ -n "$(find "$root/aalib/src" "$root/asciiverse/include/aalib" -newer "$prefix/lib/libaa.a" -type f)" ]; then
  rm -rf "$deps/aalib-obj" && mkdir -p "$deps/aalib-obj"
  for f in aafont aafonts aavyhen aamktabl aamem aaprintf aahelp aafastre fontgl font16 \
           font14 fontx16 fontx13 fontx13b fontcour aarec font9 font8 fontline aacurses \
           aacurkbd aacurmou aalib aaflush aarender aaout aain aaedit aaregist aakbdreg \
           aamoureg aasave aastdout aastdin aaparse aaimgwidth aaimgheight aascrwidth \
           aascrheight aammwidth aammheight aaimage aatext aacurrfnt aaattrs aaputpixel \
           aarecfunc; do
    # shellcheck disable=SC2086
    cc $cflags -w -I"$root/asciiverse/include/aalib" -I"$root/asciiverse/include/compat" \
      -I"$root/aalib/src" -c "$root/aalib/src/$f.c" -o "$deps/aalib-obj/$f.o"
  done
  rm -f "$prefix/lib/libaa.a"
  ar rc "$prefix/lib/libaa.a" "$deps"/aalib-obj/*.o
  ranlib "$prefix/lib/libaa.a"
  mkdir -p "$prefix/include"
  cp "$root/aalib/src/aalib.h" "$prefix/include/"
fi

cd "$root/src"
srcs="
  engine/formulas.c engine/fractal.c engine/btrace.c engine/palettef.c engine/emboss.c
  engine/star.c engine/anti.c engine/dither.c engine/edge.c engine/edge2.c engine/rotate.c
  engine/zoom.c engine/blur.c engine/interlace.c engine/itersmall.c engine/stereogram.c
  engine/3d.c engine/subwindow.c engine/plane.c engine/julia.c engine/i386.c
  filter/image.c filter/palette.c filter/random.c filter/grlib.c filter/font.c filter/filter.c
  ui/drivers.c ui/ui.c ui/uihelp.c ui/param.c ui/fparams.c ui/filesel.c ui/uimenu.c
  ui/pipecmd.c ui/dialog.c
  ui-hlp/autopilot.c ui-hlp/ui_helper.c ui-hlp/menu.c ui-hlp/play.c ui-hlp/messg.c
  ui-hlp/render.c ui-hlp/playtext.c ui-hlp/save.c ui-hlp/wstack.c
  util/png.c util/catalog.c util/thread.c util/xstring.c util/help.c util/xerror.c
  util/xshl.c util/xldio.c util/xstdio.c util/xmenu.c util/timers.c
  sffe/sffe.c sffe/sffe_cmplx_gsl.c
  ui/ui-drv/aa/ui_aa.c"
static=""
[ "$(uname)" = Darwin ] || static="-static"
rm -f "$root/xaos"
# shellcheck disable=SC2086
cc $cflags -fomit-frame-pointer -w -DSFFE_USING -DSFFE_CMPLX_GSL \
  -I"$root/asciiverse/include/xaos" -I"$root/asciiverse/include/compat" -Iinclude \
  -I"$prefix/include" $srcs $static -L"$prefix/lib" -laa $curses -lgsl -lpng -lz -lm \
  -o "$root/xaos"
strip "$root/xaos"
echo "built xaos"
