#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

void traco(){
	printf("\n===================================================================================================\n");
}


typedef struct{

	int I_bloco,F_bloco;  //I_bloco= Inicio do Bloco ,F_bloco = Fim do bloco
	char estado;         // Estado do bloco ('o' = ocupado , 'l' = livre)

}bloco;

typedef struct b{

	bloco info1,info2;
	struct b *esq,*cen,*dir;
	int Ninfos;

}arvore23;

int hefolha(arvore23 *No){
	int flag = 0;

	if (No != NULL){
		if (No->esq == NULL && No->cen == NULL && No->dir == NULL)
			flag = 1;
	}
	
	return flag;
}

void criaNo(arvore23 **No, bloco info, arvore23 *esq, arvore23 *cen ){ //recebe um No e uma info e cria um novo No

	*No = (arvore23 *)malloc(sizeof(arvore23));

	(*No)->info1 = info;
	(*No)->Ninfos = 1;
	(*No)->esq = esq;
	(*No)->cen = cen;
	(*No)->dir = NULL;
}

void adicionaNo(arvore23 **No, bloco info, arvore23 *filho){ /*quando o No tem espaço, adiciona a info no No
														    filho pode ser NULL ou ele sera o No com a maior
														    info apos a quebra de um No
														  */ 
	if (info.I_bloco > (*No)->info1.I_bloco ){ 
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

void quebraNo(arvore23 **No,bloco info, bloco *sobe, arvore23 **No_maior,  arvore23 *filho){ /*recebe um No e uma info
																						e um filho que pode ser NUll ou nao
																						e devolve na variavel sobe:a informação que sobe
																						No_maior: o No criado com a maior info e no
																						No fica a menor info*/

	if (info.I_bloco < (*No)->info1.I_bloco ){ // o do meio é a info1
		
		*sobe = (*No)->info1;
		(*No)->info1 = info;
		criaNo(No_maior,(*No)->info2,(*No)->cen,(*No)->dir);
		(*No)->cen = filho;
		

	}else if (info.I_bloco < (*No)->info2.I_bloco ){ // o do meio é a info
		*sobe = info; 
		criaNo(No_maior,(*No)->info2,filho,(*No)->dir); //modificação
	

	}else{ 
		*sobe = (*No)->info2;
		criaNo(No_maior,info,(*No)->dir,filho);
	}

	(*No)->dir = NULL;
	(*No)->Ninfos = 1;


}

struct b* insere(arvore23 **Pai,arvore23 **Raiz ,bloco info, bloco *sobe){ /* recebe um No pai incia sempre com NULL
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

			if (info.I_bloco < (*Raiz)->info1.I_bloco ){
			    No_maior= insere(Raiz,&(*Raiz)->esq,info,sobe);
			
		    }else if ((*Raiz)->Ninfos == 2 && info.I_bloco > (*Raiz)->info2.I_bloco){
			    No_maior= insere(Raiz,&(*Raiz)->dir,info,sobe);
		   	
		   	}else{
			    No_maior= insere(Raiz,&(*Raiz)->cen,info,sobe);
		    }

			if (No_maior != NULL){

				if ((*Raiz)->Ninfos == 1){
					adicionaNo(Raiz,*sobe,No_maior);			
					No_maior = NULL;
					
				}else{
					bloco sobe2;
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
int remove_folha_esq(arvore23 **Raiz,arvore23 **pai){ //Recebe um No folha e o seu pai e
												
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
		bloco aux = (**pai).cen->info1;
		
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

int remover_folha(arvore23 **Pai,arvore23 **Raiz, int bloco_I){  //remove o No quando é folha
												             //recebe o No que vai ter seu valor removido e o No pai
	int balanceamento = 0;									//e remover o No 

	if ((*Raiz)->Ninfos == 2){
					
		if ( bloco_I == (*Raiz)->info1.I_bloco){
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

		else if (*Raiz == (**Pai).dir){
			remove_folha_dir(Raiz,Pai);
		}

	}

	return balanceamento;
}
int remover_No_filhos_folhas(arvore23 **Raiz ,int info){ //recebe o No e a info
														//remove o valor do No quando os filhos do No são folhas 

	int balanceamento = 0;

	if(info == (**Raiz).info1.I_bloco){ //remove quando a info é a info1 do No
		
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

	bloco sobe;
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

int remover_Menor_No(arvore23 **pai_aux,arvore23 **No,bloco *info_sobe){ //recebe um No e perrcore a partir desse No buscando
																	  // a menor info e remove a info e devolve ela na info sobe

	int balanceamento = 0;

	if ((*No)->esq != NULL){

		balanceamento = remover_Menor_No(No,&(*No)->esq,info_sobe);
	
	}else{
		*info_sobe = (*No)->info1;
		balanceamento = remover_folha(pai_aux,No,(*No)->info1.I_bloco);
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

int remover(arvore23 **Pai,arvore23 **Raiz ,int info, int *flag){ 

	int balanceamento = 0;

	if(*Raiz != NULL){
		if ( ((*Raiz)->info1.I_bloco == info ) || ((*Raiz)->Ninfos == 2 && (*Raiz)->info2.I_bloco == info)){
			*flag = 1;

			if (hefolha(*Raiz) == 1){
				balanceamento = remover_folha(Pai,Raiz,info);
			
			}else if( (hefolha((*Raiz)->esq) == 1 && hefolha((*Raiz)->cen) == 1 && hefolha((*Raiz)->dir) == 1) || (hefolha((*Raiz)->esq) == 1 && hefolha((*Raiz)->cen) == 1 && (*Raiz)->Ninfos == 1)){
				balanceamento = remover_No_filhos_folhas(Raiz,info);
			
			}else{
				arvore23 *pai_aux = NULL;
				bloco info_sobe;
				
				if ((*Raiz)->info1.I_bloco == info){

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
				
		}else if( info < (*Raiz)->info1.I_bloco )
	        balanceamento = remover(Raiz,&(*Raiz)->esq,info,flag);
	        
		else if(  (*Raiz)->Ninfos == 2 && info > (*Raiz)->info2.I_bloco )
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


void flush_in(){ 
int ch;
while( (ch = fgetc(stdin)) != EOF && ch != '\n' ){} 

}

void imprimir_bloco(bloco b){

	printf("bloco: %d , %d -%c\n",b.I_bloco,b.F_bloco,b.estado);

}

struct b* busca_Menor_No(arvore23 **No){  //recebe um No e perrcore a partir desse No busca
										 // e retorna o No com a menor info
	arvore23 *aux;													  

	if ((*No)->esq != NULL)
		aux = busca_Menor_No(&(*No)->esq);
	else
		aux = *No;

	return aux;
	
}

struct b* busca_Maior_No(arvore23 **No){  //recebe um No e perrcore a partir desse No busca
										 // e retorna o No com a Maior info
	arvore23 *aux;													  

	if ((*No)->cen != NULL)
		aux = busca_Menor_No(&(*No)->cen);
	else
		aux = *No;

	return aux;
	
}

void concatenafolha(arvore23 **Raiz,arvore23 **Pai){ /* recebe o Pai e a Raiz com a info qu queremos ocupar 
													essa função é utilizadas quando temos que ocupar a quantidade exata de uma info
													entao concatenamos as infos*/
	int flag = 0,aux;

	if ((*Raiz)->Ninfos == 1){
									//caso em que a Raiz esta entre um No ocupado e um livre
		if ((*Pai)->esq == *Raiz){ //concatena raiz com a info1 do pai e remove a Raiz


			(*Pai)->info1.I_bloco = (*Raiz)->info1.I_bloco;
			remover(Pai,Raiz,(*Raiz)->info1.I_bloco,&flag); 

										  //caso em que a Raiz esta entre um No ocupado e um livre
		}else if ((*Pai)->dir == *Raiz){ //concatena raiz com a info2 do pai e remove a Raiz

			(*Pai)->info2.F_bloco = (*Raiz)->info1.F_bloco;
			
			remover(Pai,Raiz,(*Raiz)->info1.I_bloco,&flag); 
			
		}else{
									   //caso em que a Raiz esta entre duas infos ocupadas
			if ((*Pai)->Ninfos == 2){ //concatena raiz com a info1 e a info2 do pai e remove a Raiz  e a info2 do pai
				
				(*Pai)->info1.F_bloco = (*Pai)->info2.F_bloco;
				
				aux = (*Pai)->info2.I_bloco;

				remover(Pai,Raiz,(*Raiz)->info1.I_bloco,&flag);	
				remover(Pai,Raiz,aux,&flag);	
			
			}else{

			}

		}
	
	}else{   //quando a Raiz possui 2 infos
			// entao a info que queremos ocupar esta entre duas infos ocupadas
		   // concatenamos com a info do pai e removemos a Raiz	
		
		if((*Pai)->cen == *Raiz){

			(*Pai)->info1.F_bloco = (*Raiz)->info2.F_bloco;
		}else{
			(*Pai)->info2.F_bloco = (*Raiz)->info2.F_bloco;
		}

		remover(Pai,Raiz,(*Raiz)->info2.I_bloco,&flag);
		remover(Pai,Raiz,(*Raiz)->info1.I_bloco,&flag);

	}

}


void ocupa_espaco(arvore23 **Pai ,arvore23 **Raiz, int Tam_bloco, int *flag){ /*recebe o pai que inicia com Null a raiz da arvore 
																			 e a quantidade de bloco que se deseja ocupar esta função irar 
																			 a info com a quantidade livre nescessaria e se encontar o cupa o espaço
																			 se nao encontrar devolve 0 em flag para indicar que nao foi possivel realizar operação*/
   
	
	if(*Raiz != NULL && *flag != 1 ){
		
		if ( (*Raiz)->info1.estado == 'l' && ((*Raiz)->info1.F_bloco - (*Raiz)->info1.I_bloco +1) > Tam_bloco){ //caso em que o bloco livre encontrado
			*flag = 1;																						// possui mais espaço do que o desejado e é a info1 do No

			if (hefolha(*Raiz) == 1){

				if ((*Raiz)->Ninfos == 1 && *Pai == NULL){ 	//caso em que é a Raiz da arvore e so tem uma info
					(*Raiz)->info2.F_bloco = (*Raiz)->info1.F_bloco;
					(*Raiz)->info1.F_bloco -= Tam_bloco;
					(*Raiz)->info2.I_bloco = (*Raiz)->info1.F_bloco + 1;
					(*Raiz)->info2.estado = 'o';
					(*Raiz)->Ninfos = 2;
					
				}else if ((*Raiz)->Ninfos == 2){
					(*Raiz)->info1.F_bloco -= Tam_bloco;
					(*Raiz)->info2.I_bloco = (*Raiz)->info1.F_bloco + 1; 
				
					
				}else{
					
					if ((*Raiz)->info1.I_bloco < (*Pai)->info1.I_bloco ){
						(*Raiz)->info1.F_bloco -= Tam_bloco;
						(*Pai)->info1.I_bloco = (*Raiz)->info1.F_bloco + 1;

					}else{
						(*Raiz)->info1.I_bloco += Tam_bloco;

						if((*Raiz) == (*Pai)->cen) 
							(*Pai)->info1.F_bloco += Tam_bloco;	
						else
							(*Pai)->info2.F_bloco += Tam_bloco;;
					
					}

				}
			
			}else{
				arvore23 *aux;

				(*Raiz)->info1.F_bloco -= Tam_bloco;
				aux = busca_Menor_No(&(*Raiz)->cen);

				aux->info1.I_bloco = (*Raiz)->info1.F_bloco + 1;

			}

		}else if ( (*Raiz)->info1.estado == 'l' && ((*Raiz)->info1.F_bloco - (*Raiz)->info1.I_bloco + 1) == Tam_bloco){ //caso em que o bloco livre encontrado
																													// possui exatamente o espaço do que o desejado e é a info1 do No
			*flag = 1;
				
			if (hefolha(*Raiz) == 1){

				if (*Pai == NULL){	//caso em que é a Raiz da arvore

					if ((*Raiz)->Ninfos == 2){
						(*Raiz)->info2.I_bloco = (*Raiz)->info1.I_bloco;
						(*Raiz)->info1 = (*Raiz)->info2;
						(*Raiz)->Ninfos = 1;
						
					}else{
						(*Raiz)->info1.estado = 'o'; 
					}
					
				}else{
					concatenafolha(Raiz,Pai);
					
				}
			
			}else{ //caso em que o NO livre esta entre os ocupados e o No livre nao hé folha
				   //entao concatenamos os nos

				arvore23 *maior,*menor;

				maior = busca_Maior_No(&(*Raiz)->esq); //busca o maior No da esquerda
				menor = busca_Menor_No(&(*Raiz)->cen); //busca o menor No do cento

				maior->info1.F_bloco = menor->info1.F_bloco; //concatena os Nos

				remover(Pai,Raiz,menor->info1.I_bloco,flag);
				remover(Pai,Raiz,(*Raiz)->info1.I_bloco,flag);

			}
		
		}else if ( (*Raiz)->Ninfos == 2 && (*Raiz)->info2.estado == 'l' && ((*Raiz)->info2.F_bloco - (*Raiz)->info2.I_bloco + 1) > Tam_bloco){ //caso em que o bloco livre encontrado
			*flag = 1;																													// possui mais espaço do que o desejado e é a info2 do No
			
			if(hefolha(*Raiz) == 1){
				(*Raiz)->info2.I_bloco += Tam_bloco;
				(*Raiz)->info1.F_bloco += Tam_bloco;
			
			}else{
				arvore23 *aux;

				(*Raiz)->info2.F_bloco -= Tam_bloco;
				
				aux = busca_Menor_No(&(*Raiz)->dir);

				aux->info1.I_bloco = (*Raiz)->info2.F_bloco + 1;
			}

		}else if ( (*Raiz)->Ninfos == 2 && (*Raiz)->info2.estado == 'l' && ((*Raiz)->info2.F_bloco - (*Raiz)->info2.I_bloco + 1) == Tam_bloco){
			*flag = 1;

			if (hefolha(*Raiz) == 1){
				(*Raiz)->info1.F_bloco = (*Raiz)->info2.F_bloco;
				(*Raiz)->Ninfos = 1;

			
			}else{ //caso em que o NO livre esta entre os ocupados e o No livre nao hé folha
				   //entao concatenamos os nos

				arvore23 *maior,*menor;

				maior = busca_Maior_No(&(*Raiz)->cen); //busca o maior No do centro
				menor = busca_Menor_No(&(*Raiz)->dir); //busca o menor No do direita

				maior->info1.F_bloco = menor->info1.F_bloco; //concatena os Nos

				remover(Pai,Raiz,menor->info1.I_bloco,flag);
				remover(Pai,Raiz,(*Raiz)->info2.I_bloco,flag);

				
			}

		}else{

			ocupa_espaco(Raiz,&(*Raiz)->esq,Tam_bloco,flag);
			ocupa_espaco(Raiz,&(*Raiz)->cen,Tam_bloco,flag);
			ocupa_espaco(Raiz,&(*Raiz)->dir,Tam_bloco,flag);

		}
			
	}

}

void inserir_valores(arvore23 **Raiz, int quant_blocos){

	arvore23 *Pai;
	bloco info,sobe;

	info.I_bloco = info.F_bloco = 0;

	traco();
	flush_in();
	printf("digite o estado do primeiro bloco(o = ocupado ou l = livre): ");
	scanf("%c",&info.estado);
	flush_in();

	info.estado = tolower(info.estado);

	while(info.estado != 'o' && info.estado != 'l' ){
		printf("\ndigite um estado valido!!\n");
		printf("digite o estado do primeiro bloco(o = ocupado ou l = livre): ");
		scanf("%c",&info.estado);
		info.estado = tolower(info.estado);
		flush_in();

	}

	while(info.F_bloco < quant_blocos-1){

		Pai = NULL;

		traco();
		
		printf("\ninicio do bloco: %d\n",info.I_bloco);
		printf("digite o fim do bloco: ");
		scanf("%d",&info.F_bloco);

		while(info.F_bloco >= quant_blocos || info.F_bloco < info.I_bloco ){
			
			printf("\nValor invalido\n");
			printf("digite um valor valido para o fim do bloco(Espaco disponivel: %d): ",quant_blocos -info.I_bloco );
			scanf("%d",&info.F_bloco);
		}

		insere(&Pai,Raiz,info,&sobe);

		info.I_bloco = info.F_bloco + 1;

		if (info.estado == 'l')
			info.estado = 'o';
		else 
			info.estado = 'l';

	}
		
}

void imprimir(arvore23 *Raiz){

		if(Raiz != NULL){
			imprimir(Raiz->esq);

			imprimir_bloco(Raiz->info1);

			imprimir(Raiz->cen);

			if(Raiz->Ninfos == 2){
			    imprimir_bloco(Raiz->info2);
			}

			imprimir(Raiz->dir);


		}

}

int menu(){ //imprime menu
	int op;
	
	traco();
	printf("1- imprimir arvore \n");
	printf("2- Ocupar spaco \n");
	printf("3- sair \n");
	printf("\ndigite opcao: ");
	scanf("%d",&op);

	return op;
}



int main(){
	arvore23 *Raiz = NULL,*Pai;

	int op,n,flag,quant_blocos;

	traco();

	printf("\ndigite o tamanho da memoria em Mbyte: ");
	scanf("%d",&quant_blocos);

	while(quant_blocos <= 0){
		printf("\ndigite uma quantidade valida!!\n");
		printf("\ndigite o tamanho da memoria em Mbyte: ");
		scanf("%d",&quant_blocos);
	}

	inserir_valores(&Raiz,quant_blocos);

	do{
		
		op = menu();

		switch (op){

			case 1:
				traco();
				
				imprimir(Raiz);
				
				break;

			case 2:
				flag = 0;
				Pai = NULL;
				traco();

				printf("\ndigite o tamanho do bloco que voce deseja ocupar: ");
				scanf("%d",&n);

				while(n <= 0){
					printf("Valor nao pode ser menor ou igual a 0!!\n");
					printf("\ndigite o tamanho do valido: ");
					scanf("%d",&n);
				}

				ocupa_espaco(&Pai,&Raiz,n,&flag);

				printf("Saiu main\n");

				if (flag == 0){
					printf("\nquantidade de blocos informada não existe livre!!Nao e possível alocar essa quantidade de blocos.\n");
				
				}else{
					printf("\nOperacao concluida!!\n");
				}

				

				break;

			case 3:

				printf("\nSaindo.....\n");
			
				break;		
			
			default:
				printf("\nopcao invalida!!!\n");

				break;
			

		}


	}while(op != 3);
	


	return 0;
}
