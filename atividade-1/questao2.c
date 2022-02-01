#include<stdio.h>


void divisores(int num,int i){  //recebe um numero e uma variavel i que deve inciar com 1
							   // e mostra todos os divisores do numero recebido

	if (i <= num ){
		
		if (num%i == 0){
			printf("%d \n",i);
		}

		divisores(num,++i);
	}



}


int main(){

	int num;

	printf("digite um valor: ");
	scanf("%d",&num);

	divisores(num,1);

	
	return 0;
}