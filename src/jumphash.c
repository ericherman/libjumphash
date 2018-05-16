/* essentially a copy-paste from  https://arxiv.org/pdf/1406.2294v1.pdf */
int32_t JumpConsistentHash(uint64_t key, int32_t num_buckets)
{
	int64_t b = -1, j = 0;

	while (j < num_buckets) {
		b = j;
		key = key * 2862933555777941757ULL + 1;
		j = (b + 1) * (double(1LL << 31) / double((key >> 33) + 1));
	}
	return b;
}
