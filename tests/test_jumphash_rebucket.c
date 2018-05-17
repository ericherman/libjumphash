/*
test_jumphash_rebucket: shows that jumphash is consistent
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
#include <stdio.h>
#include <stdlib.h>
#include <jumphash.h>

#define THRESHOLD 0.0001

#define atosize_t(x) ((size_t)strtoul(x, NULL, 10))

int main(int argc, char **argv)
{
	size_t from_buckets, to_buckets, stayed, moved;
	int verbose, fail;
	size_t key, first_key, num_keys;
	int32_t first, next;
	double ratio, ideal, diff;

	from_buckets = argc > 1 ? atosize_t(argv[1]) : 4;
	to_buckets = argc > 2 ? atosize_t(argv[2]) : from_buckets + 1;
	verbose = argc > 3 ? atoi(argv[3]) : 0;
	num_keys = argc > 4 ? atosize_t(argv[4]) : 10 * 1000 * 1000;
	first_key = argc > 5 ? atosize_t(argv[5]) : 0;

	if (from_buckets < to_buckets) {
		ideal = ((double)from_buckets) / ((double)to_buckets);
	} else {
		ideal = ((double)to_buckets) / ((double)from_buckets);
	}
	stayed = 0;
	moved = 0;
	for (key = first_key; key < (first_key + num_keys); ++key) {
		first = jumphash(key, from_buckets);
		next = jumphash(key, to_buckets);
		if (first == next) {
			++stayed;
		} else {
			++moved;
		}
	}
	ratio = ((double)stayed) / ((double)(moved + stayed));
	diff = ratio >= ideal ? ratio - ideal : ideal - ratio;
	fail = !(diff < THRESHOLD);

	if (verbose || fail) {
		printf("tested %llu keys (%llu <= %llu)\n",
		       (unsigned long long)num_keys,
		       (unsigned long long)first_key,
		       (unsigned long long)(first_key + num_keys));
		printf("with %llu buckets and %llu buckets\n",
		       (unsigned long long)from_buckets,
		       (unsigned long long)to_buckets);
		printf("%llu stayed in the same bucket, %llu moved buckets\n",
		       (unsigned long long)stayed, (unsigned long long)moved);
		printf("for a ratio of %g, ideal would be %g, diff: %g\n",
		       ratio, ideal, diff);
	}

	if (fail) {
		fprintf(stderr, "FAIL: diff == %g, expected < %g\n", diff,
			THRESHOLD);
		return 1;
	} else if (verbose) {
		printf("PASS\n");
	}

	return 0;
}
