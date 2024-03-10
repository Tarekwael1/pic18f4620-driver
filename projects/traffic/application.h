/* 
 * File:   application.h
 * Author: OKTA
 *
 * Created on September 14, 2023, 9:24 PM
 */

#ifndef APPLICATION_H
#define	APPLICATION_H


/*section : Includes */
#include "ECU_layer/ecu_layer_init.h"


/*section : Macro Declarations   */



/*section : Macro Function declarations */

/*section : Data Type Declarations */
extern keypad_t keypad1;
extern led_t led1;
extern led_t led2;
extern led_t led3;
extern chr_lcd_8bit_t lcd_2;
extern chr_lcd_4bit_t lcd_1;
/*section : Function declarations */
void application_initialize(void);

#endif	/* APPLICATION_H */

