#include <stdio.h>

void dump(unsigned int num[])
{
	int i;
	for (i = sizeof(unsigned int) * 8 - 1; i >= 0; i--) {
		printf("%d  ",
		       ((num[1] >> i) & 0x01) == 1 ? -1 : (num[0] >> i) & 0x01);
	}
	printf("\n");
}

void toNAF(unsigned int NAF[], unsigned int d)
{
	int threed = 3 * d;
	int i;
	NAF[0] = 0;
	NAF[1] = 0;
	for (i = sizeof(unsigned int) * 8 - 1; i > 0; i--) {
		int bit;
		bit = ((threed >> i) & 0x01) - ((d >> i) & 0x01);
		if (bit >= 0) {
			NAF[0] |= bit << (i - 1);
		} else {
			NAF[1] |= 1 << (i - 1);
		}
	}
}

int main()
{
	int d;
	unsigned int NAF[2];

	printf("d:");
	scanf("%d", &d);

	toNAF(NAF, d);

	dump(NAF);

	return 0;
}
