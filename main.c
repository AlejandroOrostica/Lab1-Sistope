#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define LECTURA 0
#define ESCRITURA 1


char** procesarLinea(char* linea,char** lista){

    int tamano = strlen(linea);
	char delimitador[2] = ",";

	char *token = strtok(linea, delimitador);
    int j =0;
	while(token != NULL)
	{
		
		lista[j]=token;
        token = strtok(NULL, delimitador);
        
        j++;
	}


	
    return lista;
	
} 



int main(int argc, char const *argv[]){
    int pid, radio, numeroDiscos, ppid;
    numeroDiscos = 2;
    int* pids = (int*)malloc(sizeof(int)*numeroDiscos);

    int** arregloPipes = (int**)malloc(sizeof(int*)*numeroDiscos*2)
    for(int i=0 ; i<numeroDiscos*2; i++){
        arregloPipes[i] = (int*)malloc(sizeof(int)*2)
    }
    
    FILE* archivo;
    char buffer[100];
    char* linea= (char*)malloc(sizeof(char)*100);
    char* puntoV = (char*)malloc(sizeof(char)*100);
    char* puntoU = (char*)malloc(sizeof(char)*100);
    puntoU, puntoV = '\0'
    char** lista= (char**)malloc(sizeof(char*)*5);
    for(int i=0;i<5;i++){
        lista[i]= (char*)malloc(sizeof(char)*100);
    }    


    ppid = getpid();

    for(int i=0; i<numeroDiscos; i++){
        if(ppid == getpid()){
            pid = fork()
            
        }
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
    
    

    }
    
    return 0;
}