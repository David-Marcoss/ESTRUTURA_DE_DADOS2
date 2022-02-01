#include<stdio.h>
#include<stdlib.h>


typedef struct b{
	int info;

	struct b *esq,*dir;


}arvorebin;


void aloca(arvorebin **No , int valor){
	arvorebin *novo;

	novo = (arvorebin *)malloc(sizeof(arvorebin));

	novo->info = valor;
	
	novo->dir = novo->esq = NULL;

	*No = novo;


}


void insere(arvorebin **Raiz ,arvorebin *No){

	if (*Raiz == NULL){  				 			 	 
		*Raiz = No;     								//se a raiz for null ela recebe o No
	
	}else if (No->info < (*Raiz)->info){            		   
		insere(&(*Raiz)->esq,No);   		           // faz a chamada recusiva passando a esqueda da raiz
			
	}else if (No->info > (*Raiz)->info){         								// se o valor do No for maior que o valor da raiz
		insere(&(*Raiz)->dir,No);       	   // faz a chamada recusiva passando a direita da raiz
	}

	

}


void busca(arvorebin *Raiz ,int valor, int *flag){

	if (Raiz != NULL){

		if (valor == Raiz->info){  					   //verifica se o valor da raiz
			*flag = 1;							      // é o valor buscado
		
		}else if(valor < Raiz->info){               // se o valor for menor que o valor da raiz raiz 
			busca(Raiz->esq,valor,flag);				   // faz a chamda recursiva fazendo que a raiz va para esquerda

		}else{									 // se o valor for maior que o valor da raiz raiz
			busca(Raiz->dir,valor,flag);             // faz a chamda recursiva fazendo que a raiz va para esquerda
		}
	
	}else{
		*flag = 0;   //flag recebe 1 se o valor buscado foi encontrado
					// flag recebe 0 se o valor buscado nao foi encontrado
	}



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

void remover(arvorebin **Raiz ,int valor,int *flag, arvorebin *Raiz_ant){

	if (*Raiz != NULL){

		if (valor == (*Raiz)->info){
									 /*se entrar neste caso que dizer que o valor da raiz
									 é o no que queremos remover e Raiz_ant aponta para o No anterior 
									 do No que iramos remover */

			arvorebin *aux=NULL;

			*flag = 1;

			if ((*Raiz)->esq == NULL && (*Raiz)->dir == NULL){ /*remove no caso se o No for nao possuir
																filhos entao faz com que aux receber raiz
																e a raiz receber NUll e da um free o aux*/
				aux = *Raiz;

				*Raiz = NULL;

				free(aux);
	
			}else if ((*Raiz)->esq != NULL && (*Raiz)->dir == NULL){ /*remove no caso do No possuir um filho a esquerda
																	   entao faz o aux receber a raiz e faz com que a raiz agora aponte 
																	   para o filho da esquerda e da um free na raiz*/
				aux = *Raiz;


				*Raiz = (*Raiz)->esq;

				free(aux);


	
			}else if ((*Raiz)->esq == NULL && (*Raiz)->dir != NULL){ /*remove no caso do No possuir um filho a direita
																	   entao faz o aux receber a raiz e faz com que a raiz agora aponte 
																	   para o filho da direita e da um free na raiz*/
					aux = *Raiz;

					*Raiz = (*Raiz)->dir;

					free(aux);
					
	
			}else{                                            // O PROBLEMA ESTA AQUI \\ 

				arvorebin *maior;			
			
				maior_valor((*Raiz)->esq,&maior); //busca o maior valor da esquerda e devolve na variavel maior

				aux = *Raiz;

				maior->dir = (*Raiz)->dir;

				*Raiz = (*Raiz)->esq;

				free(aux);


			}

										      			
		
		}else if(valor < (*Raiz)->info){  //busca o No que sera removido
		    
		    Raiz_ant = *Raiz;    //faz com que a raiz_ant receber a raiz atual
		    					// e faz a chamada recursiva fazendo que a raiz passe para o proximo No      										 
			
			remover(&(*Raiz)->esq,valor,flag,Raiz_ant);				  

		}else{
			Raiz_ant = *Raiz;									 
			
			remover(&(*Raiz)->dir,valor,flag,Raiz_ant);             
		}
	
	}else{
		*flag = 0;   //flag recebe 1 se o valor buscado foi removido
					// flag recebe 0 se o valor buscado nao foi removido
	}



}



void imprimir(arvorebin *Raiz){

	if (Raiz != NULL){
		
		//printf("%d ",Raiz->info);
		imprimir(Raiz->esq);
		printf("%d ",Raiz->info);
		imprimir(Raiz->dir);
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

int quant_nos_arvore(arvorebin *Raiz){

	int n=0;
	
	if (Raiz != NULL){
		
		n = 1 + quant_nos_arvore(Raiz->esq) + quant_nos_arvore(Raiz->dir);;
	}

	return n;

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


void num_descendentes(arvorebin *Raiz,int valor, int *quant, int *flag){ //recebe a raiz da arvore e um valor de um no
																		// busca o No e devolve a quantidade de descendentes do No buscado

	if (Raiz != NULL){

		if (valor == Raiz->info){  					   //valor da raiz é o valor buscado
			*flag = 1;

			*quant = quant_nos_arvore(Raiz) - 1 ;  //passa a raiz para calcular quantos nos a raiz possui
											 // assim discobrindo a quantidade de descendentes do No buscado

		
		}else if(valor < Raiz->info){                
			num_descendentes(Raiz->esq,valor,quant,flag);				   // faz a chamda recursiva fazendo que a raiz va para esquerda

		}else{						
			num_descendentes(Raiz->dir,valor,quant,flag);             // faz a chamda recursiva fazendo que a raiz va para esquerda
		}
	
	}else{
		*flag = 0;   //flag recebe 1 se o valor buscado foi encontrado
					// flag recebe 0 se o valor buscado nao foi encontrado
	}

}


int menu(){ //imprime menu
	int op;
	
	printf("\n1- Inserir dados na arvore\n");
	printf("2- imprimir arvore \n");
	printf("3- busca valor \n");
	printf("4- remover valor \n");
	printf("5- ver quantidade de nos e ramos arvore \n");
	printf("6- calcular profundidade No\n");
	printf("7- calcular quantidade de descendentes de um No\n");
	printf("8- sair \n");
	printf("\ndigite opcao: ");
	scanf("%d",&op);

	return op;
}



int main(){
	arvorebin *Raiz = NULL,*No;
	arvorebin *Raiz_ant;

	int op,n,flag,cont,altura,altura2;

	do{
		
		op = menu();

		switch (op){

			case 1:
				inserir_valores(&Raiz);

				break;

			case 2:
				imprimir(Raiz);
				
				altura = altura_no(Raiz);

				altura2 = altura;

				menor_profundidade(Raiz,&altura2,Raiz);
				
				
				printf("\nmaior altura: %d\n",altura);
				printf("menor altura: %d\n",altura2);

				printf("\n\n");

				break;
			
			case 3:

				printf("\ndigite um valor: ");
				scanf("%d",&n);

				flag = 0;
				busca(Raiz,n,&flag);

				if (flag == 1)
					printf("\nvalor encontrado !!\n");
				else
					printf("\nvalor nao encontrado !!\n");



				break;

			case 4:

				
				printf("\ndigite um valor: ");
				scanf("%d",&n);

				flag = 0;
				remover(&Raiz,n,&flag,Raiz_ant);

				if (flag == 0){
					printf("\nvalor nao encontrado !!\n");
				}else{
					printf("\nvalor removido !!\n");
				}

				break;

			case 5:
			

				n = quant_nos_arvore(Raiz);

				printf("\nquantidade de nos: %d\nquantidade de ramos: %d\n",n,n-1);
				
				break;

			case 6:
				printf("\ndigite um valor: ");
				scanf("%d",&n);

				cont = 0;
				
				profundidade_no(Raiz,n,&cont,&flag);

				if (flag == 1)
					printf("\nprofundidade do NO: %d \n",cont);
				
				else
					printf("\nNo nao encontrado !!\n");

				break;


			case 7:

				printf("\ndigite um valor: ");
				scanf("%d",&n);

				flag = 0;
				
				num_descendentes(Raiz,n,&cont,&flag);

				if (flag == 1)
					printf("\nnumero de descendentes do No: %d \n",cont);
				else
					printf("\nvalor nao encontrado !!\n");



				break;




			case 8:
				printf("\nSAINDO.........\n");
				break;
	

			
			
			default:
				printf("\nopcao invalida!!!\n");

				break;
			

		}


	}while(op != 8);
	


	return 0;
}
