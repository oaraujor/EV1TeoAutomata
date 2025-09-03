//archivo cabecera para el proyecto
#ifndef CADENAS
#define CADENAS

#include <string.h>
#include <ctype.h>

#include "listasEncadenadas.h"

#ifdef __WIN32
	#define LIMPIAR_PANTALLA system("cls")
#else
	#define LIMPIAR_PANTALLA system("clear")
#endif

//enum para diferenciar tipos de datos
typedef enum tipoDato {
    TODO = 0,
    LETRA,
    NUMERO,
} TIPODATO;

void crearAlfabeto(NODO **, const char *);
void leerCadena(const char *, NODO **, TIPODATO );
void printAlfabeto(NODO** );
void crearIniciales(const char *, NODO **);

//validaciones
bool ch_cad_EnAlfa(NODO **, NODO **);
bool ch_cad_primEsDig(NODO **);
bool procesarCadena(NODO **, NODO **, NODO **);
bool ch_cad_iniciales(NODO **, NODO **);
bool ch_cad_ptsNoConsecu(NODO **);

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

//checar que la cadena contenga simbolos del Alfabeto, si incluye otros, rechazar cadena
bool ch_cad_EnAlfa(NODO **alfabeto, NODO **cadena) {
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

bool ch_cad_primEsDig(NODO **cadena){
    bool valido;
    char cAnalizar;
    
    cAnalizar = (*cadena)->letra;
    valido = (isdigit(cAnalizar));
    
    return valido;
}

bool ch_cad_ptsNoConsecu(NODO **cadena){
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
    
/*
bool ch_cad_ptoYmatric(NODO **alfabeto, NODO **cadena){
    bool valido;
    return valido;


}
*/

void crearIniciales(const char *nombre, NODO **inciales){
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

bool ch_cad_iniciales(NODO **cadena_usuario, NODO **iniciales){
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

bool procesarCadena(NODO **alfabeto, NODO **cadena_usuario, NODO** inciales) {
    //bool valido;

    printf("Prueba checar que la cadena solo tenga del alfabeto\n");
	if (ch_cad_EnAlfa(alfabeto, cadena_usuario)) {
		printf("\tPASS - todos pertenecen al alfabeto\n");
	}
	else{
		printf("\tNO\n");
	}

	printf("\n");

	printf("Prueba checar que primer elemento sea numero\n");
	if (ch_cad_primEsDig(cadena_usuario)) {
		printf("\tPASS - primer elemento es numero\n");
	}
	else{
		printf("\tNO\n");
	}

    printf("\n");

	printf("Prueba checar que contenga iniciales\n");
	if (ch_cad_iniciales(cadena_usuario, inciales)) {
		printf("\tPASS - contiene inciales\n");
	}
	else{
		printf("\tNO\n");
	}

    printf("Prueba checar puntos no consecutivos\n");
	if (ch_cad_ptsNoConsecu(cadena_usuario)) {
		printf("\tPASS - no contiene puntos consecutivos\n");
	}
	else{
		printf("\tNO\n");
	}
    //return valido;
}


#endif