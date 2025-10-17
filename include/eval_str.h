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
bool evaluar_gramatica(NODO **, NODO **, NODO**, NODO **, NODO **, NODO **);
void LST_crear_sigma(NODO **, const char *);

bool compararPatron_y_continuar(NODO **, NODO **);
int contar_repeticiones_n(NODO **, NODO **);

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

/*
    Procesador de la gramática:
        L = { i (w)^n i (w^I)^(2n) j^2 }
    Donde:
        i: lista completa de matricula (NODO **LST_matricula_i)
        w: lista de iniciales (NODO **LST_iniciales_w)
        w^I: lista reversa de iniciales (NODO** LST_rev_iniciales_wi)
        j: lista completa del nombre (NODO ** LST_nombre_j)
    La funcion:
        checa alfabeto
        verificar i al inicio
        contar n >= 1 repeticiones consecutivas de w
        verificar i de nuevo
        verificar que haya exactamente 2*n repeticiones de w^I
        verificar j dos veces
        la cadena debe terminar exactamente al finalizar la segunda j
*/
bool
evaluar_gramatica(NODO **LST_cadena_usr, NODO **LST_matricula_i, NODO **LST_iniciales_w, NODO** LST_rev_iniciales_wi, NODO ** LST_nombre_j, NODO **LST_alfabeto) {
    NODO *patron_i;
    NODO *patron_w;
    NODO *patron_wi;
    NODO *patron_j;
    NODO *cursor;
    bool LST_aceptado;
    int k;
    
    patron_i = *LST_matricula_i;
    patron_w = *LST_iniciales_w;
    patron_wi = *LST_rev_iniciales_wi;
    patron_j = *LST_nombre_j;
    cursor = *LST_cadena_usr;

    if (patron_i != NULL && patron_j != NULL && patron_wi != NULL && patron_w && cursor != NULL) {
        
        if (checar_LST_enAlfabeto(LST_alfabeto, LST_cadena_usr) == false) {
            return false;
        }
        /*i al inicio */
        if (!compararPatron_y_continuar(&cursor, &patron_i)) {
            return false;
        }
    
        /*(w)^n con n >= 1 */
        int n = contar_repeticiones_n(&cursor, &patron_w);
        if (n < 1) {
            return false;
        }
    
        /*i otra vez */
        if (!compararPatron_y_continuar(&cursor, &patron_i)) {
            return false;
        }
    
        /*(w^I)^(2n) */
        k = 0;
        for (k = 0; k < 2 * n; ++k) {
            if (!compararPatron_y_continuar(&cursor, &patron_wi)) {
                return false;
            }
        }
    
        /*j^2 => j dos veces consecutivas */
        if (!compararPatron_y_continuar(&cursor, &patron_j)) {
            return false;
        }
        if (!compararPatron_y_continuar(&cursor, &patron_j)) {
            return false;
        }
    
        /*la cadena debe terminar exactamente aquí */
        if (cursor != NULL) {
            return false;
        }
        LST_aceptado = true;
    }
    else {
        return false;
    }
}


bool
compararPatron_y_continuar(NODO **LST_cursor, NODO **LST_patron) {
    NODO *orig;
    NODO *p;
    NODO *cursor_temp;

    orig = *LST_cursor;
    p = *LST_patron;
    cursor_temp = *LST_cursor;

    if (orig != NULL && p != NULL && cursor_temp != NULL) {
        while (p != NULL && cursor_temp != NULL) {
            if (p->letra != cursor_temp->letra) {
                *LST_cursor = orig;
                return false;
            }
            p = p->sig_letra;
            cursor_temp = cursor_temp->sig_letra;
        }
        if (p == NULL) {
            *LST_cursor = cursor_temp;
            return true;
        }
        *LST_cursor = orig;
        return false;
    }
    else {
        return false;
    }
}

int
contar_repeticiones_n(NODO **cursor, NODO **pattern) {
    int n = 0;
    if (*cursor != NULL && *pattern != NULL) {
        while (compararPatron_y_continuar(cursor, pattern)) {
            n++;
        }
        return n;
    }
    else {
        return 0;
    }
}


#endif