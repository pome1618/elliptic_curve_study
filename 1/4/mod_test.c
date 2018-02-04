#include <stdio.h>

int mod( int a, int m )
{
	  if ( m < 0 ) { m = -m; }
	    if ( a < 0 ) { 
			    a = m - ((-a) % m);
				  }
		  else { 
			      a = a % m; 
				    }

		    return a;
}

int main(){
	int i,j;
	for(i=-20;i<10;i++){
		for(j=1;j<10;j++){
			printf("%d mod %d =%d\n",i,j,mod(i,j));
		}
	}
	printf("-5p12=%d",(-5)%12);
	return 0;
}

