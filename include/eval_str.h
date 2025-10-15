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

void crearAlfabeto(NODO **, const char *);
void leer_cadena_usr(const char *, NODO **);
void printAlfabeto(NODO** );
void crearIniciales(const char *, NODO **);

bool ch_cad_EnAlfa(NODO **, NODO **);
bool ch_cad_primEsDig(NODO **);
bool procesarCadena(NODO **, NODO **, NODO **, const char*);
bool ch_cad_iniciales(NODO **, NODO **);
bool ch_cad_ptsNoConsecu(NODO **);
bool ch_cad_ptoYmatric(const char *, NODO **);

void
printAlfabeto(NODO** cadena) {
    NODO *curr;
    curr = *cadena;
    printf("SIGMA = {");
    while(curr != NULL) {
        printf("%c", curr->letra);
        if (curr->sig_letra != NULL) {
            printf(",");
        }
        curr = curr->sig_letra;
    }
    printf("}\n");
}

void
leer_cadena_usr(const char *msg, NODO **cadena) {
    char c;

    do {
        deshacerCadena(cadena);
        printf("%s", msg);

        while ((c = getchar()) != '\n' && c != EOF) {
            c = tolower(c);
            agregarACadena(cadena, c);
        }

    } while(*cadena == NULL);
}

void
crearAlfabeto(NODO **alfabeto, const char *cadena) {
    const char *cadenaAnalizar;
    int i;

    cadenaAnalizar = cadena;

    i = 0;
    while (*(cadenaAnalizar + i) != '\0') {
        if (!buscarEnCadena(alfabeto, *(cadenaAnalizar + i)) &&
                *(cadenaAnalizar + i) != ' ') {
            agregarACadena(alfabeto, *(cadenaAnalizar + i));
        }
        i++;
    }
    
}

bool
ch_cad_EnAlfa(NODO **alfabeto, NODO **cadena) {
    NODO *temp_cad;
    bool valido;
    
    temp_cad = *cadena;
    
    valido = true;
    while (valido && temp_cad != NULL) {
        if (!buscarEnCadena(alfabeto, temp_cad->letra)) {
            valido = false;
        }
        temp_cad = temp_cad->sig_letra;
    }
    return valido;
}

bool
ch_cad_primEsDig(NODO **cadena){
    bool valido;
    char cAnalizar;
    
    cAnalizar = (*cadena)->letra;
    valido = (isdigit(cAnalizar));
    
    return valido;
}

bool
ch_cad_ptsNoConsecu(NODO **cadena){
    NODO *temp_cadena_usr;
    temp_cadena_usr = *cadena;
    char letra_actual;
    bool pto_visto = false;
    
    while(temp_cadena_usr != NULL) {
        letra_actual = temp_cadena_usr->letra;
        if (letra_actual == '.') {
            if (pto_visto){
                return false;
            }
            pto_visto = true;
        }
        else {
            pto_visto = false;
        }
        temp_cadena_usr = temp_cadena_usr->sig_letra;
    }
    return true;
}
    
bool
ch_cad_ptoYmatric(const char *matricula, NODO **cadena_usuario) {
    int list_len, mat_len;
    NODO * tmp;

    if (!matricula || !cadena_usuario || !(*cadena_usuario))
        return false;

    mat_len = strlen(matricula);

    list_len = 0;
    tmp = *cadena_usuario;
    while (tmp) {
        list_len++;
        tmp = tmp->sig_letra;
    }

    if (list_len < mat_len + 1)
        return false;

    tmp = *cadena_usuario;
    for (int i = 0; i < list_len - (mat_len + 1); i++) {
        tmp = tmp->sig_letra;
    }

    if (tmp->letra != '.')
        return false;

    tmp = tmp->sig_letra;
    for (int i = 0; i < mat_len; i++) {
        if (!tmp || tmp->letra != matricula[i])
            return false;
        tmp = tmp->sig_letra;
    }

    return true;
}

void
crearIniciales(const char *nombre, NODO **inciales){
    const char *temp_nombreUsuario;
    bool visto_espacio = false;
    int i;

    temp_nombreUsuario = nombre;
    i = 0;

    agregarACadena(inciales, *(temp_nombreUsuario + i));
    while(*(temp_nombreUsuario + i) != '\0') {
        if (visto_espacio == true) {
            agregarACadena(inciales, *(temp_nombreUsuario + i));
            visto_espacio = false;
        }
        if(*(temp_nombreUsuario + i) == ' ') {
            visto_espacio = true;
        }
        i++;
    }
}

bool
ch_cad_iniciales(NODO **cadena_usuario, NODO **iniciales){
    NODO *temp_cadena_usuario, *temp_iniciales;
    temp_cadena_usuario = *cadena_usuario;
    temp_iniciales = *iniciales;

    while(temp_cadena_usuario != NULL) {
        if (temp_iniciales != NULL && temp_iniciales->letra == temp_cadena_usuario->letra) {
            temp_iniciales = temp_iniciales->sig_letra;
        }
        temp_cadena_usuario = temp_cadena_usuario->sig_letra;
        if(temp_iniciales == NULL) {
            return true;
        }
    }
    return false;
    }

bool
procesarCadena(NODO **alfabeto, NODO **cadena_usuario, NODO** inciales, const char* matricula) {
    if (ch_cad_EnAlfa(alfabeto, cadena_usuario) &&
            ch_cad_primEsDig(cadena_usuario) &&
                ch_cad_iniciales(cadena_usuario, inciales) &&
                    ch_cad_ptsNoConsecu(cadena_usuario) &&
                        ch_cad_ptoYmatric(matricula, cadena_usuario)) {
            return true;
    }
    else {
        return false;
    }
}


#endif