/*
libjumphash: A Fast, Minimal Memory, Consistent Hash Algorithm (origin: Google)
Copyright (C) 2018 Eric Herman <eric@freesa.org>

This work is free software: you can redistribute it and/or modify it
under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or (at
your option) any later version.

This work is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
License for more details.

        https://www.gnu.org/licenses/lgpl-3.0.txt
        https://www.gnu.org/licenses/gpl-3.0.txt

Much of this code was from 2014 by John Lamping, Eric Veach of Google
https://arxiv.org/pdf/1406.2294v1.pdf
  Google has not applied for patent protection for this algorithm, and,
  as of this writing, has no plans to. Rather, it wishes to contribute
  this algorithm to the community.
*/

#include <jumphash.h>

/* see also: http://random.mat.sbg.ac.at/results/karl/server/node5.html */
#define Linear_Congruential_Generator_64 2862933555777941757ULL

/* essentially a copy-paste from  https://arxiv.org/pdf/1406.2294v1.pdf */
int32_t jumphash(uint64_t key, int32_t num_buckets)
{
	int64_t b = -1;
	int64_t j = 0;

	while (j < num_buckets) {
		b = j;
		key = key * Linear_Congruential_Generator_64 + 1;
		j = (b + 1) * ((double)(1LL << 31)) / ((double)(key >> 33) + 1);
	}
	return b;
}
