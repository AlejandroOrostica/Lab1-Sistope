#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

float calcularMediaReal(float* numerosReales, int n ){
    int i;
    float total = 0.0; 

    for(i=0; i<n ; i++ ){
        total += numerosReales[i]
    }
    total = total / n 
    return total;
}

float calcularMediaImaginaria(float* numerosImaginarios, int n ){
    int i;
    float total = 0.0; 

    for(i=0; i<n ; i++ ){
        total += numerosImaginarios[i]
    }
    total = total / n 
    return total;
}

float calcularPotencia(float* numerosReales, float* numerosImaginarios){
    int i,n;
    float total = 0.0;
    
    for(i=0;  i<n ; i++ ){
       total += sqrtf(powf(numerosReales[i], 2.0) + powf(numerosImaginarios[i], 2.0))
    }
}

float calcularRuido(float* ruido){
    int i,n;
    float total = 0.0
    for(i=0; i<n, i++){
        total += ruido[i];
    }
}




int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}
