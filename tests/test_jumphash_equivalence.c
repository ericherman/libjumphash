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

static int check_jumphash(int32_t expected, uint64_t key, int32_t num_buckets)
{
	int32_t result;

	result = jumphash(key, num_buckets);

	if (expected == result) {
		return 0;
	}

	fprintf(stderr, "FAIL: jumphash(%lu, %ld). Expected %ld but was %ld\n",
		(unsigned long)key, (long)num_buckets, (long)expected,
		(long)result);

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
		fail += check_jumphash(golden100[i], i, 100);
	}
	fail += check_jumphash(6, 10863919174838991L, 11);
	fail += check_jumphash(3, 2016238256797177309L, 11);
	fail += check_jumphash(5, 1673758223894951030L, 11);
	fail += check_jumphash(80343, 2, 100001);
	fail += check_jumphash(22152, 2201, 100001);
	fail += check_jumphash(15018, 2202, 100001);

	return fail ? 1 : 0;
}
