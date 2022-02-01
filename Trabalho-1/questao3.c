#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <time.h>
#define TAM 6  //quantidade de unidades que serao lidas


void traco(){

	printf("\n===========================================================================================\n");
}


double Tempo_gasto(clock_t tempo[2]){  //recebe o tempo inicial e o final da execulção
                                      // e calcula e retorna o tempo gasto

    double Tempo_ex;
	
	Tempo_ex = (tempo[1] - 	tempo[0]) * 1000.0 / CLOCKS_PER_SEC;
    

    return Tempo_ex;
}




//////////////////////////////////////--FUNÇÕES TRATAMENTO E LEITURA ARQUIVO--///////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct{  //armazena palavra
	
	char palavra[50];

}palavras;


typedef struct{   /*armazena palavra em ingles
					e um vetor contendo as palavras
					equivalentes em portugues e a quantidade
					dessas palavras
				 */
	char ingles[50];
	
	palavras portugues[10];

	int quant;
	
}vocabulario;


void abrir_arquivo(FILE **file,char arquivo[50]){

	*file = fopen(arquivo,"r");

	if (*file == NULL){
	 	printf("\nERRO: nao foi possivel abrir arquivo!!\n");
	 } 

}


void trata_string(vocabulario *v, char frase[200]){ /*recebe string lida no arquivo e trata ela
                                                        armazenando seus dados na estrutura vocabulario
                                                        Ex = texto1[100] = "line:linha,fila"
                                                        devolve: v.ingles = "line", v.portugues[] = "linha" e "fila"
                                                    */
    int i=0, tam;
    char *t,*aux;
    char texto1[200];

    tam = strlen(frase)-1;  

    strncpy(texto1, frase, strlen(frase)-1);  //elimina /n da string

    texto1[tam] = '\0';
      
    t = strtok(texto1,":");
      
    while(t != NULL){
        
        if (i == 0){
            strcpy(v->ingles,t);
        
        }else{

            aux = strtok(t,",");

            v->quant = 0;

            while(aux != NULL){
 
                strcpy(v->portugues[v->quant].palavra,aux);

                v->quant++;
                
                aux = strtok(NULL,",");
            
            }
        }
        
        t = strtok(NULL,":");
        i++;
      
    }


}

void imprime_vocabulario(vocabulario v){

    printf("%s: ",v.ingles);

    for (int i = 0; i < v.quant; ++i){
        
        printf("%s ",v.portugues[i].palavra);
    }


}


////////////////////////////////////////--FUNÇOES PARA LISTA--///////////////////////////////////////////////////////////////////////////////////

typedef struct l{  //lista palavras ingles
	
	char ingles[50];

	struct l *prox;
	
}lista;

void aloca_lista(lista **No, char plv[50]){
	lista *novo;

	novo = (lista*)malloc(sizeof(lista));
	
	strcpy(novo->ingles, plv);

	novo->prox = NULL;

	*No = novo;

}


void imprimir_lista(lista *t){  //imprime a lista

	printf("Equivalentes ingles: ");

	while(t != NULL){

		printf("%s ,",t->ingles); 
		
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
		
		aux->prox = No;     //insere o valor na ultima pisição da lista

	}

}


void insere_plv_ingles(lista **inicio, char plv[50]){ // recebe lista e a palavra em ingles e insere na lista
	
	lista *No;

	aloca_lista(&No,plv);
	insere_lista(inicio,No);

}


////////////////////////////////////////--FUNÇOES PARA ARVORE BIN--///////////////////////////////////////////////////////////////////////////////////

typedef struct b{ 			//arvore palavras portugues
	
	char palavra[50];

	lista *l_ingles;  //lista de palavras ingles

	struct b *esq,*dir;


}arvorebin;

typedef struct{           //armazena arvores de palavras
	
	char nome[30];
	arvorebin *arvore;

}unidades;


void aloca_arvore(arvorebin **No , char plv[50] ){
	
	arvorebin *novo;

	novo = (arvorebin *)malloc(sizeof(arvorebin));

	strcpy(novo->palavra, plv);
	
	novo->dir = novo->esq = NULL;

	novo->l_ingles = NULL;

	*No = novo;

}

//--ARVORE BINARIA//

void insere_arvore(arvorebin **Raiz ,arvorebin *No, char plv_ingles[50]){

	if (*Raiz == NULL){  				 			 	 
		*Raiz = No;

		insere_plv_ingles(&((*Raiz)->l_ingles), plv_ingles);
	
	}else if ( strcmp(No->palavra,(*Raiz)->palavra) < 0){

		insere_arvore(&(*Raiz)->esq,No,plv_ingles);   		
			
	}else if ( strcmp(No->palavra,(*Raiz)->palavra) > 0 ){ 
		
		insere_arvore(&(*Raiz)->dir,No,plv_ingles);       	
	
	
	}else if( strcmp(No->palavra,(*Raiz)->palavra) == 0){  /* caso em que a palavra portugues ja foi inserida 
															 entao apenas insere a palavra em ingles na lista do No
		  												  */
		
		insere_plv_ingles(&((*Raiz)->l_ingles), plv_ingles);
	
	}

	

}

void imprimir_arvore(arvorebin *Raiz){

	if (Raiz != NULL){
		

		imprimir_arvore(Raiz->esq);
		
		printf("portugues: %s ",Raiz->palavra);
		imprimir_lista(Raiz->l_ingles);
		printf("\n");

		imprimir_arvore(Raiz->dir);
	}

}

void insere_plv_portugues(arvorebin **Raiz , vocabulario v){

	int i;
	arvorebin *No;

	for (i = 0; i < v.quant; ++i){

		aloca_arvore(&No,v.portugues[i].palavra);
		
		insere_arvore(Raiz,No,v.ingles);
		
	}


}

//////////////////////////////--FUNÇOES PARA RESOLUÇÃO DA QUESTAO--////////////////////////////////////////////////////////////


void ler_dados(FILE *file, unidades uni[TAM]){ /* recebe um vetor de unidades que armazena arvores
												e um ponteiro para um arquivo essa função
												ira ler os dados dos arquivos e a cada unidade encontrada 
												inseres as palavras da unidade em uma arvore
											*/

	char frase[200],unidade[30];

	vocabulario v;

	int i,quant_unidades = -1;

    clock_t Ticks[2];

    Ticks[0] = clock();

	while(fgets(frase,200,file)){

		v.quant = 0;

		if (frase[0] == '%'){

			quant_unidades++;

			uni[quant_unidades].arvore = NULL;

			strcpy(uni[quant_unidades].nome,frase);

		}else{

			trata_string(&v,frase);

			insere_plv_portugues(&(uni[quant_unidades].arvore),v);

		}

	}

	Ticks[1] = clock();

	traco();

	printf("\nTempo gasto para insercao: %g ms.", Tempo_gasto(Ticks));

}

int imprimir_unidade(unidades uni[TAM],char unidade[30]){  //receve vetor de arvores e o nome de uma unidade
	int i,flag=0;                                        // busca e imprime a arvore de palavras da unidade

	char aux[30]="%";

	strcat(aux, unidade);

	for (i = 0; i < TAM; ++i){

		if (strncmp(uni[i].nome,aux,strlen(uni[i].nome)-1) == 0){

			printf("\n%s\n\n",unidade);

			imprimir_arvore(uni[i].arvore);
		
			printf("\n");

			flag = 1;
		}
	}

	return flag;
}

void busca_palavra(arvorebin *Raiz, char str[50],int *flag){ //busca palavra e imprime sua listas
															// se emcontrada

	if (Raiz != NULL){
		
		if ( strcmp(str,Raiz->palavra) == 0){
			imprimir_lista(Raiz->l_ingles);
			*flag = 1;
		}
		
		else if (strcmp(str,Raiz->palavra) < 0)
			busca_palavra(Raiz->esq,str,flag);
		else
			busca_palavra(Raiz->dir,str,flag);
	
	}

}

int imprimir_equivalentes_ingles(unidades uni[TAM],char str[30]){ //receve vetor de arvores e uma palavra em portugues
	int i,flag=0;                                              // e imprime todas as equivalentes em ingles

	for (i = 0; i < TAM; ++i){

		busca_palavra(uni[i].arvore,str,&flag);
		
	}

	return flag;
}

void remover_lista(lista **l){

	lista *aux;

	while(*l != NULL){
		aux = *l;
		*l = (*l)->prox;

		free(aux);

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


void remover(arvorebin **Raiz ,char str[50] ,int *flag){ //recebe arvore e uma palavra e remove a palavra e sua lista
														// e retorna 1 se a operação foi concluida
	if (*Raiz != NULL){

		if ( strcmp(str,(*Raiz)->palavra) == 0){
									 /*se entrar neste caso que dizer que o valor da raiz
									 é o no que queremos remover e Raiz_ant aponta para o No anterior 
									 do No que iramos remover */

			arvorebin *aux = NULL;

			remover_lista(&(*Raiz)->l_ingles);  //remove todas palavras da lista 

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

										      			
		
		}else if( strcmp(str,(*Raiz)->palavra) < 0){  //busca o No que sera removido
		    
			remover(&(*Raiz)->esq,str,flag);				  

		}else{

			remover(&(*Raiz)->dir,str,flag);             
		}
	
	}


}

int remover_palavra(unidades uni[TAM],char unidade[30],char str[50]){  //receve vetor de arvores e o nome de uma unidade
	int i,flag=0;                                        			//e uma palavra e busca e remove a palavra da arvore e sua lista

	char aux[30]="%";

	strcat(aux, unidade);

	for (i = 0; i < TAM; ++i){

		if (strncmp(uni[i].nome,aux,strlen(uni[i].nome)-1) == 0){

			remover(&uni[i].arvore,str,&flag);
		
			printf("\n");
		}
	}

	return flag;
}

void busca_palavra2(arvorebin *Raiz, char str[50],int *flag){ //busca palavra e devove 1 se encontrou

	if (Raiz != NULL){
		
		if ( strcmp(str,Raiz->palavra) == 0){
			*flag = 1;
		}
		
		else if (strcmp(str,Raiz->palavra) < 0)
			busca_palavra2(Raiz->esq,str,flag);
		else
			busca_palavra2(Raiz->dir,str,flag);
	
	}

}

void calcula_tempo_busca(unidades uni[TAM],char str[50]){ 
	int i,flag=0;

	clock_t Ticks[2];

    Ticks[0] = clock();                                      

	for (i = 0; i < TAM; ++i){

		busca_palavra2(uni[i].arvore,str,&flag);
		
	}


	Ticks[1] = clock();

	printf("\nTempo busca palavra %s: %g ms.", str,Tempo_gasto(Ticks));

}

int menu(){ //imprime menu
	int op;

	traco();
	
	printf("\n1- Imprimir palavras de uma unidade\n");
	printf("2- imprimir palavras em ingles equivalentes a uma em portugues\n");
	printf("3- Remover palavra em portugues e suas equivalentes em ingles\n");
	printf("4- sair \n");
	printf("\ndigite opcao: ");
	scanf("%d",&op);

	return op;
}


int main(){

	int op,n;

	FILE *file;

	unidades arvores[TAM];

	char unidade[30],str[50];


	abrir_arquivo(&file,"ingles-portugues.txt");
	
	ler_dados(file,arvores);
	
	calcula_tempo_busca(arvores,"poder");    


	do{
		
		op = menu();

		switch (op){

			case 1:

				printf("\ndigite o nome da unidade: ");
				scanf("%s",unidade);

				traco();

				n = imprimir_unidade(arvores,unidade);

				if (n == 0){
					printf("\nUnidade buscada nao exite!!!\n");
				}


			
				break;

			case 2:

				printf("\ndigite a palavra em portugues: ");
				scanf("%s",unidade);

				traco();

				n = imprimir_equivalentes_ingles(arvores,unidade);

				if (n == 0){
					printf("\nPalavra buscada nao exite!!!\n");
				}

				break;
			
			case 3:

				printf("\ndigite o nome da unidade: ");
				scanf("%s",unidade);

				printf("\ndigite a palavra em portugues: ");
				scanf("%s",str);

				traco();

				n = remover_palavra(arvores,unidade,str);

				if (n == 0)
					printf("\nPalavra ou uinidade inexistente!!!\n");
				else
					printf("\nOperacao concluida!!\n");



				break;

			case 4:
				printf("\nSAINDO.........\n");
				break;
	

			
			
			default:
				printf("\nopcao invalida!!!\n");

				break;
			

		}


	}while(op != 4);
	


	return 0;
}
