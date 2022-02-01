#include<stdio.h>
#include<string.h>



void lerstr(char strings[][30],int i,int tam){

	if (i<tam){

		scanf("%s",strings[i]);

		lerstr(strings,++i,tam);
	
	}
}

void mostrar(char strings[][30],int tam){
	int i;

	for (i = 0; i < tam; ++i){
		printf("%s\n",strings[i]);
	}

}

int maiortam(char strings[][30],int i,int tam, char *str){  //devolve na variavel srt a string de maior tamanho
	int maior=0;										

	if (i<tam){

		maior = maiortam(strings,++i,tam,str); //maior recebe o tamanho da maior string

		if (maior < strlen(strings[i]) ){    //verifica se o valor da string é maior que o valor de maior
			maior = strlen(strings[i]);     // se sim maior recebe um novovalor
			strcpy(str,strings[i]);        // e str recebe a string

			printf("I: %d\n",i);
			
		}
	
	}

	return maior;

}

void ehvogal(char str,int i,int *aux){ //recebe um caracter e devolve na 
									 // variavel aux, 1 se for vogal e 0 se nao for

	char vogais[] = "aeiouAEIOU";


	if (i < strlen(vogais) && *aux != 1){

		if (str == vogais[i]){
			*aux = 1;
		}

		ehvogal(str,++i,aux);
		
	}

}

void contvogal(char strings[][30],int i,int tam,int *resul){ //recebe as strings de entrada 
											                // e devolve na variavel resul quantas strings 
														   // inciam com vogal
	int aux = 0 ;

	if (i<tam){
		
		ehvogal(strings[i][0],0,&aux); //passa o primeiro caracter da string
									  // verifica se a string inicia com vogal
		if (aux == 1){
			*resul+=1;
		}

		contvogal(strings,++i,tam,resul);

	}


}

void strmaiusculas(char strings[][30],int i,int tam, char strings2[][30],int *j){  //recebe as strings de entrada 
																				  // e devolve na variavel strings2 as strings que tem tamanho
																				 // maior igual a 4 e inicia com letra maiuscula

	if (i<tam){
		
		if (strlen(strings[i]) >= 4 && (strings[i][0] > 64 && strings[i][0] < 91  ) ){
			
			strcpy(strings2[*j],strings[i]);
			(*j)++;  //conta quantas strings foram inseridas no vetor strisngs2
		}

		strmaiusculas(strings,++i,tam,strings2, j);
	}

}

int menu(){

	int op;

	printf("\n\n1- string de maior tamanho  \n");
	printf("2-  quantidade de strings que iniciam com vogal \n");
	printf("3- strings  com  tamanho  >=4  e  que iniciam com letra maiúscula. \n");
	printf("4- sair  \n");

	printf("\nescolha uma opacao: ");
	scanf("%d",&op);

	return op;
}



int main(){
	char strings[4][30],str[30], strings2[4][30];
	int aux = 0,resul= 0 ,op,j=0;

	printf("digite as palavras: ");
	lerstr(strings,0,4);

	do{

		op = menu();

		switch(op){

			case 1:

				aux = maiortam(strings,0,4,str); 

				printf("\nstring de maior tamanho: %s\n",str);


				break;

			case 2:

				contvogal(strings,0,4,&resul);

				printf("\nquantdade de strings que iniciam com vogais: %d\n",resul);

				break;
			
			case 3:

				strmaiusculas(strings,0,4,strings2,&j);

				if (j == 0){
					printf("\nNao ha strings que possuem tamnaho >=4 e que iniciam com letra maiúscula!!\n");
				
				}else{
					mostrar(strings2,j);
				}

				break;

			case 4:
				printf("\nSAINDO.....\n");

				break;

			
			default:

				printf("opacao invalida!!\n");

				break;
			


		}
		
	

	} while (op != 4);	




























	return 0;
}