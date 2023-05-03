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
	int nibs = len * k;
	uint8_t orig[nibs];
	for (int i = 0; i < nibs; i++)
		orig[i] = rand() % 16;
	uint8_t blocks[nibs];
	for (int i = 0; i < k; i++)
		gf16_crs_encode16(orig, blocks + i * len, numbers[i], k);
	uint8_t data[nibs];
	for (int i = 0; i < k; i++)
		gf16_crs_decode16(data + i * len, blocks, numbers, i, k);
	for (int i = 0; i < nibs; i++)
		assert(data[i] == orig[i]);
	return 0;
}

