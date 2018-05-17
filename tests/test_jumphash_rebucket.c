#include <stdio.h>
#include <stdlib.h>
#include <jumphash.h>

#define THRESHOLD 0.0001

int main(int argc, char **argv)
{
	size_t from_buckets, to_buckets, stayed, moved;
	int verbose, fail;
	size_t key, first_key, num_keys;
	int32_t first, next;
	double ratio, ideal, diff;

	from_buckets = argc > 1 ? (size_t)atoi(argv[1]) : 4;
	to_buckets = argc > 2 ? (size_t)atoi(argv[2]) : from_buckets + 1;
	verbose = argc > 3 ? atoi(argv[1]) : 0;
	num_keys = argc > 4 ? (size_t)atoi(argv[4]) : 10 * 1000 * 1000;
	first_key = argc > 5 ? (size_t)atoi(argv[5]) : 0;

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
