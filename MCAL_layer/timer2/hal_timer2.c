/* 
 * File:   hal_timer2.c
 * Author: OKTA
 *
 * Created on January 22, 2024, 4:38 PM
 */

#include "hal_timer2.h"

#if TIMER2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
static InterruptHandler TIMER2_InterruptHandler = NULL;
#endif

static uint8 timer2_preload = ZERO_INIT;

/**
 * @brief Initialize the Timer2 module 
 * @param _timer pointer of object that we can go to register from
 * @return Status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action
 */
std_ReturnType Timer2_Init(const timer2_t *_timer)
{
    std_ReturnType ret = E_NOT_OK;
    if(NULL == _timer)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* Disable TIMER2 Module */
        TIMER2_MODULE_DISABLE();
        /* Timer2 Prescaler Select bits */
        TIMER2_PRESCALER_SELECT(_timer->timer2_prescaler_value);
        /* Timer2 Postscaler Select bits */
        TIMER2_POSTSCALER_SELECT(_timer->timer2_postscaler_value);
        /* Set the preload value*/
        TMR2 = _timer->timer2_preload_value;
        timer2_preload = _timer->timer2_preload_value; 
/* Configure the interrupt */
#if TIMER2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE  
        TIMER2_InterruptEnable();
        TIMER2_InterruptflagClear();
        TIMER2_InterruptHandler = _timer->TIMER2_InterruptHandler;
/* Interrupt priority configurations */       
    #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 
            INTERRUPT_PriotrityLevelsEnable();
            if(INTERRUPT_HIGH_PRIORITY == _timer->priority)
            {
                INTERRUPT_GlobalInterruptHighEnable();
                TIMER2_SetHighPriority();
            }
            else if(INTERRUPT_LOW_PRIORITY == _timer->priority)
            {
                INTERRUPT_GlobalInterruptLowEnable();
                TIMER2_SetLowPriority();
            }
            else{/*NOTHING*/}  
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInrerruptEnable();
    #endif
#endif
        /* Enable TIMER2 Module */
        TIMER2_MODULE_ENABLE();
        ret = E_OK;
    }
    return ret; 
}

/**
 * @brief Deinitialize the Timer2 module 
 * @param _timer pointer of object that we can go to register from
 * @return Status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action
 */
std_ReturnType Timer2_DeInit(const timer2_t *_timer)
{
    std_ReturnType ret = E_NOT_OK;
    if(NULL == _timer)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* Disable TIMER2 Module */
        TIMER2_MODULE_DISABLE();
        #if TIMER2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        /* Disable TIMER2 Module Interrupt */
        TIMER2_InterruptDisable();
        #endif
        ret = E_OK;
    }
    return ret; 
}

/**
 * @brief Write value in timer2 register 
 * @param _timer pointer of object that we can go to register from
 * @param _Value The value that will be writen 
 * @return Status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action
 */
std_ReturnType Timer2_Write_Value(const timer2_t *_timer, uint8 _Value)
{
    std_ReturnType ret = E_NOT_OK;
    if(NULL == _timer)
    {
        ret = E_NOT_OK;
    }
    else
    {
        TMR2 = _Value;
        ret = E_OK;
    }
    return ret; 
}

/**
 * @brief Read value from timer2 register
 * @param _timer pointer of object that we can go to register from
 * @param _Value The value that will be Read 
 * @return Status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action
 */
std_ReturnType Timer2_Read_Value(const timer2_t *_timer, uint8 *_Value)
{
    std_ReturnType ret = E_NOT_OK;
    if((NULL == _timer) || (NULL == _Value))
    {
        ret = E_NOT_OK;
    }
    else
    {
        *_Value = TMR2;
        ret = E_OK;
    }
    return ret; 
}



/**
 * Call back function
 */
void TIMER2_ISR(void)
{
    TIMER2_InterruptflagClear();
    TMR2 = timer2_preload;
    if(TIMER2_InterruptHandler)
    {
        TIMER2_InterruptHandler();
    }
}
