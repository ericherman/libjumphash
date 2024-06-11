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
*/
/*
   A Fast, Minimal Memory, Consistent Hash Algorithm
   John Lamping, Eric Veach
   Google

   https://arxiv.org/pdf/1406.2294v1.pdf
*/
#ifndef JUMP_HASH_H
#define JUMP_HASH_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/* returns the bucket number for this key */
uint32_t jumphash(uint64_t key, uint32_t num_buckets);

/*
The "jumphash" consistent hashing described by Lamping & Veach is a special
case of a A 64-bit Linear Congruential Generator. An LCG is a type of
pseudorandom number generator which is extremely simple and consists of a
seed, a multiplier, and an increment (often 1). With a well chosen value of
the multiplier, very good randomness is achieved regardless of seed, in spite
of the simplicity of the formula. See "The Art of Computer Programming,
Volume 2: Seminumerical Algorithms", by Knuth.

Empirical Testing shows that both the widely recommended value
6364136223846793005ULL (used in Knuth's MMIX) and the less common value
2862933555777941757ULL (used in some Java libraries and the jumphash paper)
generate sequences with long periods and multi-dimensional uniformity.
See also: https://web.archive.org/web/20181118052646/http://random.mat.sbg.ac.at/results/karl/server/node5.html

The jumphash_lcg_multiplier defaults to 2862933555777941757ULL
*/
extern uint64_t jumphash_lcg_multiplier;

#ifdef __cplusplus
}
#endif

#endif /* JUMP_HASH_H */
