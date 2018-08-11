/*
test_jumphash_equivalence: shows that jumphash is same as others
Copyright (C) 2018 Eric Herman <eric@freesa.org>

This work is free software: you can redistribute it and/or modify it
under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 2.1 of the License, or (at
your option) any later version.

This work is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
License for more details.

	https://www.gnu.org/licenses/old-licenses/lgpl-2.1.txt
*/

/*
   See Also:
   https://github.com/google/guava/blob/master/guava-tests/test/com/google/common/hash/HashingTest.java#L230
   https://github.com/dgryski/go-jump/blob/master/jump_test.go#L30
*/

#include <stdio.h>
#include <jumphash.h>

#define assert_equals(expected, actual) \
	fl_assert_long_eq(__FILE__, __LINE__, expected, actual)

static int fl_assert_long_eq(const char *file, int line, uint32_t expected,
			     uint32_t actual)
{
	if (expected == actual) {
		return 0;
	}

	fprintf(stderr, "FAIL: Expected %ld but was %ld [%s:%d]\n",
		(long)expected, (long)actual, file, line);

	return 1;
}

int main(void)
{
	size_t i, fail;

	int golden100[] = {
		0, 55, 62, 8, 45, 59, 86, 97, 82, 59,
		73, 37, 17, 56, 86, 21, 90, 37, 38, 83
	};
	size_t golden100_len = 20;

	fail = 0;
	for (i = 0; i < golden100_len; ++i) {
		fail += assert_equals(golden100[i], jumphash(i, 100));
	}
	fail += assert_equals(6, jumphash(10863919174838991L, 11));
	fail += assert_equals(3, jumphash(2016238256797177309L, 11));
	fail += assert_equals(5, jumphash(1673758223894951030L, 11));
	fail += assert_equals(80343, jumphash(2, 100001));
	fail += assert_equals(22152, jumphash(2201, 100001));
	fail += assert_equals(15018, jumphash(2202, 100001));

	return fail ? 1 : 0;
}
