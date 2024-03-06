/* 
 * File:   ecu_dc_motor.h
 * Author: OKTA
 *
 * Created on September 20, 2023, 4:21 PM
 */

#ifndef ECU_DC_MOTOR_H
#define	ECU_DC_MOTOR_H


/*section : Includes */
#include "ecu_dc_motor_cfg.h"
#include "../../MCAL_layer/GPIO/hal_gpio.h"


/*section : Macro Declarations   */
#define DC_MOTOR_ON_STATUS  0x01U
#define DC_MOTOR_OFF_STATUS 0x00U

#define DC_MOTOR_PIN1       0x00U
#define DC_MOTOR_PIN2       0x01U

#define PINS_OF_MOTOR       2
/*section : Macro Function declarations */


/*section : Data Type Declarations */
typedef struct
{
    pin_config_t dc_motor_pin[PINS_OF_MOTOR];
}dc_motor_t;

/*section : Function declarations */

/**
 * @brief Initialize the assigned pin to be (INPUT OR OUTPUT) of (dc_motor) and turn the motor on or off
 * @param _dc_motor Pointer to the dc_motor module configurations
 * @return Status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action
 */        
std_ReturnType dc_motor_initialize(const dc_motor_t *_dc_motor);

/**
 * @brief Move the motor right
 * @param _dc_motor Pointer to the dc_motor module configurations
 * @return Status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action
 */
std_ReturnType dc_motor_move_right(const dc_motor_t *_dc_motor);

/**
 * @brief Move the motor left
 * @param _dc_motor Pointer to the dc_motor module configurations
 * @return Status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action
 */
std_ReturnType dc_motor_move_left(const dc_motor_t *_dc_motor);

/**
 * @brief Stop the motor
 * @param _dc_motor Pointer to the dc_motor module configurations
 * @return Status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action
 */
std_ReturnType dc_motor_stop(const dc_motor_t *_dc_motor);

#endif	/* ECU_DC_MOTOR_H */

