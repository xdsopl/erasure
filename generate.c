/*
Galois field tables generator

Copyright 2023 Ahmet Inan <xdsopl@gmail.com>
*/

#include <stdio.h>

int main()
{
	int M = 4, P = 19;
	int Q = 1 << M, N = Q - 1;
	int log[Q], exp[Q];
	log[exp[N] = 0] = N;
	for (int i = 0, a = 1; i < N; ++i) {
		log[exp[i] = a] = i;
		a <<= 1;
		if (a & Q)
			a ^= P;
	}
	printf("log:");
	for (int i = 0; i < Q; ++i)
		printf(" %d,", log[i]);
	printf("\n");
	printf("exp:");
	for (int i = 0; i < Q; ++i)
		printf(" %d,", exp[i]);
	printf("\n");
	printf("inv:");
	for (int i = 0; i < Q; ++i)
		printf(" %d,", i ? exp[(N-log[i])%N] : 0);
	printf("\n");
	for (int j = 0; j < Q; ++j) {
		if (j)
			printf("    ");
		else
			printf("mul:");
		for (int i = 0; i < Q; ++i)
			printf(" %d,", i&&j ? exp[(log[j]+log[i])%N] : 0);
		printf("\n");
	}
	return 0;
}

