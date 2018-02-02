#include <stdio.h>

int check_deltaE(int a,int b,int p){ 
	return (0<=a&&a<p&&0<=b&&b<p)&&((4*a*a*a+27*b*b)!=0);
}

int check_on_curve(int x,int y,int a,int b,int p){
	int l,r;
	l=(y*y)%p;
	r=(x*x*x+a*x+b)%p;
	return l==r;
}

int main(){
	int a,b,p;

	printf("y^2=x^3+ax+b\n");
	printf("a:");scanf("%d",&a);
	printf("b:");scanf("%d",&b);
	printf("p:");scanf("%d",&p);

	int x,y;
	for(x=0;x<p;x++){
		for(y=0;y<p;y++){
			if(check_on_curve(x,y,a,b,p)){
				printf("(%d,%d)\n",x,y);
			}
		}
	}
	printf("0\n");

	return 0;
}
