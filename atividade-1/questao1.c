#include<stdio.h>
#include<string.h>
#include <math.h>

#define TAM 10

int pot(int b,int e){
	
	int i,r=1;


	for (i = 0; i < e; ++i){
		r*= b;
	}

	


	return r;

}

void misterio1(char b[TAM], float *dec, int i) {


   if( i < strlen(b)){

      if(b[i] == '1')    
      	*dec = *dec + pot(2,i); 

       misterio1(b,dec,++i);  
   
   	} 
} 


float misterio2(char b[TAM], float dec, int i){

   if(i < strlen(b) ){

     	dec = misterio2(b,dec,i+1);  
        
        if(b[i] == '1') 
          dec = dec + pot(2,i); 
    } 
	
	return(dec); 
}

 



int main(){

	char b[10] = "0s1sda1e";
	float dec = 0;
	int i=0;


	misterio1(b,&dec,i);

	printf("\n misterio1: %f \n",dec);

	printf("\n misterio2: %f \n",misterio2(b,0,0) );


	return 0;
}