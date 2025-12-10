/*
	Obtener las reglas de transicion, el diagrama y las configuraciones (para una cadena valida
	evaluando cada exponente evaluable al cubo). Ademas, desarrollar un analizador de lenguaje,
	cuya interfaz grafica, tome como entrada una cadena, mostrando si esta es valida o invalida
	para dicho lenguaje, tantas veces que requiera el usuario.

	L = { wcw | w en {a,b}*}

	*/

#include "turingM.h"

bool continuarSiNO();

int
main() {
	NODO *LST_cadena_usr = NULL;
	int tamanoInstruc;
	//reglas de transicion simples	
	Instruc reglas_trans[] = {
			//Estado 0: inicio en BLN y me muevo a la derecha
			{0, BLN, 1, BLN, R},

			//estado 1: decidir si la siguiente letra inicia w (a/b) o si estamos ya en la 'c'
			{1, 'a', 2, BLN, R},   //entrar en fase de avanzar hasta c sabiendo que la primera fue 'a'
			{1, 'b', 3, BLN, R},   //análogo para 'b'
			{1, 'c', 7, BLN, R},   //si llegamos a c sin más símbolos, pasar a verificación/aceptación

			//estados 2 y 3: avanzar hacia la 'c' sobre a,b,A,B (no modifican)
			{2, 'a', 2, 'a', R},
			{2, 'b', 2, 'b', R},
			{2, 'c', 4, 'c', R},   //al encontrar c pasar a la fase de marcar el símbolo correspondiente desde la derecha

			{3, 'a', 3, 'a', R},
			{3, 'b', 3, 'b', R},
			{3, 'c', 5, 'c', R},

			//estado 4: desde c, buscar a la derecha el primer 'a' no marcada y marcarla como 'A'
			{4, 'X', 4, 'X', R},
			{4, 'a', 6, 'X', L},   //marcar 'a' -> 'A' y empezar a regresar hacia la c

			//estado 5: análogo para 'b'
			{5, 'X', 5, 'X', R},
			{5, 'b', 6, 'X', L},   //marcar 'b' -> 'B' y regresar

			// estado 6: regresar hacia la izquierda hasta BLN y luego volver al estado 1 para procesar siguiente letra
			{6, 'X', 6, 'X', L},
			{6, 'a', 6, 'a', L},
			{6, 'b', 6, 'b', L},
			{6, 'c', 6, 'c', L},

			{6, BLN, 1, BLN, R},

			//estado 8: verificación/limpieza final.
			//Aquí asumimos que si ya no hay letras sin marcar (a/b) en la derecha, aceptamos.
			{7, 'X', 7, BLN, R},   // borrar X
			{7, BLN, 8, BLN, HALT} // cuando lleguemos al BLN de la derecha, HALT (aceptar)
			
	};

	/*
	Instruc reglas_trans[] = {
		{0, BLN, 1, BLN, R},
		{1, 'a', 1, 'a' , R},
		{1, 'b', 1, 'Y' , R},	
		{1, 'c', 1, 'N' , R},
		{1, BLN, 2, BLN , L},
		{2, 'a', 2, BLN , L},
		{2, 'Y', 2, BLN , L},	
		{2, 'c', 2, BLN , L},
		{2, BLN, 3, BLN , HALT},
	};
	*/
	
		tamanoInstruc = sizeof(reglas_trans) / sizeof(Instruc);

	do {
		LIMPIAR_PANTALLA;

		leer_cinta(&LST_cadena_usr);

		LIMPIAR_PANTALLA;

		if(exe_turing(&LST_cadena_usr, reglas_trans, tamanoInstruc)) {
			printf(TCV"Cadena Valida!\n"TCN);
		}
		else {
			printf(TCR"Cadena Invalida!\n"TCN);
		}

	}while(continuarSiNO());

	printf("Saliendo del programa...\n");

	_free_cadena(&LST_cadena_usr);
	return 0;
}

bool
continuarSiNO() {
    char si_no;

    while (true) {
        printf("Continuar? (s/n): ");
        
        si_no = getchar();
        while (getchar() != '\n');

        switch (si_no) {
            case 's':
            case 'S':
                return true;
            case 'n':
            case 'N':
                return false;
            default:
				LIMPIAR_PANTALLA;
                printf(TCR"\rPor favor ingrese 's' o 'n'.\n"TCN);
				break;
        }
    }
}
