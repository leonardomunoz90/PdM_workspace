/*
 * API_debounce.c
 *
 *  Created on: Mar 25, 2023
 *      Author: leonardo
 */

#include "API_debounce.h"

static debounceState_t debounce;
static bool_t pressed = false;

void debounceFSM_init() {
	debounce = BUTTON_UP;
	BSP_PB_Init(BUTTON_USER, BUTTON_MODE_GPIO);
	BSP_LED_Init(LED_RED);
}

void debounceFSM_update() {
	switch (debounce) {
	case BUTTON_UP:
		if (!BSP_PB_GetState(BUTTON_USER)) {
			debounce = BUTTON_FALLING;
		}
		break;
	case BUTTON_FALLING:
		if (!BSP_PB_GetState(BUTTON_USER)) {
			debounce = BUTTON_DOWN;
			pressed = true;
			BSP_LED_On(LED_RED);
		} else {
			debounce = BUTTON_UP;
		}
		break;
	case BUTTON_DOWN:
		if (BSP_PB_GetState(BUTTON_USER)) {
			debounce = BUTTON_RAISING;
		}
		break;
	case BUTTON_RAISING:
		if (BSP_PB_GetState(BUTTON_USER)) {
			debounce = BUTTON_UP;
			pressed = false;
			BSP_LED_Off(LED_RED);
		} else {
			debounce = BUTTON_DOWN;
		}
		break;
	default:
		break;
	}
}

bool_t readKey() {
	if (pressed){
		pressed=false;
		return true;
	}
	else
		return false;
}
