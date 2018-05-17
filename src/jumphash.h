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

int32_t jumphash(uint64_t key, int32_t num_buckets);

#ifdef __cplusplus
}
#endif

#endif /* JUMP_HASH_H */
