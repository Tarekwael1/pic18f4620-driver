/* 
 * File:   hal_timer0.c
 * Author: OKTA
 *
 * Created on October 20, 2023, 11:30 AM
 */

#include "hal_timer0.h"

static inline void Timer0_Prescaler_config(const timer0_t *_timer);
static inline void Timer0_Mode_select(const timer0_t *_timer);
static inline void Timer0_Register_Size_Config(const timer0_t *_timer);

#if TIMER0_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
static InterruptHandler TIMER0_InterruptHandler = NULL;
#endif

static uint16 timer0_preload = ZERO_INIT;

/**
 * @brief Initialize the Timer0 module 
 * @param _timer pointer of object that we can go to register from
 * @return Status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action
 */
std_ReturnType Timer0_Init(const timer0_t *_timer)
{
    std_ReturnType ret = E_NOT_OK;
    if(NULL == _timer)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* Disable TIMER0 Module */
        TIMER0_MODULE_DISABLE();
        /* Timer0 Prescaler Select bits */
        Timer0_Prescaler_config(_timer->prescaler_value);
        /* Timer0 Clock Source Select */
        Timer0_Mode_select(_timer);
        /* Timer0 8-Bit/16-Bit Control */
        Timer0_Register_Size_Config(_timer);
        /* Set the preload value*/
        TMR0H = (_timer->timer0_preload_value) >> 8;
        TMR0L = (uint8)(_timer->timer0_preload_value);
        timer0_preload = _timer->timer0_preload_value;
/* Configure the interrupt */
#if TIMER0_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE  
        TIMER0_InterruptEnable();
        TIMER0_InterruptflagClear();
        TIMER0_InterruptHandler = _timer->TIMER0_InterruptHandler;
/* Interrupt priority configurations */       
    #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 
            INTERRUPT_PriotrityLevelsEnable();
            if(INTERRUPT_HIGH_PRIORITY == _timer->priority)
            {
                INTERRUPT_GlobalInterruptHighEnable();
                TIMER0_SetHighPriority();
            }
            else if(INTERRUPT_LOW_PRIORITY == _timer->priority)
            {
                INTERRUPT_GlobalInterruptLowEnable();
                TIMER0_SetLowPriority();
            }
            else{/*NOTHING*/}  
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInrerruptEnable();
    #endif
#endif
        /* Enable TIMER0 Module */
        TIMER0_MODULE_ENABLE();
                
        ret = E_OK;
    }
    return ret;
}

/**
 * @brief Deinitialize the Timer0 module 
 * @param _timer pointer of object that we can go to register from
 * @return Status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action
 */
std_ReturnType Timer0_DeInit(const timer0_t *_timer)
{
    std_ReturnType ret = E_NOT_OK;
    if(NULL == _timer)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* Disable TIMER0 Module */
        TIMER0_MODULE_DISABLE();
        #if TIMER0_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        /* Disable TIMER0 Module Interrupt */
        TIMER0_InterruptDisable();
        #endif
        ret = E_OK;
    }
    return ret;
}

/**
 * @brief Write value in timer0 register 
 * @param _timer pointer of object that we can go to register from
 * @param _Value The value that will be writen 
 * @return Status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action
 */
std_ReturnType Timer0_Write_Value(const timer0_t *_timer, uint16 _Value)
{
    std_ReturnType ret = E_NOT_OK;
    if(NULL == _timer)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* Set the preload value*/
        TMR0H = (_Value) >> 8;
        TMR0L = (uint8)(_Value);
        ret = E_OK;
    }
    return ret;
}

/**
 * @brief Read value from timer0 register
 * @param _timer pointer of object that we can go to register from
 * @param _Value The value that will be Read 
 * @return Status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action
 */
std_ReturnType Timer0_Read_Value(const timer0_t *_timer, uint16 *_Value)
{
    std_ReturnType ret = E_NOT_OK;
    uint8 l_tmr0l = ZERO_INIT, l_tmr0h = ZERO_INIT;
    if((NULL == _timer) || (NULL == _Value))
    {
        ret = E_NOT_OK;
    }
    else
    {
        l_tmr0l = TMR0L;
        l_tmr0h = TMR0H;
        *_Value = (uint16)((l_tmr0h << 8) + l_tmr0l);
        ret = E_OK;
    }
    return ret;
}



/**
 * Call back function
 */
void TIMER0_ISR(void)
{
    TIMER0_InterruptflagClear();
    TMR0H = (timer0_preload) >> 8;
    TMR0L = (uint8)(timer0_preload);
    if(TIMER0_InterruptHandler)
    {
        TIMER0_InterruptHandler();
    }
}

/**
 * @brief Helper function to configure the prescaler of timer0 module
 * @param _timer pointer of object that we can go to register from
 */
static inline void Timer0_Prescaler_config(const timer0_t *_timer)
{
    if(TIMER0_PRESCALER_ENABLE_CFG == _timer->prescaler_enable)
    {
        TIMER0_PRESCALER_ENABLE();
        T0CONbits.T0PS = _timer->prescaler_value;
    }
    else if(TIMER0_PRESCALER_DISABLE_CFG == _timer->prescaler_enable)
    {
        TIMER0_PRESCALER_DISABLE();
    }
    else{/* NOTHING */}
}

/**
 * @brief Helper function to select the mode of timer0 (timer or counter)
 * @param _timer pointer of object that we can go to register from
 */
static inline void Timer0_Mode_select(const timer0_t *_timer)
{
    if(TIMER0_TIMER_MODE == _timer->timer0_mode)
    {
        TIMER0_TIMER_MODE_ENABLE();
    }
    else if(TIMER0_COUNTER_MODE == _timer->timer0_mode)
    {
        TIMER0_COUNTER_MODE_ENABLE();
        if(TIMER0_COUNTER_RISING_EDGE_CFG == _timer->timer0_counter_edge)
        {
            TIMER0_RISING_EDGE_ENABLE();
        }
        else if(TIMER0_COUNTER_FALLING_EDGE__CFG == _timer->timer0_counter_edge)
        {
            TIMER0_FALLING_EDGE_ENABLE();
        }
        else{/* NOTHING */}
    }
    else{/* NOTHING */}
}

/**
 * @brief Helper function to chose the size of timer0 module (8 or 16)
 * @param _timer pointer of object that we can go to register from
 */
static inline void Timer0_Register_Size_Config(const timer0_t *_timer)
{
    if(TIMER0_8BIT_REGISTER_MODE == _timer->timer0_register_size)
    {
        TIMER0_8BIT_REGISTER_MODE_ENABLE();
    }
    else if(TIMER0_16BIT_REGISTER_MODE == _timer->timer0_register_size)
    {
        TIMER0_16BIT_REGISTER_MODE_ENABLE();
    }
    else{/* NOTHING */}
}
