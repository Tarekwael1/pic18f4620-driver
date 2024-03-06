/* 
 * File:   hal_timer1.h
 * Author: OKTA
 *
 * Created on January 22, 2024, 9:54 AM
 */

#ifndef HAL_TIMER1_H
#define	HAL_TIMER1_H

/*---------- section : Includes --------------------*/
#include "pic18f4620.h"
#include "../MCAL_STD_types.h"
#include "../../MCAL_layer/GPIO/hal_gpio.h"
#include "../../MCAL_layer/interrupt/mcal_internal_interrupt.h"
 
/*---------- section : Macro Declarations --------------------  */

    /* Timer1 Mode */
#define TIMER1_TIMER_MODE                       0
#define TIMER1_COUNTER_MODE                     1
   
    /* Timer1 External Clock Input Synchronization */
#define TIMER1_ASYNC_COUNTER_MODE               1
#define TIMER1_SYNC_COUNTER_MODE                0

    /* Timer1 Oscillator */
#define TIMER1_OSCILLATOR_ENABLE                1
#define TIMER1_OSCILLATOR_DISABLE               0

    /* Timer1 Input Clock Prescaler */
#define TIMER1_PRESCALER_DIV_BY_1               0
#define TIMER1_PRESCALER_DIV_BY_2               1
#define TIMER1_PRESCALER_DIV_BY_4               2
#define TIMER1_PRESCALER_DIV_BY_8               3

    /* 16-Bit Read/Write Mode Enable */
#define TIMER1_RW_REG_8BIT_MODE                 0
#define TIMER1_RW_REG_16BIT_MODE                1
/*---------- section : Macro Function declarations --------------------*/

    /* Enable or Disable Timer1 */
#define TIMER1_MODULE_ENABLE()                  (T1CONbits.TMR1ON = 1)
#define TIMER1_MODULE_DISABLE()                 (T1CONbits.TMR1ON = 0)

    /* Timer1 Mode */
#define TIMER1_TIMER_MODE_ENABLE()              (T1CONbits.TMR1CS = 0)
#define TIMER1_COUNTER_MODE_ENABLE()            (T1CONbits.TMR1CS = 1)
    
    /* Timer1 External Clock Input Synchronization */
#define TIMER1_ASYNC_COUNTER_MODE_ENABLE()      (T1CONbits.T1SYNC = 1)
#define TIMER1_SYNC_COUNTER_MODE_ENABLE()       (T1CONbits.T1SYNC = 0)

    /* Timer1 Oscillator */
#define TIMER1_OSCILLATOR_HW_ENABLE()           (T1CONbits.T1OSCEN = 1)
#define TIMER1_OSCILLATOR_HW_DISABLE()          (T1CONbits.T1OSCEN = 0)

    /* Timer1 Input Clock Prescaler */
#define TIMER1_PRESCALER_SELECT(_PRESCALER_)    (T1CONbits.T1CKPS = _PRESCALER_)

    /* Timer1 System Clock Status */
#define TIMER1_SYSTEM_CLK_STATUS()              (T1CONbits.T1RUN)  

    /* 16-Bit Read/Write Mode Enable */
#define TIMER1_RW_REG_8BIT_MODE_ENABLE          (T1CONbits.RD16 = 0)
#define TIMER1_RW_REG_16BIT_MODE_ENABLE         (T1CONbits.RD16 = 1)

/*---------- section : Data Type Declarations --------------------*/
typedef struct
{
#if TIMER1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    void (* TIMER1_InterruptHandler)(void);      /* Call back */
    interrupt_priority_cfg  priority;
#endif
    uint16 timer1_preload_value;
    uint8 timer1_prescaler_value    : 2;
    uint8 timer1_mode               : 1;
    uint8 timer1_counter_mode       : 1;
    uint8 timer1_osc_cfg            : 1;
    uint8 timer1_reg_rw_mode        : 1;
    uint8 timer1_reserved           : 2;
}timer1_t;

/*---------- section : Function declarations --------------------*/
/**
 * @brief Initialize the Timer1 module 
 * @param _timer pointer of object that we can go to register from
 * @return Status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action
 */
std_ReturnType Timer1_Init(const timer1_t *_timer);

/**
 * @brief Deinitialize the Timer1 module 
 * @param _timer pointer of object that we can go to register from
 * @return Status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action
 */
std_ReturnType Timer1_DeInit(const timer1_t *_timer);

/**
 * @brief Write value in timer1 register 
 * @param _timer pointer of object that we can go to register from
 * @param _Value The value that will be writen 
 * @return Status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action
 */
std_ReturnType Timer1_Write_Value(const timer1_t *_timer, uint16 _Value);

/**
 * @brief Read value from timer1 register
 * @param _timer pointer of object that we can go to register from
 * @param _Value The value that will be Read 
 * @return Status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action
 */
std_ReturnType Timer1_Read_Value(const timer1_t *_timer, uint16 *_Value);

#endif	/* HAL_TIMER1_H */

