#include <stdio.h>
#include <stdlib.h>
#define Mayuscula(A) ((A > 64) && (A <91)) 
#define R 65

int buscar(char pal, char matriz[]){
	int i = 0;
	for(;i<25;i++)
		if(matriz[i] == pal)
			return i;
	return -1;
}

void cifrar(char primero, char segundo, char matriz[], char *Cis, int i){
	int pr = buscar(primero, matriz);
	int se = buscar(segundo, matriz);
	//printf("\n-- %c %d %c %d --\n", primero, pr, segundo, se);
	if(( ((pr%5)) == ((se%5)) ) ) { // Misma columna
		Cis[i] = matriz[(pr + 5)%25];
		Cis[i+1] =  matriz[(se + 5)%25];
		printf("%c%c",matriz[(pr + 5)%25],matriz[(se + 5)%25]);
	}
	else if(( ((int)(pr/5)) == ((int)(se/5)) )){ // Mismo renglon
		Cis[i] = matriz[ (((int)(pr/5)) * 5) + ((pr+1)%5)];
		Cis[i+1] =  matriz[ (((int)(se/5)) * 5) + ((se+1)%5)];
		printf("%c%c",matriz[ (((int)(pr/5)) * 5) + ((pr+1)%5)],matriz[ (((int)(se/5)) * 5) + ((se+1)%5)]);
	}
	else{ // Caso rentangulo
		Cis[i] = matriz[ (((int)(pr/5)) * 5) + ((int)(se%5))];
		Cis[i + 1] =  matriz[ (((int)(se/5)) * 5) + ((int)(pr%5))];
		printf("%c%c", matriz[ (((int)(pr/5)) * 5) + ((int)(se%5))], matriz[(((int)(se/5)) * 5) + ((int)(pr%5))]);
	}	
}

void descifrar(char primero, char segundo, char matriz[]){
	int pr = buscar(primero, matriz);
	int se = buscar(segundo, matriz);
	//printf("\n-- %c %d %c %d --\n", primero, pr, segundo, se);
	if(( ((pr%5)) == ((se%5)) ) ) { // Misma columna
		printf("%c%c",matriz[(pr + 20)%25],matriz[(se + 20)%25]);
	}
	else if(( ((int)(pr/5)) == ((int)(se/5)) )){ // Mismo renglon
		printf("%c%c",matriz[ (((int)(pr/5)) * 5) + ((pr+4)%5)],matriz[ (((int)(se/5)) * 5) + ((se+4)%5)]);
	}
	else{ // Caso rentangulo
		printf("%c%c", matriz[ (((int)(pr/5)) * 5) + ((int)(se%5))], matriz[(((int)(se/5)) * 5) + ((int)(pr%5))]);
	}	
}

int main(int argc, char** args){
	if(argc < 3){ printf("Se requieren mas argumentos\n"); return -1;}
	int Tpalabra, Tclave, i = 0 , renglon = 0, columna = 0;
	char k = 0, o = 1;	
	char *Tem;
	char alfabeto[26] = {0};
	char *letras = "ABCDEFGHIKLMNOPQRSTUVWXYZ";
	char matriz[25]; 
	
	// Conocer el tamaño de las palabras y verificacion de letras en mayusculas
	for(Tem = args[1];*Tem && Mayuscula(*Tem);Tem++); Tpalabra = Tem - args[1];
	if(*Tem){printf("Revisar palabra (Mayusculas)\n"); return -1;}
	for(Tem = args[2];*Tem && Mayuscula(*Tem); Tem++); Tclave = Tem - args[2];	 
	if(*Tem){printf("Revisar clave (Mayusculas)\n"); return -1;}
	
	char *cis = malloc(sizeof(char) * (Tpalabra + 2));

	// ALGORITMO DE PLAYFAIR
	
	// Creamos la matriz
	for(Tem = args[2]; *Tem; Tem++) // Se considera que si se repite sigue añadiendo las siguientes letras
		if(!alfabeto[*Tem - R]){
			matriz[i++] = (*Tem == 'J')? 'I' : *Tem ;
			alfabeto[*Tem - R] = 1;
			if(*Tem == 'J' || *Tem == 'I'){
				alfabeto[8] = 1;
				alfabeto[9] = 1;
			}
		}	
	// Rellenamos la matriz
	for(int j = 0; letras[j] != '\0'; j++){
	    if(!alfabeto[letras[j] - 'A']){
		matriz[i++] = letras[j];
		alfabeto[letras[j] - 'A'] = 1;
	    }
	}		
	printf("Matriz: ");
	for(int g = 0; g < 25;g++){
		if(!(g%5)) printf("\n");
		printf("%c",matriz[g]);
	}
	printf("\n");
	//
	int f = 0;
	printf("Cifrado: ");
	for(Tem = args[1]; *Tem; Tem++, f++){
		if(*Tem == 'J') *Tem = 'I';
		if((o%2 == 0)){
			if(*(Tem - 1) == *Tem)
				*Tem= 'X';
			// cifrar
			cifrar(*(Tem - 1) ,*Tem, matriz, cis,f);	
		}		
		o++;
	}
	if(Tpalabra % 2){
		*(Tem) = 'X';
    		*(Tem + 1) = '\0';
    		// cifrar
    		cifrar(*(Tem - 1) ,*Tem, matriz, cis, f);
    		Tpalabra++;
	}
	printf("\n");
	printf("Descifrado: ");
	for(int s = 0, o = 1;s<Tpalabra;s++,o++)
		if(o%2 == 0)
			descifrar(cis[o-1],cis[o], matriz);
	printf("\n");
	
	}
