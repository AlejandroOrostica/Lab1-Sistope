#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <math.h>


#define LECTURA 0
#define ESCRITURA 1
void crearSalida(char* nombreArchivo, int hijo,char* mediaReal,char* mediaImaginaria,char*potencia, char* ruido){
    FILE* salida;
    salida = fopen(nombreArchivo, "a");

    char* numeroDisco = (char*) malloc(sizeof(char)*5);
    sprintf(numeroDisco, "%i", hijo+1);
    strcat(numeroDisco, ":\n");

    char cadena1[100] = "\nDisco ";
    strcat(cadena1,numeroDisco );
    fwrite( cadena1, sizeof(char), strlen(cadena1), salida );
    char cadena2[] = "Media Real:";
    fwrite( cadena2, sizeof(char), strlen(cadena2), salida );
    fwrite( mediaReal, sizeof(char), strlen(mediaReal), salida );
    char cadena3[] = "\nMedia Imaginaria:";
    fwrite( cadena3, sizeof(char), strlen(cadena3), salida );
    fwrite( mediaImaginaria, sizeof(char), strlen(mediaImaginaria), salida );
    char cadena4[] = "\nPotencia Total:";
    fwrite( cadena4, sizeof(char), strlen(cadena4), salida );
    fwrite( potencia, sizeof(char), strlen(potencia), salida );

    char cadena5[] = "\nRuido Total:";
    fwrite( cadena5, sizeof(char), strlen(cadena5), salida );
    fwrite( ruido, sizeof(char), strlen(ruido), salida );
    char cadena6[] = "\n";
    fwrite(cadena6, sizeof(char),strlen(cadena6), salida);



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



int main(int argc, char  *argv[]){
    int pid, radio, numeroDiscos, ppid,opt, flag;
    float distancia;
    flag = 0;
    char* archivoEntrada = (char*)malloc(sizeof(char)*40);
    char* archivoSalida = (char*)malloc(sizeof(char)*40);


    while((opt = getopt(argc, argv, "i:o:n:d:b")) != -1){
        switch(opt) {
            case 'i':
                strcpy(archivoEntrada,optarg);
                break;
            case 'o':
                strcpy(archivoSalida,optarg);
                break;
            case 'n':
                numeroDiscos = atoi(optarg);
                break;
            case 'd':
                radio = atoi(optarg);
                break;
            case 'b':
                flag = 1;
                break;

        }
    }

    FILE* archivoS;
    archivoS = fopen(archivoSalida,"w");
    fclose(archivoS);
    int* pids = (int*)malloc(sizeof(int)*numeroDiscos);

    int** arregloPipes = (int**)malloc(sizeof(int*)*numeroDiscos*2);
    for(int i=0 ; i<numeroDiscos*2; i++){
        arregloPipes[i] = (int*)malloc(sizeof(int)*2);
        pipe(arregloPipes[i]);
    }
    
    FILE* archivo;
    char buffer[100];
    char* linea= (char*)malloc(sizeof(char)*100);
    char** lista= (char**)malloc(sizeof(char*)*5);
    for(int i=0;i<5;i++){
        lista[i]= (char*)malloc(sizeof(char)*100);
    }    
    ppid=getpid();
    
    for(int i=0; i<numeroDiscos; i++){
        
        if(ppid == getpid()){
            
            pid = fork();
            if(pid == 0){
                pids[i] = getpid();
                char *canalWrite = malloc(sizeof(char)*100);
                char *canalRead = malloc(sizeof(char)*100);
                char *pidHijo = malloc(sizeof(char)*100);
                char *discos = malloc(sizeof(char)*100);
                char *bandera = malloc(sizeof(char)*100);
                sprintf(canalWrite,"%i",arregloPipes[2*i+1][ESCRITURA]);
                sprintf(canalRead,"%i",arregloPipes[2*i][LECTURA]);
                sprintf(pidHijo,"%i", getpid() );
                sprintf(discos,"%i",numeroDiscos);
                sprintf(bandera, "%i",flag);
                char * array[] = {"./vis",canalWrite,canalRead,pidHijo,discos,bandera,NULL};
                execv("./vis",array);




            }
        }

    }
    
    if(ppid == getpid()){
        archivo = fopen(archivoEntrada, "r");

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
                if(l==numeroDiscos-1){

                    int j=2;
                    while(j<5){

                    
                    write(arregloPipes[2*l][ESCRITURA], lista[j], sizeof(char)*100);
                    j++;
                    }//write(arregloPipes[2*l][ESCRITURA], lista[3] , sizeof(char)*100);
                   // printf("Este dato va al disco %i\n",l);
                    char *disco = malloc(sizeof(char)*100);
                    sprintf(disco,"%i",l);
                    write(arregloPipes[2*l][ESCRITURA], disco, sizeof(char)*100);
                    break;
                }
                else if(distancia<max && distancia>=min){
                    int j=2;
                    while(j<5){

                    
                    write(arregloPipes[2*l][ESCRITURA], lista[j], sizeof(char)*100);
                    j++;
                    }//write(arregloPipes[2*l][ESCRITURA], lista[3] , sizeof(char)*100);
                   // printf("Este dato va al disco %i\n",l);
                    char *disco = malloc(sizeof(char)*100);
                    sprintf(disco,"%i",l);
                    write(arregloPipes[2*l][ESCRITURA], disco, sizeof(char)*100);
                    break;
                } 

            }
            
    
    

        }
        for(int i=0; i<numeroDiscos; i++){
            char* fin = (char*)malloc(sizeof(char)*100);
            strcpy(fin, "FIN");
            write(arregloPipes[i*2][ESCRITURA],fin, sizeof(char)*100 );
        }
        
        char* mediaReal = (char*)malloc(sizeof(char)*100);
        char* mediaImaginaria = (char*)malloc(sizeof(char)*100);
        char* potencia = (char*)malloc(sizeof(char)*100);
        char* ruido = (char*)malloc(sizeof(char)*100);
        for(int i=0; i<numeroDiscos; i++){
            read(arregloPipes[i*2 +1][LECTURA],mediaReal,sizeof(char)*100);
            read(arregloPipes[i*2 +1][LECTURA],mediaImaginaria,sizeof(char)*100);
            read(arregloPipes[i*2 +1][LECTURA],potencia,sizeof(char)*100);
            read(arregloPipes[i*2 +1][LECTURA],ruido,sizeof(char)*100);
            crearSalida(archivoSalida, i, mediaReal,mediaImaginaria,potencia,ruido);

            printf("DEL HIJO %d TRAJE: \nMEDIA REAL: %s\nMEDIA IMAGINARIA: %s\nPOTENCIA: %s\nRUIDO: %s \n ", i,mediaReal,mediaImaginaria,potencia,ruido);

        }
        
        
        
        fclose(archivo);
        
    }




    
    
    return 0;
}