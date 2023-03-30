Practica 4, ejercicio 1 de PdM

Implementacion de una maquina de estados para implementar un antirebote

void debounceFSM_init();	// debe cargar el estado inicial
void debounceFSM_update();	// debe leer las entradas, resolver la lógica de transición de 		estados y actualizar las salidas
				
void buttonPressed();		// debe invertir el estado del LED1
void buttonReleased();		// debe invertir el estado del LED3

Las funciones deben implementarse en el archivo main.c y sus correspondientes declaraciones en main.h

La actualización de la máquina de estados debe hacerse con retardos no bloqueantes
