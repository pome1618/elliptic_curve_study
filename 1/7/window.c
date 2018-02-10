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
#if DEBUG
	printf("P at add=(%d,%d)\n",P->x,P->y);
	printf("Q at add=(%d,%d)\n",Q->x,Q->y);
#endif
	int x,y,d,tmp;
	if(P->x==-1&&P->y==-1){
		R->x=Q->x;
		R->y=Q->y;
	}else if(Q->x==-1&&Q->y==-1){
		R->x=P->x;
		R->y=P->y;
	}else{
		if(P->x==Q->x&&P->y==mod(-Q->y,p)){
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

			tmp=mod(lambda*lambda-P->x-Q->x,p);
			R->y=mod(lambda*(P->x-tmp)-P->y,p);
			R->x=tmp;
#if DEBUG
			printf("\tnumerator is %d\n\tdenominator is %d\n\tlamda is %d\n\tr=(%d,%d)\n",numerator,denominator,lambda,R->x,R->y);
#endif
		}
	}
}

void window(point *P,unsigned int d,point *R,int a,int p){
	point Q,P_i[4];
	int bit=sizeof(unsigned int)*8-2;
	int i;
	P_i[0].x=-1;P_i[0].y=-1;
	P_i[1].x=P->x;P_i[1].y=P->y;
	for(i=2;i<4;i++){
		add(P,&P_i[i-1],&P_i[i],a,p);
	}
#if DEBUG
	for(i=0;i<4;i++){
		printf("P_i[%d]=(%d,%d)\n",i,P_i[i].x,P_i[i].y);
	}
#endif
	while(d>>bit==0){
		bit-=2;
	}
#if DEBUG
	printf("bit:%d\n",bit);
#endif
	Q.x=P_i[d>>bit].x;Q.y=P_i[d>>bit].y;
	for(i=bit-2;i>=0;i-=2){
		add(&Q,&Q,&Q,a,p);
		add(&Q,&Q,&Q,a,p);
		
		add(&Q,&P_i[(d>>i)&3],&Q,a,p);
	}
	R->x=Q.x;R->y=Q.y;
}

void scalar(point *P,unsigned int d,point *R,int a,int p){
	point Q;
	int bit=sizeof(unsigned int)*8-1;
	while(d>>bit==0){
		bit--;
	}
#if DEBUG
	printf("bit:%d\n",bit);
#endif
	Q.x=P->x;Q.y=P->y;
#if DEBUG
	printf("Q=(%d,%d)\n",Q.x,Q.y);
#endif
	int i;
	for(i=bit-1;i>=0;i--){
		add(&Q,&Q,&Q,a,p);
		if((d>>i)&1){
#if DEBUG
			printf("process if((d>>i)&1)\n");
#endif
			add(P,&Q,&Q,a,p);
		}
#if DEBUG
	printf("added Q=(%d,%d)\n",Q.x,Q.y);
#endif

	}
	R->x=Q.x;R->y=Q.y;
}


int check_P(point P[],point *R){
	int i;
	for(i=0;i<10;i++){
		if(P[i].x==R->x&&P[i].y==R->y){
			return i;
		}
	}
	return -1;
}

int main(){
	int a,b,p;
	int p_n,d;
	point P[10]={{-1,-1},{0,2},{1,1},{2,2},{5,2},
								{6,0},{5,5},{2,5},{1,6},{0,5}};
	point R;

	printf("a:");scanf("%d",&a);
    printf("b:");scanf("%d",&b);
    printf("p:");scanf("%d",&p);
	printf("d:");scanf("%d",&d);
	printf("P_n:");scanf("%d",&p_n);
	
	if(d<0){
		return -1;
	}

	window(&P[p_n],d,&R,a,p);

	printf("%d*P%d=P%d\n",d,p_n,check_P(P,&R));

	return 0;
}

