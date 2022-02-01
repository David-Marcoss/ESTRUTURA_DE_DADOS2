#include<stdio.h>
#include<stdlib.h>

typedef struct b{

	int info1,info2;
	struct b *esq,*cen,*dir;
	int Ninfos;
	
}arvore23;

int hefolha(arvore23 *No){
	int flag = 0;

	if (No->esq == NULL && No->cen == NULL && No->dir == NULL)
		flag = 1;

	return flag;
}

void criaNo(arvore23 **No, int info, arvore23 *esq, arvore23 *cen ){

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

void quebraNo(arvore23 **No,int info, int *sobe, arvore23 **No_maior,  arvore23 *filho){

	if (info < (*No)->info1 ){ // o do meio é a info1
		
		*sobe = (*No)->info1;
		(*No)->info1 = info;
		criaNo(No_maior,(*No)->info2,(*No)->cen,(*No)->dir);
		(*No)->cen = filho;
		

	}else if (info < (*No)->info2){ // o do meio é a info
		*sobe = info; 
		criaNo(No_maior,(*No)->info2,(*No)->cen,(*No)->dir);
		(*No)->cen = filho;
		
	

	}else{ 
		*sobe = (*No)->info2;
		criaNo(No_maior,info,(*No)->dir,filho);
	}

	(*No)->dir = NULL;
	(*No)->Ninfos = 1;


}

struct b* insere(arvore23 **Raiz, arvore23 **Pai ,int info, int *sobe){
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
		
		}else if (info < (*Raiz)->info1 ){
			*Pai = *Raiz;
			No_maior= insere(&(*Raiz)->esq,Pai,info,sobe);
			
		}else if ((*Raiz)->Ninfos == 2 && info > (*Raiz)->info2){
			*Pai = *Raiz;
			No_maior= insere(&(*Raiz)->dir,Pai,info,sobe);
		}else{
			*Pai = *Raiz;
			No_maior= insere(&(*Raiz)->cen,Pai,info,sobe);
		}

		if (No_maior != NULL){
			
			if ((*Raiz)->Ninfos == 1){
				printf("sobe:%d Raiz:%d maior: %d\n",*sobe,(*Raiz)->info1,No_maior->info1);
				
				adicionaNo(Raiz,*sobe,No_maior);
				
				No_maior = NULL;
			
			}else{
				int sobe2;
				arvore23 *No_maior2;

				quebraNo(Raiz,*sobe,&sobe2,&No_maior2,No_maior);

				if (*Pai == NULL){
					arvore23 *aux;
					
					criaNo(&aux,sobe2,*Raiz,No_maior2);

					*Raiz = aux;

					No_maior = NULL;
					
				}else
					No_maior= No_maior2;


			}
			
		}

	}

	return No_maior;

}


void inserir_valores(arvore23 **Raiz){

	int n,sobe;
	arvore23 *Pai;

	printf("\ndigite -1 para parar!!\n");
	printf("digite um valor: ");
	scanf("%d",&n);

	if (n > 0){
		
		Pai = NULL;
		
		insere(Raiz,&Pai,n,&sobe);

		inserir_valores(Raiz);
	}



}
/*
IMPRIME ORDENADO
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
*/
void imprimir(arvore23 *Raiz){
		    
		if(Raiz != NULL){

			printf("%dI1 ",Raiz->info1);
			
			if(Raiz->Ninfos == 2){
			    printf("%dI2 ",Raiz->info2);
			}

			imprimir(Raiz->esq);

			imprimir(Raiz->cen);

			imprimir(Raiz->dir);


		}

}

/*

int busca(arvore23 *Raiz, int num){
	int flag = 0;    
	
	if(Raiz != NULL){
			if ( (Raiz->Info1 == num ) || (Raiz->NInfos == 2 && Raiz->Info2 == num) )
	      flag = 1;

	    else if( num < Raiz->Info1 )
	        flag = busca(Raiz->esq,num);
	        
				  else if(  Raiz->NInfos == 2 && num > Raiz->Info2 )
	            flag = busca(Raiz->dir,num);
	        else{
	            flag = busca(Raiz->cen,num);

	}				}

	 return flag;
}

*/

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
	arvore23 *Raiz = NULL,*aux;

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

				//printf("flag: %d\n",busca(Raiz,n));

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
