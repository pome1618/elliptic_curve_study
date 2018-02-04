#include <stdio.h>

#define DEBUG 1

typedef struct point_s{
	int x;
	int y;
} point;

void input_point(point *p){
	scanf("%d,%d",&(p->x),&(p->y));
}

int mod(int num,int p){
	if(num%p==0){
		num=0;
	}else if(num<0){
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

void add(point *P,point *Q,point *R,int a,int p){
	int x,y,d;
	if(P->x==-1&&P->y==-1){
		R->x=Q->x;
		R->y=Q->y;
	}else if(Q->x==-1&&Q->y==-1){
		R->x=P->x;
		R->y=P->y;
	}else{
		if(P->y==-Q->y){
			R->x=-1;
			R->y=-1;
		}else{
			int lambda;
			int numerator,denominator;
			if(P->x!=Q->x){
				numerator=P->y-Q->y;
				denominator=P->x-Q->x;
			}else{
				numerator=3*P->x*P->x+a;
				denominator=2*P->y;
			}
			numerator=mod(numerator,p);
			denominator=mod(denominator,p);
			extgcd(p,denominator,&x,&y,&d);
			lambda=mod(numerator*y,p);

			R->x=mod(lambda*lambda-P->x-Q->x,p);
			R->y=mod(lambda*(P->x-R->x)-P->y,p);
#if DEBUG
			printf("\tnumerator is %d\n\tdenominator is %d\n\tlamda is %d\n\tR=(%d,%d)\n",numerator,denominator,lambda,R->x,R->y);
#endif
		}
	}
}

int check_P(point P[],point *R){
	int i;
	for(i=0;i<10;i++){
		if(P[i].x==R->x&&P[i].y==R->y){
			return i;
		}
	}
}

int main(){
	int a,b,p;
	point P[10]={{-1,-1},{0,2},{1,1},{2,2},{5,2},
								{6,0},{5,5},{2,5},{1,6},{0,5}};
	point R;

	printf("a:");scanf("%d",&a);
    printf("b:");scanf("%d",&b);
    printf("p:");scanf("%d",&p);
	
	int i,j;
	for(i=0;i<10;i++){
		for(j=0;j<10;j++){
			add(&P[i],&P[j],&R,a,p);
			printf("P%d+P%d=P%d\n",i,j,check_P(P,&R));
		}
		printf("\n\n");
	}

	return 0;
}

