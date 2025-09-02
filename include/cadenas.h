//archivo cabecera para el proyecto
#ifndef CADENAS
#define CADENAS

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#ifdef __WIN32
	#define LIMPIAR_PANTALLA system("cls")
#else
	#define LIMPIAR_PANTALLA system("clear")
#endif 


typedef struct _nodo {
    char letra;
    struct _nodo *sig_letra;
    
} NODO;

typedef enum tipoDato {
    ALPHA_NUM,
    LETRA,
    NUMERO,
} TIPODATO;


//void crearAlfabeto();
//void procesarCadenas();
void agregarACadena(NODO ** , char );

void deshacerCadena(NODO **);
void leerCadena(const char *, NODO **, TIPODATO );
void printCadena(NODO** );
//bool buscarEnCadena(NODO **, char );



void agregarACadena(NODO **cadena , char letra)
{
    NODO *newNODE, *prevNODE, *currNODE;
    newNODE = malloc(sizeof(NODO));
    if(newNODE != NULL) {
        newNODE->letra = letra;
        newNODE->sig_letra = NULL;
        prevNODE = NULL;
        currNODE = *cadena;
        while(currNODE != NULL) {
            prevNODE = currNODE;
            currNODE = currNODE->sig_letra;
        }
        if (prevNODE == NULL) {
            *cadena = newNODE;
        }
        else {
            prevNODE->sig_letra = newNODE;
        }
    }
}

void printCadena(NODO** list) {
    NODO *curr;
    curr = *list;
    int i = 0;
    while(curr != NULL) {
            printf("%c", curr->letra);
            curr = curr->sig_letra;
            i++;
    }
    printf("\n");
}

void deshacerCadena(NODO **list) {
    NODO *curr = NULL, *temp = NULL;
    curr = *list;
    while(curr != NULL) {
        temp = curr->sig_letra;
        free(curr);
        curr = temp;
    }
    *list = NULL;
}

void leerCadena(const char *msg, NODO **cadena, TIPODATO tipoDeDato) {
    char c;
    bool valido, aceptado;
    char *msError;

    do {
        deshacerCadena(cadena);
        valido = true;
        LIMPIAR_PANTALLA;
        printf("%s", msg);

        while ((c = getchar()) != '\n' && c != EOF) {
            aceptado = false;

            switch (tipoDeDato) {
                case ALPHA_NUM:
                    aceptado = true;
                    break;
                case LETRA:
                    aceptado = (isalpha(c) || c == ' ');
                    msError = "(Solo Letras y Espacios)";
                    break;
                case NUMERO:
                    aceptado = (isdigit(c));
                    msError = "(Solo Numeros)";
                    break;
            }

            if (!aceptado) {
                valido = false;
            }
            else {
                c = tolower(c);
                agregarACadena(cadena, c);
            }
        }
        if (valido == false) {
            LIMPIAR_PANTALLA;
            printf("Cadena Invalida %s\n", msError);
        }

    } while (!valido || *cadena == NULL);
}

/*
bool buscarEnCadena(NODO **cadena, char valorBuscar) {
    NODO *curr;
    bool encontrado = false;

    if (cadena != NULL) {
        curr = *cadena;
        while (curr != NULL && encontrado == false) {
            if (curr->letra == valorBuscar){
                encontrado = true;
            }
            curr = curr->sig_letra;
        }
    }
    return encontrado;
}

void crearAlfabeto(NODO **alfabeto, NODO **cadena){

}

*/

#endif