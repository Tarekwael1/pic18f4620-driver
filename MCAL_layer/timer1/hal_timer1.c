/* 
 * File:   hal_timer1.c
 * Author: OKTA
 *
 * Created on January 22, 2024, 9:54 AM
 */


#include "hal_timer1.h"

static inline void Timer1_Mode_select(const timer1_t *_timer);

#if TIMER1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
static InterruptHandler TIMER1_InterruptHandler = NULL;
#endif

static uint16 timer1_preload = ZERO_INIT;

/**
 * @brief Initialize the Timer0 module 
 * @param _timer pointer of object that we can go to register from
 * @return Status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action
 */
std_ReturnType Timer1_Init(const timer1_t *_timer)
{
    std_ReturnType ret = E_NOT_OK;
    if(NULL == _timer)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* Disable TIMER1 Module */
        TIMER1_MODULE_DISABLE();
        /* Timer1 Prescaler Select bits */
        TIMER1_PRESCALER_SELECT(_timer->timer1_prescaler_value);
        /* Timer1 Clock Source Select */
        Timer1_Mode_select(_timer);
        /* Set the preload value*/
        TMR1H = (_timer->timer1_preload_value) >> 8;
        TMR1L = (uint8)(_timer->timer1_preload_value);
        timer1_preload = _timer->timer1_preload_value;
/* Configure the interrupt */
#if TIMER1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE  
        TIMER1_InterruptEnable();
        TIMER1_InterruptflagClear();
        TIMER1_InterruptHandler = _timer->TIMER1_InterruptHandler;
/* Interrupt priority configurations */       
    #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 
            INTERRUPT_PriotrityLevelsEnable();
            if(INTERRUPT_HIGH_PRIORITY == _timer->priority)
            {
                INTERRUPT_GlobalInterruptHighEnable();
                TIMER1_SetHighPriority();
            }
            else if(INTERRUPT_LOW_PRIORITY == _timer->priority)
            {
                INTERRUPT_GlobalInterruptLowEnable();
                TIMER1_SetLowPriority();
            }
            else{/*NOTHING*/}  
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInrerruptEnable();
    #endif
#endif
        /* Enable TIMER1 Module */
        TIMER1_MODULE_ENABLE();
                
        ret = E_OK;
    }
    return ret;
}

/**
 * @brief Deinitialize the Timer1 module 
 * @param _timer pointer of object that we can go to register from
 * @return Status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action
 */
std_ReturnType Timer1_DeInit(const timer1_t *_timer)
{
    std_ReturnType ret = E_NOT_OK;
    if(NULL == _timer)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* Disable TIMER1 Module */
        TIMER1_MODULE_DISABLE();
        #if TIMER1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        /* Disable TIMER1 Module Interrupt */
        TIMER1_InterruptDisable();
        #endif
        ret = E_OK;
    }
    return ret;
}

/**
 * @brief Write value in timer1 register 
 * @param _timer pointer of object that we can go to register from
 * @param _Value The value that will be writen 
 * @return Status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action
 */
std_ReturnType Timer1_Write_Value(const timer1_t *_timer, uint16 _Value)
{
    std_ReturnType ret = E_NOT_OK;
    if(NULL == _timer)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* Set the preload value*/
        TMR1H = (_Value) >> 8;
        TMR1L = (uint8)(_Value);
        ret = E_OK;
    }
    return ret;
}

/**
 * @brief Read value from timer1 register
 * @param _timer pointer of object that we can go to register from
 * @param _Value The value that will be Read 
 * @return Status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action
 */
std_ReturnType Timer1_Read_Value(const timer1_t *_timer, uint16 *_Value)
{
    std_ReturnType ret = E_NOT_OK;
    uint8 l_tmr1l = ZERO_INIT, l_tmr1h = ZERO_INIT;
    if((NULL == _timer) || (NULL == _Value))
    {
        ret = E_NOT_OK;
    }
    else
    {
        l_tmr1l = TMR1L;
        l_tmr1h = TMR1H;
        *_Value = (uint16)((l_tmr1h << 8) + l_tmr1l);
        ret = E_OK;
    }
    return ret;
}

static inline void Timer1_Mode_select(const timer1_t *_timer)
{
    if(TIMER1_TIMER_MODE == _timer->timer1_mode)
    {
        TIMER1_TIMER_MODE_ENABLE();
    }
    else if(TIMER1_COUNTER_MODE == _timer->timer1_mode)
    {
        TIMER1_COUNTER_MODE_ENABLE();
        if(TIMER1_ASYNC_COUNTER_MODE == _timer->timer1_counter_mode)
        {
            TIMER1_ASYNC_COUNTER_MODE_ENABLE();
        }
        else if(TIMER1_SYNC_COUNTER_MODE == _timer->timer1_counter_mode)
        {
            TIMER1_SYNC_COUNTER_MODE_ENABLE();
        }
        else{/* NOTHING */}
    }
    else{/* NOTHING */}
}

/**
 * Call back function
 */
void TIMER1_ISR(void)
{
    TIMER1_InterruptflagClear();
    TMR1H = (timer1_preload) >> 8;
    TMR1L = (uint8)(timer1_preload);
    if(TIMER1_InterruptHandler)
    {
        TIMER1_InterruptHandler();
    }
}

