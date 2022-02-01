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
			
	}else{         								// se o valor do No for maior que o valor da raiz
		insere(&(*Raiz)->dir,No);       	   // faz a chamada recusiva passando a direita da raiz
	}

	

}


void busca(arvorebin *Raiz ,int valor, int *flag, arvorebin **devolve){

	if (Raiz != NULL){

		if (valor == Raiz->info){  					   //verifica se o valor da raiz
			*flag = 1;							      // é o valor buscado

			*devolve = Raiz;   //devolve o endereço do no buscado
		
		}else if(valor < Raiz->info){               // se o valor for menor que o valor da raiz raiz 
			busca(Raiz->esq,valor,flag,devolve);				   // faz a chamda recursiva fazendo que a raiz va para esquerda

		}else{									 // se o valor for maior que o valor da raiz raiz
			busca(Raiz->dir,valor,flag,devolve);             // faz a chamda recursiva fazendo que a raiz va para esquerda
		}
	
	}else{
		*flag = 0;   //flag recebe 1 se o valor buscado foi encontrado
					// flag recebe 0 se o valor buscado nao foi encontrado
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
	printf("\ndigite um valor: ");
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

int calcular_altura(arvorebin *Raiz){
	int h1,h2,altura;

	if (Raiz == NULL){  //se a raiz é nula sua altura é -1
		altura = -1;    // entao a função retornara -1
	
	}else{  // se nao for null
		
		h1 = calcular_altura(Raiz->esq);  //h1 recebe a altura da raiz da esquerda
		h2 = calcular_altura(Raiz->dir);  //h2 recebe a altura da raiz da direita


		if (h1 > h2)           // verifica qual a maior altura
							  //se h1 for maior que h2
			altura = h1+1;   // a altura sera a altura da esquerda + 1
		else
			altura = h2+1; //se nao a altura sera a altura da direita + 1

	}

	return altura; //retorna a maior altura


}

int menu(){ //imprime menu
	int op;
	
	printf("\n1- Inserir dados na arvore\n");
	printf("2- imprimir arvore \n");
	printf("3- ver quantidade de nos e ramos arvore \n");
	printf("4- calcular profundidade No\n");
	printf("5- calcular altura No\n");
	printf("6- calcular quantidade de descendentes de um No\n");
	printf("7- sair \n");
	
	printf("\ndigite opcao: ");
	scanf("%d",&op);

	return op;
}



int main(){
	arvorebin *Raiz = NULL,*No;
	arvorebin *Raiz_aux;

	int op,n,flag,cont;

	do{
		
		op = menu();

		switch (op){

			case 1:
				inserir_valores(&Raiz);

				break;

			case 2:
				imprimir(Raiz);

				printf("\n\n");

				break;
			
			
			case 3:
			

				n = quant_nos_arvore(Raiz);

				printf("\nquantidade de nos: %d\nquantidade de ramos: %d\n",n,n-1);
				
				break;

			case 4:
			
				printf("\ndigite um valor: ");
				scanf("%d",&n);

				cont = 0;
				
				profundidade_no(Raiz,n,&cont,&flag);

				if (flag == 1)
					printf("\nprofundidade do NO: %d \n",cont);
				
				else
					printf("\nNo nao encontrado !!\n");

				break;



			case 5:

				printf("\ndigite um valor: ");
				scanf("%d",&n);

				flag = 0;

				busca(Raiz,n,&flag,&Raiz_aux);

				if (flag == 1)

					printf("\nAltura do No: %d \n",calcular_altura(Raiz_aux));
				else
					printf("\nvalor nao encontrado !!\n");



				break;




			
			case 6:

				printf("\ndigite um valor: ");
				scanf("%d",&n);

				flag = 0;
				
				busca(Raiz,n,&flag,&Raiz_aux); //busca o No 

				if (flag == 1)
					printf("\nnumero de descendentes do No: %d \n",quant_nos_arvore(Raiz_aux) - 1 );  //passa o NO para calcular quantos ramos o no possui
											 													// assim discobrindo a quantidade de descendentes do No buscado
				else
					printf("\nvalor nao encontrado !!\n");



				break;



			case 7:
				printf("\nSAINDO.........\n");
				break;
	

			
			
			default:
				printf("\nopcao invalida!!!\n");

				break;
			

		}


	}while(op != 7);
	


	return 0;
}