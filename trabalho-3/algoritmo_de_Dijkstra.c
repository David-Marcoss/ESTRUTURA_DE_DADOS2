#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

typedef struct v{

	int vertice; //num do vertice
	int peso;   //peso do vertice


	struct v *prox;

}l_adjacencia;

typedef struct l{  //lista vertices
	
	int vertice; //num do vertice

	l_adjacencia *adj; //lista de vertice adjacentes 
		
}grafo;

typedef struct{  /* estrutura para auxiliar o Dijkstra
					guarda a distancia do vertice inicial até seu vertice adjacente
			    	seu vertice predecessor e o seu estado 'A' = aberto e 'F' fecheado*/
	
	int indice_vertice;
	int distancia;
	int predecessor;
	char estado;

}dist;


void traco(){
	printf("\n=======================================================================================================================\n");
}

void aloca_adjacencia(l_adjacencia **No,int vertice, int peso){
	
	l_adjacencia *novo;

	novo = (l_adjacencia*)malloc(sizeof(l_adjacencia));
	
	novo->vertice = vertice;
	novo->peso = peso;

	novo->prox = NULL;

	*No = novo;
}

void insere_l_adjacencia(l_adjacencia **inicio,l_adjacencia *No){ //insere vertices adjacentes na lista do vertice 
																 // recebe um no e insere no fim da lista
	
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

void cria_vertice(grafo *gr,int vertice,int vertice_adjacente,int peso, int *quant_vertices){ /*recebe o grafo e o vertice que se deseja criar e o vertece adjacente
																							    ao vertice que sera criado e tambem o pesso da aresta entre os vertice 
																								essa função ira inserir o vertice no grafo e inserir na lista do vertice o
																								seu vertice adjacente
																							   */
	
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

void inicializa_distancia(dist *distancia,int quant_vertices, int vertice_inicial){ /*recebe o vetor de distancias e inicializa
															   	                      todas as distancias com infinito e seus predecessores
																                      com -1 e inicializa todos os vertices como aberto*/
	int i;
	
	for (i = 0; i < quant_vertices; ++i){
		
		distancia[i].indice_vertice = i;
		distancia[i].distancia = INT_MAX / 2;
		distancia[i].predecessor = -1;
		distancia[i].estado = 'A';
	}

	distancia[vertice_inicial].distancia = 0; //inicializa a distancia do vertice inicial com 0

}

int existe_aberto(dist *distancia, int quant_vertices){ /*recebe o vetor de distancias
										    			  e verifica se tem algum vertice que é aberto
													   	  ou seja qua nao foi visitado ainda e retorna 1 se existe algum verte aberto
													   	  ou 0 se todos os vertices ja estão fechados*/
	int flag = 0,i=0;
	
	while( i < quant_vertices && flag != 1){
		
		if (distancia[i].estado == 'A'){
			flag = 1;
		}				 	  
		
		i++;
	}

	return flag;
}

int menor_distancia(dist *distancia, int quant_vertices){ /*recebe o vetor de distancias e aquantidade de vertices
														    e busca no vetor de distancia o indice da posição do vetor que possui
														    a menor distancia e ainda não foi visitado*/
	
	int menor = INT_MAX / 2;
	int menor_dist,i=0;

	while( i < quant_vertices){
		
		if (menor > distancia[i].distancia && distancia[i].estado == 'A'){
			menor = distancia[i].distancia;
			menor_dist = i;
		}

		i++;
	}

	return menor_dist;
}

void relaxamento(grafo *gr, dist *distancia, int menor_dist){ /*recebe um vertice do grafo e um vetor de distancia
															    e o indice da posição do vetor que possui a menor distancia
															 	e calcula e atualisa no vetor de diatancia as distancias 
															 	dos vertices adjacentes ao vertice recebido 
															 */

	l_adjacencia *aux;

	aux = gr->adj;

	while(aux != NULL){

		if(distancia[aux->vertice].distancia > distancia[menor_dist].distancia + aux->peso ){
			
			distancia[aux->vertice].distancia = distancia[menor_dist].distancia + aux->peso;
			distancia[aux->vertice].predecessor = aux->vertice;

		}

		aux = aux->prox;
	}



}

void imprimir_distancia(dist *distancia, int quant_vertices ,int vertice_inicial){

	printf("\nVertice inicial %d:\n",vertice_inicial);
	
	for (int i = 0; i < quant_vertices; ++i){
		printf("Menor distancia para o vertice [V%d]: %d\n",i,distancia[i].distancia);

	}

}

void dijkstra(grafo *gr, int vertice_inicial,dist *distancia, int quant_vertices){ /*recebe um grafo ja definido, um vertice inicial,
																				   o vetor de distancia e a quantidade de vertices 
																				   e devolve um vetor contendo as menores distancias do 
																				   vertice inicial até os demais vertices do grafo*/ 

	int menor_dist;

	inicializa_distancia(distancia,quant_vertices,vertice_inicial);
	
	while(existe_aberto(distancia,quant_vertices) != 0){
		
		menor_dist = menor_distancia(distancia,quant_vertices);

		distancia[menor_dist].estado = 'F';
		
		relaxamento(&gr[distancia[menor_dist].indice_vertice],distancia,menor_dist);

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

void grafo1(){  //grafos para teste do algoritimo de dijkstra

	grafo gr[5];
	int quant_vertices = 0;
	dist distancia[5];

	traco();
	printf("Teste Grafo 1\n");
	traco();

	cria_vertice(gr,0,1,2,&quant_vertices);	
	cria_vertice(gr,1,2,4,&quant_vertices);
	cria_vertice(gr,2,0,12,&quant_vertices);
	cria_vertice(gr,2,4,40,&quant_vertices);
	cria_vertice(gr,3,1,3,&quant_vertices);
	cria_vertice(gr,4,3,8,&quant_vertices);

	imprimir_grafo(gr,quant_vertices);

	dijkstra(gr,0,distancia,quant_vertices);

	printf("\n");
	imprimir_distancia(distancia,quant_vertices,0);

	printf("\n");

}

void grafo2(){  //grafos para teste do algoritimo de dijkstra

	grafo gr[6];
	int quant_vertices = 0;
	dist distancia[6];

	traco();
	printf("Teste Grafo 2\n");
	traco();

	cria_vertice(gr,0,1,10,&quant_vertices);	
	cria_vertice(gr,0,2,5,&quant_vertices);
	cria_vertice(gr,1,3,1,&quant_vertices);
	cria_vertice(gr,2,1,3,&quant_vertices);
	cria_vertice(gr,2,3,8,&quant_vertices);
	cria_vertice(gr,2,4,2,&quant_vertices);
	cria_vertice(gr,3,5,4,&quant_vertices);
	cria_vertice(gr,4,3,4,&quant_vertices);
	cria_vertice(gr,5,4,6,&quant_vertices);
	

	imprimir_grafo(gr,quant_vertices);

	dijkstra(gr,0,distancia,quant_vertices);

	printf("\n");
	imprimir_distancia(distancia,quant_vertices,0);

	printf("\n");


}

void criar_grafo(grafo *gr, int tam){
	int vertice, peso,quant_vertices = 0,flag = 0,i; 

	for (i = 0; i < tam; ++i){

		do{

			printf("\ndigite os vertices adjacentes a [V%d]: ",i); // o vertice a djacentes tem que esta entre os vertices do grafo
			scanf("%d",&vertice);

			printf("digite o peso: "); //o pesso nao pode ser negativo
			scanf("%d",&peso);

			cria_vertice(gr,i,vertice,peso,&quant_vertices);


			printf("\n\ndigite [1] para continuar a inserir vertices adjacentes a [V%d] ou [0] para parar: ",i);
			scanf("%d",&flag);
		
		}while(flag > 0);
		
	}

}

int main(){
	int aux,tam,vertice_inicial;
	
	grafo1();
	grafo2();

	traco();
	printf("deseja criar grafo [1] sim [2] nao: ");
	scanf("%d",&aux);

	if (aux == 1){
		traco();
		printf("Didite a quantidade de vertices do grafo: "); //valor tem que ser maior que 1
		scanf("%d",&tam);

		grafo gr[tam];

		criar_grafo(gr,tam);

		traco();
		printf("Grafo criado com suceso!!\n");
		imprimir_grafo(gr,tam);

		traco();
		printf("deseja execultar o agoritimo de dijkstra [1] sim ou [2] nao: ");
		scanf("%d",&aux);

		while(aux != 2){
			
			dist distancia[tam];
			
			printf("Dijite o valor do vertice inicial: "); //o vertice inicial tem que ser entre 0 e quantidade de vertices
			scanf("%d",&vertice_inicial);

			dijkstra(gr,vertice_inicial,distancia,tam);

			printf("\n");
			imprimir_distancia(distancia,tam,vertice_inicial);

			printf("\n");

			printf("digite [1] para execultar novemente ou [2] para parar: ");
			scanf("%d",&aux);
		}
		
	}


	return 0;
}