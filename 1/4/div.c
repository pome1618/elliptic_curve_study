#include <stdio.h>

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

int main(){
	int a,b,p;
	int x,y,d;
	printf("a:");scanf("%d",&a);
    printf("b:");scanf("%d",&b);
    printf("p:");scanf("%d",&p);

	extgcd(p,b,&x,&y,&d);

	printf("%d/%d=%d\n",a,b,(a*y)%p);

	return 0;
}

