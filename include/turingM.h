#ifndef T_MACH
#define T_MACH

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#ifdef __WIN32
	#define LIMPIAR_PANTALLA system("cls")
#else
	#define LIMPIAR_PANTALLA system("clear")
#endif

#define BLN '\0'
#define TCN "\033[0m"
#define TCV "\033[0;32m"
#define TCR "\033[0;31m"

typedef enum _dir {
    L = -1,
    S,
    R
} Dir;

typedef struct _instruc{
    // (
    int q_Actual;
    char letraEval;
    // ) = (
    int q_Sig;
    char charAescribir;
    Dir movimiento;
    // )        
} Instruc;


typedef struct _nodo {
    char letra;
    char* t_color;
    struct _nodo *sig_letra;
    struct _nodo *prev_letra;
} NODO;

typedef struct _nodo CADENA;
        
void leer_cinta(NODO **);
void _agreg_cadena(CADENA **, char );
void _impr_cadena(CADENA **);
void _free_cadena(CADENA **);

bool exe_turing(CADENA**);

void
_agreg_cadena(CADENA **usr_cadena , char letra) {
    NODO *nuevoNodo, *tempNodo;
    
    nuevoNodo = (NODO *)malloc(sizeof(NODO));
    if(nuevoNodo != NULL) {
        //init de nuevoNodo
        nuevoNodo->letra = letra;
        nuevoNodo->t_color = TCN; 
        nuevoNodo->sig_letra = NULL;
        nuevoNodo->prev_letra = NULL;
        
        //
        tempNodo = *usr_cadena;
        if(tempNodo != NULL) {
            while (tempNodo->sig_letra != NULL) {
                tempNodo = tempNodo->sig_letra;
            }
            tempNodo->sig_letra = nuevoNodo;
            nuevoNodo->prev_letra = tempNodo;
        }
        else {
            *usr_cadena = nuevoNodo;
        }
    }
}

void
_impr_cadena(CADENA** cadena) {
    CADENA *temp_cadena;

    temp_cadena = *cadena;
    printf("[");
    while(temp_cadena != NULL) {
        printf("|%s%c"TCN, temp_cadena->t_color ,temp_cadena->letra == BLN ? '_' : temp_cadena->letra);
        temp_cadena = temp_cadena->sig_letra;
    }
    printf("]\n");
}

void
_free_cadena(CADENA **cadena) {
    NODO *actualLetra, *tempNodo;

    tempNodo = NULL;
    actualLetra = *cadena;
    while(actualLetra != NULL) {
        tempNodo = actualLetra->sig_letra;
        free(actualLetra);
        actualLetra = tempNodo;
    }
    *cadena = NULL;
}

void
leer_cinta(CADENA **cinta) {
    char c;

    //do {
    _free_cadena(cinta);
    _agreg_cadena(cinta, BLN);
    printf("Ingrese la cadena: ");
    while ((c = getchar()) != '\n' && c != EOF) {
        _agreg_cadena(cinta, c);
    }
    _agreg_cadena(cinta, BLN);
    //} while(*cinta == NULL);
}

bool exe_turing(CADENA** cadena_usr) {
    return true;
}

#endif