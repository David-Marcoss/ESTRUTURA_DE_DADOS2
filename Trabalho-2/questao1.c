#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<time.h>

double Tempo_gasto(clock_t tempo[2]){  //recebe o tempo inicial e o final da execulção
                                      // e calcula e retorna o tempo gasto

    double Tempo_ex;

    Tempo_ex = (tempo[1] - tempo[0]) * 1000.0 / CLOCKS_PER_SEC;
    

    return Tempo_ex;
}


void traco(){

	printf("\n===========================================================================================\n");
}


////////////////////////////////////////--FUNÇOES PARA LISTA--///////////////////////////////////////////////////////////////////////////////////

typedef struct l{  //lista palavras ingles
	
	int linha;

	struct l *prox;
	
}lista;

void aloca_lista(lista **No, int linha){
	lista *novo;

	novo = (lista*)malloc(sizeof(lista));
	
	novo->linha = linha;

	novo->prox = NULL;

	*No = novo;

}


void imprimir_lista(lista *t){  //imprime a lista

	printf("linha: ");

	while(t != NULL){

		printf("%d, ",t->linha); 
		
		t = t->prox;
	}

	printf("\n");

}

void insere_lista(lista **inicio, lista *No){ // recebe um no e insere no fim da lista
	
	lista *aux;
	
	if (*inicio == NULL){       //primeiro caso
		*inicio = No;         // insere o valor na primeira posição da lista
	
	}else{   // se o inicio nao for null


		aux = *inicio; 
		
		while(aux->prox != NULL){ // busca o ultimo no da lista
			aux= aux->prox;
		}  
		
		if (aux->linha != No->linha){
			aux->prox = No;     //insere o valor na ultima pisição da lista
		}

	}

}


void insere_linha(lista **inicio, int linha){ // recebe lista e a palavra em ingles e insere na lista
	
	lista *No;

	aloca_lista(&No,linha);
	insere_lista(inicio,No);

}


int remover_lista(lista **inicio, int num){ // recebe um valor e remove se existir
											// devolve 1 se o valor for removido e 0 se nao 
	lista *aux;

	int flag = 0;

	if ( num > (*inicio)->linha && (*inicio)->prox != NULL){
		
		flag = remover_lista(&(*inicio)->prox,num);
	}else{

		if (num == (*inicio)->linha){
			aux = *inicio;
			*inicio = (*inicio)->prox;

			free(aux);

			flag = 1;
		}


	}

	return flag;

}

///////////////////////////////////////////////////////////FUNÇÕES PARA ARVORE VP \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\


typedef struct b{ /*cor v= vermelho e p = preto*/
	char str[30];

	char cor;   /*cor v= vermelho e p = preto*/

	lista *l;

	struct b *esq,*dir;


}arvoreVP;

void aloca(arvoreVP **No , char str[30]){
	arvoreVP *novo;

	novo = (arvoreVP *)malloc(sizeof(arvoreVP));

	strcpy(novo->str,str);

	novo->cor = 'v';

	novo->l = NULL;

	novo->dir = novo->esq = NULL;

	*No = novo;

}

void minusculo(char *palavra, char *aux){ 		//recebe duas string e faz com que a segunda string receba
	int i;										//recebe a string 1 com seus caracteres em minusculo

	for (i = 0; i < strlen(palavra); ++i){
		aux[i] = tolower(palavra[i]);
	}
	aux[i] = '\0';

}

int compara(char *p1 , char *p2 ){ // compara duas strings pela ordem alfabetica comparando seus caracteres
	int i,tam;	
	char aux1[50],aux2[50]; 

	minusculo(p1,aux1);  //aux1 recebe p1 com seus caracteres em minusculos
	minusculo(p2,aux2); //aux2 recebe p2 com seus caracteres em minusculos

	return strcmp(aux1,aux2);
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

void TrocarCor(arvoreVP *RAIZ){ // troca a cor do no 
							    // e de seus filhos
	
	inverte_cor(RAIZ);
	inverte_cor(RAIZ->dir);
	inverte_cor(RAIZ->esq);
}

char cor(arvoreVP *No){ //retorna a cor de um No
	char c;

	if (No == NULL)
		c = 'p';
	else
		c = No->cor;

	return c;

}

struct b* balancear(arvoreVP *No){ //recebe um No e verifica se é necessario
								  // balancear a arvore

	//No vermelho é sempre o filho da esquerda
	if ( cor(No->dir) == 'v'){
		 No = rotacionaesq(No);
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


void insere(arvoreVP **Raiz ,arvoreVP *No, int linha){ //recebe a Raiz e um No com uma palavra e a linha
													  // e insere o No se a palavra ja nao existir, se
													 // existir apaenas insere a linha na lista do No

	

	if (*Raiz == NULL){  				 			 	 
		*Raiz = No;  								//se a raiz for null ela recebe o No
		insere_linha(&(*Raiz)->l,linha);            //insere linha na lista da palavra

	}else if ( compara(No->str,(*Raiz)->str) < 0){            		   
		insere(&(*Raiz)->esq,No,linha);   		          
			
	}else if (compara(No->str,(*Raiz)->str) > 0){         						
		insere(&(*Raiz)->dir,No,linha);       	  
	
	}else{ //palavra ja foi enserida
		insere_linha(&(*Raiz)->l,linha);            //insere linha na lista da palavra
	}

	*Raiz = balancear(*Raiz); //verifica se ao inserir No, foi quebrado alguma regra
							 // e balanceia arvore se necessario
	
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

struct b* remover(arvoreVP *Raiz, char str[30]){ //recebe a Raiz e uma palavra e remove a palavra
												//e balanceia a arvore se nsescessario

	if (compara(str,Raiz->str) < 0){
		
		if (cor(Raiz->esq) == 'p' && cor(Raiz->esq->esq) == 'p'){
			Raiz = moveEsqRed(Raiz);
		}
		Raiz->esq = remover(Raiz->esq,str);
	
	}else{

		if (cor(Raiz->esq) == 'v'){
			Raiz = rotacionadir(Raiz);

		}

		if (compara(str,Raiz->str) == 0 && Raiz->dir == NULL){
			free(Raiz);
			Raiz = NULL;
			
		}else{

			if (cor(Raiz->dir) == 'p' && cor(Raiz->dir->esq) == 'p'){
				Raiz = moveDirRed(Raiz);
			}


			if (compara(str,Raiz->str) == 0){
				arvoreVP *x;

				x = procura_menor(Raiz->dir);
				strcpy(Raiz->str, x->str);
				Raiz->dir = remover_menor(Raiz->dir);

			}else{
				Raiz->dir = remover(Raiz->dir,str);
			}	

		}

	}

	if (Raiz != NULL){
		Raiz = balancear(Raiz);
	}

	return Raiz;

}

///////////////////////////////////////////////////////////Funçoes para solução da questao \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

int remover_linha(arvoreVP *Raiz ,char str[30], int linha){/* recebe a raiz , uma palavra e uma linha
															busca e remove a linha em que a palavra aparece
															é devolvido 0 se a linha ou palavra não foi encontrada
															é devolvido 1 se a linha foi removida e a lista ainda possui valores
															é devolvido -1 se a linha foi removida e a lista não mais possui valores
															*/
	 int flag = 0;
	
	if (Raiz != NULL){

		if (compara(str,Raiz->str) == 0){  				   

			flag = remover_lista(&Raiz->l,linha);

			if (Raiz->l == NULL){
				flag = -1;
			}
		
		}else if(compara(str,Raiz->str) < 0){         
			flag = remover_linha(Raiz->esq,str,linha);				 

		}else{									 
			flag = remover_linha(Raiz->dir,str,linha);
		}
	
	}

	return flag;
}

int remover_info(arvoreVP **Raiz, char str[30],int linha){ /* recebe a raiz , uma palavra e uma linha
															busca e remove a linha em que a palavra aparece
															e se a palavra nao possuir mais linhas remove a palavra
															da arvore*/
	int flag;

	flag = remover_linha(*Raiz,str,linha);
	
	if (flag == -1){
		*Raiz = remover(*Raiz,str);

		if ((*Raiz)->cor != 'p')
			(*Raiz)->cor = 'p';
		
	}

	return flag;

}

typedef struct{  //armazena palavra
	
	char str[50];

}palavras;

void abrir_arquivo(FILE **file,char arquivo[50]){

	*file = fopen(arquivo,"r");

	if (*file == NULL){
	 	printf("\nERRO: nao foi possivel abrir arquivo!!\n");
	 } 

}

void trata_str(char str[30]){ //RECEBE UMA STRING E EXCLUI SINAIS DE PONTUAÇÕES 
							 //COMO: .!,',",(,),:,; 	ENTRE OUTROS QUE PODEM APARECER
							//NO INICIO OU FIM DE UMA PALAVRA

	char aux[30];
	int i,j=0;

	if ( (str[0] > 31 && str[0] < 48) || (str[strlen(str)-1] > 31 && str[strlen(str)-1] < 48 || str[strlen(str)-1] != 58 || str[strlen(str)-1]!= 59)){

		for (i = 0; i < strlen(str); ++i){
			
			if ( !(str[i] > 31 && str[i] < 48) && str[i] != 58 && str[i] != 59 ){
				aux[j] = str[i];
				j++;
			}
		}

		aux[j]= '\0';
		strcpy(str,aux);
	}

}


int trata_frase(palavras *v, char frase[1000]){ /* recebe uma string contendo uma frase do texto
											       quebra a string dividindo pelo esapço e a cada string
											       armazena num vetor de palavras e a função devolve o vetor
											       e a quantidade de palavras inseridas*/ 

    int i=0,tam;
    char *t;
    char texto1[1000];

    tam = strlen(frase)-1;  

    strncpy(texto1, frase, strlen(frase)-1);  //elimina /n da string

    texto1[tam] = '\0';
      
    t = strtok(texto1," ");
      
    while(t != NULL){
        
        strcpy(v[i].str,t);

        trata_str(v[i].str);

        t = strtok(NULL," ");
        i++;
      
    }

    return i;
}

void inserir_palavras(arvoreVP **Raiz, palavras *v, int linha, int tam){/* recebe a raiz da arvore e um vetor de strings
																		 com as palavras de uma linha do texto e a linha corespondente
																		 e insere todas as palavras na arvore*/

	arvoreVP *No;
	int i;

	for (i = 0; i < tam; ++i){

		aloca(&No,v[i].str);
		
		insere(Raiz,No,linha);

		if ((*Raiz)->cor != 'p'){
				
			(*Raiz)->cor = 'p';
		}
	}




}
void ler_dados(FILE *file, arvoreVP **Raiz){  //recebe o arquivo e a Raiz da arvore e
											 // lé as linhas do arquivo e insere as palavras das
											// linhas lidas na arvore

	char frase[1000];

	int linha = 1,tam;

	clock_t Tempo_ex[2];

	Tempo_ex[0] = clock();



	while(fgets(frase,1000,file)){

		palavras v[100];

		tam = trata_frase(v,frase);

		inserir_palavras(Raiz,v,linha,tam);

		linha++;

	}


	Tempo_ex[1] = clock();

	traco();
	printf("\nTempo gasto insercao: %g ms.\n", Tempo_gasto(Tempo_ex));

}

void imprimir(arvoreVP *Raiz){

	if (Raiz != NULL){
		
		
		imprimir(Raiz->esq);
		printf("%s :",Raiz->str);
		imprimir_lista(Raiz->l);
		imprimir(Raiz->dir);
	}

}

void busca_plv(arvoreVP *Raiz ,char str[30],int passos){ //busca um palavra na arvore imprime 
														// e mostra quantos passos foram percorridos para
														// encontar ou nao a palavra 

	if (Raiz != NULL){

		if (compara(str,Raiz->str) == 0){
			printf("\n%s :",Raiz->str);
			imprimir_lista(Raiz->l);
			printf("passos percorridos: %d\n",passos);
		
		}else if(compara(str,Raiz->str) < 0){     
			busca_plv(Raiz->esq,str,++passos);				   

		}else{									 
			busca_plv(Raiz->dir,str,++passos);       
		}
	
	}else{
		printf("\nPalavra nao encontrada!!\n");
		printf("passos percorridos: %d\n",passos);
	}

}


void calcular_tempo_busca(arvoreVP *Raiz){
	int flag = 0;
	
	clock_t tempo_busca[2];

	char str[] = "a";

	traco();
	tempo_busca[0] = clock();

	busca_plv(Raiz,str,0);

	tempo_busca[1] = clock();

	printf("\nTempo busca: %g ms\n",Tempo_gasto(tempo_busca) );

}

int menu(){ //imprime menu
	int op;
	
	printf("\n1- Inserir dados na arvore\n");
	printf("2- imprimir arvore\n");
	printf("3- buscar palavra \n");
	printf("4- remover palavra\n");
	printf("5- sair \n");
	printf("\ndigite opcao: ");
	scanf("%d",&op);

	return op;
}



int main(){
	arvoreVP *Raiz = NULL,*No;
	char str[30];

	int op,n,flag;


	FILE *file;


	abrir_arquivo(&file,"texto1.txt");
	
	ler_dados(file,&Raiz);

	calcular_tempo_busca(Raiz);

	traco();

	imprimir(Raiz);
			
	printf("\n");

	do{
		traco();
		op = menu();

		switch (op){

			case 1:

				printf("\ndigite uma palavra: ");
				scanf("%s",str);

				printf("\ndigite a linha: ");
				scanf("%d",&n);

				aloca(&No,str);

				insere(&Raiz,No,n);

				printf("\nPalavra inserida com sucesso!!\n");


				break;

			case 2:
				imprimir(Raiz);

				break;


			case 3:

				flag = 0;

				printf("\ndigite uma palavra: ");
				scanf("%s",str);

				busca_plv(Raiz,str,0);

				break;

			case 4:

				flag = 0;

				printf("\ndigite um valor: ");
				scanf("%s",str);

				printf("\ndigite a linha: ");
				scanf("%d",&n);

				flag = remover_info(&Raiz,str,n);

				if (flag == 0)
					printf("\nNao foi possivel remover palavra!!\n");
				else
					printf("\npalavra removida com sucesso!!\n");


				break;
	

			case 5:

				printf("\nSaindo.....\n");
						
			
			default:
				printf("\nopcao invalida!!!\n");

				break;
			

		}


	}while(op != 5);
	


	return 0;
}