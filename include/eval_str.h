//archivo cabecera para el proyecto
#ifndef CADENAS
#define CADENAS

#include <string.h>
#include <ctype.h>

#include "linkedL.h"

#ifdef __WIN32
	#define LIMPIAR_PANTALLA system("cls")
#else
	#define LIMPIAR_PANTALLA system("clear")
#endif

void leer_cadena_usr(const char *, NODO **);
void str_a_LST(NODO **, const char *);
bool checar_LST_enAlfabeto(NODO **, NODO **);
void crearIniciales(const char *, NODO **);
bool procesarCadena(NODO **, NODO **, NODO**, NODO **, NODO **, NODO **);
void LST_crear_sigma(NODO **, const char *);

void
leer_cadena_usr(const char *msg, NODO **cadena) {
    char c;

    do {
        liberar_LST(cadena);
        printf("%s", msg);

        while ((c = getchar()) != '\n' && c != EOF) {
            c = tolower(c);
            agregar_a_LST(cadena, c);
        }

    } while(*cadena == NULL);
}

void
str_a_LST(NODO **inicio_LST, const char *str_a_convertir) {
    int i;

    i = 0;
    while (*(str_a_convertir + i) != '\0') {
        agregar_a_LST(inicio_LST, *(str_a_convertir + i));
        i++;
    }
    
}

bool
checar_LST_enAlfabeto(NODO **alfabeto, NODO **LST_cadena_usr) {
    NODO *temp_cad;
    bool valido;
    
    temp_cad = *LST_cadena_usr;
    
    valido = true;
    while (valido && temp_cad != NULL) {
        if (!buscar_en_LST(alfabeto, temp_cad->letra)) {
            valido = false;
        }
        temp_cad = temp_cad->sig_letra;
    }
    return valido;
}


void
crearIniciales(const char *nombre, NODO **inciales){
    const char *temp_nombreUsuario;
    bool visto_espacio = false;
    int i;

    temp_nombreUsuario = nombre;
    i = 0;

    agregar_a_LST(inciales, *(temp_nombreUsuario + i));
    while(*(temp_nombreUsuario + i) != '\0') {
        if (visto_espacio == true) {
            agregar_a_LST(inciales, *(temp_nombreUsuario + i));
            visto_espacio = false;
        }
        if(*(temp_nombreUsuario + i) == ' ') {
            visto_espacio = true;
        }
        i++;
    }
}

void
LST_crear_sigma(NODO **LST_sigma, const char *str_a_convertir) {
    const char *cadenaAnalizar;
    int i;

    cadenaAnalizar = str_a_convertir;


    i = 0;
    while (*(cadenaAnalizar + i) != '\0') { //iterar sobre la cadena
        if (!buscar_en_LST(LST_sigma, *(cadenaAnalizar + i)) && *(cadenaAnalizar + i) != ' ') {
            agregar_a_LST(LST_sigma, *(cadenaAnalizar + i));
        }
        i++;
    }
    
}

bool
procesarCadena(NODO **LST_cadena_usr, NODO **LST_matricula_i, NODO **LST_iniciales_w, NODO** LST_rev_iniciales_wi, NODO ** LST_nombre_j, NODO **LST_alfabeto) {
    
    if (checar_LST_enAlfabeto(LST_alfabeto, LST_cadena_usr) == false) {
        return false;
    }
    else {
        return true;
    }
    
}


#endif