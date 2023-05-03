/*
GF(2^4) Galois field arithmetic

Copyright 2023 Ahmet Inan <xdsopl@gmail.com>
*/

#pragma once

static inline int gf16_add(int a, int b)
{
	return a ^ b;
}

static const uint8_t gf16_inv_lut[16] __attribute__((aligned(16))) = {
	0, 1, 9, 14, 13, 11, 7, 6, 15, 2, 12, 5, 10, 4, 3, 8,
};

static inline int gf16_inv(int a)
{
	return gf16_inv_lut[a];
}

static const uint8_t gf16_mul_lut[256] __attribute__((aligned(16))) = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
	0, 2, 4, 6, 8, 10, 12, 14, 3, 1, 7, 5, 11, 9, 15, 13,
	0, 3, 6, 5, 12, 15, 10, 9, 11, 8, 13, 14, 7, 4, 1, 2,
	0, 4, 8, 12, 3, 7, 11, 15, 6, 2, 14, 10, 5, 1, 13, 9,
	0, 5, 10, 15, 7, 2, 13, 8, 14, 11, 4, 1, 9, 12, 3, 6,
	0, 6, 12, 10, 11, 13, 7, 1, 5, 3, 9, 15, 14, 8, 2, 4,
	0, 7, 14, 9, 15, 8, 1, 6, 13, 10, 3, 4, 2, 5, 12, 11,
	0, 8, 3, 11, 6, 14, 5, 13, 12, 4, 15, 7, 10, 2, 9, 1,
	0, 9, 1, 8, 2, 11, 3, 10, 4, 13, 5, 12, 6, 15, 7, 14,
	0, 10, 7, 13, 14, 4, 9, 3, 15, 5, 8, 2, 1, 11, 6, 12,
	0, 11, 5, 14, 10, 1, 15, 4, 7, 12, 2, 9, 13, 6, 8, 3,
	0, 12, 11, 7, 5, 9, 14, 2, 10, 6, 1, 13, 15, 3, 4, 8,
	0, 13, 9, 4, 1, 12, 8, 5, 2, 15, 11, 6, 3, 14, 10, 7,
	0, 14, 15, 1, 13, 3, 2, 12, 9, 7, 6, 8, 4, 10, 11, 5,
	0, 15, 13, 2, 9, 6, 4, 11, 1, 14, 12, 3, 8, 7, 5, 10,
};

static inline int gf16_mul(int a, int b)
{
	return gf16_mul_lut[16 * a + b];
}

static inline int gf16_div(int a, int b)
{
	return gf16_mul(a, gf16_inv(b));
}

static inline void gf16_mul16(uint8_t *c, const uint8_t *a, int b)
{
	const uint8_t *lut = gf16_mul_lut + 16 * b;
	for (int i = 0; i < 16; i++)
		c[i] = lut[a[i]];
}

static inline void gf16_mac16(uint8_t *c, const uint8_t *a, int b)
{
	const uint8_t *lut = gf16_mul_lut + 16 * b;
	for (int i = 0; i < 16; i++)
		c[i] ^= lut[a[i]];
}

