#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <math.h>

float calcularMediaReal(float* numerosReales, int n ){
    int i;
    float total = 0.0; 

    for(i=0; i<n ; i++ ){
        total += numerosReales[i];
    }
    total = total / n; 
    return total;
}

float calcularMediaImaginaria(float* numerosImaginarios, int n ){
    int i;
    float total = 0.0; 

    for(i=0; i<n ; i++ ){
        total += numerosImaginarios[i];
    }
    total = total / n ;
    return total;
}

float calcularPotencia(float* numerosReales, float* numerosImaginarios){
    int i,n;
    float total = 0.0;
    
    for(i=0;  i<n ; i++ ){
       total += sqrtf(powf(numerosReales[i], 2.0) + powf(numerosImaginarios[i], 2.0));
    }
    return total;
}

float calcularRuido(float* ruido){
    int i,n;
    float total = 0.0;
    for(i=0; i<n; i++){
        total += ruido[i];
    }
}




int main(int argc, char const *argv[])
{
    int i=0
    float potencia =0.0;
    float mediaImaginaria =0.0;
    float mediaReal =0.0;
    float ruido=0.0;
    float reales=0.0;
    float imaginarios=0.0;
    float total=0.0;
    char string[100];
    read(atoi(argv[2]),string, 100);
    while(strcmp(string,"FIN" )!=0){
        i++;
        //ruido+=ruidoenargv;
        //imaginarios+=imaginariosargv;
        //reales+=realesargv;
    }
    if(strcmp(string,"FIN" )==0){
        mediaReal= calcularMediaReal(reales,total);
        mediaImaginaria= calcularMediaImaginaria(imaginarios,total);
        potencia=calcularPotencia(reales,imaginarios);
        //enviar datos por el pipe al padre;

    }
    printf("Los numeros son %f %f %f %f\n",mediaReal,mediaImaginaria,potencia,ruido);
    printf("Soy el hijito y esto lei: %s\n", string);
    return 0;
}
