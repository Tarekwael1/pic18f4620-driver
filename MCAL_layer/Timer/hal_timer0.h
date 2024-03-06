/* 
 * File:   hal_timer0.h
 * Author: OKTA
 *
 * Created on October 20, 2023, 11:30 AM
 */

#ifndef HAL_TIMER0_H
#define	HAL_TIMER0_H
/*---------- section : Includes --------------------*/
#include "pic18f4620.h"
#include "../MCAL_STD_types.h"
#include "../../MCAL_layer/GPIO/hal_gpio.h"
#include "../../MCAL_layer/interrupt/mcal_internal_interrupt.h"

/*---------- section : Macro Declarations --------------------  */
    
    /* Timer0 prescaler */
#define TIMER0_PRESCALER_ENABLE_CFG             0
#define TIMER0_PRESCALER_DISABLE_CFG            1
    
    /* Timer0 counter modes */
#define TIMER0_COUNTER_RISING_EDGE_CFG          0
#define TIMER0_COUNTER_FALLING_EDGE__CFG        1

    /* Timer0 modes */
#define TIMER0_TIMER_MODE                       0
#define TIMER0_COUNTER_MODE                     1

    /* Size of register */
#define TIMER0_8BIT_REGISTER_MODE               1
#define TIMER0_16BIT_REGISTER_MODE              0


/*---------- section : Macro Function declarations --------------------*/

    /* Timer0 prescaler */
#define TIMER0_PRESCALER_ENABLE()               (T0CONbits.PSA = 0)
#define TIMER0_PRESCALER_DISABLE()              (T0CONbits.PSA = 1)
    
    /* Timer0 counter modes */
#define TIMER0_RISING_EDGE_ENABLE()             (T0CONbits.T0SE = 0)
#define TIMER0_FALLING_EDGE_ENABLE()            (T0CONbits.T0SE = 1)

    /* Timer0 modes */
#define TIMER0_TIMER_MODE_ENABLE()              (T0CONbits.T0CS = 0)
#define TIMER0_COUNTER_MODE_ENABLE()            (T0CONbits.T0CS = 1)

    /* Size of register */
#define TIMER0_8BIT_REGISTER_MODE_ENABLE()      (T0CONbits.T08BIT = 1)
#define TIMER0_16BIT_REGISTER_MODE_ENABLE()     (T0CONbits.T08BIT = 0)
    
    /* Timer0 Enable or disable */
#define TIMER0_MODULE_ENABLE()                  (T0CONbits.TMR0ON = 1)
#define TIMER0_MODULE_DISABLE()                 (T0CONbits.TMR0ON = 0)

/*---------- section : Data Type Declarations --------------------*/
typedef enum
{
    TIMER0_PRESCALER_DIV_BY_2 = 0,
    TIMER0_PRESCALER_DIV_BY_4,    
    TIMER0_PRESCALER_DIV_BY_8, 
    TIMER0_PRESCALER_DIV_BY_16, 
    TIMER0_PRESCALER_DIV_BY_32, 
    TIMER0_PRESCALER_DIV_BY_64, 
    TIMER0_PRESCALER_DIV_BY_128,
    TIMER0_PRESCALER_DIV_BY_256 
}timer0_prescaler_select_t;


typedef struct
{
#if TIMER0_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    void (* TIMER0_InterruptHandler)(void);      /* Call back */
    interrupt_priority_cfg  priority;
#endif
    timer0_prescaler_select_t   prescaler_value;
    uint16 timer0_preload_value;
    uint8 prescaler_enable      : 1;
    uint8 timer0_counter_edge   : 1;
    uint8 timer0_mode           : 1;
    uint8 timer0_register_size  : 1;
    uint8 timer0_reserved       : 4;
}timer0_t;
/*---------- section : Function declarations --------------------*/
/**
 * @brief Initialize the Timer0 module 
 * @param _timer pointer of object that we can go to register from
 * @return Status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action
 */
std_ReturnType Timer0_Init(const timer0_t *_timer);

/**
 * @brief Deinitialize the Timer0 module 
 * @param _timer pointer of object that we can go to register from
 * @return Status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action
 */
std_ReturnType Timer0_DeInit(const timer0_t *_timer);

/**
 * @brief Write value in timer0 register 
 * @param _timer pointer of object that we can go to register from
 * @param _Value The value that will be writen 
 * @return Status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action
 */
std_ReturnType Timer0_Write_Value(const timer0_t *_timer, uint16 _Value);

/**
 * @brief Read value from timer0 register
 * @param _timer pointer of object that we can go to register from
 * @param _Value The value that will be Read 
 * @return Status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action
 */
std_ReturnType Timer0_Read_Value(const timer0_t *_timer, uint16 *_Value);
#endif	/* HAL_TIMER0_H */

 