#ifndef LNKD_LST
#define LNKD_LST

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

//NODO para las listas encadenandas
typedef struct _nodo {
    char letra;
    struct _nodo *sig_letra;
} NODO;

void agregarACadena(NODO ** , char );
void printCadena(NODO** );
bool buscarEnCadena(NODO **, char );
void deshacerCadena(NODO **);
size_t tamanoCadena(NODO **);
void voltearCadena(NODO **);


//agrega NODO * a la cadena (NODO * - lista encadenanda) 
void agregarACadena(NODO **cadena , char letra) {
    NODO *newNODE, *prevNODE, *currNODE;
    newNODE = (NODO *)malloc(sizeof(NODO));
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

//imprime la cadena (NODO * - lista encadenanda) 
void printCadena(NODO** cadena) {
    NODO *curr;
    curr = *cadena;
    int i = 0;
    while(curr != NULL) {
        printf("%c", curr->letra);
        curr = curr->sig_letra;
        i++;
    }
    printf("\n");
}

//buscamos en la cadena (NODO * - lista encadenada) si valor se encuentra en cadena
bool buscarEnCadena(NODO **cadena, char valorBuscar) {
    NODO *curr;
    bool encontrado = false;

    if (cadena != NULL) {
        curr = *cadena;
        while (curr != NULL && encontrado == false) {
            if (curr->letra == valorBuscar){
                encontrado = true;
            }
            else {
                curr = curr->sig_letra;
            }
        }
    }
    else {
        encontrado = false;
    }
    return encontrado;
}

//colapsa/borra la cadena (NODO * - lista encadenanda) 
void deshacerCadena(NODO **cadena) {
    NODO *curr = NULL, *temp = NULL;
    curr = *cadena;
    while(curr != NULL) {
        temp = curr->sig_letra;
        free(curr);
        curr = temp;
    }
    *cadena = NULL;
}

size_t tamanoCadena(NODO **cadena) {
    NODO * actual = NULL;
    actual = *cadena;
    size_t conteo = 0;

    while (actual != NULL) {
        conteo++;
        actual = actual->sig_letra;
    }
    return conteo;
}

void voltearCadena(NODO **cadena) {
    NODO *prev, *actual, *sig;

    prev = NULL;
    actual = *cadena;
    
    while (actual != NULL) {
        sig = actual->sig_letra;
        actual->sig_letra = prev;
        prev = actual;
        actual = sig;
    }
    *cadena = prev;
}

#endif

