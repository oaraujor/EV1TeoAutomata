/*
	Obtener las reglas de transicion, el diagrama y las configuraciones (para una cadena valida
	evaluando cada exponente evaluable al cubo). Ademas, desarrollar un analizador de lenguaje,
	cuya interfaz grafica, tome como entrada una cadena, mostrando si esta es valida o invalida
	para dicho lenguaje, tantas veces que requiera el usuario.

	L = { wcw | w en {a,b}*}
	



	{0, BLN, 1, BLN, R},

	{1, 'a', 2, BLN, R},
	{1, 'b', 3, BLN, R},
	{1, 'c', 8, 'c', R},

	{2, 'a', 2, 'a', R},
	{2, 'b', 2, 'b', R},
	{2, 'A', 2, 'A', R},
	{2, 'B', 2, 'B', R},
	{2, 'c', 4, 'c', R},

	{3, 'a', 3, 'a', R},
	{3, 'b', 3, 'b', R},
	{3, 'A', 3, 'A', R},
	{3, 'B', 3, 'B', R},
	{3, 'c', 5, 'c', R},

	{4, 'A', 4, 'A', R},
	{4, 'B', 4, 'B', R},
	{4, 'a', 6, 'A', L},
	{5, 'A', 5, 'A', R},
	{5, 'B', 5, 'B', R},
	{5, 'b', 6, 'B', L},

	{6, 'A', 6, 'A', L},
	{6, 'B', 6, 'B', L},
	{6, 'a', 6, 'a', L},
	{6, 'b', 6, 'b', L},
	{6, 'c', 7, 'c', L}, //c

	{7, 'A', 7, 'A', L},
	{7, 'B', 7, 'B', L},
	{7, 'a', 7, 'a', L},
	{7, 'b', 7, 'b', L},
	{7, BLN, 1, BLN, R},

	{8, 'A', 8, BLN, R}, // A
	{8, 'B', 8, BLN, R},// B
	{8, 'c', 8, BLN, R},  // might del
	{8, BLN, 9, BLN, HALT},
	{9, BLN, 9, BLN, HALT},

	*/

#include "turingM.h"

bool continuarSiNO();

int
main() {
	NODO *LST_cadena_usr = NULL;
	int tamanoInstruc;
	//reglas de transicion simples	
	Instruc reglas_trans[] = {
		{0, BLN, 1, BLN, R},

		/* estado 1: decidir si la siguiente letra inicia w (a/b) o si estamos ya en la 'c' */
		{1, 'a', 2, BLN, R},   /* entrar en fase de avanzar hasta c sabiendo que la primera fue 'a' */
		{1, 'b', 3, BLN, R},   /* análogo para 'b' */
		{1, 'c', 8, BLN, R},   /* si llegamos a c sin más símbolos, pasar a verificación/aceptación */

		/* estados 2 y 3: avanzar hacia la 'c' sobre a,b,A,B (no modifican) */
		{2, 'a', 2, 'a', R},
		{2, 'b', 2, 'b', R},
		{2, 'A', 2, 'A', R},
		{2, 'B', 2, 'B', R},
		{2, 'c', 4, 'c', R},   /* al encontrar c pasar a la fase de marcar el símbolo correspondiente desde la derecha */

		{3, 'a', 3, 'a', R},
		{3, 'b', 3, 'b', R},
		{3, 'A', 3, 'A', R},
		{3, 'B', 3, 'B', R},
		{3, 'c', 5, 'c', R},

		/* estado 4: desde c, buscar a la derecha el primer 'a' no marcada y marcarla como 'A' */
		{4, 'A', 4, 'A', R},
		{4, 'B', 4, 'B', R},
		{4, 'a', 6, 'A', L},   /* marcar 'a' -> 'A' y empezar a regresar hacia la c */

		/* estado 5: análogo para 'b' */
		{5, 'A', 5, 'A', R},
		{5, 'B', 5, 'B', R},
		{5, 'b', 6, 'B', L},   /* marcar 'b' -> 'B' y regresar */

		/* estado 6: regresar hacia la izquierda hasta la 'c' */
		{6, 'A', 6, 'A', L},
		{6, 'B', 6, 'B', L},
		{6, 'a', 6, 'a', L},
		{6, 'b', 6, 'b', L},
		{6, 'c', 7, 'c', L},

		/* estado 7: seguir regresando hasta BLN y luego volver al estado 1 para procesar siguiente letra */
		{7, 'A', 7, 'A', L},
		{7, 'B', 7, 'B', L},
		{7, 'a', 7, 'a', L},
		{7, 'b', 7, 'b', L},
		{7, BLN, 1, BLN, R},

		/* estado 8: verificación/limpieza final.
		Aquí asumimos que si ya no hay letras sin marcar (a/b) en la derecha, aceptamos. */
		{8, 'A', 8, BLN, R},   /* borrar A */
		{8, 'B', 8, BLN, R},   /* borrar B */
		{8, 'c', 8, BLN, R},
		{8, BLN, 8, BLN, HALT} /* cuando lleguemos al BLN de la derecha, HALT (aceptar) */
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
