#include<stdio.h>

void laco(int i, int j,int *r){


	if(i < j){
		*r+= i;
		printf("R: %d\n",*r);
		laco(++i,j,r);

	}

}

void invertido(int i, int j,int *r){


	if(i < j){
		*r+= i;
		laco(i,j,r);
		i++;
		printf("R: %d\n",i);

	}

}

int main(){

	int r = 0;

	invertido(0,10,&r);

	


	return 0;
}