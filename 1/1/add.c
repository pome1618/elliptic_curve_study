#include <stdio.h>
#include <stdlib.h>

int add(int a, int b, int p)
{
	return (a + b) % p;
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
			res[p * i + j] = add(set[i], set[j], p);
			printf("  %2d    ", res[p * i + j]);
		}
		printf("\n");
	}

	return 0;
}
