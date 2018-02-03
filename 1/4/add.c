#include <stdio.h>

typedef struct point_s{
	int x;
	int y;
} point;

void input_point(point *p){
	scanf("%d,%d",&(p->x),&(p->y));
}

int mod(int num,int p){
	if(num<0){
		num=p-((-num)%p);
	}else{
		num%=p;
	}
	return num;
}

void extgcd( int a, int b, int* x, int* y, int* d )
{
	int u,v,q,tmp; 
	*x=1;
	*y=0;
	u=0;
	v=1;
	while(b>0){
		q=a/b;
		tmp=u;u=*x-q*u;*x=tmp;
		tmp=v;v=*y-q*v;*y=tmp;
		tmp=b;b=a-q*b;a=tmp;
	}
	*d=a;
}

void extgcd2(int A,int B,int *x,int *y,int *d){
	int R1,X1,X2,R2,Y1,Y2,R3,Q,X3,Y3;
	R1=A;
	X1=1;
	X2=0;
	R2=B;
	Y2=1;
	while(R2!=0){
		R3=R1%R2;
		Q=R1/R2;
		X3 = X1 - Q * X2;
		Y3 = Y1 - Q * Y2;
		R1 = R2;
		R2 = R3;
		X1 = X2;
		X2 = X3;
		Y1 = Y2;
		Y2 = Y3;
	}
	printf("Y1=%d\n",Y1);
	*x=X1;
	*y=Y1;
	*d=R1;
}

int main(){
	int a,b,p;
	int x,y,d;
	point P,Q,R;
	printf("a:");scanf("%d",&a);
    printf("b:");scanf("%d",&b);
    printf("p:");scanf("%d",&p);
	
	printf("P:");input_point(&P);
	printf("Q:");input_point(&Q);
	
	if(P.x==-1&&P.y==-1){
		R.x=Q.x;
		R.y=Q.y;
	}else if(Q.x==-1&&Q.y==-1){
		R.x=P.x;
		R.y=P.y;
	}else{
		if(P.y==-Q.y){
			R.x=-1;
			R.y=-1;
		}else{
			int lambda;
			int numerator,denominator;
			if(P.x!=Q.x){
				numerator=P.y-Q.y;
				denominator=P.x-Q.x;
			}else{
				numerator=3*P.x*P.x+a;
				denominator=2*P.y;
			}
			numerator=mod(numerator,p);
			denominator=mod(denominator,p);
			extgcd(p,denominator,&x,&y,&d);
			lambda=mod(numerator*y,p);

			R.x=mod(lambda*lambda-P.x-Q.x,p);
			R.y=mod(lambda*(P.x-R.x)-P.y,p);
		}
	}

	printf("R=(%d,%d)\n",R.x,R.y);

	return 0;
}

