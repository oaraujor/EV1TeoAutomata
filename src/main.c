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

int main() {
	NODO *cadena_ingresada_usr;
	NODO *gramatica_sigma;
	NODO *gramatica_W;
	NODO *gramatica_WI;
	const char * charPtr_gramatica_j = "octavio";
	const char * cadena_apellidos = "araujo rosales";
	const char * charPtr_gramatica_i = "2173394";

	cadena_ingresada_usr = NULL; //cadena ingresada por el usuario como listas encadenadas
	gramatica_sigma = NULL; //gramatica_sigma como listas encadenadas
	gramatica_W = NULL; //iniciales como listas encadenadas
	gramatica_WI = NULL; //iniciales como listas encadenadas
	
	crearAlfabeto(&gramatica_sigma, charPtr_gramatica_j);
	crearAlfabeto(&gramatica_sigma, cadena_apellidos);
	crearAlfabeto(&gramatica_sigma, charPtr_gramatica_i);
	crearIniciales(cadena_apellidos, &gramatica_W);
	crearIniciales(cadena_apellidos, &gramatica_WI);
	voltearCadena(&gramatica_WI);
	
	do {
		LIMPIAR_PANTALLA;
		printf("Nombre: %s ", charPtr_gramatica_j);
		printf("%s\n", cadena_apellidos);
		printf("Matricula: %s\n\n", charPtr_gramatica_i);
		printAlfabeto(&gramatica_sigma);
		
		printf("w = ");
		printCadena(&gramatica_W);
		
		printf("i = %s\n", charPtr_gramatica_i);
		
		printf("w^I = ");
		printCadena(&gramatica_WI);
		
		printf("j = %s\n", cadena_apellidos);

		printf("\n");
		leer_cadena_usr("Cadena a analizar: ", &cadena_ingresada_usr); //la cadena a analizar es una linked list
		printf("\n\n");
		
		if(procesarCadena(&gramatica_sigma, &cadena_ingresada_usr, &gramatica_W, charPtr_gramatica_i)) {
			printf(GREEN"Cadena Valida!\n"NORMAL);
		}
		else {
			printf(RED"Cadena Invalida!\n"NORMAL);
		}

	}while(continuarSiNO());

	deshacerCadena(&cadena_ingresada_usr);
	deshacerCadena(&gramatica_sigma);
	deshacerCadena(&gramatica_W);
	return 0;
}

bool continuarSiNO() {
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
