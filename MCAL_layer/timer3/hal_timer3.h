/* 
 * File:   hal_timer3.h
 * Author: OKTA
 *
 * Created on January 22, 2024, 4:38 PM
 */

#ifndef HAL_TIMER3_H
#define	HAL_TIMER3_H

/*---------- section : Includes --------------------*/
#include "pic18f4620.h"
#include "../MCAL_STD_types.h"
#include "../../MCAL_layer/GPIO/hal_gpio.h"
#include "../../MCAL_layer/interrupt/mcal_internal_interrupt.h"

/*---------- section : Macro Declarations --------------------*/

    /* Timer3 modes */
#define TIMER3_TIMER_MODE                       0
#define TIMER3_COUNTER_MODE                     1

    /* Timer3 Input Clock Prescaler */
#define TIMER3_PRESCALER_DIV_BY_1               0
#define TIMER3_PRESCALER_DIV_BY_2               1
#define TIMER3_PRESCALER_DIV_BY_4               2
#define TIMER3_PRESCALER_DIV_BY_8               3

    /* 16-Bit Read/Write Mode Enable */
#define TIMER3_RW_REG_8BIT_MODE                 0
#define TIMER3_RW_REG_16BIT_MODE                1

    /* Timer1 External Clock Input Synchronization */
#define TIMER3_ASYNC_COUNTER_MODE               1
#define TIMER3_SYNC_COUNTER_MODE                0

/*---------- section : Macro Function declarations --------------------*/
   
    /* Enable or Disable Timer3 */
#define TIMER3_MODULE_ENABLE()                  (T3CONbits.TMR3ON = 1)
#define TIMER3_MODULE_DISABLE()                 (T3CONbits.TMR3ON = 0)

    /* Timer3 Modes */
#define TIMER3_TIMER_MODE_ENABLE()              (T3CONbits.TMR3CS = 0)
#define TIMER3_COUNTER_MODE_ENABLE()            (T3CONbits.TMR3CS = 1)

    /* Timer3 External Clock Input Synchronization */
#define TIMER3_ASYNC_COUNTER_MODE_ENABLE()      (T3CONbits.T3SYNC = 1)
#define TIMER3_SYNC_COUNTER_MODE_ENABLE()       (T3CONbits.T3SYNC = 0)

    /* 16-Bit Read/Write Mode Enable */
#define TIMER3_RW_REG_8BIT_MODE_ENABLE          (T3CONbits.RD16 = 0)
#define TIMER3_RW_REG_16BIT_MODE_ENABLE         (T3CONbits.RD16 = 1)

    /* Timer3 Input Clock Prescaler */
#define TIMER3_PRESCALER_SELECT(_PRESCALER_)    (T3CONbits.T3CKPS = _PRESCALER_)

/*---------- section : Data Type Declarations --------------------*/
typedef struct
{
#if TIMER3_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    void (* TIMER3_InterruptHandler)(void);      /* Call back */
    interrupt_priority_cfg  priority;
#endif
    uint16 timer3_preload_value;
    uint8 timer3_prescaler_value    : 2;
    uint8 timer3_mode               : 1;
    uint8 timer3_counter_mode       : 1;
    uint8 timer3_reg_rw_mode        : 1;
    uint8 timer3_reserved           : 3;
}timer3_t;

/*---------- section : Function declarations --------------------*/

/**
 * @brief Initialize the Timer3 module 
 * @param _timer pointer of object that we can go to register from
 * @return Status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action
 */
std_ReturnType Timer3_Init(const timer3_t *_timer);

/**
 * @brief Deinitialize the Timer3 module 
 * @param _timer pointer of object that we can go to register from
 * @return Status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action
 */
std_ReturnType Timer3_DeInit(const timer3_t *_timer);

/**
 * @brief Write value in timer3 register 
 * @param _timer pointer of object that we can go to register from
 * @param _Value The value that will be writen 
 * @return Status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action
 */
std_ReturnType Timer3_Write_Value(const timer3_t *_timer, uint16 _Value);

/**
 * @brief Read value from timer3 register
 * @param _timer pointer of object that we can go to register from
 * @param _Value The value that will be Read 
 * @return Status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action
 */
std_ReturnType Timer3_Read_Value(const timer3_t *_timer, uint16 *_Value);

#endif	/* HAL_TIMER3_H */

