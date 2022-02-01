#include <stdio.h>


int main(){

	int x,y,z,delta;
	
	printf("digite os valores de x,y e z:");
	scanf("%d%d%d",&x,&y,&z);

	delta = (y*y) - 4*x*z;

	printf("delta: %d\n",delta);
	
}