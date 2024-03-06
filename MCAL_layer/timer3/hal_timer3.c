/* 
 * File:   hal_timer3.c
 * Author: OKTA
 *
 * Created on January 22, 2024, 4:38 PM
 */


#include "hal_timer3.h"

#if TIMER3_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
static InterruptHandler TIMER3_InterruptHandler = NULL;
#endif

static uint16 timer3_preload = ZERO_INIT;

static inline void Timer3_Mode_select(const timer3_t *_timer);

/*---------- section : Function declarations --------------------*/
/**
 * @brief Initialize the Timer3 module 
 * @param _timer pointer of object that we can go to register from
 * @return Status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action
 */
std_ReturnType Timer3_Init(const timer3_t *_timer)
{
    std_ReturnType ret = E_NOT_OK;
    if(NULL == _timer)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* Disable TIMER1 Module */
        TIMER3_MODULE_DISABLE();
        /* Timer1 Prescaler Select bits */
        TIMER3_PRESCALER_SELECT(_timer->timer3_prescaler_value);
        /* Timer1 Clock Source Select */
        Timer3_Mode_select(_timer);
        /* Set the preload value*/
        TMR3H = (_timer->timer3_preload_value) >> 8;
        TMR3L = (uint8)(_timer->timer3_preload_value);
        timer3_preload = _timer->timer3_preload_value;
/* Configure the interrupt */
#if TIMER3_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE  
        TIMER3_InterruptEnable();
        TIMER3_InterruptflagClear();
        TIMER3_InterruptHandler = _timer->TIMER3_InterruptHandler;
/* Interrupt priority configurations */       
    #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 
            INTERRUPT_PriotrityLevelsEnable();
            if(INTERRUPT_HIGH_PRIORITY == _timer->priority)
            {
                INTERRUPT_GlobalInterruptHighEnable();
                TIMER3_SetHighPriority();
            }
            else if(INTERRUPT_LOW_PRIORITY == _timer->priority)
            {
                INTERRUPT_GlobalInterruptLowEnable();
                TIMER3_SetLowPriority();
            }
            else{/*NOTHING*/}  
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInrerruptEnable();
    #endif
#endif
        /* Enable TIMER1 Module */
        TIMER3_MODULE_ENABLE();
        ret = E_OK;
    }
    return ret;
}

/**
 * @brief Deinitialize the Timer3 module 
 * @param _timer pointer of object that we can go to register from
 * @return Status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action
 */
std_ReturnType Timer3_DeInit(const timer3_t *_timer)
{
    std_ReturnType ret = E_NOT_OK;
    if(NULL == _timer)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* Disable TIMER3 Module */
        TIMER3_MODULE_DISABLE();
        #if TIMER3_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        /* Disable TIMER3 Module Interrupt */
        TIMER3_InterruptDisable();
        #endif
        ret = E_OK;
    }
    return ret;
}

/**
 * @brief Write value in timer3 register 
 * @param _timer pointer of object that we can go to register from
 * @param _Value The value that will be writen 
 * @return Status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action
 */
std_ReturnType Timer3_Write_Value(const timer3_t *_timer, uint16 _Value)
{
    std_ReturnType ret = E_NOT_OK;
    if(NULL == _timer)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* Set the preload value*/
        TMR3H = (_Value) >> 8;
        TMR3L = (uint8)(_Value);
        ret = E_OK;
    }
    return ret;
}

/**
 * @brief Read value from timer3 register
 * @param _timer pointer of object that we can go to register from
 * @param _Value The value that will be Read 
 * @return Status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action
 */
std_ReturnType Timer3_Read_Value(const timer3_t *_timer, uint16 *_Value)
{
    std_ReturnType ret = E_NOT_OK;
    uint8 l_tmr3l = ZERO_INIT, l_tmr3h = ZERO_INIT;
    if((NULL == _timer) || (NULL == _Value))
    {
        ret = E_NOT_OK;
    }
    else
    {
        l_tmr3l = TMR3L;
        l_tmr3h = TMR3H;
        *_Value = (uint16)((l_tmr3h << 8) + l_tmr3l);
        ret = E_OK;
    }
    return ret;
}



static inline void Timer3_Mode_select(const timer3_t *_timer)
{
    if(TIMER3_TIMER_MODE == _timer->timer3_mode)
    {
        TIMER3_TIMER_MODE_ENABLE();
    }
    else if(TIMER3_COUNTER_MODE == _timer->timer3_mode)
    {
        TIMER3_COUNTER_MODE_ENABLE();
        if(TIMER3_ASYNC_COUNTER_MODE == _timer->timer3_counter_mode)
        {
            TIMER3_ASYNC_COUNTER_MODE_ENABLE();
        }
        else if(TIMER3_SYNC_COUNTER_MODE == _timer->timer3_counter_mode)
        {
            TIMER3_SYNC_COUNTER_MODE_ENABLE();
        }
        else{/* NOTHING */}
    }
    else{/* NOTHING */}
}

/**
 * Call back function
 */
void TIMER3_ISR(void)
{
    TIMER3_InterruptflagClear();
    TMR3H = (timer3_preload) >> 8;
    TMR3L = (uint8)(timer3_preload);
    if(TIMER3_InterruptHandler)
    {
        TIMER3_InterruptHandler();
    }
}
