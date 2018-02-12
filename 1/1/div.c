#include <stdio.h>
#include <stdlib.h>

int divi(int a, int b, int p)
{
	if (b == 0) {
		return -1;
	}
	while (a % b != 0) {
		a += p;
	}
	return a / b;
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
			res[p * i + j] = divi(set[i], set[j], p);
			printf("  %2d    ", res[p * i + j]);
		}
		printf("\n");
	}

	return 0;
}
