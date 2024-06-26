/*
libjumphash: A Fast, Minimal Memory, Consistent Hash Algorithm (origin: Google)
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

Much of this code was from 2014 by John Lamping, Eric Veach of Google
https://arxiv.org/pdf/1406.2294v1.pdf
  Google has not applied for patent protection for this algorithm, and,
  as of this writing, has no plans to. Rather, it wishes to contribute
  this algorithm to the community.
*/

#include <jumphash.h>

uint64_t jumphash_lcg_multiplier = 2862933555777941757ULL;

/* essentially a copy-paste from  https://arxiv.org/pdf/1406.2294v1.pdf */
uint32_t jumphash(uint64_t key, uint32_t num_buckets)
{
	uint64_t b = 0;
	uint64_t j = 0;

	while (j < num_buckets) {
		b = j;
		key = key * jumphash_lcg_multiplier + 1;
		j = (b + 1) * ((double)(1LL << 31) / (double)((key >> 33) + 1));
	}
	return ((uint32_t) b);
}
