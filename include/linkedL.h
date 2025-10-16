#ifndef LNKD_LST
#define LNKD_LST

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct _nodo {
    char letra;
    struct _nodo *sig_letra;
} NODO;

void agregar_a_LST(NODO **, char );
void imprimir_LST(NODO** );
bool buscar_en_LST(NODO **, char );
void liberar_LST(NODO **);
size_t tamano_LST(NODO **);
void invertir_LST(NODO **);

void
agregar_a_LST(NODO **inicio_LST , char letra) {
    NODO *nuevoNodo, *prevNodo, *actualNodo;
    
    nuevoNodo = (NODO *)malloc(sizeof(NODO));
    if(nuevoNodo != NULL) {
        nuevoNodo->letra = letra;
        nuevoNodo->sig_letra = NULL;
        prevNodo = NULL;
        actualNodo = *inicio_LST;
        while(actualNodo != NULL) {
            prevNodo = actualNodo;
            actualNodo = actualNodo->sig_letra;
        }
        if (prevNodo == NULL) {
            *inicio_LST = nuevoNodo;
        }
        else {
            prevNodo->sig_letra = nuevoNodo;
        }
    }
}

void
imprimir_LST(NODO** inicio_LST) {
    NODO *actual;

    actual = *inicio_LST;
    while(actual != NULL) {
        printf("%c", actual->letra);
        actual = actual->sig_letra;
    }
    printf("\n");
}

bool
buscar_en_LST(NODO **inicio_LST, char valorBuscar) {
    NODO *actualNodo;
    bool encontrado;

    actualNodo = NULL;
    encontrado = false;
    if (inicio_LST != NULL) {
        actualNodo = *inicio_LST;
        while (actualNodo != NULL && encontrado == false) {
            if (actualNodo->letra == valorBuscar){
                encontrado = true;
            }
            else {
                actualNodo = actualNodo->sig_letra;
            }
        }
    }
    else {
        encontrado = false;
    }
    return encontrado;
}

void
liberar_LST(NODO **inicio_LST) {
    NODO *actualNodo, *tempNodo;

    tempNodo = NULL;
    actualNodo = *inicio_LST;
    while(actualNodo != NULL) {
        tempNodo = actualNodo->sig_letra;
        free(actualNodo);
        actualNodo = tempNodo;
    }
    *inicio_LST = NULL;
}

size_t
tamano_LST(NODO **inicio_LST) {
    NODO * actualNodo = NULL;
    size_t tamano;

    tamano = 0;
    actualNodo = *inicio_LST;
    while (actualNodo != NULL) {
        tamano++;
        actualNodo = actualNodo->sig_letra;
    }
    return tamano;
}

void
invertir_LST(NODO **inicio_LST) {
    NODO *prevNodo, *actualNodo, *sigNodo;

    prevNodo = NULL;
    actualNodo = *inicio_LST;
    while (actualNodo != NULL) {
        sigNodo = actualNodo->sig_letra;
        actualNodo->sig_letra = prevNodo;
        prevNodo = actualNodo;
        actualNodo = sigNodo;
    }
    *inicio_LST = prevNodo;
}

#endif

