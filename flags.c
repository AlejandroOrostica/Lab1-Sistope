#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<string.h>


int main(int argc, char** argv){

	char* nombre= NULL;
	nombre= (char*)malloc(sizeof(char)*10);

	char* rut= NULL;
	rut= (char*)malloc(sizeof(char)*10);
	int edad =0;
	int flag =0;
	int opt;

	while((opt = getopt(argc, argv, "n:r:e:m")) != -1) { 
	   switch(opt) {
	   case 'm'://se busca el flag -m, en caso de ser encontrado se setea el valor flags = 1, no se considera lo que se ingrese despues del flag -m
		   flag = 1;
		   break;
	   case 'n': //se busca el flag -n
		   strcpy(nombre,optarg);
		   break;
   	   case 'r': //se busca el flag -n
		   strcpy(rut,optarg);
		   break;
	   case 'e': //se busca el flag -n
		   edad = atoi(optarg);//se parsea el argumento ingresado junto al flag -h a entero
		   break;
	   
	
	   	 /* '?' */
	   }
	}
	if (flag){
		printf ("%s jhg ", nombre);
		printf ("%s ", rut);
		printf ("%d ", edad);
	}


	return 0;
}