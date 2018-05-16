lib_LTLIBRARIES=libjumphash.la

CSTD_CFLAGS=-std=c89
# DEBUG_CFLAGS=-ggdb -O0 -DDEBUG \
#  -fsanitize=address,leak,undefined
DEBUG_CFLAGS=-ggdb -O3 -DNDEBUG -Wno-unused-parameter -fomit-frame-pointer
NOISY_CFLAGS=-Wall -Wextra -Werror
AM_CFLAGS=\
 -I./src \
 $(CSTD_CFLAGS) \
 $(DEBUG_CFLAGS) \
 $(NOISY_CFLAGS) \
 -pipe

# extracted from https://github.com/torvalds/linux/blob/master/scripts/Lindent
LINDENT=indent -npro -kr -i8 -ts8 -sob -l80 -ss -ncs -cp1 -il0

ACLOCAL_AMFLAGS=-I m4 --install

EXTRA_DIST=COPYING.GPL

check_PROGRAMS=\
 test_jumphash

tidy:
	patch -Np1 -i misc/pre-tidy.patch
	$(LINDENT) \
		-T FILE \
		-T size_t \
		-T int32_t \
		-T uint64_t \
		`find src tests -name '*.h' -o -name '*.c'`
	patch -Rp1 -i misc/pre-tidy.patch

spotless:
	rm -rf `cat .gitignore | sed -e 's/#.*//'`
	pushd src && rm -rf `cat ../.gitignore | sed -e 's/#.*//'`; popd
	pushd tests && rm -rf `cat ../.gitignore | sed -e 's/#.*//'`; popd

test: $(check_PROGRAMS)
	./test_jumphash 1 2 1
	./test_jumphash 2 4 1
	./test_jumphash 3 7 1
	./test_jumphash 4 8 1
	./test_jumphash 5 11 1
	./test_jumphash 6 12 1
	./test_jumphash 7 13 1
	./test_jumphash 8 16 1

valgrind: $(check_PROGRAMS)
	libtool --mode=execute valgrind -q ./test_jumphash


libjumphash_la_SOURCES=src/jumphash.c

include_HEADERS=src/jumphash.h

TESTS=$(check_PROGRAMS)

T_COMMON_SOURCES=\
  $(include_HEADERS)

T_COMMON_LDADD=libjumphash.la

test_jumphash_SOURCES=tests/test_jumphash.c \
 $(T_COMMON_SOURCES)
test_jumphash_LDADD=$(T_COMMON_LDADD)
