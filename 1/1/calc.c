#include <stdio.h>
#include <stdlib.h>

int add(int a,int b,int p){
	return (a+b)%p;
}

int sub(int a,int b,int p){
	int res=a-b;
	while(res<0||p<res){
		if(res<0){
			res+=p;
		}else{
			res-=p;
		}
	}
	return res;
}

int mul(int a,int b,int p){
	return (a*b)%p;
}

int divi(int a,int b,int p){
	if(b==0){
		return -1;
	}
	while(a%b!=0){
		a+=p;
	}
	return a/b;
}

int main(){
	int p,*set,*res;
	int op,i,j;
	char op_str[4][4]={"add","sub","mul","div"};
	printf("p:");scanf("%d",&p);
	set=(int*)malloc(sizeof(int)*p);
	res=(int*)malloc(sizeof(int)*p*p);
	for(i=0;i<p;i++){
		set[i]=i;
	}

	for(op=0;op<4;op++){
		printf("---%s result---\n   ",op_str[op]);
		for(i=0;i<p;i++){
			printf("|--%2d--|",set[i]);
		}
		printf("\n");
		for(i=0;i<p;i++){
			printf("%2d |",set[i]);
			for(j=0;j<p;j++){
				switch(op){
					case 0 : res[p*i+j]=add(set[i],set[j],p);
							 break;
					case 1 : res[p*i+j]=sub(set[i],set[j],p);
							 break;
					case 2 : res[p*i+j]=mul(set[i],set[j],p);
						 break;
					case 3 : res[p*i+j]=divi(set[i],set[j],p);
							 break;
					default: res[p*i+j]=-1;
							 break;
				}
				printf("  %2d    ",res[p*i+j]);
			}
			printf("\n");
		}
		printf("\n\n");
	}

	return 0;
}
