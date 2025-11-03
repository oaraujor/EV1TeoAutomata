/*
	Obtener las reglas de transicion, el diagrama y las configuraciones (para una cadena valida
	evaluando cada exponente evaluable al cubo). Ademas, desarrollar un analizador de lenguaje,
	cuya interfaz grafica, tome como entrada una cadena, mostrando si esta es valida o invalida
	para dicho lenguaje, tantas veces que requiera el usuario.

	L = { wcw | w en {a,b}*}
	
	*/

#include "turingM.h"

bool continuarSiNO();

//L = { wcw | w en {a,b}*}
int
main() {
	NODO *LST_cadena_usr = NULL;
	int tamanoInstruc;
	//here i just want to do a simple traversal unitl the end
	Instruc reglas_trans[] = {
		{0, BLN, 1, BLN, R},
		{1, 'a', 1, BLN , R},
		{1, 'b', 1, BLN , R},	
		{1, 'c', 1, BLN , R},
		{1, BLN, 2, BLN ,HALT},
	};

		tamanoInstruc = sizeof(reglas_trans) / sizeof(Instruc);


	do {
		LIMPIAR_PANTALLA;

		leer_cinta(&LST_cadena_usr);

		LIMPIAR_PANTALLA;
		printf("Cadena Ingresada: ");
		_impr_cadena(&LST_cadena_usr);

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
