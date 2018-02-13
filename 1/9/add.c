#include <stdio.h>

#define DEBUG 0

typedef struct affine_point_s {
	int x;
	int y;
} affine_point;

typedef struct projective_point_s {
	int X;
	int Y;
	int Z;
} projective_point;

void input_affine_point(affine_point * p)
{
	scanf("%d,%d", &(p->x), &(p->y));
}

int check_P(affine_point P[], affine_point * R)
{
	int i;
	for (i = 0; i < 10; i++) {
		if (P[i].x == R->x && P[i].y == R->y) {
			return i;
		}
	}
	return -1;
}

int mod(int num, int p)
{
	if (num % p == 0) {
		num = 0;
	} else if (num < 0) {
		num = p - ((-num) % p);
	} else {
		num %= p;
	}
	return num;
}

void extgcd(int a, int b, int *x, int *y, int *d)
{
	int u, v, q, tmp;
	*x = 1;
	*y = 0;
	u = 0;
	v = 1;
	while (b > 0) {
		q = a / b;
		tmp = u;
		u = *x - q * u;
		*x = tmp;
		tmp = v;
		v = *y - q * v;
		*y = tmp;
		tmp = b;
		b = a - q * b;
		a = tmp;
	}
	*d = a;
}

void add(projective_point * P, projective_point * Q, projective_point * R,
	 int a, int p)
{
	if (P->X == 0 && P->Y == 1 && P->Z == 0) {
		R->X = Q->X;
		R->Y = Q->Y;
		R->Z = Q->Z;
	} else if (Q->X == 0 && Q->Y == 1 && Q->Z == 0) {
		R->X = P->X;
		R->Y = P->Y;
		R->Z = P->Z;
	} else if (P->X == Q->X && P->Y == Q->Y && P->Z == Q->Z) {
		int omega = mod(a * P->Z * P->Z + 3 * P->X * P->X, p);
		int s = mod(P->Y * P->Z, p);
		int B = mod(s * P->X * P->Y, p);
		int h = mod(omega * omega - 8 * B, p);
		R->X = mod(2 * h * s, p);
		R->Y = mod(omega * (4 * B - h) - 8 * P->Y * P->Y * s * s, p);
		R->Z = mod(8 * s * s * s, p);
	} else {
		int u = mod(Q->Y * P->Z - P->Y * Q->Z, p);
		int v = mod(Q->X * P->Z - P->X * Q->Z, p);
		int A =
		    mod(u * u * P->Z * Q->Z - v * v * v -
			2 * v * v * P->X * Q->Z, p);
		R->X = mod(v * A, p);
		R->Y =
		    mod(u * (v * v * P->X * Q->Z - A) - v * v * v * P->Y * Q->Z,
			p);
		R->Z = mod(v * v * v * P->Z * Q->Z, p);
	}
}

void aff_to_pro(projective_point * pp, affine_point * ap)
{
	if (ap->x == -1 && ap->y == -1) {
		pp->X = 0;
		pp->Y = 1;
		pp->Z = 0;
	} else {
		pp->X = ap->x;
		pp->Y = ap->y;
		pp->Z = 1;
	}
}

void pro_to_aff(affine_point * ap, projective_point * pp, int p)
{
	int x, y, d;
	if (pp->Z == 0) {
		ap->x = -1;
		ap->y = -1;
	} else {
		extgcd(p, pp->Z, &x, &y, &d);
		ap->x = mod(pp->X * y, p);
		ap->y = mod(pp->Y * y, p);
	}
}

int main()
{
	int a, b, p;
	affine_point point[10] = { {-1, -1}, {0, 2}, {1, 1}, {2, 2}, {5, 2},
	{6, 0}, {5, 5}, {2, 5}, {1, 6}, {0, 5}
	};
	projective_point P, Q, R;

	printf("a:");
	scanf("%d", &a);
	printf("b:");
	scanf("%d", &b);
	printf("p:");
	scanf("%d", &p);

	int i, j;
	for (i = 0; i < 10; i++) {
		for (j = 0; j < 10; j++) {
			affine_point tmp;
			aff_to_pro(&P, &point[i]);
			aff_to_pro(&Q, &point[j]);
			add(&P, &Q, &R, a, p);
			pro_to_aff(&tmp, &R, p);
#if DEBUG
			printf
			    ("\tP=(%d,%d,%d)\n\tQ=(%d,%d,%d)\n\tR=(%d,%d,%d)\n\ttmp=(%d,%d)\n",
			     P.X, P.Y, P.Z, Q.X, Q.Y, Q.Z, R.X, R.Y, R.Z, tmp.x,
			     tmp.y);
#endif
			printf("P%d+P%d=P%d\n", i, j, check_P(point, &tmp));
		}
		printf("\n\n");
	}

	return 0;
}
