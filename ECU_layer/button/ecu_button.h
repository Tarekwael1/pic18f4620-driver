/* 
 * File:   ecu_button.h
 * Author: OKTA
 *
 * Created on September 19, 2023, 12:01 PM
 */

#ifndef ECU_BUTTON_H
#define	ECU_BUTTON_H

/*section : Includes */
#include "ecu_button_cfg.h"
#include "../../MCAL_layer/GPIO/hal_gpio.h"

/*section : Macro Declarations   */


/*section : Macro Function declarations */

/*section : Data Type Declarations */
typedef enum 
{
    BUTTON_PRESSED,
    BUTTON_RELEASED
}button_state_t;

typedef enum
{
    BUTTON_ACTIVE_HIGH,
    BUTTON_ACTIVE_LOW
}button_active_t;

typedef struct
{
    pin_config_t    button_pin;
    button_state_t  button_state;
    button_active_t button_connection;
}button_t;

/*section : Function declarations */

/**
 * @brief Initialize the assigned pin to input 
 * @param btn pointer to the button configuration 
 * @return Status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action 
 */
std_ReturnType button_initialize(const button_t *btn);

/**
 * @brief Read a state of button 
 * @param btn pointer to the button configuration 
 * @param btn_state button state @ref button_state_t
 * @return Status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action 
 */
std_ReturnType button_read_state(const button_t *btn, button_state_t *btn_state);

#endif	/* ECU_BUTTON_H */

