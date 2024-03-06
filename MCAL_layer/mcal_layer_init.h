/* 
 * File:   mcal_layer_init.h
 * Author: OKTA
 *
 * Created on October 9, 2023, 8:43 PM
 */

#ifndef MCAL_LAYER_INIT_H
#define	MCAL_LAYER_INIT_H
/*---------------------- section : Includes ----------------------*/
#include "interrupt/mcal_external_interrupt.h"
#include "EEPROM/hal_eeprom.h"
#include "ADC/hal_adc.h"
#include "GPIO/hal_gpio.h"
#include "Timer/hal_timer0.h"
#include "Timer1/hal_timer1.h"
#include "timer2/hal_timer2.h"
#include "timer3/hal_timer3.h"
#include "CCP/hal_ccp.h"
#include "usart/hal_usart.h"
#include "I2C/hal_i2c.h"
/*---------------------- section : Macro Declarations ----------------------   */

/*---------------------- section : Macro Function declarations ---------------------- */


/* ---------------------- section : Data Type Declarations ---------------------- */

/*---------------------- section : Function declarations ---------------------- */
void ADC_DefaultInterruptHandler(void);

#endif	/* MCAL_LAYER_INIT_H */

