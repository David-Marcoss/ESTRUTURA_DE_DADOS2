#include <stdio.h>
#include<stdlib.h>
#include<string.h>

typedef  struct p{ 
    int id; 
    char Nome[30]; 
    int AnoNascimento; 
    float Altura; 

}pessoa; 


typedef struct l{
	pessoa info;
	struct l *prox;
	
}lista;

void inicia(lista **inicio, lista **fim){
		*inicio = *fim = NULL;
}

void aloca(lista **No, pessoa info){
	lista *novo;

	novo = (lista*)malloc(sizeof(lista));
	novo->info = info;
	novo->prox = NULL;

	*No = novo;

}

void insere(lista **inicio, lista **fim, lista **No){
	lista *ant,*aux;
	
	ant = NULL;
	aux = *inicio;

	if (*inicio == NULL){       //primeiro caso
		*inicio = *fim = *No;
	
	}else if ( (**No).info.id < (**inicio).info.id){  // insere no inicio
		(**No).prox = *inicio;
		*inicio = *No;
		
	}else if ((**No).info.id > (**fim).info.id){  //insere no fim 
		(**fim).prox = *No;
		*fim = *No;
	
	}else{   // se o valor nao foi inserido no inicio nem no fim
		
		while((**No).info.id > aux->info.id){ // busca a posisao no qual vai ser inserido o valor
			ant = aux;
			aux= aux->prox;

		}
		if ((**No).info.id != aux->info.id){   
			ant->prox = *No;     //inser o valor na posição correta
			(**No).prox = aux;

		} // se nao entrar neste caso que dizer que o valor que o usuario quer inserir ja foi inserido
		 // e este valor é o que esta no inicio
	}

}

void imprimir(lista *inicio){ //imprime a lista
	lista *aux;
	
	aux = inicio;

	while(aux != NULL){
		
		printf("id: %d \n",aux->info.id);
		printf("nome:%s \n",aux->info.Nome);
		printf("ano de nascimento: %d \n",aux->info.AnoNascimento);
		printf("altura: %.2f \n\n",aux->info.Altura);
		
		aux = aux->prox;
		
	}

}
 
void insere_valores(lista **inicio, lista **fim){  //insere valores na lista
	lista *No;
	pessoa info;

	int n;

	do{
		printf("\nid: ");
		scanf("%d",&info.id);
		
		printf("Nome: ");
		scanf("%s",info.Nome);
		
		printf("AnoNascimento: ");
		scanf("%d",&info.AnoNascimento);
		
		printf("Altura: ");
		scanf("%f",&info.Altura);


		aloca(&No,info);

		insere(inicio,fim,&No);

		printf("\ndigite [0] para parar ou [1] para continuar: ");
		scanf("%d",&n);



	}while(n != 0);

}

void maior_altura(lista *aux, float *maior, float *menor){ //devolve a maior altura e menor altura da lista

	if(aux != NULL){
		
		if (aux->info.Altura > *maior){
			*maior = aux->info.Altura;

		}

		if (aux->info.Altura < *menor){
			*menor = aux->info.Altura;

		}

		maior_altura(aux->prox,maior,menor);
	}
		
}

typedef struct{   //recebe os nome das pessoas com maior idade
	char nome[30];
}pessoas;

void maior_idade(lista *aux, int *maior){ //devolve o ano de nascimento da pessoa mais velha

	if(aux != NULL){
		
		if (aux->info.AnoNascimento < *maior){
			*maior = aux->info.AnoNascimento;

		}

		maior_idade(aux->prox,maior);
	}
		
}

void mais_velhas(lista *inicio ,int maior_id, pessoas *mais_velhos,int *quant){    //recebe o ano de nascimento das pessoa mais velha
																				// e devolve no vetor mais_velhos o nome das pessoas com essa idade
																			   // e devolve a quantidade de pessoas inseridas no vetor
	if(inicio != NULL){
			
			if (inicio->info.AnoNascimento == maior_id){
				strcpy(mais_velhos[*quant].nome,inicio->info.Nome);
				

				printf("%s \n",mais_velhos[*quant].nome);

				*quant+= 1;

			}

			mais_velhas(inicio->prox,maior_id,mais_velhos,quant);
		}
			


}

void pessoas_altura_mediana(lista *inicio, float altura_mediana,int *quant_altura_mediana){  //devolve quantidade de pessoas
																							// com altura mediana

	if(inicio != NULL){
		
		if (inicio->info.Altura == altura_mediana){
			*quant_altura_mediana+= 1;

		}

		pessoas_altura_mediana(inicio->prox,altura_mediana,quant_altura_mediana);
	}
		

}

int calcular_idade(int AnoNascimento){

	return 2021-AnoNascimento;
}

void pessoas_altura_maior_mediana(lista *inicio, float altura_mediana,int *quant_altura_maior_mediana){  //devolve quantidade de pessoas
																							// com altura maior que a mediana e idade menor 
																							// que 40 anos

	if(inicio != NULL){
		
		if (inicio->info.Altura > altura_mediana && calcular_idade(inicio->info.AnoNascimento) < 40){
			*quant_altura_maior_mediana+= 1;

		}

		pessoas_altura_maior_mediana(inicio->prox,altura_mediana,quant_altura_maior_mediana);
	}
		

}



void menu(int *op){ //imprime menu
	
	printf("\n1- Inserir dados pessoa\n");
	printf("2- imprimir dados da lista \n");
	printf("3- ver menor e maior altura \n");
	printf("4- ver pessoas mais velhas da lista \n");
	printf("5- ver quantidade de pessoas com altura mediana\n");
	printf("6- ver quantidade de pessoas com idade menor que 40 anos e altura maior que altura mediana\n");
	printf("7- sair\n");
	printf("\ndigite opcao: ");
	scanf("%d",op);
}


int main(){
	
	lista *inicio,*fim,*No, *aux; 
	int N,op=1;

	float maior=0,menor,altura_mediana; //altura

	int maior_id,quant=0,quant_altura_mediana,quant_altura_maior_mediana;

	pessoas mais_velhos[10]; //recebe o nome das pessoas mais velhas

	
	
	inicia(&inicio,&fim);

	while(op!=7){
		
		menu(&op);

		switch(op){
			
			case 1:
					
				insere_valores(&inicio,&fim); //insere pessoas na lista
					
				break;

			case 2:	 
				imprimir(inicio);
				
				break;
			

			case 3:

				if(inicio != NULL){

					menor = inicio->info.Altura;

					maior_altura(inicio,&maior,&menor);

					printf("\nmaior altura: %.2f\nmenor altura: %.2f \n",maior,menor);

				}else{
					printf("\nErro!! nao ha dados cadastrados!!\n\n");

				}


				break;

			case 4:

				if(inicio!= NULL){

					maior_id = inicio->info.AnoNascimento;

					maior_idade(inicio,&maior_id); //devolve o ano de nascimento da pessoa mais velhas

					printf("\npessoas mais velhas:\n");
					mais_velhas(inicio,maior_id,mais_velhos,&quant); //devolve o nome da pessoa mais velha

				}else{
						printf("\nErro!! nao ha dados cadastrados!!\n\n");

				}	
				
				break;

			
			case 5:

				if (inicio != NULL){
			
				

					quant_altura_mediana = 0;
					
					menor = inicio->info.Altura;

					maior_altura(inicio,&maior,&menor); //devoleve maior e menor altura da lista

					altura_mediana = (maior+menor)/2; //calcula altura_mediana

					pessoas_altura_mediana(inicio,altura_mediana,&quant_altura_mediana); //devolve quantidade de pessoas
																						// com altura mediana
					printf("\npessoas com altura mediana: %d \n",quant_altura_mediana);
				
				}else{
						printf("\nErro!! nao ha dados cadastrados!!\n\n");

				}

				break;

			
			case 6:

				if (inicio!= NULL){

					quant_altura_maior_mediana = 0;

					menor = inicio->info.Altura;

					maior_altura(inicio,&maior,&menor); //devoleve maior e menor altura da lista

					altura_mediana = (maior+menor)/2; //calcula altura_mediana

					
					pessoas_altura_maior_mediana(inicio,altura_mediana,&quant_altura_maior_mediana);

					printf("\npessoas com idade menor que 40 anos e altura maoi que mediana: %d \n",quant_altura_maior_mediana);				



				}else{
					printf("\nErro!! nao ha dados cadastrados!!\n\n");

				}
				
				break;


			case 7:
				printf("\nsaindo.....\n");
				break;


			
			default:
				printf("ERRO: opcao invalida \n");
				break;

		}
	}

	return 0;
}