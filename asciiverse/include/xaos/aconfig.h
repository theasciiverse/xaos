/* XaoS's aconfig.h for the Asciiverse build (asciiverse/build.sh), written
   by hand in place of configure's: the text-mode (AAlib) driver only, for
   Linux (musl or glibc) and macOS. */
#define AA_DRIVER 1
/* not a real folder: the data is found next to the binary ("\01" paths in
   src/util/xstdio.c), wherever the archive or package puts it */
#define DATAPATH "/nonexistent/XaoS"
#define HAVE_ALLOCA 1
#define HAVE_ALLOCA_H 1
#define HAVE_DIRENT_H 1
#define HAVE_ERRNO_H 1
#define HAVE_FABSL 1
#define HAVE_FCNTL_H 1
#define HAVE_FINITE 1
#define HAVE_FLOAT_H 1
#define HAVE_GETCWD 1
#define HAVE_GETTIMEOFDAY 1
#define HAVE_INTTYPES_H 1
#define HAVE_LIBAA 1
#define HAVE_LIBGEN_H 1
#define HAVE_LIBM 1
#define HAVE_LIBPNG 1
#define HAVE_LIBZ 1
#define HAVE_LIMITS_H 1
#define HAVE_LOCALE_H 1
#define HAVE_LONG_DOUBLE 1
#define HAVE_MEMCHR 1
#define HAVE_MEMMOVE 1
#define HAVE_MEMORY_H 1
#define HAVE_MEMSET 1
#define HAVE_POW 1
#define HAVE_SELECT 1
#define HAVE_SETITIMER 1
#define HAVE_SETLOCALE 1
#define HAVE_SLEEP 1
#define HAVE_SQRT 1
#define HAVE_STDDEF_H 1
#define HAVE_STDINT_H 1
#define HAVE_STDLIB_H 1
#define HAVE_STRDUP 1
#define HAVE_STRERROR 1
#define HAVE_STRINGS_H 1
#define HAVE_STRING_H 1
#define HAVE_STRSTR 1
#define HAVE_SYS_STAT_H 1
#define HAVE_SYS_TIME_H 1
#define HAVE_SYS_TYPES_H 1
#define HAVE_SYS_WAIT_H 1
#define HAVE_UNISTD_H 1
#define PACKAGE_BUGREPORT "xaos-devel@lists.sourceforge.net"
#define PACKAGE_NAME "XaoS"
#define PACKAGE_STRING "XaoS 3.7"
#define PACKAGE_TARNAME "xaos"
#define PACKAGE_URL ""
#define SIZEOF_INT 4
#ifdef __LP64__
#define SIZEOF_LONG 8
#else
#define SIZEOF_LONG 4
#endif
#define SIZEOF_SHORT 2
#define STDC_HEADERS 1
#define TIME_WITH_SYS_TIME 1
#define USE_PNG 1
