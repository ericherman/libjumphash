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
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <jumphash.h>

#define atosize_t(x) ((size_t)strtoul(x, NULL, 10))
#define atou64(x) ((uint64_t)strtoull(x, NULL, 10))

int test_jumphash_rebucket(size_t from_buckets, size_t to_buckets,
			   size_t num_keys, size_t first_key, int verbose,
			   uint64_t lcg_multiplier, double threshold)
{
	double ratio, ideal, diff;
	size_t key, stayed, moved;
	uint32_t first, next;
	uint64_t orig_lcg_multiplier;
	int fail;

	if (lcg_multiplier) {
		orig_lcg_multiplier = jumphash_lcg_multiplier;
		jumphash_lcg_multiplier = lcg_multiplier;
	}

	if (from_buckets < to_buckets) {
		ideal = ((double)from_buckets) / ((double)to_buckets);
	} else {
		ideal = ((double)to_buckets) / ((double)from_buckets);
	}
	fail = 0;
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
	fail = !(diff < threshold);

	if (verbose || fail) {
		printf("tested %zu keys (%zu <= %zu)\n",
		       num_keys, first_key, (first_key + num_keys));
		printf("with %zu buckets and %zu buckets\n",
		       from_buckets, to_buckets);
		printf(" (using LCG multiplier: %" PRIu64 ")\n",
		       jumphash_lcg_multiplier);
		printf("%zu stayed in the same bucket, %zu moved buckets\n",
		       stayed, moved);
		printf("for a ratio of %g, ideal would be %g, diff: %g\n",
		       ratio, ideal, diff);
	}

	if (fail) {
		fprintf(stderr, "FAIL: diff == %g, expected < %g\n", diff,
			threshold);
	} else if (verbose) {
		printf("PASS\n");
	}

	if (lcg_multiplier) {
		jumphash_lcg_multiplier = orig_lcg_multiplier;
	}
	return fail;
}

int main(int argc, char **argv)
{
	size_t from_buckets = argc > 1 ? atosize_t(argv[1]) : 0;
	size_t to_buckets = argc > 2 ? atosize_t(argv[2]) : 0;
	int verbose = argc > 3 ? atoi(argv[3]) : 0;
	size_t num_keys = argc > 4 ? atosize_t(argv[4]) : 0;
	size_t first_key = argc > 5 ? atosize_t(argv[5]) : 0;
	uint64_t lcg_multiplier = argc > 6 ? atosize_t(argv[6]) : 0;
	double threshold = argc > 7 ? atof(argv[7]) : 0.0;
	int fails = 0;

	from_buckets = from_buckets ? from_buckets : 4;
	to_buckets = to_buckets ? to_buckets : from_buckets + 1;
	num_keys = num_keys ? num_keys : 10 * 1000 * 1000;
	threshold = threshold > 0.0 ? threshold : 0.0001;

	fails +=
	    test_jumphash_rebucket(from_buckets, to_buckets, num_keys,
				   first_key, verbose, lcg_multiplier,
				   threshold);

	return fails ? 1 : 0;
}
