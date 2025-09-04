/*
	Desarrollar un programa computacional para el lenguaje regular que represente todas las cadenas escritas sobre el
	alfabeto compuesto por todas las letras de tu(s) nombr(e) y apellidos. todas minusculas y sin acentos, asi como
	los digitos que componenea tu matricula, ademas del punto y que cumplan con lo siguiente.

		1) Que el primer simbolo sea un digito.
		2) Que tenga cualquier combinacion de letras y digitos intermedia, validos en el alfabeto.
		3) Que la cadena contenga tus iniciales en forma consecutiva al menos una vez.
		4) que la cadena contenga como ultimos simbolos un punto seguido de tu numero de matricula completo.
		5) Que acepte puntos intermedios, pero no en forma consecuitiva.

	El programa debe de ser capaz de tomar como entrada una cadena de caracteres y que como resultado indique si la
	cadena es valida o no para el lenguaje regular. Ademas, debe dar la opcion de solicitar otra cadena de entrada para
	analizar, hasta que ya no se quiera analizar mas cadenas.

	Ejemplo de cadenas validas.

	Nombre: yazmany jahaziel guerrero ceja
	Matricula: 1339767

	El alfabeto es:
	S = {y,a,z,m,n,j,h,i,e,l,g,u,r,o,c,1,3,9,7,6,.}

	Una entrada valida: 1mnyjgccicyjgci.an3.1339767

	Otra valida: 6611zzzraoll99yjgc3j1.1339767
*/

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>



#ifdef __WIN32
	#define LIMPIAR_PANTALLA system("cls")
#else
	#define LIMPIAR_PANTALLA system("clear")
#endif

#define NORMAL "\033[0m"
#define GREEN "\033[0;32m"
#define RED "\033[0;31m"

//NODO para las listas encadenandas
typedef struct _nodo {
    char letra;
    struct _nodo *sig_letra;
} NODO;

typedef enum tipoDato {
    TODO = 0,
    LETRA,
    NUMERO,
} TIPODATO;

void agregarACadena(NODO ** , char );
void printCadena(NODO** );
bool buscarEnCadena(NODO **, char );
void deshacerCadena(NODO **);
size_t tamanoCadena(NODO **);

void crearAlfabeto(NODO **, const char *);
void leerCadena(const char *, NODO **, TIPODATO );
void printAlfabeto(NODO** );
void crearIniciales(const char *, NODO **);

//validaciones
bool ch_cad_EnAlfa(NODO **, NODO **);
bool ch_cad_primEsDig(NODO **);
bool procesarCadena(NODO **, NODO **, NODO **, const char*);
bool ch_cad_iniciales(NODO **, NODO **);
bool ch_cad_ptsNoConsecu(NODO **);
bool ch_cad_ptoYmatric(const char *, NODO **);

bool continuarSiNO();

int main() {
	//Declaraciones
	NODO *cadena_usuario;
	NODO *alfabeto;
	NODO *inciales;
	const char * cadena_nombre = "octavio araujo rosales";
	const char * cadena_matricula = "2173394";

	//Inicializaciones
	cadena_usuario = NULL; //cadena ingresada por el usuario como listas encadenadas
	alfabeto = NULL; //alfabeto como listas encadenadas
	inciales = NULL; //iniciales como listas encadenadas
	
	
	crearAlfabeto(&alfabeto, cadena_nombre);
	crearAlfabeto(&alfabeto, cadena_matricula);
	crearIniciales(cadena_nombre, &inciales);
	agregarACadena(&alfabeto, '.');
	
	//prompt usuario
	do {
		LIMPIAR_PANTALLA;
		printf("Nombre: %s\n", cadena_nombre);
		printf("Matricula: %s\n\n", cadena_matricula);

		printAlfabeto(&alfabeto);
		printf("\n");
		leerCadena("Cadena a analizar: ", &cadena_usuario, TODO); //la cadena a analizar es una linked list
		printf("\n");
		
		if(procesarCadena(&alfabeto, &cadena_usuario, &inciales, cadena_matricula)) {
			printf(GREEN"Cadena Valida!\n"NORMAL);
		}
		else {
			printf(RED"Cadena Invalida!\n"NORMAL);
		}
		printf("\n");
	}while(continuarSiNO());

	deshacerCadena(&alfabeto);
	deshacerCadena(&cadena_usuario);
	deshacerCadena(&inciales);
	return 0;
}

bool continuarSiNO() {
    char si_no;

    while (true) {
        printf("Validar otra cadena? (s/n): ");
        
        si_no = getchar();
        while (getchar() != '\n'); // clear input buffer

        switch (si_no) {
            case 's':
            case 'S':
                return true;
            case 'n':
            case 'N':
                return false;
            default:
				LIMPIAR_PANTALLA;
                printf(RED"\rPor favor ingrese 's' o 'n'.\n"NORMAL);
				break;
        }
    }
}

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

//checar que la cadena inicie con un digito (numero)
bool ch_cad_primEsDig(NODO **cadena){
    bool valido;
    char cAnalizar;
    
    cAnalizar = (*cadena)->letra;
    valido = (isdigit(cAnalizar));
    
    return valido;
}

//checar que la cadena no contenga puntos consecutivos
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
    
//checar que la cadena termine con punto y matricula
bool ch_cad_ptoYmatric(const char *matricula, NODO **cadena_usuario) {
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

    // Check if current is '.'
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

//funcion para crear iniciales apartir del nombre estatico
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

//checar que la cadena contenga las iniciales al menos 1 vez
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

//funcion tipo botella para encapsular dif componentes de la cadena haciendolas validas o no 
bool procesarCadena(NODO **alfabeto, NODO **cadena_usuario, NODO** inciales, const char* matricula) {
    /*
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

    printf("Prueba checar punto y matricula final\n");
	if (ch_cad_ptoYmatric(matricula, cadena_usuario)) {
		printf("\tPASS - tiene .matricula\n");
	}
	else{
		printf("\tNO\n");
	}

    */
    if (ch_cad_EnAlfa(alfabeto, cadena_usuario) && ch_cad_primEsDig(cadena_usuario) &&
        ch_cad_iniciales(cadena_usuario, inciales) && ch_cad_ptsNoConsecu(cadena_usuario) && ch_cad_ptoYmatric(matricula, cadena_usuario)) {
            return true;
    }
    else {
        return false;
    }
}