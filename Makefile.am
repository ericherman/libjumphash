# Makefile.am for building libjumphash
# Copyright (C) 2018 Eric Herman <eric@freesa.org>
#
# This work is free software: you can redistribute it and/or modify it
# under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 2.1 of the License, or (at
# your option) any later version.
#
# This work is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
# FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
# License for more details.
#
#        https://www.gnu.org/licenses/old-licenses/lgpl-2.1.txt

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

EXTRA_DIST=misc

check_PROGRAMS=\
 test_jumphash_rebucket

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
	./test_jumphash_rebucket 1 2 1
	./test_jumphash_rebucket 2 4 1
	./test_jumphash_rebucket 3 7 1
	./test_jumphash_rebucket 4 8 1
	./test_jumphash_rebucket 5 11 1
	./test_jumphash_rebucket 6 12 1
	./test_jumphash_rebucket 7 13 1
	./test_jumphash_rebucket 8 16 1
	./test_jumphash_rebucket 16 8 1
	./test_jumphash_rebucket 5 4 1
	./test_jumphash_rebucket 3 2 1

valgrind: $(check_PROGRAMS)
	libtool --mode=execute valgrind -q ./test_jumphash_rebucket


libjumphash_la_SOURCES=src/jumphash.c

include_HEADERS=src/jumphash.h

TESTS=$(check_PROGRAMS)

T_COMMON_SOURCES=\
  $(include_HEADERS)

T_COMMON_LDADD=libjumphash.la

test_jumphash_rebucket_SOURCES=tests/test_jumphash_rebucket.c \
 $(T_COMMON_SOURCES)
test_jumphash_rebucket_LDADD=$(T_COMMON_LDADD)
