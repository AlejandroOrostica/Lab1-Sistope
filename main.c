#include <stdio.h>
#include <string.h>
#include <stdlib.h>
char** procesarLinea(char* linea,char** lista){

    int tamano = strlen(linea);
	char deli[2] = ",";

	char *token = strtok(linea, deli);
    int j =0;
	while(token != NULL)
	{
		
		lista[j]=token;
        token = strtok(NULL, deli);
        
        j++;
	}


	
    return lista;
	
} 

int main(){
    FILE* archivo;
    char buffer[100];
    char* linea= (char*)malloc(sizeof(char)*100);
    char** lista= (char**)malloc(sizeof(char*)*5);
    for(int i=0;i<5;i++){
        lista[i]= (char*)malloc(sizeof(char)*100);
    }    
    archivo = fopen("prueba.csv", "r");

    while(!feof(archivo)){
    int i=0;
    int pos=0;
    while (i<1){
    fread(buffer,1,1, archivo);
    
    
    if(strcmp(buffer,"\n")==0||feof(archivo)){
        
        i++;
    }
    else{
        linea[pos]=buffer[0];
        pos++;
    }
    
    }
    //procesado de linea
    lista=procesarLinea(linea,lista);
        for(int k=0;k<5;k++){
        printf("%s ", lista[k]);
        

    }
   printf("\n");
    }
    
    return 0;
}