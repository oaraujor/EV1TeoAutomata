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

//NODO para las listas encadenandas
typedef struct _nodo {
    char letra;
    struct _nodo *sig_letra;
    
} NODO;

//enum para diferenciar tipos de datos
typedef enum tipoDato {
    TODO = 0,
    LETRA,
    NUMERO,
} TIPODATO;

//agrega NODO * a la cadena (NODO * - lista encadenanda) 
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

//imprime el alfaberto (NODO * - lista encadenada)
void printAlfabeto(NODO** cadena) {
    NODO *curr;
    curr = *cadena;
    printf("S = {");
    while(curr != NULL) {
        printf("%c", curr->letra);
        if (curr->sig_letra != NULL) {  // Si NO es el último elemento
            printf(",");
        }
        curr = curr->sig_letra;
    }
    printf("}\n");
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

//funcion para leer la cadena de ingreso de stdin. y guardarla como cadena - (NODO * - lista encadenada) EVITA ERRORES!!
void leerCadena(const char *msg, NODO **cadena, TIPODATO tipoDeDato) {
    char c;
    bool valido, aceptado;
    //char *msError;

    do {
        deshacerCadena(cadena);
        valido = true;
        printf("%s", msg);

        while ((c = getchar()) != '\n' && c != EOF) {
            aceptado = false;
            switch (tipoDeDato) {
                case TODO:
                    aceptado = true;
                    break;
                default:
                    
                    break;
                //case LETRA:
                //    aceptado = (isalpha(c) || c == ' ');
                //    msError = "(Solo Letras y Espacios)";
                //    break;
                //case NUMERO:
                //    aceptado = (isdigit(c));
                //    msError = "(Solo Numeros)";
                //    break;
            }
            if (!aceptado) {
                valido = false;
            }
            else {
                c = tolower(c);
                agregarACadena(cadena, c);
            }
        }
        //if (valido == false) {
        //    LIMPIAR_PANTALLA;
        //    printf("Cadena Invalida \n", );
        //}

    } while (!valido || *cadena == NULL);
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

//crea el alfabeto (NODO* - lista encadenada), ningun elemento se repite de la cadena de entrada, ignora espacios
void crearAlfabeto(NODO **alfabeto, const char *cadena) {
    const char *cadenaAnalizar;
    cadenaAnalizar = cadena;

    int i;

    i = 0;
    while (*(cadenaAnalizar + i) != '\0') { //iterar sobre la cadena
        if (!buscarEnCadena(alfabeto, *(cadenaAnalizar + i)) && *(cadenaAnalizar + i) != ' ') {
            agregarACadena(alfabeto, *(cadenaAnalizar + i));
        }
        i++;
    }
    
}

#endif