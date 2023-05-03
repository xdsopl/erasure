/*
Cauchy Reed Solomon Erasure Coding

Copyright 2023 Ahmet Inan <xdsopl@gmail.com>
*/

#pragma once

#include "gf16.h"

static inline int gf16_cauchy_matrix(int i, int j)
{
	int row = i, col = 15 - j;
	return gf16_inv(gf16_add(row, col));
}

static inline int gf16_inverse_cauchy_matrix(const int *rows, int i, int j, int n)
{
	int col_i = 15 - i;
	int prod_xy = 1, prod_x = 1, prod_y = 1;
	for (int k = 0; k < n; k++) {
		int col_k = 15 - k;
		prod_xy = gf16_mul(prod_xy, gf16_mul(gf16_add(rows[j], col_k), gf16_add(rows[k], col_i)));
		if (k != j)
			prod_x = gf16_mul(prod_x, gf16_add(rows[j], rows[k]));
		if (k != i)
			prod_y = gf16_mul(prod_y, gf16_add(col_i, col_k));
	}
	return gf16_div(prod_xy, gf16_mul(gf16_mul(gf16_add(rows[j], col_i), prod_x), prod_y));
}

static inline void gf16_crs_encode16(const uint8_t *data, uint8_t *block, int number, int count)
{
	for (int k = 0; k < count; k++) {
		int a_ik = gf16_cauchy_matrix(number, k);
		if (k)
			gf16_mac16(block, data + 16 * k, a_ik);
		else
			gf16_mul16(block, data + 16 * k, a_ik);
	}
}

static inline void gf16_crs_decode16(uint8_t *data, const uint8_t *blocks, const int *numbers, int index, int count)
{
	for (int k = 0; k < count; k++) {
		int b_ik = gf16_inverse_cauchy_matrix(numbers, index, k, count);
		if (k)
			gf16_mac16(data, blocks + 16 * k, b_ik);
		else
			gf16_mul16(data, blocks + 16 * k, b_ik);
	}
}

