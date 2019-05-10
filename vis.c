#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <math.h>

float calcularMediaReal(float numerosReales, int n ){
    int i;
    float total = 0.0; 

    for(i=0; i<n ; i++ ){
        total += numerosReales;
    }
    total = total / n; 
    return total;
}

float calcularMediaImaginaria(float numerosImaginarios, int n ){
    int i;
    float total = 0.0; 

    for(i=0; i<n ; i++ ){
        total += numerosImaginarios;
    }
    total = total / n ;
    return total;
}

float calcularPotencia(float numerosReales, float numerosImaginarios,float n){
    float i;
    float total = 0.0;
    
    for(i=0.0;  i<n ; i++ ){
       total += sqrtf(powf(numerosReales, 2.0) + powf(numerosImaginarios, 2.0));
    }
    return total;
}

float calcularRuido(float ruido){
    int i,n;
    float total = 0.0;
    for(i=0; i<n; i++){
        total += ruido;
    }
}




int main(int argc, char const *argv[]){
    int i=0;
    int flag = atoi(argv[5]);
    float potencia =0.0;
    float mediaImaginaria =0.0;
    float mediaReal =0.0;
    float ruido=0.0;
    float reales=0.0;
    float imaginarios=0.0;
    float total=0.0;
    int disco=0;
    char* string = (char*)malloc(sizeof(char)*100);
    char fin[100] = "FIN";
    
    int k=0;
    while(i ==0){
        read(atoi(argv[2]),string, 100);
        if(strcmp(fin,string) == 0){
            
            i++;
        }
        else if(k==0){
            
            reales+=strtof(string,NULL);
       
            k++;
        }
        else if(k==1){
            
            imaginarios+=strtof(string,NULL);
            
            k++;
        }
        else if(k==2){
            
            ruido+=strtof(string,NULL);
            k++;
        }
        else if(k==3){
            
            disco=atoi(string);
            k=0;
        }        
        total+=1.0;
        
    }
    int all = (int)total;
    
    if(atoi(argv[5]) == 1){
        printf("SOY EL HIJO DE PID %s, PROCESE %i VISIBILIDADES \n ",argv[3], (all-1)/atoi(argv[4]));
    }

    
    

    
    mediaReal= calcularMediaReal(reales,total);
    
    mediaImaginaria= calcularMediaImaginaria(imaginarios,total);
    
    potencia=calcularPotencia(reales,imaginarios,total);
    

   // printf("Los numeros son %f %f %f %f\n",mediaReal,mediaImaginaria,potencia,ruido);
    char *mR = malloc(sizeof(char)*100);
    char *mI = malloc(sizeof(char)*100);
    char *p = malloc(sizeof(char)*100);
    char *r = malloc(sizeof(char)*100);
    sprintf(mR,"%f",mediaReal);
    sprintf(mI,"%f",mediaImaginaria);
    sprintf(p,"%f", potencia);
    sprintf(r,"%f",ruido);
    
    
    char* weaita = (char*)malloc(sizeof(char)*100);
    write(atoi(argv[1]), mR, sizeof(char)*100);
    write(atoi(argv[1]), mI, sizeof(char)*100);
    write(atoi(argv[1]), p, sizeof(char)*100);
    write(atoi(argv[1]), r, sizeof(char)*100);
    return 0;
}
