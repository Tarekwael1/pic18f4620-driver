/* 
 * File:   ecu_relay.h
 * Author: OKTA
 *
 * Created on September 20, 2023, 12:44 PM
 */

#ifndef ECU_RELAY_H
#define	ECU_RELAY_H


/*section : Includes */
#include "ecu_relay_cfg.h"
#include "../../MCAL_layer/GPIO/hal_gpio.h"


/*section : Macro Declarations   */
#define RELAY_ON_STATUS  0x01U
#define RELAY_OFF_STATUS 0x00U

/*section : Macro Function declarations */

/*section : Data Type Declarations */
typedef struct
{
    uint8 relay_port   : 4;
    uint8 reley_pin    : 3;
    uint8 reley_status : 1;
}relay_t;


/*section : Function declarations */
/**
 * @brief Initialize the assigned pin to be (INPUT OR OUTPUT) of (relay) and turn the relay on or off
 * @param _relay Pointer to the relay module configurations
 * @return Status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action 
 */
std_ReturnType relay_initialize(const relay_t *_relay);

/**
 * @brief Turn the relay on 
 * @param _relay Pointer to the relay module configurations
 * @return Status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action 
 */
std_ReturnType relay_turn_on(const relay_t *_relay);

/**
 * @brief Turn the relay off 
 * @param _relay Pointer to the relay module configurations
 * @return Status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action 
 */
std_ReturnType relay_turn_off(const relay_t *_relay);

#endif	/* ECU_RELAY_H */

