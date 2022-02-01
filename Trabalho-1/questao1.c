#include<stdio.h>
#include<stdlib.h>
#include<time.h>


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


void insere(arvorebin **Raiz ,arvorebin *No,int *flag){  //insere no e devolve 1 se for inserido

	if (*Raiz == NULL){  				 			 	 
		*Raiz = No;     								//se a raiz for null ela recebe o No
		*flag = 1;
	
	}else if (No->info < (*Raiz)->info){            		   
		insere(&(*Raiz)->esq,No,flag);   		           // faz a chamada recusiva passando a esqueda da raiz
			
	}else if (No->info > (*Raiz)->info){         								// se o valor do No for maior que o valor da raiz
		insere(&(*Raiz)->dir,No,flag);       	   // faz a chamada recusiva passando a direita da raiz
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

void remover(arvorebin **Raiz ,int valor,int *flag){

	if (*Raiz != NULL){

		if (valor == (*Raiz)->info){
									 /*se entrar neste caso que dizer que o valor da raiz
									 é o no que queremos remover */

			arvorebin *aux;

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
	
	}else{
		*flag = 0;   //flag recebe 1 se o valor buscado foi removido
					// flag recebe 0 se o valor buscado nao foi removido
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

int altura_no(arvorebin *Raiz){ //recebe arvore e calcula altura da arvore
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




void menor_profundidade(arvorebin *Raiz, int *menor, arvorebin *aux){ //Recebe arvore e busca e calcula qual das folhas possui 
																	 // menor profundidade e devolve o valor 

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



double Tempo_gasto(clock_t tempo[2]){  //recebe o tempo inicial e o final da execulção
                                      // e calcula e retorna o tempo gasto

    double Tempo_ex;

    Tempo_ex = (tempo[1] - tempo[0]) * 1000.0 / CLOCKS_PER_SEC;
    

    return Tempo_ex;
}

int num_aleatorio(int num){ //devolve numero aleatorio entre 0 e 10.000

    num = rand() % 10000;

    if (num % 2 == 0)
        num /= 2;        
    else
        num *= 2;


    return  num;
}

void busca(arvorebin *Raiz ,int valor, int *flag){

	if (Raiz != NULL){

		if (valor == Raiz->info){  					  
			*flag = 1;					      
		
		}else if(valor < Raiz->info){             
			busca(Raiz->esq,valor,flag);

		}else{									 
			busca(Raiz->dir,valor,flag);
		}
	
	}else{
		*flag = 0;   //flag recebe 1 se o valor buscado foi encontrado
					// flag recebe 0 se o valor buscado nao foi encontrado
	}



}

void inserir_valores(arvorebin **Raiz){  // função ira inserir os 1000 valores na arvore 
										// e mostra o tempo de inserção

	int n,tam = 0,flag;
	
	arvorebin *No;

	clock_t Tempo_ex[2];

	Tempo_ex[0] = clock();



	while(tam < 1000){

		flag = 0;

		n = num_aleatorio(tam); //gera valor aleatorio

		aloca(&No,n);
	
		insere(Raiz,No,&flag); 
			
		tam+= flag;
	
	}

	Tempo_ex[1] = clock();

	printf("\nTempo gasto insercao: %g ms.\n", Tempo_gasto(Tempo_ex));


}

void liberar_memoria(arvorebin **Raiz, arvorebin *aux){  //recebe raiz e remove todos elemsntos da arvore

	int flag=0;

	if (aux != NULL){

		liberar_memoria(Raiz,aux->esq);

		remover(Raiz,aux->info,&flag);
			
		liberar_memoria(Raiz,aux->dir);
	}


}

void mostrar_profundidade(int maior_p, int menor_p){ //mostrar profundidade maxima e minima da arvore
																		 // e o tempo gasto para essa operação

	printf("\nmaior profundidade: %d\n",maior_p);
	printf("menor profundidade: %d\n",menor_p);



}

int calcular_profundidade(arvorebin *Raiz){  //recebe arvore e calcula profundidade maxima e minima da arvore
											//e retorna diferença entre as profundidades
	int maior_p,menor_p;


	maior_p = altura_no(Raiz);       //receber distancia da raiz ate a folha de maior altura
	    							//obtendo folha de maior produndiade
	menor_p = maior_p;

	menor_profundidade(Raiz,&menor_p,Raiz); //busca e devolve valor da folha de menor profundidade

	
	mostrar_profundidade(maior_p,menor_p);


	return maior_p - menor_p;

}

void traco(){
	printf("\n__________________________________________________________________________________________\n");
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
	essas funçoes servem para calcular e mostrar a quantidade de vezes
	em que a diferença entre as profundidades maxima e minima se repitiram
	durante os testes com as 30 arvores

*/

int cont_frequencia(int vet_profundidades[30],int i , int diferenca){

	int cont=0;

	if(i < 30){
		
		cont = cont_frequencia(vet_profundidades,++i,diferenca);

		if (diferenca == vet_profundidades[i]){
			cont++;
		}

	}


	return cont;
}

int busca_num(int vet_profundidades[30],int i ,int tam, int diferenca){

	int flag=0;

	if(i < tam){
		
		if (diferenca == vet_profundidades[i])
			flag = 1;
		else
			flag = busca_num(vet_profundidades,++i,tam,diferenca);
	}

	return flag;

}


void mostrar_diferenca_profundiades(int vet_profundidades[30]){
	int i,vet_aux[30],j=0;

	traco();

	for (i = 0; i < 30; ++i){

		if (busca_num(vet_aux,0,j,vet_profundidades[i]) == 0 ){
			
			printf("Quantidade de vezes em que diferenca entre as profundiades  das Arvores foi %d: %d\n",vet_profundidades[i],cont_frequencia(vet_profundidades,i-1,vet_profundidades[i]));	

			vet_aux[j] = vet_profundidades[i];
			j++;
		}
		
	}

}

void calcular_tempo_busca(arvorebin *Raiz){
	int flag = 0;
	int n = 19674;

	clock_t tempo_busca[2];


	tempo_busca[0] = clock();

	busca(Raiz,n,&flag);

	tempo_busca[1] = clock();

	printf("Tempo busca numero %d: %g ms\n",n,Tempo_gasto(tempo_busca) );

}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(){

	arvorebin *Raiz= NULL;

	int i,tempo;

	int vet_profundidades[30];

	srand(time(NULL));

	for (i = 0; i < 30; ++i){

	    traco();

	    printf("\nArvore: %d\n",i+1);

	    inserir_valores(&Raiz);

	    calcular_tempo_busca(Raiz);

	    vet_profundidades[i] = calcular_profundidade(Raiz);           // armazena diferença entre as profundiades

		liberar_memoria(&Raiz,Raiz);

	}

	printf("\n");

	mostrar_diferenca_profundiades(vet_profundidades);

	traco();

	
	return 0;

}
