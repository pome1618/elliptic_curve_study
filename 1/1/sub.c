#include <stdio.h>
#include <stdlib.h>

int sub(int a, int b, int p)
{
	int res = a - b;
	while (res < 0 || p < res) {
		if (res < 0) {
			res += p;
		} else {
			res -= p;
		}
	}
	return res;
}

int main()
{
	int p, *set, *res;
	int i, j;
	printf("p:");
	scanf("%d", &p);
	set = (int *)malloc(sizeof(int) * p);
	res = (int *)malloc(sizeof(int) * p * p);
	for (i = 0; i < p; i++) {
		printf("set[%2d]=", i);
		scanf("%d", &set[i]);
	}

	printf("---result---\n   ");
	for (i = 0; i < p; i++) {
		printf("|--%2d--|", set[i]);
	}
	printf("\n");
	for (i = 0; i < p; i++) {
		printf("%2d |", set[i]);
		for (j = 0; j < p; j++) {
			res[p * i + j] = sub(set[i], set[j], p);
			printf("  %2d    ", res[p * i + j]);
		}
		printf("\n");
	}

	return 0;
}
