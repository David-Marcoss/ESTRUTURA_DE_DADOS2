#include<stdio.h>
#include<stdlib.h>

typedef struct b{

	int info1,info2;
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

void criaNo(arvore23 **No, int info, arvore23 *esq, arvore23 *cen ){ //recebe um No e uma info e cria um novo No

	*No = (arvore23 *)malloc(sizeof(arvore23));

	(*No)->info1 = info;
	(*No)->Ninfos = 1;
	(*No)->esq = esq;
	(*No)->cen = cen;
	(*No)->dir = NULL;
}

void adicionaNo(arvore23 **No, int info, arvore23 *filho){ /*quando o No tem espaço, adiciona a info no No
														    filho pode ser NULL ou ele sera o No com a maior
														    info apos a quebra de um No
														  */ 
	if (info > (*No)->info1 ){ 
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

void quebraNo(arvore23 **No,int info, int *sobe, arvore23 **No_maior,  arvore23 *filho){ /*recebe um No e uma info
																						e um filho que pode ser NUll ou nao
																						e devolve na variavel sobe:a informação que sobe
																						No_maior: o No criado com a maior info e no
																						No fica a menor info*/

	if (info < (*No)->info1 ){ // o do meio é a info1
		
		*sobe = (*No)->info1;
		(*No)->info1 = info;
		criaNo(No_maior,(*No)->info2,(*No)->cen,(*No)->dir);
		(*No)->cen = filho;
		

	}else if (info < (*No)->info2){ // o do meio é a info
		*sobe = info; 
		criaNo(No_maior,(*No)->info2,filho,(*No)->dir); //modificação
	

	}else{ 
		*sobe = (*No)->info2;
		criaNo(No_maior,info,(*No)->dir,filho);
	}

	(*No)->dir = NULL;
	(*No)->Ninfos = 1;


}

struct b* insere(arvore23 **Pai,arvore23 **Raiz ,int info, int *sobe){ /* recebe um No pai incia sempre com NULL
																		A Raiz e uma info e insere a info na arvore*/
	arvore23 *No_maior;
	No_maior = NULL;

	if (*Raiz == NULL){
		criaNo(Raiz,info,NULL,NULL);

	}else{

		if (hefolha(*Raiz) == 1){
			printf("inserir: %d \n",info);
			
			if ((*Raiz)->Ninfos == 1  && info !=(*Raiz)->info1 ){
				adicionaNo(Raiz,info,NULL);
			
			}else if(info != (*Raiz)->info1  && info !=(*Raiz)->info2){
				
				quebraNo(Raiz,info,sobe,&No_maior,NULL);
				printf("sobe q1:%d \n",*sobe);

				if (*Pai == NULL){
					arvore23 *aux;
					criaNo(&aux,*sobe,*Raiz,No_maior);

					*Raiz = aux;

					No_maior = NULL;
				}
			}
		
		}else {

			if (info < (*Raiz)->info1 ){
			    No_maior= insere(Raiz,&(*Raiz)->esq,info,sobe);
			
		    }else if ((*Raiz)->Ninfos == 2 && info > (*Raiz)->info2){
			    No_maior= insere(Raiz,&(*Raiz)->dir,info,sobe);
		   	
		   	}else if ( ((*Raiz)->Ninfos == 2 && info > (*Raiz)->info1 && info < (*Raiz)->info2) || (*Raiz)->Ninfos == 1 && info > (*Raiz)->info1 ){
			    No_maior= insere(Raiz,&(*Raiz)->cen,info,sobe);
		    }

			if (No_maior != NULL){

				if ((*Raiz)->Ninfos == 1){
					adicionaNo(Raiz,*sobe,No_maior);			
					No_maior = NULL;
					
				}else{
					int sobe2;
					arvore23 *No_maior2;

					printf("inserir sobe:%d \n",*sobe);
			
					quebraNo(Raiz,*sobe,&sobe2,&No_maior2,No_maior);

					printf("sobe q2:%d \n",sobe2);

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
		int aux = (**pai).cen->info1;
		
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

int remover_folha(arvore23 **Pai,arvore23 **Raiz, int info){  //remove o No quando é folha
												             //recebe o No que vai ter seu valor removido e o No pai
	int balanceamento = 0;									//e remover o No 

	if ((*Raiz)->Ninfos == 2){
					
		if (info == (*Raiz)->info1 ){
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

int remover_No_filhos_folhas(arvore23 **Raiz ,int info){ //recebe o No e a info
														//remove o valor do No quando os filhos do No são folhas 

	int balanceamento = 0;

	if(info == (**Raiz).info1){ //remove quando a info é a info1 do No
		
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

	int sobe;
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

int remover_Menor_No(arvore23 **pai_aux,arvore23 **No,int *info_sobe){ //recebe um No e perrcore a partir desse No buscando
																	  // a menor info e remove a info e devolve ela na info sobe

	int balanceamento = 0;

	if ((*No)->esq != NULL){

		balanceamento = remover_Menor_No(No,&(*No)->esq,info_sobe);
	
	}else{
		*info_sobe = (*No)->info1;
		balanceamento = remover_folha(pai_aux,No,(*No)->info1);
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
		if ( ((*Raiz)->info1 == info ) || ((*Raiz)->Ninfos == 2 && (*Raiz)->info2 == info)){
			*flag = 1;

			if (hefolha(*Raiz) == 1){ 
				balanceamento = remover_folha(Pai,Raiz,info);
			
			}else if( (hefolha((*Raiz)->esq) == 1 && hefolha((*Raiz)->cen) == 1 && hefolha((*Raiz)->dir) == 1) || (hefolha((*Raiz)->esq) == 1 && hefolha((*Raiz)->cen) == 1 && (*Raiz)->Ninfos == 1)){
				balanceamento = remover_No_filhos_folhas(Raiz,info);
			
			}else{
				arvore23 *pai_aux = NULL;
				int info_sobe;
				
				if ((*Raiz)->info1 == info){

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
				
		}else if( info < (*Raiz)->info1 )
	        balanceamento = remover(Raiz,&(*Raiz)->esq,info,flag);
	        
		else if(  (*Raiz)->Ninfos == 2 && info > (*Raiz)->info2 )
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

/*
void inserir_valores(arvore23 **Raiz){


	int n,sobe;
	arvore23 *Pai;

	printf("\ndigite -1 para parar!!\n");
	printf("digite um valor: ");
	scanf("%d",&n);

	if(n > 0){
		
		Pai = NULL;
		
		insere(&Pai,Raiz,n,&sobe);

		inserir_valores(Raiz);
	}



}*/

void inserir_valores(arvore23 **Raiz){

		
	int tam = 5,sobe; //,135,451,229,407,402,399
	
	int v[5] ={120,50,500,600,450};
	


	arvore23 *Pai;
	
	for (int i = 0; i < tam; ++i){
		
		Pai = NULL;
		
		insere(&Pai,Raiz,v[i],&sobe);
		printf("\n");

	}
		
}
void imprimir(arvore23 *Raiz){
		    
		if(Raiz != NULL){
			imprimir(Raiz->esq);

			printf("%d ",Raiz->info1);

			imprimir(Raiz->cen);

			if(Raiz->Ninfos == 2){
			    printf("%d ",Raiz->info2);
			}

			imprimir(Raiz->dir);


		}

}

/*void imprimir(arvore23 *Raiz){
		    
		if(Raiz != NULL){

			printf("%dI1 ",Raiz->info1);
			
			if(Raiz->Ninfos == 2){
			    printf("%dI2 ",Raiz->info2);
			}

			imprimir(Raiz->esq);

			imprimir(Raiz->cen);

			imprimir(Raiz->dir);


		}

}*/

int busca(arvore23 *Raiz, int num){
	int flag = 0;    
	
	if(Raiz != NULL){
		if ( (Raiz->info1 == num ) || (Raiz->Ninfos == 2 && Raiz->info2 == num) )
	      flag = 1;

	    else if( num < Raiz->info1 )
	        flag = busca(Raiz->esq,num);
	        
		else if(  Raiz->Ninfos == 2 && num > Raiz->info2 )
	        flag = busca(Raiz->dir,num);
	    else{
	        flag = busca(Raiz->cen,num);

		}				
	}

	 return flag;
}


int menu(){ //imprime menu
	int op;
	
	printf("\n1- Inserir dados na arvore\n");
	printf("2- imprimir arvore \n");
	printf("3- buscar valor \n");
	printf("4- remover \n");
	printf("5- sair \n");
	printf("\ndigite opcao: ");
	scanf("%d",&op);

	return op;
}



int main(){
	arvore23 *Raiz = NULL,*Pai;

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

				printf("flag: %d\n",busca(Raiz,n));

				break;


			case 4:
				Pai = NULL;
				flag = 0;

				printf("\ndigite um valor: ");
				scanf("%d",&n);

				remover(&Pai,&Raiz,n,&flag);

				printf("flag: %d\n",flag);
	
			
				break;	

			case 5:

				printf("\nSaindo.....\n");
			
				break;		
			
			default:
				printf("\nopcao invalida!!!\n");

				break;
			

		}


	}while(op != 5);
	


	return 0;
}
