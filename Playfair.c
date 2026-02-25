#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 300
#define Mayuscula(A) ((A > 64) && (A < 91))
#define R 65

int buscar(char pal, char matriz[]){
    for(int i = 0; i < 25; i++)
        if(matriz[i] == pal)
            return i;
    return -1;
}

void cifrar(char primero, char segundo, char matriz[]){
    int pr = buscar(primero, matriz);
    int se = buscar(segundo, matriz);

    if((pr % 5) == (se % 5)){ // Misma columna
        printf("%c%c",
            matriz[(pr + 5) % 25],
            matriz[(se + 5) % 25]);
    }
    else if((pr / 5) == (se / 5)){ // Mismo renglón
        printf("%c%c",
            matriz[(pr/5)*5 + ((pr%5 + 1)%5)],
            matriz[(se/5)*5 + ((se%5 + 1)%5)]);
    }
    else{ // Rectángulo
        printf("%c%c",
            matriz[(pr/5)*5 + (se%5)],
            matriz[(se/5)*5 + (pr%5)]);
    }
}

void descifrar(char primero, char segundo, char matriz[]){
    int pr = buscar(primero, matriz);
    int se = buscar(segundo, matriz);

    if((pr % 5) == (se % 5)){ // Misma columna
        printf("%c%c",
            matriz[(pr + 20) % 25],
            matriz[(se + 20) % 25]);
    }
    else if((pr / 5) == (se / 5)){ // Mismo renglón
        printf("%c%c",
            matriz[(pr/5)*5 + ((pr%5 + 4)%5)],
            matriz[(se/5)*5 + ((se%5 + 4)%5)]);
    }
    else{ // Rectángulo
        printf("%c%c",
            matriz[(pr/5)*5 + (se%5)],
            matriz[(se/5)*5 + (pr%5)]);
    }
}

int main(){

    char palabra[MAX], clave[MAX];
    char matriz[25];
    char letras[] = "ABCDEFGHIKLMNOPQRSTUVWXYZ";
    char continuar;
    int opcion;

    do{
        int i = 0;
        char alfabeto[26] = {0};

        printf("\n--- MENU PLAYFAIR ---\n");
        printf("1. Cifrar\n");
        printf("2. Descifrar\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        getchar();

        printf("Ingrese mensaje (MAYUSCULAS): ");
        fgets(palabra, MAX, stdin);
        palabra[strcspn(palabra, "\n")] = 0;

        printf("Ingrese llave (MAYUSCULAS): ");
        fgets(clave, MAX, stdin);
        clave[strcspn(clave, "\n")] = 0;

        // Construcción de matriz
        for(int j = 0; clave[j]; j++){
            if(clave[j] == 'J') clave[j] = 'I';

            if(Mayuscula(clave[j]) && !alfabeto[clave[j] - R]){
                matriz[i++] = clave[j];
                alfabeto[clave[j] - R] = 1;
            }
        }

        for(int j = 0; letras[j]; j++){
            if(!alfabeto[letras[j] - R]){
                matriz[i++] = letras[j];
                alfabeto[letras[j] - R] = 1;
            }
        }
        // imprimiendo matriz
        printf("\nMatriz con llave:\n");
        for(int g = 0; g < 25; g++){
            printf("%c ", matriz[g]);
            if((g+1)%5 == 0) printf("\n");
        }

        int len = strlen(palabra);

        // Convertir J→I
        for(int k = 0; k < len; k++)
            if(palabra[k] == 'J')
                palabra[k] = 'I';

        // REGLA: Si es impar agregar X
        if(opcion == 1 && (len % 2 != 0)){
            palabra[len] = 'X';
            palabra[len+1] = '\0';
            len++;
        }

        // REGLA: Reemplazar letras repetidas
        if(opcion == 1){
            for(int k = 0; k < len-1; k++){
                if(palabra[k] == palabra[k+1]){
                    palabra[k+1] = 'X';
                }
            }
        }

        printf("\nResultado:\n");

        if(opcion == 1){  // CIFRAR
            for(int k = 0; k < len; k += 2){
                cifrar(palabra[k], palabra[k+1], matriz);
            }
        }
        else if(opcion == 2){  // DESCIFRAR
            for(int k = 0; k < len; k += 2){
                descifrar(palabra[k], palabra[k+1], matriz);
            }
        }
        else{
            printf("Opcion invalida");
        }

        printf("\n\nDesea continuar? (S/N): ");
        scanf(" %c", &continuar);

    }while(toupper(continuar) == 'S');

    printf("Programa finalizado.\n");
    return 0;
}