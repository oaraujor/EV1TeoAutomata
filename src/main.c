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

#include "colores.h"
#include "cadenas.h"


int main() {
	//Declaraciones
	NODO *cadena_usuario;
	NODO *alfabeto;
	const char * cadena_nombre = "octavio araujo rosales";;
	const char * cadena_matricula = "2173394";

	//Inicializaciones
	cadena_usuario = NULL; //cadena ingresada por el usuario como listas encadenadas
	alfabeto = NULL; //alfabeto como listas encadenadas
	
	
	LIMPIAR_PANTALLA;
	//prompt usuario
	printf("Nombre: %s\n", cadena_nombre);
	printf("Matricula: %s\n\n", cadena_matricula);
	
	crearAlfabeto(&alfabeto, cadena_nombre);
	crearAlfabeto(&alfabeto, cadena_matricula);
	agregarACadena(&alfabeto, '.');

	printAlfabeto(&alfabeto);
	printf("\n\n");
	leerCadena("Cadena a analizar: ", &cadena_usuario, TODO); //la cadena a analizar es una linked list
	printf("\n\n");
	
	printCadena(&cadena_usuario);
	

	return 0;
}
