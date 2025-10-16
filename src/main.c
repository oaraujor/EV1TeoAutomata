/*
	Obtener lo que se solicita a continuación: 
	Con tu número de matrícula y tu nombre, desarrolla una gramática y un programa 
	computacional para el lenguaje independiente del contexto dado, que sea capaz de tomar 
	una cadena de palabras y que como resultado indique si la cadena es válida o no para dicha
	gramática. Además, debe dar la opción de solicitar otra cadena de entrada para analizar, 
	hasta que ya no se quiera analizar más cadenas. 

	L = { i (w)^n i (w^I)^(2n) j^2 }
	
		DONDE:
			w = las iniciales de tus apellidos,
			i = todos los dígitos de tu número de matrícula,
			w^I = w inversa,
			j = tu primer nombre,
			n≥ 1, n no debe leerse 
	
	(Sólo usar letras minúsculas sin acentos) 

	Ejemplo: Si tu matrícula es 0123456 y tu nombre es Yozedh Jahday Guerrero Ceja 
		Entonces,
			w = gc
			i = 0123456 
			wI = cg 
			j = yozedh 
	Algunas cadenas válidas para el lenguaje dado son: 
		0123456gc0123456cgcgyozedhyozedh 
		0123456gcgc0123456cgcgcgcgyozedhyozedh 
*/

#include "t_colors.h"
#include "eval_str.h"

bool continuarSiNO();

int
main() {
	NODO *LST_nombre = NULL;
	NODO *LST_apellidos = NULL;
	NODO *LST_matricula = NULL;
	NODO *LST_cadena_usr = NULL;
	NODO *LST_iniciales_W = NULL;
	NODO *LST_iniciales_WI = NULL;
	NODO *LST_sigma = NULL;

	const char *str_nombre = "octavio";
	const char *str_apellidos = "araujo rosales";
	const char *str_matricula = "2173394";

	LST_crear_sigma(&LST_sigma, str_nombre);
	LST_crear_sigma(&LST_sigma, str_apellidos);
	LST_crear_sigma(&LST_sigma, str_matricula);

	str_a_LST(&LST_nombre, str_nombre);
	str_a_LST(&LST_apellidos, str_apellidos);
	str_a_LST(&LST_matricula, str_matricula);
	crearIniciales(str_apellidos, &LST_iniciales_W);
	crearIniciales(str_apellidos, &LST_iniciales_WI);
	invertir_LST(&LST_iniciales_WI);
	
	do {
		LIMPIAR_PANTALLA;
		printf("Nombre: ");
		imprimir_LST(&LST_nombre);
		printf("Apellido: ");
		imprimir_LST(&LST_apellidos);
		printf("Matricula: ");
		imprimir_LST(&LST_matricula);
		
		printf("i = ");
		imprimir_LST(&LST_matricula);
		printf("w = ");
		imprimir_LST(&LST_iniciales_W);
		printf("w^I = ");
		imprimir_LST(&LST_iniciales_WI);
		printf("j = ");
		imprimir_LST(&LST_nombre);
		
		printf("\n");
		leer_cadena_usr("Cadena a analizar: ", &LST_cadena_usr); //la cadena a analizar es una linked list
		printf("\n\n");
		
		if(procesarCadena(&LST_cadena_usr, &LST_matricula, &LST_iniciales_W, &LST_iniciales_WI, &LST_nombre, &LST_sigma)) {
			printf(GREEN"Cadena Valida!\n"NORMAL);
		}
		else {
			printf(RED"Cadena Invalida!\n"NORMAL);
		}

	}while(continuarSiNO());

	liberar_LST(&LST_nombre);
	liberar_LST(&LST_apellidos);
	liberar_LST(&LST_matricula);
	liberar_LST(&LST_cadena_usr);
	liberar_LST(&LST_iniciales_W);
	liberar_LST(&LST_iniciales_WI);
	return 0;
}

bool
continuarSiNO() {
    char si_no;

    while (true) {
        printf("Continuar? (s/n): ");
        
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
