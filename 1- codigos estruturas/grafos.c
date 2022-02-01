#include<stdio.h>
#include<stdlib.h>


typedef struct v{

	int vertice; //num do vertice
	int peso;   //peso do vertice


	struct v *prox;

}l_adjacencia;

typedef struct l{  //lista vertices
	
	int vertice; //num do vertice

	l_adjacencia *adj; //lista de vertice adjacentes 
		
}grafo;

void aloca_adjacencia(l_adjacencia **No,int vertice, int peso){
	
	l_adjacencia *novo;

	novo = (l_adjacencia*)malloc(sizeof(l_adjacencia));
	
	novo->vertice = vertice;
	novo->peso = peso;

	novo->prox = NULL;

	*No = novo;
}

void insere_l_adjacencia(l_adjacencia **inicio,l_adjacencia *No){ // recebe um no e insere no fim da lista
	
	l_adjacencia *aux;

	if (*inicio == NULL){       //primeiro caso
		*inicio = No;         // insere o valor na primeira posição da lista
		
	
	}else{   // se o inicio nao for null

		aux = *inicio; 
		
		while(aux->prox != NULL){ // busca o ultimo no da lista
			aux= aux->prox;
		}  
		
		if (aux->vertice != No->vertice){
			aux->prox = No;     //insere o valor na ultima pisição da lista
		}

	}

}

void cria_vertice(grafo *gr,int vertice,int vertice_adjacente,int peso, int *quant_vertices){
	
	l_adjacencia *No;
	int i = 0,flag=0;
	
	while(i < *quant_vertices && flag != 1){

		if (gr[i].vertice == vertice){

			aloca_adjacencia(&No,vertice_adjacente,peso);
			insere_l_adjacencia(&gr[i].adj,No);
		
			flag = 1;

		}

		i++;

	}

	if (flag == 0){

		gr[*quant_vertices].vertice = vertice;
		gr[*quant_vertices].adj = NULL;

		aloca_adjacencia(&No,vertice_adjacente,peso);

		insere_l_adjacencia(&gr[*quant_vertices].adj,No);

		*quant_vertices+= 1;
	
	}

	
}

void imprimir_lista(l_adjacencia *v){  //imprime os vertices adjacentes

	while(v != NULL){

		printf("V%d(%d), ",v->vertice,v->peso); 
		
		v = v->prox;
	}

	printf("\n");

}

void imprimir_grafo(grafo *gr,int quant_vertices){

	for (int i = 0; i < quant_vertices; ++i){
		
		printf("vertice %d: ", gr[i].vertice);
		imprimir_lista(gr[i].adj);
	}

}

int main(){
	grafo gr[5];
	int quant_vertices = 0;

	cria_vertice(gr,0,1,2,&quant_vertices);	
	cria_vertice(gr,1,2,4,&quant_vertices);
	cria_vertice(gr,2,0,12,&quant_vertices);
	cria_vertice(gr,2,4,40,&quant_vertices);
	cria_vertice(gr,3,1,3,&quant_vertices);
	cria_vertice(gr,4,3,8,&quant_vertices);

	imprimir_grafo(gr,quant_vertices);

	return 0;
}