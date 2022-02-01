#include<stdio.h>
#include<stdlib.h>

#include<string.h>

//////////////////////////////////-- FUNCOES PARA ARVORE DE PARTICIPANTES---////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct{

	char nome_artista[30];
	char nome_personagem[30];
	char descricao[100];

}participante;


typedef struct p{

	participante info;

	struct p *esq,*dir;

}arvorebin_per;




void aloca_partcipante(arvorebin_per **No , participante p){
	arvorebin_per *novo;

	novo = (arvorebin_per *)malloc(sizeof(arvorebin_per));

	novo->info = p;
	novo->dir = novo->esq = NULL;

	*No = novo;


}

void insere_arvore_participantes(arvorebin_per **Raiz ,arvorebin_per *No){ //recebe arvore e um no e insere participante na arvores

	if (*Raiz == NULL){  				 			 	 
		*Raiz = No;     								//se a raiz for null ela recebe o No
	
	}else if( strcmp(No->info.nome_personagem , (*Raiz)->info.nome_personagem) < 0 ){            		   
		
		insere_arvore_participantes(&(*Raiz)->esq,No);   		           // faz a chamada recusiva passando a esqueda da raiz
			
	}else if( strcmp(No->info.nome_personagem , (*Raiz)->info.nome_personagem) > 0 ){         		// se o valor do No for maior que o valor da raiz
		
		insere_arvore_participantes(&(*Raiz)->dir,No);       	   // faz a chamada recusiva passando a direita da raiz
	}

	

}

void imprimir_partcipante(participante p){   //recebe uma estrutura do tipo participante
											// e imprime os dados da estrutura

	printf("\n nome do artista: %s\n",p.nome_artista);
	printf(" nome do personagem: %s\n",p.nome_personagem);
	printf(" descricao: %s\n\n",p.descricao);

}

void imprimir_arvore_participantes(arvorebin_per *Raiz){ //imprime todos os parcipantes da arvore

	if (Raiz != NULL){
		
		
		imprimir_arvore_participantes(Raiz->esq);
		
		imprimir_partcipante(Raiz->info);
		
		imprimir_arvore_participantes(Raiz->dir);
	}

}

void flush_in(){ 
int ch;
while( (ch = fgetc(stdin)) != EOF && ch != '\n' ){} 

}

void ler_participante(participante *p){  //recebe uma estrutura do tipo participante
										// ler os dados e devolve por parametro

	printf("\ndigite os dados do participante: \n");

	flush_in();

	printf("\nnome do artista: ");
	scanf("%[^\n]",p->nome_artista);

	flush_in();
	
	printf("nome do personagem: ");
	scanf("%[^\n]",p->nome_personagem);
	
	flush_in();

	printf("descricao: ");
	scanf("%[^\n]",p->descricao);

	flush_in();

}


void inserir_participantes(arvorebin_per **Raiz, int n){ //recebe arvore de participantes
														//ler dados dos participantes e insere na arvore

	arvorebin_per *No;
	
	participante p;

	if (n != 0){

		ler_participante(&p);

		aloca_partcipante(&No,p);
	
		insere_arvore_participantes(Raiz,No);


		printf("\ndigite [1] para inserir mais personagens ou [0] para parar: ");
		scanf("%d",&n);

		inserir_participantes(Raiz,n);
	}

}

//////////////////////////////- FUNÇOES PARA LISTA DE TEMPORADAS -/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void traco(){
	printf("______________________________________________________________________________\n");
}

typedef struct{  //dados temporada
	int num_temp;
	char titulo[30];
	int quant_ep;
	int ano;

	arvorebin_per *Raiz_per; //raiz da arvore de personagens


}temporadas;


typedef struct l{  //lista temporadas
	temporadas temp;
	struct l *prox;
	
}lista;

void aloca_lista(lista **No, temporadas temp){
	lista *novo;

	novo = (lista*)malloc(sizeof(lista));
	novo->temp = temp;
	novo->prox = NULL;

	*No = novo;

}
void ler_temprada(temporadas *t, int num_temp){  //recebe um struct do tipo temporada e o numero da temporada
												// ler os dados e devove a temporada lida
	traco();
	printf("DIGITE OS DADOS DA TEMPORADA %d\n",num_temp);
	
	t->num_temp = num_temp;
	
	printf("\ntitulo da temporada: ");
	scanf("%s",t->titulo);
	printf("quantidade de episodios: ");
	scanf("%d",&t->quant_ep);
	printf("ano lancamento: ");
	scanf("%d",&t->ano);

	t->Raiz_per = NULL; // inicia arvores de personagem com NULL

	traco();
	printf("INSERIR PARTICIPANTES DA TEMPORADA %d\n",num_temp);

	inserir_participantes(&t->Raiz_per,1); // ler e insere os personagem da temporada
												// na arvore de temporada

}

void imprimir_temp(lista *t){  // recebe lista de temporadas de uma serie 
							  //imprime a lista

	while(t != NULL){

		traco();

		printf("INFOMAÇOES DA TEMPORADA %d\n",t->temp.num_temp); 
		printf("\n  numero temporada: %d\n",t->temp.num_temp);
		printf("  titulo: %s\n",t->temp.titulo);
		printf("  numero de episodios: %d\n",t->temp.quant_ep);
		printf("  ano de lancamento: %d\n",t->temp.ano);

		t = t->prox;
	}

}

void insere_lista(lista **inicio, lista *No){ // recebe um no e insere temporada fim da lista
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


void inserir_temp(lista **temp, int quant_temp){    //recebe lista de temporadas e a quantidade de temporadas da serie
													//ler os dados das temporadas e insere na lista

	lista *No;
	temporadas t;

	int i=1;

	while(i<= quant_temp){

		ler_temprada(&t,i);

		aloca_lista(&No,t);
	
		insere_lista(temp,No);

		i++;

	}

}


///////////////////////////////////////////-- FUNÇOES PARA ARVORE DE SERIES ---/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


typedef struct{	
	int cod;
	char titulo[30];
	int quant_temp;

	lista *lista_temp; //ponteiro lista de temporadas

}serie;



typedef struct b{
	serie info;

	struct b *esq,*dir;


}arvorebin;  //arvore series


void aloca_arvore(arvorebin **No , serie s){
	arvorebin *novo;

	novo = (arvorebin *)malloc(sizeof(arvorebin));

	novo->info = s;
	novo->dir = novo->esq = NULL;

	*No = novo;


}
void insere_arvore(arvorebin **Raiz ,arvorebin *No){ //insere series na arvore de series

	if (*Raiz == NULL){  				 			 	 
		*Raiz = No;     								//se a raiz for null ela recebe o No
	
	}else if (No->info.cod < (*Raiz)->info.cod){            		   
		insere_arvore(&(*Raiz)->esq,No);   		           // faz a chamada recusiva passando a esqueda da raiz
			
	}else if (No->info.cod > (*Raiz)->info.cod){         								// se o valor do No for maior que o valor da raiz
		insere_arvore(&(*Raiz)->dir,No);       	   // faz a chamada recusiva passando a direita da raiz
	}

	

}


void ler_serie(serie *s){ //ler dados da serie

	traco();
	printf("digite os dados da serie: \n");
	traco();

	printf("\ncodigo: ");
	scanf("%d",&s->cod);
	printf("titulo: ");
	scanf("%s",s->titulo);
	printf("numero de tempodadas: ");
	scanf("%d",&s->quant_temp);

	s->lista_temp = NULL; //inicia lista de temporada com NUll 

	inserir_temp(&s->lista_temp,s->quant_temp); //passa a lista de temporada e a quantidade de temporadas 
								   			 // para ler e inserir as temporadas da serie na lista

}

void imprimir_serie( serie s){  //imprime titulo e numero de temporadas
								// da serie

	traco();
	printf("INFORMACOES DA SERIE:\n");

	printf("  titulo: %s\n",s.titulo);
	printf("  numero de tempodadas: %d\n",s.quant_temp);

}


void inserir_serie(arvorebin **Raiz, int n){ //ler dados e insere serie na arvore

	arvorebin *No;
	serie s;

	if (n != 0){
 
		ler_serie(&s);

		aloca_arvore(&No,s);
	
		insere_arvore(Raiz,No);


		printf("\ndigite [1] para inserir mais series ou [0] para parar: ");
		scanf("%d",&n);

		inserir_serie(Raiz,n);
	}

}
////////////////////////////////////////////-- FUNCOES RESOLVER QUESTAO ATIVIDADE --////////////////////////////////////////////////////////////////////////////////////////////////////////////

///FUNÇÃO PARA RESOLVER LETRA [A] DA QUESTAO///

void imprimir_arvore_series(arvorebin *Raiz){ //recebe arvore de series
											 // e imprime ordenado pelo codigo
											// o titulo e numero de temporadas das series da arvore
	if (Raiz != NULL){
		
		imprimir_arvore_series(Raiz->esq);
		
		imprimir_serie(Raiz->info);
		
		imprimir_arvore_series(Raiz->dir);
	}

}

///FUNÇÃO PARA RESOLVER LETRA [C] DA QUESTAO///

void imprimir_participantes_temporada(lista *t, int num,int *flag){    /*recebe lista de temporada e o numero da temporada
													   					buscado e imprime arvore de participantes da temporada
													   					se temporada buscada se for encontrado
																		*/
	if(t != NULL && *flag != 1){ //perccorre enquanto a lista nao for NULL
		
		if (t->temp.num_temp == num){

			*flag = 1;
			
			imprimir_arvore_participantes(t->temp.Raiz_per); //IMPRIME ARVORE DE PARTICIPANTES DA TEMPORADA
		
		}else
			imprimir_participantes_temporada(t->prox,num,flag);
	}
}

///FUNÇÃO AUXILIA RESOLUÇÃO DAS LETRAS B,C E D ///

void busca_serie(arvorebin *Raiz ,int cod_s,int *flag,  lista **t){ /*recebe arvore de series e o codigo da serie 
																	e devolve a lista de temporada da serie se a serie 
																	for encontrada
																*/
	if (Raiz != NULL && *flag != 1){

		if (cod_s == Raiz->info.cod){  					   		     //verifica se o valor da raiz
			*flag = 1;

			traco();
			printf("SERIE %s\n",Raiz->info.titulo);
			
			*t = Raiz->info.lista_temp;
		
		}else if(cod_s < Raiz->info.cod){                       // se o valor for menor que o valor da raiz raiz 
			
			busca_serie(Raiz->esq,cod_s,flag,t);				   // faz a chamda recursiva fazendo que a raiz va para esquerda

		}else{									 
			busca_serie(Raiz->dir,cod_s,flag,t);             // faz a chamda recursiva fazendo que a raiz va para esquerda
		}
	
	}else{
		*flag = 0;   //flag recebe 1 se o valor buscado foi encontrado
					// flag recebe 0 se o valor buscado nao foi encontrado
	}

}

///FUNÇÃO PARA RESOLVER LETRA [D] DA QUESTAO///

void imprime_personagem(arvorebin_per *Raiz , char nome_per [30] , int flag){   //recebe arvore de participantes e o nome de um personagem
																	// e imprime os dados do participante que interpreta o personagem
																   // se for encontrado

	if (Raiz != NULL && flag == 0){
		
	
		if( strcmp(nome_per , Raiz->info.nome_personagem) == 0 ){				 			 	 
			
			imprimir_partcipante(Raiz->info); //imprime dados participante

			flag = 1;

		}else if( strcmp(nome_per , Raiz->info.nome_personagem) < 0 ){            		   
			
			imprime_personagem(Raiz->esq,nome_per,flag);   		           // faz a chamada recusiva passando a esqueda da raiz
				
		}else
			imprime_personagem(Raiz->dir,nome_per,flag);       	   // faz a chamada recusiva passando a direita da raiz
	
	}

	
}


void imprimir_personagem(lista *t, char nome_per [30]){  /* recebe lista de temporadas de uma serie e o nome de um personagem
														  e percorre as temporadas 
	
														*/
	traco();
	printf("PARTICIPANTES QUE INTERPRETAM PERSONAGEM %s\n",nome_per);

	while(t != NULL){

		imprime_personagem(t->temp.Raiz_per,nome_per,0); // passa a arvore de participantes da temporada e o nome do personagem
												 // esta função ira imprimir os dados do participante que interpreta o personagem

		t = t->prox;
	}

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int menu(){ //imprime menu
	int op;
	
	printf("\n1- Inserir series\n");
	printf("2- imprimir series \n");
	printf("3- Imprimir os dados de todas as temporadas de uma serie\n");
	printf("4- Imprimir  todos  os  personagens  de  uma  determinada  temporada  de  uma  dada  serie\n");
	printf("5- Imprimir  o  nome  de  todos  os  artistas  que  interpretaram  um  determinado  personagem\n");
	printf("6- sair \n");
	printf("\ndigite opcao: ");
	scanf("%d",&op);

	return op;
}



int main(){
	arvorebin *Raiz = NULL,*No;

	lista *temporadas = NULL;

	int op,n,flag,n2;

	char nome[30];

	do{
		
		op = menu();

		switch (op){

			case 1:
				inserir_serie(&Raiz,1);

				break;

			case 2:
				imprimir_arvore_series(Raiz);

				printf("\n\n");

				break;
			
			case 3:

				printf("\ndigite o codigo da serie: ");
				scanf("%d",&n);

				flag = 0;
				busca_serie(Raiz,n,&flag,&temporadas); //BUSCA SERIE E DEVOLVE SUA LISTA DE TEMPORADA

				if (flag == 0)
					printf("\nSerie nao encontrado !!\n");

				else
					imprimir_temp(temporadas); //IMPRIME LISTA DE TEMPORADA



				break;

			case 4:

				printf("\ndigite o codigo da serie: ");
				scanf("%d",&n);

				flag = 0;
				busca_serie(Raiz,n,&flag,&temporadas); //BUSCA SERIE E DEVOLVE SUA LISTA DE TEMPORADA

				if (flag == 0)
					printf("\nSerie nao encontrado !!\n");
				
				else{
					
					printf("\ndigite o numero da temporada: ");
					scanf("%d",&n2);

				
					flag = 0;
					imprimir_participantes_temporada(temporadas,n2,&flag); //BUSCA TEMPORADA E IMPRIME ARVORE DE PARTICIPANTES

					if (flag == 0)
						printf("\nTemporada nao encontrada!!\n");
				}


				break;

			case 5:
				printf("\ndigite o codigo da serie: ");
				scanf("%d",&n);

				flag = 0;
				busca_serie(Raiz,n,&flag,&temporadas); //BUSCA SERIE E DEVOLVE SUA LISTA DE TEMPORADA

				if (flag == 0)
					printf("\nSerie nao encontrado !!\n");
				
				else{

					flush_in();

					printf("\ndigite o nome do personagem: ");
					scanf("%[^\n]",nome);

					flush_in();
					
					imprimir_personagem(temporadas,nome); //IMPRIME PARTICIPANTES QUE INTERPRETAM O PERSONAGEM ESCOLHIDO

					
				}


				break;

			case 6:
				printf("\nSAINDO.........\n");
				break;


			
			
			default:
				printf("\nopcao invalida!!!\n");

				break;
			

		}


	}while(op != 6);
	

	return 0;
}