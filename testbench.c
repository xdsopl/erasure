/*
Testbench for Cauchy Reed Solomon Erasure Coding

Copyright 2023 Ahmet Inan <xdsopl@gmail.com>
*/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include "crs.h"

int main(int argc, char **argv)
{
	if (argc != 3)
		return 1;
	int k = atoi(argv[1]);
	int m = atoi(argv[2]);
	if (k < 0 || m < 0 || 2 * k + m > 16)
		return 1;
	int n = k + m;
	int numbers[n];
	for (int i = 0; i < n; i++)
		numbers[i] = i;
	srand(time(0));
	for (int i = 0; i < n - 1; i++) {
		int j = i + rand() % (n - i);
		int tmp = numbers[i];
		numbers[i] = numbers[j];
		numbers[j] = tmp;
	}
	int size = 4096;
	int bytes = size * k;
	uint8_t orig[bytes] __attribute__((aligned(16)));
	for (int i = 0; i < bytes; i++)
		orig[i] = rand() % 256;
	clock_t time_a = clock();
	uint8_t blocks[bytes] __attribute__((aligned(16)));
	for (int i = 0; i < k; i++)
		gf16_crs_encode(orig, blocks + i * size, numbers[i], k, size);
	clock_t time_b = clock();
	uint8_t data[bytes] __attribute__((aligned(16)));
	for (int i = 0; i < k; i++)
		gf16_crs_decode(data + i * size, blocks, numbers, i, k, size);
	clock_t time_c = clock();
	int bps_enc = ((long long)bytes * CLOCKS_PER_SEC) / (time_b - time_a);
	int bps_dec = ((long long)bytes * CLOCKS_PER_SEC) / (time_c - time_b);
	fprintf(stderr, "encoding speed: %d kilobytes / second\n", bps_enc / 1000);
	fprintf(stderr, "decoding speed: %d kilobytes / second\n", bps_dec / 1000);
	for (int i = 0; i < bytes; i++)
		assert(data[i] == orig[i]);
	return 0;
}

