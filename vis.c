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
    char string[100];
    read(atoi(argv[2]),string, 100);
    printf("Soy el hijito y esto lei: %s\n", string);
    return 0;
}
