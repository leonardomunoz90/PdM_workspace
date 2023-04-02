/*
 * API_debounce.c
 *
 *  Created on: Mar 25, 2023
 *      Author: leonardo
 */

#include "API_debounce.h"

static debounceState_t debounce;	// Variable interna de maquina de estados
static delay_t delayFSM;
static bool_t raising = false;		//Variable si el boton se presinó
static bool_t falling = false;		//Variable si el boton se soltó

//Inicializa la maquina de estados con boton en alto, inicializaliza el pulsador
void debounceFSM_init() {
	debounce = BUTTON_UP;
	BSP_PB_Init(BUTTON_USER, BUTTON_MODE_GPIO);
	delayInit(&delayFSM, FSM_UPDATE_PERIOD); //inicializa el retardo no bloqueante de verifiacion de la MEF
}

//Implementacion de maquina de estados, se debe checkear periodicamente
void debounceFSM_update() {
	if (delayRead(&delayFSM)) {
		switch (debounce) {
		case BUTTON_UP:
			if (BSP_PB_GetState(BUTTON_USER)) {
				debounce = BUTTON_FALLING;
			}
			break;
		case BUTTON_FALLING:
			if (BSP_PB_GetState(BUTTON_USER)) {
				debounce = BUTTON_DOWN;
				falling = true;	//Variable que usuario lee a traves de readFalling
			} else {
				debounce = BUTTON_UP;
			}
			break;
		case BUTTON_DOWN:
			if (!BSP_PB_GetState(BUTTON_USER)) {
				debounce = BUTTON_RAISING;
			}
			break;
		case BUTTON_RAISING:
			if (!BSP_PB_GetState(BUTTON_USER)) {
				debounce = BUTTON_UP;
				raising = true;	//Variable que usuario lee a traves de readRaising
			} else {
				debounce = BUTTON_DOWN;
			}
			break;
		default:
			break;
		}
	}
}

//Funciones intermedias para acceder variables internas
bool_t readFalling() {
	if (falling) {
		falling = false;
		return true;
	} else
		return false;
}

bool_t readRaising() {
	if (raising) {
		raising = false;
		return true;
	} else
		return false;
}
