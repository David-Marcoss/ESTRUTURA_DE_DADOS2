#include<stdio.h>
#include<stdlib.h>


typedef struct b{
	int info;

	int altura;

	struct b *esq,*dir;


}arvorebin;


void aloca(arvorebin **No , int valor){
	arvorebin *novo;

	novo = (arvorebin *)malloc(sizeof(arvorebin));

	novo->info = valor;

	novo->dir = novo->esq = NULL;

	*No = novo;


}

int altura_no(arvorebin *Raiz){
	int h1,h2,altura;

	if (Raiz == NULL){  //se a raiz é nula sua altura é -1
		altura = -1;    // entao a função retornara -1
	
	}else{  // se nao for null
		
		h1 = altura_no(Raiz->esq);  //h1 recebe a altura da raiz da esquerda
		h2 = altura_no(Raiz->dir);  //h2 recebe a altura da raiz da direita


		if (h1 > h2)           // verifica qual a maior altura
							  //se h1 for maior que h2
			altura = h1+1;   // a altura sera a altura da esquerda + 1
		else
			altura = h2+1; //se nao a altura sera a altura da direita + 1

	}

	return altura; //retorna a maior altura


}


void imprimir(arvorebin *Raiz){

	if (Raiz != NULL){
		
		printf("%d ",Raiz->info);
		imprimir(Raiz->esq);
		//printf("%d ",Raiz->info);
		imprimir(Raiz->dir);
	}

}


int fator_balanceamento(arvorebin *Raiz){


	return  altura_no(Raiz->esq) -  altura_no(Raiz->dir);

}


void balanceia_esquerda(arvorebin **Raiz){   // Recebe o No desbalanceado e balanceia No
													// onde o desbalanceamento esta para esqueda

	arvorebin *No_aux;

	No_aux = (*Raiz)->esq;

	(*Raiz)->esq = No_aux->dir;

	No_aux->dir = *Raiz;

	*Raiz = No_aux;

}

void balanceia_direita(arvorebin **Raiz){   // Recebe o No desbalanceado e balanceia No
													// onde o desbalanceamento esta para direita

	arvorebin *No_aux;


	No_aux = (*Raiz)->dir;

	(*Raiz)->dir = No_aux->esq;

	No_aux->esq = *Raiz;

	*Raiz = No_aux;




}

void verifica_balanceamento(arvorebin **Raiz){
	int fb;

	fb = fator_balanceamento(*Raiz);

	if (fb == 2){ 									//arvore esta desbalanceada para esquerda

		if (fator_balanceamento((*Raiz)->esq) < 0){ //caso em que o galho maior for interno

				balanceia_direita(&(*Raiz)->esq);

				printf("balanceia_interno\n");

		}

		printf("balanceia_esquerda\n");
		
		balanceia_esquerda(Raiz);
	
	}else if (fb == -2){  						//arvore esta desbalanceada para direita


		if (fator_balanceamento((*Raiz)->dir) > 0){ //caso em que o galho maior for interno

			balanceia_esquerda(&(*Raiz)->dir);


				printf("balanceia_interno\n");

		}

		printf("balanceia_direita\n");
		
		balanceia_direita(Raiz);
	}


}



void insere(arvorebin **Raiz ,arvorebin *No){
	int fb;

	if (*Raiz == NULL){  				 			 	 
		*Raiz = No;     								//se a raiz for null ela recebe o No
	
	}else if (No->info < (*Raiz)->info){            		   
		insere(&(*Raiz)->esq,No);   		           // faz a chamada recusiva passando a esqueda da raiz
			
	}else if (No->info > (*Raiz)->info){         						
		insere(&(*Raiz)->dir,No);       	   // faz a chamada recusiva passando a direita da raiz
	}

	(*Raiz)->altura = altura_no(*Raiz);   //recalcula altura do No

	verifica_balanceamento(Raiz);       //verifica e se nescessario balanceia arvore 

}

void maior_valor(arvorebin *Raiz, arvorebin **maior){  //recebe raiz e uma variavel do tipo arvore e devolve nesta variavel
														               //o endereço do no da raiz que possui o maior valor

	if (Raiz != NULL){

		if (Raiz->dir != NULL)
			maior_valor(Raiz->dir,maior);             // faz a chamda recursiva fazendo que a raiz va para direita
		else
			*maior = Raiz;
	}

}

void remover(arvorebin **Raiz ,int valor,int *flag){

	if (*Raiz != NULL){

		if (valor == (*Raiz)->info){
									 /*se entrar neste caso que dizer que o valor da raiz
									 é o no que queremos remover */

			arvorebin *aux = NULL;

			*flag = 1;

			if ((*Raiz)->esq == NULL && (*Raiz)->dir == NULL){ 

				aux = *Raiz;

				*Raiz = NULL;

				free(aux);
	
			}else if ((*Raiz)->esq != NULL && (*Raiz)->dir == NULL){ 

				aux = *Raiz;


				*Raiz = (*Raiz)->esq;

				free(aux);


	
			}else if ((*Raiz)->esq == NULL && (*Raiz)->dir != NULL){ 

					aux = *Raiz;

					*Raiz = (*Raiz)->dir;

					free(aux);
					
	
			}else{                                          

				arvorebin *maior;			
			
				maior_valor((*Raiz)->esq,&maior); //busca o maior valor da esquerda e devolve na variavel maior

				aux = *Raiz;

				maior->dir = (*Raiz)->dir;

				*Raiz = (*Raiz)->esq;

				free(aux);


			}

		}else if(valor < (*Raiz)->info){  //busca o No que sera removido
		    
			remover(&(*Raiz)->esq,valor,flag);				  

		}else{
			remover(&(*Raiz)->dir,valor,flag);             
		}

		
		if (*Raiz != NULL){
			
			(*Raiz)->altura = altura_no(*Raiz);   //recalcula altura do No

			verifica_balanceamento(Raiz);       //verifica e se nescessario balanceia arvore
		}
		
	}


}

void inserir_valores(arvorebin **Raiz){

	int n;
	arvorebin *No;

	printf("\ndigite -1 para parar!!\n");
	printf("digite um valor: ");
	scanf("%d",&n);

	if (n > 0){

		aloca(&No,n);
	
		insere(Raiz,No);

		inserir_valores(Raiz);
	}



}

void profundidade_no(arvorebin *Raiz, int valor ,int *cont, int  *flag){ //recebe raiz e o valor do no e devolve 
															// a profundidade do No buscado

	if (Raiz != NULL){

		if (valor == Raiz->info){  					   //verifica se o valor da raiz
			*flag = 1;							      // é o valor buscado
		
		}else if(valor < Raiz->info){               				// se o valor for menor que o valor da raiz raiz 
			
			(*cont)++;
			profundidade_no(Raiz->esq,valor,cont,flag);				   // faz a chamda recursiva fazendo que a raiz va para esquerda

		}else{
			
			(*cont)++;
			profundidade_no(Raiz->dir,valor,cont,flag);             // faz a chamda recursiva fazendo que a raiz va para esquerda
		}
	
	}else{

		*flag = 0;
	}



}


void menor_profundidade(arvorebin *Raiz, int *menor, arvorebin *aux){

		if (Raiz != NULL){
			
			if (Raiz->esq == NULL && Raiz->dir == NULL){
				
				int cont=0,flag;

				profundidade_no(aux,Raiz->info,&cont,&flag);

				if(*menor > cont){
					*menor = cont;
				}

			
			}

			menor_profundidade(Raiz->esq,menor,aux);
			menor_profundidade(Raiz->dir,menor,aux);

		}

}

int menu(){ //imprime menu
	int op;
	
	printf("\n1- Inserir dados na arvore\n");
	printf("2- imprimir arvore \n");
	printf("3- remover valor \n");
	printf("4- sair \n");
	printf("\ndigite opcao: ");
	scanf("%d",&op);

	return op;
}



int main(){
	arvorebin *Raiz = NULL;

	int op,n,flag,altura,altura2;

	do{
		
		op = menu();

		switch (op){

			case 1:
				inserir_valores(&Raiz);

				break;

			case 2:

				printf("\n");
				
				imprimir(Raiz);
				
				altura = altura_no(Raiz);

				altura2 = altura;

				menor_profundidade(Raiz,&altura2,Raiz);
				
				
				printf("\nmaior altura: %d\n",altura);
				printf("menor altura: %d\n",altura2);

				printf("\n\n");

				
				printf("\n");

				break;


			case 3:

				flag = 0;

				printf("\ndigite um valor: ");
				scanf("%d",&n);

				remover(&Raiz,n,&flag);

				if (flag == 1)
					printf("\nvalor encontrado !!\n");
				else
					printf("\nvalor nao encontrado !!\n");



				break;

			case 4:

				printf("\nSaindo.....\n");
						
			
			default:
				printf("\nopcao invalida!!!\n");

				break;
			

		}


	}while(op != 4);
	


	return 0;
}
