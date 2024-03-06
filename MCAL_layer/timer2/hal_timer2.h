/* 
 * File:   hal_timer2.h
 * Author: OKTA
 *
 * Created on January 22, 2024, 4:38 PM
 */

#ifndef HAL_TIMER2_H
#define	HAL_TIMER2_H

/*---------- section : Includes --------------------*/
#include "pic18f4620.h"
#include "../MCAL_STD_types.h"
#include "../../MCAL_layer/GPIO/hal_gpio.h"
#include "../../MCAL_layer/interrupt/mcal_internal_interrupt.h"

/*---------- section : Macro Declarations --------------------*/
   
    /* Timer2 Input Clock postscaler */
#define TIMER2_POSTSCALER_DIV_BY_1               0
#define TIMER2_POSTSCALER_DIV_BY_2               1
#define TIMER2_POSTSCALER_DIV_BY_3               2
#define TIMER2_POSTSCALER_DIV_BY_4               3
#define TIMER2_POSTSCALER_DIV_BY_5               4
#define TIMER2_POSTSCALER_DIV_BY_6               5
#define TIMER2_POSTSCALER_DIV_BY_7               6
#define TIMER2_POSTSCALER_DIV_BY_8               7
#define TIMER2_POSTSCALER_DIV_BY_9               8
#define TIMER2_POSTSCALER_DIV_BY_10              9
#define TIMER2_POSTSCALER_DIV_BY_11              10
#define TIMER2_POSTSCALER_DIV_BY_12              11
#define TIMER2_POSTSCALER_DIV_BY_13              12
#define TIMER2_POSTSCALER_DIV_BY_14              13
#define TIMER2_POSTSCALER_DIV_BY_15              14
#define TIMER2_POSTSCALER_DIV_BY_16              15

    /* Timer2 Input Clock Prescaler */
#define TIMER2_PRESCALER_DIV_BY_1                0
#define TIMER2_PRESCALER_DIV_BY_4                1
#define TIMER2_PRESCALER_DIV_BY_16               2


/*---------- section : Macro Function declarations --------------------*/
    /* Enable or Disable Timer2 */
#define TIMER2_MODULE_ENABLE()                  (T2CONbits.TMR2ON = 1)
#define TIMER2_MODULE_DISABLE()                 (T2CONbits.TMR2ON = 0)

    /* Timer2 Input Clock Prescaler */
#define TIMER2_PRESCALER_SELECT(_PRESCALER_)    (T2CONbits.T2CKPS = _PRESCALER_)

    /* Timer2 Input Clock Postscaler */
#define TIMER2_POSTSCALER_SELECT(_POSTSCALER_)  (T2CONbits.TOUTPS = _POSTSCALER_)

/*---------- section : Data Type Declarations --------------------*/
typedef struct
{
#if TIMER2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    void (* TIMER2_InterruptHandler)(void);      /* Call back */
    interrupt_priority_cfg  priority;
#endif
    uint8 timer2_preload_value;
    uint8 timer2_prescaler_value    : 2;
    uint8 timer2_postscaler_value   : 4;
    uint8 timer2_reserved           : 2;
}timer2_t;


/*---------- section : Function declarations --------------------*/

/**
 * @brief Initialize the Timer2 module 
 * @param _timer pointer of object that we can go to register from
 * @return Status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action
 */
std_ReturnType Timer2_Init(const timer2_t *_timer);

/**
 * @brief Deinitialize the Timer2 module 
 * @param _timer pointer of object that we can go to register from
 * @return Status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action
 */
std_ReturnType Timer2_DeInit(const timer2_t *_timer);

/**
 * @brief Write value in timer2 register 
 * @param _timer pointer of object that we can go to register from
 * @param _Value The value that will be writen 
 * @return Status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action
 */
std_ReturnType Timer2_Write_Value(const timer2_t *_timer, uint8 _Value);

/**
 * @brief Read value from timer2 register
 * @param _timer pointer of object that we can go to register from
 * @param _Value The value that will be Read 
 * @return Status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action
 */
std_ReturnType Timer2_Read_Value(const timer2_t *_timer, uint8 *_Value);



#endif	/* HAL_TIMER2_H */

