/*
 * API_delay.c
 *
 *  Created on: Mar 18, 2023
 *      Author: leonardo
 */
#include "API_delay.h"
#include "stm32f4xx_hal.h"  		/* Necesario para corregir in warning al usar HAL_GetTick*/

void delayInit(delay_t *delay, tick_t duration) {
	delay->duration = duration;
	delay->running = false;
}

bool_t delayRead(delay_t *delay) {
	if (!delay->running) {
		delay->running = true;
		delay->startTime = HAL_GetTick();
		return false;
	} else {
		if ((HAL_GetTick() - delay->startTime) >= delay->duration) {
			delay->running = false;
			return true;
		} else
			return false;
	}
}

void delayWrite(delay_t *delay, tick_t duration) {
	delay->duration = duration;
}

