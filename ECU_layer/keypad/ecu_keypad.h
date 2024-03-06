/* 
 * File:   ecu_keypad.h
 * Author: OKTA
 *
 * Created on September 23, 2023, 9:33 AM
 */

#ifndef ECU_KEYPAD_H
#define	ECU_KEYPAD_H

/*section : Includes */
#include "../../MCAL_layer/GPIO/hal_gpio.h"
#include "ecu_keypad_cfg.h"

/*section : Macro Declarations   */
#define ECU_KEYPAD_ROW     4 
#define ECU_KEYPAD_COLUMNS 4

/*section : Macro Function declarations */


/*section : Data Type Declarations */
typedef struct
{
    pin_config_t keypad_row_pins[ECU_KEYPAD_ROW];
    pin_config_t keypad_columns_pins[ECU_KEYPAD_COLUMNS];
}keypad_t;
/*section : Function declarations */

/**
 * @brief Initialize the assigned pin to be (INPUT OR OUTPUT)
 * @param _keypad_obj 
 * @return Status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action 
 */
std_ReturnType keypad_initialize(const keypad_t *_keypad_obj);

/**
 * @brief
 * @param _keypad_obj
 * @param value
 * @return Status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action 
 */
std_ReturnType keypad_get_value(const keypad_t *_keypad_obj, uint8 *value);
#endif	/* ECU_KEYPAD_H */

