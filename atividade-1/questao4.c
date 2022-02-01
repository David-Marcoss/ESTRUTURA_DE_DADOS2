#include<stdio.h>



void MMC(int num[5],int i, int *mmc){ // calcula o mmc com recurçao sem pendencia
									 // apartir de I busca qual o menor valor de I que 
									//  é multiplos dos numeros achando assim o MMC


	if ( i % num[0] == 0 && i % num[1] == 0 && i % num[2] == 0 && i % num[3] == 0 && i % num[4] == 0)
		*mmc = i;
	else
		MMC(num,++i,mmc);

}

int  MMC2(int num[5],int i){ // calcula o mmc com recurçao com pendencia
	int mmc;

	if ( i % num[0] == 0 && i % num[1] == 0 && i % num[2] == 0 && i % num[3] == 0 && i % num[4] == 0) //verifica se I é multiplo
																									 // dos 5 valores recebidos
		mmc = i;																					// se for mmc é o I
	else
		mmc = MMC2(num,++i); //incrementa o I


	return mmc; //retorna o MMC

}

void maior_num(int vet[5], int *maior ,int i){ //devolve o maior numero do vetor

	if(i < 5){

		if (*maior < vet[i]){
			*maior = vet[i];
			
		}

		maior_num(vet,maior,++i);
	}

}

void ler(int *num){

	printf("digite os valores para o calculo: \n");

	for (int i = 0; i < 5 ; ++i){
		scanf("%d",&num[i]);
	
	}
}






int main(){
	int vet[5],maior = 0,mmc1,mmc2 ;

	ler(vet); //ler os 5 valores e armazena no vetor

	maior_num(vet,&maior,0); //devolve o maior valor do vetor


	MMC(vet,maior,&mmc1); 

	printf("MMC sem pendencia: %d\n",mmc1);

	printf("MMC2 com pendencia: %d\n",MMC2(vet,maior));


	
	return 0;








}