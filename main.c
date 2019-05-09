#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <math.h>

#define LECTURA 0
#define ESCRITURA 1
void crearSalida(){
    FILE* salida;
    salida = fopen("propiedades.txt", "w");
    for(int i=0;i<5;i++){
        char cadena1[] = "Disco :\n";
        fwrite( cadena1, sizeof(char), strlen(cadena1), salida );
        char cadena2[] = "Media Real:\n";
        fwrite( cadena2, sizeof(char), strlen(cadena2), salida );
        char cadena3[] = "Media Imaginaria:\n";
        fwrite( cadena3, sizeof(char), strlen(cadena3), salida );
        char cadena4[] = "Ruido Total:\n";
        fwrite( cadena4, sizeof(char), strlen(cadena4), salida );
    }




    fclose(salida);
    
}

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

float calcularDistancia(char** lista){
    float distancia =  sqrtf( powf(atof(lista[0]),2.0) +  powf(atof(lista[1]),2.0) );
    return distancia;
}



int main(int argc, char const *argv[]){
    int pid, radio, numeroDiscos, ppid;
    float distancia;
    numeroDiscos = 1;
    int* pids = (int*)malloc(sizeof(int)*numeroDiscos);

    int** arregloPipes = (int**)malloc(sizeof(int*)*numeroDiscos*2);
    for(int i=0 ; i<numeroDiscos*2; i++){
        arregloPipes[i] = (int*)malloc(sizeof(int)*2);
    }
    
    FILE* archivo;
    char buffer[100];
    char* linea= (char*)malloc(sizeof(char)*100);
    char* puntoV = (char*)malloc(sizeof(char)*100);
    char* puntoU = (char*)malloc(sizeof(char)*100);
    puntoU, puntoV = '\0';
    char** lista= (char**)malloc(sizeof(char*)*5);
    for(int i=0;i<5;i++){
        lista[i]= (char*)malloc(sizeof(char)*100);
    }    


    ppid = getpid();
    int* pipes =(int*)malloc(sizeof(int)*2);
    pipe(pipes);
    char *canalWrite = malloc(sizeof(char)*100);
    char *canalRead = malloc(sizeof(char)*100);
    sprintf(canalWrite,"%i",pipes[ESCRITURA]);
    sprintf(canalRead,"%i",pipes[LECTURA]);
    char* string2 = (char *)malloc(10*sizeof(char));
    string2[0] = '\0';
    strcpy(string2, "hola");
    write(pipes[ESCRITURA], string2, sizeof(char)*100);
    char* array[] = {"/bin/vis",canalWrite,canalRead,NULL};

    for(int i=0; i<numeroDiscos; i++){
        if(ppid == getpid()){
            pid = fork();
            if(pid == 0){
                pids[i] = getpid();
            }
        }
    }

    if(ppid == getpid()){
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
            distancia = calcularDistancia(lista);
            for(int l=0;l<numeroDiscos;l++){
                float min= radio*l;
                float max= (radio*(l+1)); 
                
                if(distancia<max && distancia>=min){
                    printf("este dato va al disco %i\n",l+1);
                    break;
                }

            }
    
    

        }
        printf("Soy el papi \n");
        
        
        printf("Según yo mandé: %s", string2);
        fclose(archivo);
        
    }
    else{

        
        execv("/bin/vis.c",array);
        printf("Soy un hijito  \n");
    }



    
    
    return 0;
}