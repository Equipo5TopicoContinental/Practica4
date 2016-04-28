/*
 * Buttons.h
 *
 *  Created on: Apr 19, 2016
 *      Author: Adrian
 */

#ifndef BUTTONS_H_
#define BUTTONS_H_
#include "stdtypedef.h"


void InitButtons(void);

T_BOOL PlayButtonState(void);
T_BOOL StopButtonState(void);
T_BOOL VolUpButtonState(void);
T_BOOL VolDownButtonState(void);

void SenseButtons(void);

#endif /* BUTTONS_H_ */
