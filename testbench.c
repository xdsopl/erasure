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
	int len = 16;
	if (k < 0 || m < 0 || 2 * k + m > len)
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
	int bytes = len * k;
	uint8_t orig[bytes];
	for (int i = 0; i < bytes; i++)
		orig[i] = rand() % 256;
	clock_t time_a = clock();
	uint8_t blocks[bytes];
	for (int i = 0; i < k; i++)
		gf16_crs_encode16(orig, blocks + i * len, numbers[i], k);
	clock_t time_b = clock();
	uint8_t data[bytes];
	for (int i = 0; i < k; i++)
		gf16_crs_decode16(data + i * len, blocks, numbers, i, k);
	clock_t time_c = clock();
	double us_enc = (time_b - time_a) / (CLOCKS_PER_SEC / 1000000.0);
	double us_dec = (time_c - time_b) / (CLOCKS_PER_SEC / 1000000.0);
	fprintf(stderr, "encoding time: %f us\n", us_enc);
	fprintf(stderr, "decoding time: %f us\n", us_dec);
	for (int i = 0; i < bytes; i++)
		assert(data[i] == orig[i]);
	return 0;
}

