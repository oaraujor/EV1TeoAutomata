#ifndef T_MACH
#define T_MACH

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#ifdef __WIN32
	#define LIMPIAR_PANTALLA system("cls")
#else
	#define LIMPIAR_PANTALLA system("clear")
#endif

#define BLN '\0'
#define TCN "\033[0m"
#define TCV "\033[0;32m"
#define TCR "\033[0;31m"
#define TCA "\033[0;33m"

typedef enum _dir {
    L = -1,
    HALT,
    R
} Dir;

typedef struct _instruc{
    int num_estado;
    char letra_esperada;

    int ir_nuevoEstado;
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

static char mov[3] = {'L','S','R'};

typedef struct _nodo CADENA;
        
void leer_cinta(NODO **);
void _agreg_cadena(CADENA **, char );
void _impr_cadena(CADENA **);
void _free_cadena(CADENA **);


static Instruc * __buscar_instrucc(int, char, Instruc *, int);
static void __mover_cabezal (NODO** , Dir);

bool exe_turing(CADENA**, Instruc *, int);

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
        printf("|%s%c"TCN, temp_cadena->t_color ,temp_cadena->letra == BLN ? '-' : temp_cadena->letra);
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

    _free_cadena(cinta);
    _agreg_cadena(cinta, BLN);
    printf("Ingrese la cadena: ");
    while ((c = getchar()) != '\n' && c != EOF) {
        _agreg_cadena(cinta, c);
    }
    _agreg_cadena(cinta, BLN);
}

bool exe_turing(CADENA** cadena_usr, Instruc *r_trans, int tamano_instruc) {
    NODO *cabezal = NULL;
    Instruc *curr_Instruct;
    int estadoActual = 0;
    bool es_HALT;
    
    cabezal = *cadena_usr;

    es_HALT = false;
    while (!es_HALT) {
        curr_Instruct = __buscar_instrucc(estadoActual, cabezal->letra, r_trans, tamano_instruc);
        if (curr_Instruct == NULL) {
            cabezal->t_color = TCR;
            LIMPIAR_PANTALLA;
            _impr_cadena(cadena_usr);
            return false;
        }
        
        cabezal->letra = curr_Instruct->charAescribir;
        cabezal->t_color = TCA;
        usleep(600000);
        LIMPIAR_PANTALLA;
        printf("o(q_%d, %c) = o(q_%d, %c, %c) \n",
                    curr_Instruct->num_estado,
                        curr_Instruct->letra_esperada,
                                curr_Instruct->ir_nuevoEstado,
                                    curr_Instruct->charAescribir,
                                        mov[curr_Instruct->movimiento + 1]);
        _impr_cadena(cadena_usr);
        estadoActual = curr_Instruct->ir_nuevoEstado;

        if (curr_Instruct->movimiento == HALT) {
            cabezal->t_color = TCV;
            es_HALT = true;

        }
        else {
            __mover_cabezal(&cabezal, curr_Instruct->movimiento);
        }
        usleep(600000);
        LIMPIAR_PANTALLA;
        printf("o(q_%d, %c) = o(q_%d, %c, %c) \n",
                    curr_Instruct->num_estado,
                        curr_Instruct->letra_esperada,
                                curr_Instruct->ir_nuevoEstado,
                                    curr_Instruct->charAescribir,
                                        mov[curr_Instruct->movimiento + 1]);
        _impr_cadena(cadena_usr);
    }
    return true;
}

static Instruc *
__buscar_instrucc(int estadoActual, char letra_cabezal, Instruc * reglas_trans, int tamano_reglas_t) {
    int i;

    i = 0;
    for (i = 0; i < tamano_reglas_t; i++) {
        if (((reglas_trans + i)->num_estado == estadoActual) && ((reglas_trans + i)->letra_esperada  == letra_cabezal)) {
            return (reglas_trans + i);
        }
    }
    return NULL;
}

static void
__mover_cabezal (NODO** cabezal, Dir movimiento) {

    if ((*cabezal)->letra == BLN) {
        (*cabezal)->t_color = TCV;
    }
    else {
        (*cabezal)->t_color = TCN;

    }
    switch (movimiento) {
        case L:
            if((*cabezal)->prev_letra != NULL) {
                (*cabezal) = (*cabezal)->prev_letra;
            }
            break;
        case R:
            if((*cabezal)->sig_letra != NULL) {
                (*cabezal) = (*cabezal)->sig_letra;
            }
            break;
        case HALT:
            break;
    }
}

#endif