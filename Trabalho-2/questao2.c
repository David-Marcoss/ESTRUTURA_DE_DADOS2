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

typedef struct{ //armazena a palavra e sua lista
	
	char str[30];
	lista *l;

}informacao;

typedef struct b{ //estrutura de um No

	informacao info1,info2;
	struct b *esq,*cen,*dir;
	int Ninfos;
	
}arvore23;

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

int hefolha(arvore23 *No){
	int flag = 0;

	if (No != NULL){
		if (No->esq == NULL && No->cen == NULL && No->dir == NULL)
			flag = 1;
	}
	
	return flag;
}

void criaNo(arvore23 **No, informacao info,arvore23 *esq, arvore23 *cen ){ //recebe um No e uma info e cria um novo No

	*No = (arvore23 *)malloc(sizeof(arvore23));

	(*No)->info1 = info;
	(*No)->Ninfos = 1;
	(*No)->esq = esq;
	(*No)->cen = cen;
	(*No)->dir = NULL;

}

void adicionaNo(arvore23 **No, informacao info, arvore23 *filho){ /*quando o No tem espaço, adiciona a info no No
														    		filho pode ser NULL ou ele sera o No com a maior
														    		info apos a quebra de um No
														  		*/ 
	if (compara(info.str,(*No)->info1.str) > 0){ 
		(*No)->info2 = info;
		(*No)->dir = filho;
		
	}else{ //caso em que a info é menor que a info1 do No

		(*No)->info2 = (*No)->info1;
		(*No)->info1 = info;
		(*No)->dir = (*No)->cen;
		(*No)->cen = filho;


	}

	(*No)->Ninfos = 2;

}


void quebraNo(arvore23 **No,informacao info, informacao *sobe, arvore23 **No_maior,  arvore23 *filho){ /*recebe um No e uma info
																						e um filho que pode ser NUll ou nao
																						e devolve na variavel sobe:a informação que sobe
																						No_maior: o No criado com a maior info e no
																						No fica a menor info*/
	if (compara(info.str,(*No)->info1.str) < 0){ // o do meio é a info1
		
		*sobe = (*No)->info1;
		(*No)->info1 = info;
		criaNo(No_maior,(*No)->info2,(*No)->cen,(*No)->dir);
		(*No)->cen = filho;
		

	}else if (compara(info.str,(*No)->info2.str) < 0){ // o do meio é a info
		*sobe = info; 
		criaNo(No_maior,(*No)->info2,filho,(*No)->dir); //modificação

	}else{ 
		*sobe = (*No)->info2;
		criaNo(No_maior,info,(*No)->dir,filho);
	}

	(*No)->dir = NULL;
	(*No)->Ninfos = 1;


}
struct b* insere(arvore23 **Pai,arvore23 **Raiz ,informacao info, informacao *sobe, int linha){ /* recebe um No pai incia sempre com NULL
																		A Raiz e uma info e insere a info na arvore*/
	arvore23 *No_maior;
	No_maior = NULL;

	if (*Raiz == NULL){
		criaNo(Raiz,info,NULL,NULL);

	}else{

		if (hefolha(*Raiz) == 1){
			
			if ((*Raiz)->Ninfos == 1){
				adicionaNo(Raiz,info,NULL);
			
			}else{
				quebraNo(Raiz,info,sobe,&No_maior,NULL);

				if (*Pai == NULL){
					arvore23 *aux;
					criaNo(&aux,*sobe,*Raiz,No_maior);

					*Raiz = aux;

					No_maior = NULL;
				}
			}
		
		}else {

			if (compara(info.str,(*Raiz)->info1.str) < 0 ){
			    No_maior= insere(Raiz,&(*Raiz)->esq,info,sobe,linha);
			
		    }else if ((*Raiz)->Ninfos == 2 && compara(info.str,(*Raiz)->info2.str) > 0){
			    No_maior= insere(Raiz,&(*Raiz)->dir,info,sobe,linha);
		   	}else 
		   		No_maior= insere(Raiz,&(*Raiz)->cen,info,sobe,linha);
		   
			if (No_maior != NULL){

				if ((*Raiz)->Ninfos == 1){
					adicionaNo(Raiz,*sobe,No_maior);			
					No_maior = NULL;
					
				}else{
					informacao sobe2;
					arvore23 *No_maior2;
			
					quebraNo(Raiz,*sobe,&sobe2,&No_maior2,No_maior);

					if (*Pai == NULL){
						arvore23 *aux;

						criaNo(&aux,sobe2,*Raiz,No_maior2);
						*Raiz = aux;
						No_maior = NULL;
					
					}else{
						*sobe = sobe2;
						No_maior= No_maior2;
					}
				}
			}
			
		}
	}

	return No_maior;

}
void libera_No(arvore23 **No){ //remove um No

	arvore23 *aux;

	aux = *No;
	*No = NULL;
	free(aux);
}

///////////////////////////////////////////////////FUNÇÕES PARA REMOVER QUANDO É FOLHA\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

int remove_folha_esq(arvore23 **Raiz,arvore23 **pai){ //Recebe um No folha e o seu pai e
													  // remove quando o No é o esquerdo do pai
	int flag = 0;

	(**Raiz).info1 = (**pai).info1;	
		
	if((**pai).cen->Ninfos == 2){
		(**pai).info1 = (**pai).cen->info1;
		(**pai).cen->info1 = (**pai).cen->info2;
		(**pai).cen->Ninfos = 1;

	}else if((**pai).Ninfos == 2){

		(**pai).info1 = (**pai).cen->info1;
		(**pai).cen->info1 = (**pai).info2;
		
		if ((**pai).dir->Ninfos == 2){
			(**pai).info2 = (**pai).dir->info1;
			(**pai).dir->info1 = (**pai).dir->info2;
			(**pai).dir->Ninfos = 1;
		
		}else{
			adicionaNo(&(**pai).cen,(**pai).dir->info1,NULL);
			libera_No(&(**pai).dir);
	       	(**pai).Ninfos = 1;
		}
			
	}else{ //caso em que o pai e seus filhos so tem uma info
		  //entao a ao remover o valor a arvore fica desbalanceada

		adicionaNo(pai,(**pai).cen->info1,NULL);

		(**pai).Ninfos = 2;

		libera_No(&(**pai).esq);
		libera_No(&(**pai).cen);
		flag = 1;
	}


	return flag; //retorna 0 se ao remover a arvore nao foi desbalanceada
				//retorna 1 se foi desbalanceada
}

int remove_folha_cen(arvore23 **Raiz,arvore23 **pai){	//Recebe um No folha e o seu pai e
													   // remove quando o No é o centro do pai
	int flag = 0;
	
	if((**pai).esq->Ninfos == 2){
		(**Raiz).info1 = (**pai).info1;
		(**pai).info1 = (**pai).esq->info2;
		(**pai).esq->Ninfos = 1;
				

	}else if((**pai).Ninfos == 2 ){
		(**Raiz).info1 = (**pai).info2;
								
		if ((**pai).dir->Ninfos == 2){
			(**pai).info2 = (**pai).dir->info1;
			(**pai).dir->info1 = (**pai).dir->info2;
			(**pai).dir->Ninfos = 1;
		}else{
			adicionaNo(&(**pai).cen,(**pai).dir->info1,NULL);
			libera_No(&(**pai).dir);
	       	(**pai).Ninfos = 1;
		}
	
	}else{ //caso em que o pai e seus filhos so tem uma info
		  //entao a ao remover o valor a arvore fica desbalanceada

		adicionaNo(pai,(**pai).esq->info1,NULL);

		(**pai).Ninfos = 2;

		libera_No(&(**pai).esq);
		libera_No(&(**pai).dir);
		flag = 1;

	}

	return flag; //retorna 0 se ao remover a arvore nao foi desbalanceada
				//retorna 1 se foi desbalanceada
}

void remove_folha_dir(arvore23 **Raiz,arvore23 **pai){ //Recebe um No folha e o seu pai e
													  // remove quando o No é o direito do pai

	(**Raiz).info1 = (**pai).info2;
	
	if((**pai).cen->Ninfos == 2){
		(**pai).info2 = (**pai).cen->info2;
		(**pai).cen->Ninfos = 1;

	}else if((**pai).esq->Ninfos == 2){
		informacao aux = (**pai).cen->info1;
		
		(**pai).cen->info1 = (**pai).info1;
		(**pai).info1 = (**pai).esq->info2;
		(**pai).info2= aux;
		(**pai).esq->Ninfos = 1;
	
	}else{
		adicionaNo(&(**pai).cen,(**pai).info2,NULL);
		(**pai).Ninfos = 1;
		libera_No(&(**pai).dir);
	}

}

int remover_folha(arvore23 **Pai,arvore23 **Raiz, char info[30]){  //remove o No quando é folha
												             //recebe o No que vai ter seu valor removido e o No pai
	int balanceamento = 0;									//e remover o No 

	if ((*Raiz)->Ninfos == 2){
					
		if (compara(info,(*Raiz)->info1.str ) == 0){
			(*Raiz)->info1 = (*Raiz)->info2;
		}

		(*Raiz)->Ninfos = 1;
				
	}else if (*Pai == NULL){
		libera_No(Raiz);	
				
	}else{

		if (*Raiz == (**Pai).esq)
			balanceamento = remove_folha_esq(Raiz,Pai);

		else if (*Raiz == (**Pai).cen)
			balanceamento = remove_folha_cen(Raiz,Pai);

		else if (*Raiz == (**Pai).dir)
			remove_folha_dir(Raiz,Pai);

	}

	return balanceamento;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int remover_No_filhos_folhas(arvore23 **Raiz ,char info[30]){ //recebe o No e a info
														//remove o valor do No quando os filhos do No são folhas 

	int balanceamento = 0;

	if( compara(info,(**Raiz).info1.str) == 0 ){ //remove quando a info é a info1 do No
		
		if((**Raiz).cen->Ninfos == 2){
			(**Raiz).info1 = (**Raiz).cen->info1;
			(**Raiz).cen->info1 = (**Raiz).cen->info2;
		   	(**Raiz).cen->Ninfos = 1;

		}else if((**Raiz).esq->Ninfos == 2){
			(**Raiz).info1 = (**Raiz).esq->info2;
   			(**Raiz).esq->Ninfos = 1;


		}else if((**Raiz).Ninfos ==2){
				(**Raiz).info1 = (**Raiz).cen->info1;
				(**Raiz).cen->info1 = (**Raiz).info2;
				
			if((**Raiz).dir->Ninfos == 2 ){
				(**Raiz).info2 = (**Raiz).dir->info1;
				(**Raiz).dir->info1 =(**Raiz).dir->info2;
				(**Raiz).dir->Ninfos = 1;

			}else{
				adicionaNo(&(**Raiz).cen,(**Raiz).dir->info1,NULL);
				(**Raiz).Ninfos = 1;
				libera_No(&(**Raiz).dir);
			}

		}else{ 	 //caso em que o pai e seus filhos so tem uma info
		  		//entao a ao remover o valor a arvore fica desbalanceada

			arvore23 *aux;

			adicionaNo(&(**Raiz).esq,(**Raiz).cen->info1,NULL);
			aux = (**Raiz).esq;
			libera_No(&(**Raiz).cen);
			libera_No(Raiz);
			*Raiz = aux;
			balanceamento = 1;
		}

	}else{ //remove quando a info é a info2 do No

		if((**Raiz).dir->Ninfos == 2){
			(**Raiz).info2 = (**Raiz).dir->info1;
			(**Raiz).dir->info1=  (**Raiz).dir->info2;
			(**Raiz).dir->Ninfos = 1;

		}else if((**Raiz).cen->Ninfos == 2){
				(**Raiz).info2 = (**Raiz).cen->info2;
		   	(**Raiz).cen->Ninfos = 1;

		}else if((**Raiz).esq->Ninfos == 2){
				(**Raiz).info2 = (**Raiz).cen->info1;
		   		(**Raiz).cen->info1 = (**Raiz).info1;
		   		(**Raiz).info1 = (**Raiz).esq->info2;
		   		(**Raiz).esq->Ninfos = 1;

		}else{
			adicionaNo(&(**Raiz).cen,(**Raiz).dir->info1,NULL);
			(**Raiz).Ninfos = 1;
			libera_No(&(**Raiz).dir);

			
		}

	}
	
	return balanceamento; //retorna 0 se ao remover a arvore nao foi desbalanceada
						 //retorna 1 se foi desbalanceada

}

int balancear(arvore23 **Raiz, int desbalanceamento){ //recebe um No e um valor para indicar 
													 // em que lado a Raiz esta desbalanceada entao balanceia o No

	informacao sobe;
	arvore23 *No_maior;
	arvore23 *aux;

	if (desbalanceamento == -1){ //quando o desbalanceamento está para a esquerda da raiz
		aux = (*Raiz)->cen->esq;
		(*Raiz)->cen->esq = (*Raiz)->esq;
		
		if((*Raiz)->cen->Ninfos == 1){
			adicionaNo(&(*Raiz)->cen,(*Raiz)->info1,aux);
			(*Raiz)->esq = NULL;
			
			if((*Raiz)->Ninfos == 1){
				aux = *Raiz;
				*Raiz = (*Raiz)->cen;
				libera_No(&aux);
			}else{
				(*Raiz)->info1 = (*Raiz)->info2;
				(*Raiz)->esq = (*Raiz)->cen;
				(*Raiz)->cen = (*Raiz)->dir;
				(*Raiz)->dir = NULL;
				(*Raiz)->Ninfos = 1;
			}
			
		}else{
			quebraNo(&(*Raiz)->cen,(*Raiz)->info1,&sobe,&No_maior,aux);
			(*Raiz)->info1 = sobe;
			(*Raiz)->esq = (*Raiz)->cen;
			(*Raiz)->cen = No_maior;
		}

	}else if (desbalanceamento == 0){ //quando o desbalanceamento está para o centro da raiz

		if((*Raiz)->esq->Ninfos == 1){
			adicionaNo(&(*Raiz)->esq,(*Raiz)->info1,(*Raiz)->cen);
			(*Raiz)->cen = NULL;
			
			if((*Raiz)->Ninfos == 1){
				aux = *Raiz;
				*Raiz = (*Raiz)->esq;
				libera_No(&aux);

			}else{
				(*Raiz)->info1 = (*Raiz)->info2;
				(*Raiz)->cen = (*Raiz)->dir;
				(*Raiz)->dir = NULL;
				(*Raiz)->Ninfos = 1;
			}
			

		}else{
			quebraNo(&(*Raiz)->esq,(*Raiz)->info1,&sobe,&No_maior,(*Raiz)->cen);
			(*Raiz)->info1 = sobe;
			(*Raiz)->cen = No_maior;
		}
		
	
	}else{ //quando o desbalanceamento está para direita da raiz
		
		if((*Raiz)->cen->Ninfos == 1){
			adicionaNo(&(*Raiz)->cen,(*Raiz)->info2,(*Raiz)->dir);
			(*Raiz)->Ninfos = 1;
			(*Raiz)->dir = NULL;

		}else{
			quebraNo(&(*Raiz)->cen,(*Raiz)->info2,&sobe,&No_maior,(*Raiz)->dir);
			(*Raiz)->info2 = sobe;
			(*Raiz)->dir = No_maior;
		}


	}
	return 0;

}

int remover_Menor_No(arvore23 **pai_aux,arvore23 **No, informacao *info_sobe){ //recebe um No e perrcore a partir desse No buscando
																	  // a menor info e remove a info e devolve ela na info sobe

	int balanceamento = 0;

	if ((*No)->esq != NULL){

		balanceamento = remover_Menor_No(No,&(*No)->esq,info_sobe);
	
	}else{
		*info_sobe = (*No)->info1;
		balanceamento = remover_folha(pai_aux,No,(*No)->info1.str);
	}
	return balanceamento;
}
/* remover recebe a Raiz o pai que incia com NULL a info que desejamos remoer e flag
   a remoção pode ser feita atavez de 3 casos
   
   1- se o No é folha
   
   2- se os filhos do No são folhas

   3- se os filhos do No não são folhas, nesse caso é buscado o menor info da direita
   da info que queremos remover e fazemos com que a info que queremos remover receba 
   a menor info da sua direita;

	apos a remoção da info a arvore pode ter ficado desbalanceado, entao se o valor
	da variavel balanceamento for 1, quer dizer que teremos que balancear o No,
	então é chamada a funçao balancear para isso

*/

int remover(arvore23 **Pai,arvore23 **Raiz ,char info[30], int *flag){ 

	int balanceamento = 0;

	if(*Raiz != NULL){
		if ( (compara((*Raiz)->info1.str , info ) == 0 ) || ( (*Raiz)->Ninfos == 2 && compara( (*Raiz)->info2.str,info) == 0) ){
			
			*flag = 1;

			if (hefolha(*Raiz) == 1){
				balanceamento = remover_folha(Pai,Raiz,info);
			
			}else if( (hefolha((*Raiz)->esq) == 1 && hefolha((*Raiz)->cen) == 1 && hefolha((*Raiz)->dir) == 1) || (hefolha((*Raiz)->esq) == 1 && hefolha((*Raiz)->cen) == 1 && (*Raiz)->Ninfos == 1)){
				balanceamento = remover_No_filhos_folhas(Raiz,info);
			
			}else{
				arvore23 *pai_aux = NULL;
				informacao info_sobe;
				
				if (compara(info, (*Raiz)->info1.str) == 0){
					balanceamento = remover_Menor_No(&pai_aux,&(*Raiz)->cen,&info_sobe);
					(*Raiz)->info1 = info_sobe;

					if (balanceamento == 1){ //arvore foi desbalanceada para o centro
						balanceamento = balancear(Raiz,0);
					}

				}else{
					balanceamento = remover_Menor_No(&pai_aux,&(*Raiz)->dir,&info_sobe);
					(*Raiz)->info2 = info_sobe;

					if (balanceamento == 1){//arvore foi desbalanceada para a direita
						balanceamento = balancear(Raiz,1);
					}


				}

			}

				
		}else if( compara(info,(*Raiz)->info1.str) < 0 )
	        balanceamento = remover(Raiz,&(*Raiz)->esq,info,flag);
	        
		else if(  (*Raiz)->Ninfos == 2 && compara(info,(*Raiz)->info2.str) > 0)
	        balanceamento = remover(Raiz,&(*Raiz)->dir,info,flag);
	    
	    else
	        balanceamento = remover(Raiz,&(*Raiz)->cen,info,flag);

	    if (balanceamento == 1 && *Raiz != NULL && *Pai != NULL){

	    	if (*Raiz == (**Pai).esq)
				balanceamento = balancear(Pai,-1);
	    	else if (*Raiz == (**Pai).cen)
				balanceamento = balancear(Pai,0);
			else if (*Raiz == (**Pai).dir)
				balanceamento = balancear(Pai,1);
	    }
	}

	return balanceamento;
}


///////////////////////////////////////////////////Funcoes para resolução da questao\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

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

int busca(arvore23 *Raiz ,char str[30],int linha){ //busca um palavra e verifica se ela ja existe
												  //se existir apenas insere a linha na lista da palavra e devolve 1
												 //se nao devolve 0 para indicar que a palavra nao existe na arvore
	int flag = 0;

	if (Raiz != NULL){

		if (compara(str,Raiz->info1.str) == 0){
			insere_linha(&Raiz->info1.l,linha);
			flag = 1;
			
		}else if (Raiz->Ninfos == 2 && compara(str,Raiz->info2.str) == 0){
			insere_linha(&Raiz->info2.l,linha);
			flag = 1;
		
		}else if(compara(str,Raiz->info1.str) < 0){     
			flag =busca(Raiz->esq,str,linha);
		
		}else if( Raiz->Ninfos == 2 && compara(str,Raiz->info2.str) > 0){     
			flag =busca(Raiz->dir,str,linha);				   
				  
		}else{									 
			flag =busca(Raiz->cen,str,linha);       
		}
	
	}
	return flag;
}

void inserir_palavras(arvore23 **Raiz, palavras *v, int linha, int tam){/* recebe a raiz da arvore e um vetor de strings
																		 com as palavras de uma linha do texto e a linha corespondente,
																		 busca a strings e se ela ja existir insere a linha na lista da palavra
																		 se nao existir insere a palavra na arvore */

	arvore23 *No,*Pai;
	int i,flag;

	for (i = 0; i < tam; ++i){

		flag = busca(*Raiz,v[i].str,linha);

		if (flag == 0){

			informacao info,sobe;
			Pai = NULL;

			strcpy(info.str,v[i].str);
			
			info.l = NULL;
			insere_linha(&info.l,linha);
			
			insere(&Pai,Raiz,info,&sobe,linha);		
		}
	}

}
void ler_dados(FILE *file, arvore23 **Raiz){  //recebe o arquivo e a Raiz da arvore e
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

void imprimir(arvore23 *Raiz){
		    
		if(Raiz != NULL){
			imprimir(Raiz->esq);

			printf("%s :",Raiz->info1.str);
			imprimir_lista(Raiz->info1.l);

			imprimir(Raiz->cen);

			if(Raiz->Ninfos == 2){    
					printf("%s :",Raiz->info2.str);
					imprimir_lista(Raiz->info2.l);
			}

			imprimir(Raiz->dir);
		}
}

void busca_plv(arvore23 *Raiz ,char str[30],int passos){ //busca um palavra na arvore imprime 
														// e mostra quantos passos foram percorridos para
														// encontar ou nao a palavra 

	if (Raiz != NULL){

		if (compara(str,Raiz->info1.str) == 0){
			printf("\n%s :",Raiz->info1.str);
			imprimir_lista(Raiz->info1.l);
			printf("passos percorridos: %d\n",passos);

		}else if (Raiz->Ninfos == 2 && compara(str,Raiz->info2.str) == 0){
			printf("\n%s :",Raiz->info2.str);
			imprimir_lista(Raiz->info2.l);
			printf("passos percorridos: %d\n",passos);
		
		}else if(compara(str,Raiz->info1.str) < 0){     
			busca_plv(Raiz->esq,str,++passos);
		
		}else if( Raiz->Ninfos == 2 && compara(str,Raiz->info2.str) > 0){     
			busca_plv(Raiz->dir,str,++passos);				   
				  
		}else{									 
			busca_plv(Raiz->cen,str,++passos);       
		}
	
	}else{
		printf("\nPalavra nao encontrada!!\n");
		printf("passos percorridos: %d\n",passos);
	}

}

int remover_linha(arvore23 *Raiz ,char str[30], int linha){/* recebe a raiz , uma palavra e uma linha
															busca e remove a linha em que a palavra aparece
															é devolvido 0 se a linha ou palavra não foi encontrada
															é devolvido 1 se a linha foi removida e a lista ainda possui valores
															é devolvido -1 se a linha foi removida e a lista não mais possui valores
															*/
	int flag = 0;

	if (Raiz != NULL){

		if (compara(str,Raiz->info1.str) == 0){
			
			flag = remover_lista(&Raiz->info1.l,linha);

			if (Raiz->info1.l == NULL){
				flag = -1;
			}
			
		}else if (Raiz->Ninfos == 2 && compara(str,Raiz->info2.str) == 0){
			
			flag = remover_lista(&Raiz->info2.l,linha);

			if (Raiz->info2.l == NULL){
				flag = -1;
			}
		
		}else if(compara(str,Raiz->info1.str) < 0){     
			flag = remover_linha(Raiz->esq,str,linha);
		
		}else if( Raiz->Ninfos == 2 && compara(str,Raiz->info2.str) > 0){     
			flag = remover_linha(Raiz->dir,str,linha);				   
				  
		}else{									 
			flag = remover_linha(Raiz->cen,str,linha);       
		}
	
	}
	return flag;
}

int remover_info(arvore23 **Raiz, char str[30],int linha){ /* recebe a raiz , uma palavra e uma linha
															busca e remove a linha em que a palavra aparece
															e se a palavra nao possuir mais linhas remove a palavra
															da arvore*/
	int flag=0;
	arvore23 *Pai;

	flag = remover_linha(*Raiz,str,linha);
	
	if (flag == -1){
		Pai = NULL;
		remover(&Pai,Raiz,str,&flag);
	}
	
	return flag;
}

void calcular_tempo_busca(arvore23 *Raiz){
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
	arvore23 *Raiz = NULL,*No;
	palavras v[2];
	int op,n,flag;
	char str[30];


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
				scanf("%s",v[0].str);

				printf("\ndigite a linha: ");
				scanf("%d",&n);

				inserir_palavras(&Raiz,v,n,1);

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