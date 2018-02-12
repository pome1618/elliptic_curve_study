#include <stdio.h>

int main()
{
	int a, b, r;

	printf("a:");
	scanf("%d", &a);
	printf("b:");
	scanf("%d", &b);

	printf("%d/%d=%d...%d\n", a, b, a / b, a % b);
	r = a % b;
	while (r != 0) {
		a = b;
		b = r;
		r = a % b;
		printf("%d/%d=%d...%d\n", a, b, a / b, a % b);
	}

	return 0;
}
