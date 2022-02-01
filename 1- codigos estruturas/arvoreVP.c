#include<stdio.h>
#include<stdlib.h>

typedef struct b{ /*cor v= vermelho e p = preto*/
	int info;

	char cor;   /*cor v= vermelho e p = preto*/

	struct b *esq,*dir;


}arvoreVP;


void aloca(arvoreVP **No , int valor){
	arvoreVP *novo;

	novo = (arvoreVP *)malloc(sizeof(arvoreVP));

	novo->info = valor;
	novo->cor = 'v';

	novo->dir = novo->esq = NULL;

	*No = novo;

}

struct b* rotacionaesq(arvoreVP *A){

	arvoreVP *B = A->dir;

	A->dir = B->esq;
	B->esq = A;
	B->cor = A->cor;
	A->cor = 'v';

	return B;

}

struct b* rotacionadir(arvoreVP *A){
	arvoreVP *B = A->esq;

	A->esq = B->dir;
	B->dir = A;
	B->cor = A->cor;
	A->cor = 'v';

	return B;

}

char inverte_cor(arvoreVP *No){

	if (No != NULL){
		
		if (No->cor == 'p')
			No->cor = 'v';
		else
			No->cor = 'p';
	}

}

void TrocarCor(arvoreVP *RAIZ){
	
	inverte_cor(RAIZ);
	inverte_cor(RAIZ->dir);
	inverte_cor(RAIZ->esq);
}

char cor(arvoreVP *No){
	char c;

	if (No == NULL)
		c = 'p';
	else
		c = No->cor;

	return c;

}

/*Arvore vermelha e preta caida para esquerda
  
  Regra o filho da direita de um No nunca pode ser vermelho

  casos de implementação:

  -quando o filho da direita de um No for vermelho
   e o filho da esquerda for preto ou nulo
   devemos rotacionar o No para esquerda

   -quando o filho da esuqerda de um No for vermelho e
	o neto da esuquerda tambem for vermelho devemos rotacionar
	o No para esquerda
	
   -quando o filho da direita e o da esquerda um No for vermelho
   devemos trocar cor do No

*/

struct b* balancear(arvoreVP *No){

	//No vermelho é sempre o filho da esquerda
	if ( cor(No->dir) == 'v'){
		 No = rotacionaesq(No);
		 //printf("entrou balancear\n");
	}
	
	//filho da esquerda e neto sao vermelhos
	if (No->esq != NULL && cor(No->esq) == 'v' && cor(No->esq->esq) == 'v'){

		No = rotacionadir(No);
		
	}

	//dois filhos sao vermelhos troca cor
	if (cor(No->esq) == 'v' && cor(No->dir) == 'v'){

		TrocarCor(No);
		
	}

	return No;

}


void insere(arvoreVP **Raiz ,arvoreVP *No){
	

	if (*Raiz == NULL){  				 			 	 
		*Raiz = No;  								//se a raiz for null ela recebe o No
	
	}else if (No->info < (*Raiz)->info){            		   
		insere(&(*Raiz)->esq,No);   		          
			
	}else if (No->info > (*Raiz)->info){         						
		insere(&(*Raiz)->dir,No);       	  
	}

	//verifica_balanceamento_VP(Raiz);

	*Raiz = balancear(*Raiz);
	
}

struct b* moveEsqRed(arvoreVP *No){
	TrocarCor(No);

	if (cor(No->dir->esq) == 'v'){

		No->dir = rotacionadir(No->dir);
		No = rotacionaesq(No);

		TrocarCor(No);
		
	}

	return No;

}

struct b* moveDirRed(arvoreVP *No){
	TrocarCor(No);

	if (cor(No->esq->esq) == 'v'){

		No = rotacionadir(No);

		TrocarCor(No);
		
	}

	return No;

}

struct b* remover_menor(arvoreVP *No){

	if (No->esq == NULL){
		free(No);
		No = NULL;
	
	}else{ 

		if (cor(No->esq) == 'p' && cor(No->esq->esq) == 'p')
			No = moveEsqRed(No);

		No->esq = remover_menor(No->esq);
		No = balancear(No);
	}

	return No;

}

struct b* procura_menor(arvoreVP *Raiz){

	if (Raiz->esq != NULL){
		
		Raiz = procura_menor(Raiz->esq);
	}

	return Raiz;

}

struct b* remover(arvoreVP *Raiz, int valor){

	if (valor < Raiz->info){
		
		if (cor(Raiz->esq) == 'p' && cor(Raiz->esq->esq) == 'p'){
			Raiz = moveEsqRed(Raiz);
			printf("entoru move esq\n");

		}
		Raiz->esq = remover(Raiz->esq,valor);
	
	}else{

		if (cor(Raiz->esq) == 'v'){
			Raiz = rotacionadir(Raiz);
			printf("entoru dir\n");

		}

		if (valor == Raiz->info && Raiz->dir == NULL){
			free(Raiz);
			Raiz = NULL;
			
		}else{

			if (cor(Raiz->dir) == 'p' && cor(Raiz->dir->esq) == 'p'){
				Raiz = moveDirRed(Raiz);
				printf("entoru move\n");
			}


			if (valor == Raiz->info){
				arvoreVP *x;

				x = procura_menor(Raiz->dir);
				Raiz->info = x->info;
				Raiz->dir = remover_menor(Raiz->dir);

			}else{
				Raiz->dir = remover(Raiz->dir,valor);
			}	

		}

	}

	if (Raiz != NULL){
		Raiz = balancear(Raiz);
	}

	return Raiz;

}

void busca(arvoreVP *Raiz ,int valor, int *flag){

	if (Raiz != NULL){

		if (valor == Raiz->info){  					   //verifica se o valor da raiz
			*flag = 1;							      // é o valor buscado
		
		}else if(valor < Raiz->info){               // se o valor for menor que o valor da raiz raiz 
			busca(Raiz->esq,valor,flag);				   // faz a chamda recursiva fazendo que a raiz va para esquerda

		}else{									 // se o valor for maior que o valor da raiz raiz
			busca(Raiz->dir,valor,flag);             // faz a chamda recursiva fazendo que a raiz va para esquerda
		}
	
	}

}

int remover_info(arvoreVP **Raiz, int valor){
	int flag = 0;

	busca(*Raiz,valor,&flag);
	
	if (flag == 1){
		*Raiz = remover(*Raiz,valor);

		if ((*Raiz)->cor != 'p')
			(*Raiz)->cor = 'p';
		
	}

	return flag;

}

void inserir_valores(arvoreVP **Raiz){

	int n;
	arvoreVP *No;

	printf("\ndigite -1 para parar!!\n");
	printf("digite um valor: ");
	scanf("%d",&n);

	if (n > 0){

		aloca(&No,n);
	
		insere(Raiz,No);

		if ((*Raiz)->cor != 'p'){
			
			(*Raiz)->cor = 'p';
		}

		inserir_valores(Raiz);
	}



}

void imprimir(arvoreVP *Raiz){

	if (Raiz != NULL){
		
		printf("%d %c- ",Raiz->info,Raiz->cor);

		imprimir(Raiz->esq);
		//printf("%d ",Raiz->info);
		imprimir(Raiz->dir);
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
	arvoreVP *Raiz = NULL,*aux;

	int op,n,flag;

	do{
		
		op = menu();

		switch (op){

			case 1:
				inserir_valores(&Raiz);

				break;

			case 2:

				printf("\n");
				
				imprimir(Raiz);
			
				printf("\n");

				break;


			case 3:

				flag = 0;

				printf("\ndigite um valor: ");
				scanf("%d",&n);

				remover_info(&Raiz,n);



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
