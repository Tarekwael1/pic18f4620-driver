/* 
 * File:   ecu_led.h
 * Author: OKTA
 *
 * Created on September 14, 2023, 9:18 PM
 */

#ifndef ECU_LED_H
#define	ECU_LED_H


/*section : Includes */
#include "../../MCAL_layer/GPIO/hal_gpio.h"
#include "ecu_led_cfg.h"    

/*section : Macro Declarations   */


/*section : Macro Function declarations */

/*section : Data Type Declarations */
typedef enum
{
    LED_OFF = 0,
    LED_ON
}led_status_t;


typedef struct
{
    uint8 port_name  : 4;
    uint8 pin        : 3;
    uint8 led_status : 1;
}led_t;

/*section : Function declarations */
/**
 * @brief Initialize the assigned pin to be (INPUT OR OUTPUT) and turn the led on or off
 * @param led : Pointer to the led module configurations
 * @return Status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action 
 */
std_ReturnType led_initialize(const led_t *led);

/**  
 * @brief   Turn the led on 
 * @param led : Pointer to the led module configurations
 * @return Status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action 
 */
std_ReturnType led_turn_on(const led_t *led);

/**
 * @brief   Turn the led off
 * @param led : Pointer to the led module configurations
 * @return Status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action 
 */
std_ReturnType led_turn_off(const led_t *led);

/**
 * @brief   Reverse state of led if on turn it of ... 
 * @param led : Pointer to the led module configurations
 * @return Status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action 
 */
std_ReturnType led_turn_toggle(const led_t *led);

#endif	/* ECU_LED_H */

