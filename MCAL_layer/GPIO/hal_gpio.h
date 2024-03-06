/* 
 * File:   hal_gpio.h
 * Author: OKTA
 *
 * Created on September 14, 2023, 8:46 PM
 */

#ifndef HAL_GPIO_H
#define	HAL_GPIO_H

/*section : Includes */

#include "pic18f4620.h"
#include "../MCAL_STD_types.h"
#include "../device_config.h"
#include "hal_gpio_cfg.h"

/*section : Macro Declarations   */
#define BIT_MASK             (uint8)1

#define PORT_PIN_MAX_NUMBER  8
#define PORT_MAX_NUMBER      5

#define PORTC_MASK           0XFF

/*section : Macro Function declarations */
#define HWREG8(_X)     (*((volatile uint8 *)(_X)))

#define SET_BIT(REG, BIT_POS)        (REG |= (BIT_MASK << BIT_POS))
#define CLEAR_BIT(REG, BIT_POS)      (REG &= ~(BIT_MASK << BIT_POS))
#define TOGGLE_BIT(REG, BIT_POS)     (REG ^= (BIT_MASK << BIT_POS))
#define READ_BIT(REG, BIT_POS)       ((REG >> BIT_POS) & BIT_MASK)

/*section : Data Type Declarations */
typedef enum{
    GPIO_LOW = 0,
    GPIO_HIGH
}logic_t;

typedef enum{
    GPIO_DIRECTION_OUTPUT = 0,
    GPIO_DIRECTION_INPUT
}direction_t;

typedef enum{
    GPIO_PIN0 = 0,
    GPIO_PIN1,
    GPIO_PIN2,
    GPIO_PIN3,
    GPIO_PIN4,
    GPIO_PIN5,
    GPIO_PIN6,
    GPIO_PIN7        
}pin_index_t;

typedef enum{
    PORTA_INDEX = 0,
    PORTB_INDEX,
    PORTC_INDEX,
    PORTD_INDEX,
    PORTE_INDEX        
}port_index_t;

typedef struct{
    uint8 port      : 3;      /* @ref port_index_t*/ // 3 is the size that save in the memory 3 bits
    uint8 pin       : 3;      /* @ref pin_index_t*/  // this mean that you need to goto pin_index_t to know the values that you must input
    uint8 direction : 1;      /* @ref direction_t*/
    uint8 logic     : 1;      /* @ref logic_t*/
}pin_config_t;

/*section : Function declarations */

/**
 * @brief Initialize the functions in pins to limit number of calls of functions in main (for output signal)
 * @param _pin_config is a pointer to the configuration @ref pin_config_t
 * @return status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action 
 */
std_ReturnType gpio_pin_initialize(const pin_config_t *_pin_config);

/**
 * @brief Initialize the direction of a specific pin (output or input) @ref direction_t 
 * @param _pin_config is a pointer to the configuration @ref pin_config_t
 * @return status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action 
 */
std_ReturnType gpio_pin_direction_initialize(const pin_config_t *_pin_config);

/**
 * @brief  Function to read the direction (input or output)that in pins 
 * @param _pin_config is a pointer to the configuration @ref pin_config_t
 * @param direction_status is a pointer to store the value in 
 * @return Status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action 
 */
std_ReturnType gpio_pin_get_direction_status(const pin_config_t *_pin_config, direction_t *direction_status);

/**
 * @brief Function to write the logic in pins (HIGH OR LOW)
 * @param _pin_config is a pointer to the configuration @ref pin_config_t
 * @param logic Is a variable that check input (if high write 1 if low write 0)
 * @return Status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action 
 */
std_ReturnType gpio_pin_write_logic(const pin_config_t *_pin_config, logic_t logic);

/**
 * @brief Function to read the logic in pins (HIGH OR LOW)
 * @param _pin_config is a pointer to the configuration @ref pin_config_t
 * @param logic is a pointer to store the value in it 
 * @return status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action 
 */
std_ReturnType gpio_pin_read_logic(const pin_config_t *_pin_config, logic_t *logic);

/**
 * @brief Function to reverse the value that in pins 
 * @param _pin_config is a pointer to the configuration @ref pin_config_t
 * @return status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action 
 */
std_ReturnType gpio_pin_toggle_logic(const pin_config_t *_pin_config);



/**
 * @brief Initialize the direction of a specific port (output or input) @ref direction_t 
 * @param port The port that will initialize @ref port_index_t
 * @param direction is a direction that you need in the port 
 * @return status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action 
 */
std_ReturnType gpio_port_direction_initialize(port_index_t port, uint8 direction);

/**
 * @brief Function to read the direction of the port
 * @param port the port that you need to read its direction @ref port_index_t
 * @param direction_status
 * @return status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action 
 */
std_ReturnType gpio_port_get_direction_status(port_index_t port, uint8 *direction_status);

/**
 * @brief Function to write the logic in ports (HIGH OR LOW)
 * @param port The port that you need to write logic on it  @ref port_index_t
 * @param logic Is the state that will writen in port (HIGH OR LOW)
 * @return status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action 
 */
std_ReturnType gpio_port_write_logic(port_index_t port, uint8 logic);

/**
 * @brief Function to read the logic in ports (HIGH OR LOW)
 * @param port The port that you need to read logic from it  @ref port_index_t
 * @param logic Is the state that will road from port (HIGH OR LOW)
 * @return status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action 
 */
std_ReturnType gpio_port_read_logic(port_index_t port, uint8 *logic);

/**
 * @brief Function to reverse the value that in ports 
 * @param port Is a port that you need to toggle @ref port_index_t
 * @return status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action 
 */
std_ReturnType gpio_port_toggle_logic(port_index_t port);

#endif	/* HAL_GPIO_H */

