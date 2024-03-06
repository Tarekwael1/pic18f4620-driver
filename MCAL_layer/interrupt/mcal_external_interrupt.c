/* 
 * File:   mcal_external_interrupt.c
 * Author: OKTA
 *
 * Created on October 1, 2023, 9:46 AM
 */
#include "mcal_external_interrupt.h"
/*=========== Pointer to functions to hold the callback for INTx ======start===== */
static InterruptHandler INT0_InterruptHandler = NULL;
static InterruptHandler INT1_InterruptHandler = NULL;
static InterruptHandler INT2_InterruptHandler = NULL;
/*=========== Pointer to functions to hold the callback for INTx ======= end==== */

/*=========== Pointer to Helper functions to hold the callback for RBx ======start===== */


/* Pointer to Helper function to hold the callback for RBx */
static InterruptHandler RB4_InterruptHandler_HIGH = NULL;
static InterruptHandler RB4_InterruptHandler_LOW= NULL;
static InterruptHandler RB5_InterruptHandler_HIGH = NULL;
static InterruptHandler RB5_InterruptHandler_LOW= NULL;
static InterruptHandler RB6_InterruptHandler_HIGH = NULL;
static InterruptHandler RB6_InterruptHandler_LOW= NULL;
static InterruptHandler RB7_InterruptHandler_HIGH = NULL;
static InterruptHandler RB7_InterruptHandler_LOW= NULL;
/*=========== Pointer to Helper functions to hold the callback for RBx ======= end==== */


/*=========================== Helper Functions for INTx =============start================= */
static std_ReturnType Interrupt_INTx_Pin_Init(const interrupt_INTx_t *int_obj);
static std_ReturnType Interrupt_INTx_Edge_Init(const interrupt_INTx_t *int_obj);
static std_ReturnType Interrupt_INTx_Disable(const interrupt_INTx_t *int_obj);
static std_ReturnType Interrupt_INTx_Enable(const interrupt_INTx_t *int_obj);
static std_ReturnType Interrupt_INTx_Clear_Flag(const interrupt_INTx_t *int_obj);

static std_ReturnType INT0_SetInterruptHandler(void (*InterruptHandler)(void));
static std_ReturnType INT1_SetInterruptHandler(void (*InterruptHandler)(void));
static std_ReturnType INT2_SetInterruptHandler(void (*InterruptHandler)(void));
static std_ReturnType Interrupt_INTx_SetInterruptHandler(const interrupt_INTx_t *int_obj);
/*=========================== Helper Functions for INTx =============end================= */

/*=========================== Functions for RBx =============start================= */
static std_ReturnType Interrupt_RBx_Enable(const interrupt_RBx_t *int_obj);
static std_ReturnType Interrupt_RBx_Disable(const interrupt_RBx_t *int_obj);
static std_ReturnType Interrupt_RBx_Pin_Init(const interrupt_RBx_t *int_obj);
static std_ReturnType Interrupt_RBx_Clear_Flag(const interrupt_RBx_t *int_obj);
static std_ReturnType Interrupt_RBx_Callback(const interrupt_RBx_t *int_obj);
/*=========================== Helper Functions for RBx =============end================= */




/*=========================== Helper Functions for INTx =============start================= */
void INT0_ISR(void)
{
    /* The INT0 external interrupt occurred (must be cleared in software) */
    EXT_INT0_InterruptflagClear();
    /* Code */
    
    /* Callback function gets called every time this ISR executes */
    if(INT0_InterruptHandler){INT0_InterruptHandler();}
}

void INT1_ISR(void)
{
    /* The INT1 external interrupt occurred (must be cleared in software) */
    EXT_INT1_InterruptflagClear();
    /* Code */
    
    /* Callback function gets called every time this ISR executes */
    if(INT1_InterruptHandler){INT1_InterruptHandler();}
}

void INT2_ISR(void)
{
    /* The INT2 external interrupt occurred (must be cleared in software) */
    EXT_INT2_InterruptflagClear();
    /* Code */
    
    /* Callback function gets called every time this ISR executes */
    if(INT2_InterruptHandler){INT2_InterruptHandler();}
}

/*=========================== Helper Functions for INTx =============end================= */


/*===================== Helper Functions declaration for INTx =============start================= */
/**
 * @brief Initialization the INTx interrupt 
 * @param int_obj interrupt object
 * @return status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action 
 */
std_ReturnType Interrupt_INTx_Init(const interrupt_INTx_t *int_obj)
{
    std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* Disable the external interrupt */
        ret = Interrupt_INTx_Disable(int_obj);
        /* clear interrupt flag : external interrupt did not occur */
        ret |= Interrupt_INTx_Clear_Flag(int_obj);
        /* configure external interrupt edge */
        ret |= Interrupt_INTx_Edge_Init(int_obj);

        
        //#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
       /* configure external interrupt priority */
        //ret |= Interrupt_INTx_Priority_Init(int_obj); #endif  we can remove this because we make enable in  Interrupt_INTx_Enable
   
        
        
        /* configure external interrupt I/O pin */
        ret |= Interrupt_INTx_Pin_Init(int_obj);
        /* configure default interrupt callback */
        ret |= Interrupt_INTx_SetInterruptHandler(int_obj);
        /* Enable the external interrupt */ 
        ret |= Interrupt_INTx_Enable(int_obj);
    } 
    return ret;
}

/**
 * @brief DeInitialization the INTx interrupt 
 * @param int_obj interrupt object
 * @return status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action 
 */
std_ReturnType Interrupt_INTx_DeInit(const interrupt_INTx_t *int_obj)
{
    std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = Interrupt_INTx_Disable(int_obj);
    } 
    return ret;
}


/* ========****=== HELPER FUNCTION FOR INTx ====== start =====*/
/**
 * @brief Helper function to enable the interrupt
 * @param int_obj interrupt object
 * @return status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action 
 */
static std_ReturnType Interrupt_INTx_Enable(const interrupt_INTx_t *int_obj)
{
    std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch(int_obj->source)
        {
            case INTERRUPT_EXTERNAL_INT0:
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE                
                INTERRUPT_GlobalInterruptHighEnable();
#else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInrerruptEnable();
#endif                
                EXT_INT0_InterruptEnable();
                ret = E_OK;
                break;
            case INTERRUPT_EXTERNAL_INT1:
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE   
                INTERRUPT_PriotrityLevelsEnable();
                if(INTERRUPT_LOW_PRIORITY == int_obj->priority) 
                {
                    INTERRUPT_GlobalInterruptLowEnable();
                }
                else if (INTERRUPT_HIGH_PRIORITY == int_obj->priority) 
                {
                    INTERRUPT_GlobalInterruptHighEnable();
                }
                else{/*NITHING*/}  
#else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInrerruptEnable();
#endif 
                EXT_INT1_InterruptEnable(); 
                ret = E_OK; 
                break;
            case INTERRUPT_EXTERNAL_INT2:
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE   
                INTERRUPT_PriotrityLevelsEnable();
                if(INTERRUPT_LOW_PRIORITY == int_obj->priority) 
                {
                    INTERRUPT_GlobalInterruptLowEnable();
                }
                else if (INTERRUPT_HIGH_PRIORITY == int_obj->priority) 
                {
                    INTERRUPT_GlobalInterruptHighEnable();
                }
                else{/*NITHING*/}  
#else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInrerruptEnable();
#endif 
                EXT_INT2_InterruptEnable(); 
                ret = E_OK; 
                break;
            default : ret = E_NOT_OK;
        }
    } 
    return ret;
}

/**
 * @brief Helper function to disable the interrupt
 * @param int_obj interrupt object
 * @return status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action 
 */
static std_ReturnType Interrupt_INTx_Disable(const interrupt_INTx_t *int_obj)
{
    std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch(int_obj->source)
        {
            case INTERRUPT_EXTERNAL_INT0:
                EXT_INT0_InterruptDisable();
                ret = E_OK;
                break;
            case INTERRUPT_EXTERNAL_INT1:
                EXT_INT1_InterruptDisable(); 
                ret = E_OK; 
                break;
            case INTERRUPT_EXTERNAL_INT2:
                EXT_INT2_InterruptDisable(); 
                ret = E_OK; 
                break;
            default : ret = E_NOT_OK;
        }
    } 
    return ret;
}

/*

#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
static std_ReturnType Interrupt_INTx_Priority_Init(const interrupt_INTx_t *int_obj)
{
    std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch(int_obj->source)
        {
            case INTERRUPT_EXTERNAL_INT1:
                if(INTERRUPT_LOW_PRIORITY == int_obj->priority) 
                {
                    EXT_INT1_SetLowPriority();
                }
                else if (INTERRUPT_HIGH_PRIORITY == int_obj->priority) 
                {
                    EXT_INT1_SetHighPriority();
                }
                else{}
                ret = E_OK;
                break;
            case INTERRUPT_EXTERNAL_INT2:
                if(INTERRUPT_LOW_PRIORITY == int_obj->priority) 
                {
                    EXT_INT2_SetLowPriority();
                }
                else if (INTERRUPT_HIGH_PRIORITY == int_obj->priority) 
                {
                    EXT_INT2_SetHighPriority();
                }
                else{} 
                ret = E_OK; 
                break;
            default : ret = E_NOT_OK;
        }
    } 
    return ret;
}
#endif
*/

/**
 * @brief Helper function to set the edge of the interrupt
 * @param int_obj interrupt object
 * @return status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action 
 */
static std_ReturnType Interrupt_INTx_Edge_Init(const interrupt_INTx_t *int_obj)
{
    std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch(int_obj->source)
        {
            case INTERRUPT_EXTERNAL_INT0:
                if(INTERRUPT_FALLING_EDGE == int_obj->edge){ EXT_INT0_FallingEdgeSet();}
                else if(INTERRUPT_RISING_EDGE == int_obj->edge){EXT_INT0_RisingEdgeSet();}
                else{/*NOTHUNG*/}
                ret = E_OK;
                break;
            case INTERRUPT_EXTERNAL_INT1:
                if(INTERRUPT_FALLING_EDGE == int_obj->edge){ EXT_INT1_FallingEdgeSet(); }
                else if(INTERRUPT_RISING_EDGE == int_obj->edge){ EXT_INT1_RisingEdgeSet(); }
                else{/*NOTHUNG*/} 
                ret = E_OK; 
                break;
            case INTERRUPT_EXTERNAL_INT2:
                if(INTERRUPT_FALLING_EDGE == int_obj->edge){ EXT_INT2_FallingEdgeSet(); }
                else if(INTERRUPT_RISING_EDGE == int_obj->edge){ EXT_INT2_RisingEdgeSet(); }
                else{/*NOTHUNG*/} 
                ret = E_OK; 
                break;
            default : ret = E_NOT_OK;
        }
    } 
    return ret;
}


/**
 * @brief Helper function to set pin of the interrupt
 * @param int_obj  interrupt object
 * @return status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action 
 */
static std_ReturnType Interrupt_INTx_Pin_Init(const interrupt_INTx_t *int_obj)
{
    std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_direction_initialize(&(int_obj->mcu_pin));
    } 
    return ret;
}

/**
 * @brief Helper function to clear flag of the interrupt
 * @param int_obj  interrupt object
 * @return status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action 
 */
static std_ReturnType Interrupt_INTx_Clear_Flag(const interrupt_INTx_t *int_obj)
{
    std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch(int_obj->source)
        {
            case INTERRUPT_EXTERNAL_INT0:
                EXT_INT0_InterruptflagClear();
                ret = E_OK;
                break;
            case INTERRUPT_EXTERNAL_INT1:
                EXT_INT1_InterruptflagClear(); 
                ret = E_OK; 
                break;
            case INTERRUPT_EXTERNAL_INT2:
                EXT_INT2_InterruptflagClear(); 
                ret = E_OK; 
                break;
            default : ret = E_NOT_OK;
        }
    } 
    return ret;
}


static std_ReturnType INT0_SetInterruptHandler(void (*InterruptHandler)(void))
{
   std_ReturnType ret = E_NOT_OK;
    if(NULL == InterruptHandler)
    {
        ret = E_NOT_OK;
    }
    else
    {
        INT0_InterruptHandler = InterruptHandler;
        ret = E_OK;
    } 
    return ret; 
}

static std_ReturnType INT1_SetInterruptHandler(void (*InterruptHandler)(void))
{
    std_ReturnType ret = E_NOT_OK;
    if(NULL == InterruptHandler)
    {
        ret = E_NOT_OK;
    }
    else
    {
        INT1_InterruptHandler = InterruptHandler;
        ret = E_OK;
    } 
    return ret; 
}

static std_ReturnType INT2_SetInterruptHandler(void (*InterruptHandler)(void))
{
    std_ReturnType ret = E_NOT_OK;
    if(NULL == InterruptHandler)
    {
        ret = E_NOT_OK;
    }
    else
    {
        INT2_InterruptHandler = InterruptHandler;
        ret = E_OK;
    } 
    return ret; 
}

static std_ReturnType Interrupt_INTx_SetInterruptHandler(const interrupt_INTx_t *int_obj)
{
    std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch(int_obj->source)
        {
            case INTERRUPT_EXTERNAL_INT0:
                /* set default interrupt handler for INT0 External interrupt : Application ISR*/
                ret = INT0_SetInterruptHandler(int_obj->EXT_InterruptHandler);
                break;
            case INTERRUPT_EXTERNAL_INT1:
                /* set default interrupt handler for INT1 External interrupt : Application ISR*/
                ret = INT1_SetInterruptHandler(int_obj->EXT_InterruptHandler); 
                break;
            case INTERRUPT_EXTERNAL_INT2:
                /* set default interrupt handler for INT2 External interrupt : Application ISR*/
                ret = INT2_SetInterruptHandler(int_obj->EXT_InterruptHandler); 
                break;
            default : ret = E_NOT_OK;
        }
    } 
    return ret;
}


/* ========****=== HELPER FUNCTION FOR INTx ====== end =====*/


/*===================== Helper Functions declaration for INTx =============end================= */

/*===================== Helper Functions declaration for INTx ============= start ================= */

/**
 * @brief Initialization the RBx interrupt 
 * @param int_obj interrupt object
 * @return status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action 
 */
std_ReturnType Interrupt_RBx_Init(const interrupt_RBx_t *int_obj)
{
    std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* This routine clears interrupt disable for the external interrupt , RBx */
        ret = Interrupt_RBx_Disable(int_obj);
        /* This routine clears the interrupt flag for external interrupt , RBx */
        ret |= Interrupt_RBx_Clear_Flag(int_obj);
        /* set the interrupt priority */
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
        /* This macro will enable priority levels on interrupts */
        INTERRUPT_PriotrityLevelsEnable();
        if(INTERRUPT_LOW_PRIORITY == int_obj->priority) 
        {
            /*  This macro will enable low priority global interrupts  */
            INTERRUPT_GlobalInterruptLowEnable();
             /* This routine set RBx the external interrupt priority to be Low   */
            EXT_RBx_Priority_Low();
        }
        else if (INTERRUPT_HIGH_PRIORITY == int_obj->priority) 
        {
            /*  This macro will enable high priority global interrupts  */
             INTERRUPT_GlobalInterruptHighEnable();
             /* This routine set RBx the external interrupt priority to be High   */
             EXT_RBx_Priority_High();
        }
        else{/*NITHING*/}  
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInrerruptEnable();
#endif
        /* Initialize RBx pins to be input */
        ret |= Interrupt_RBx_Pin_Init(int_obj);
        /* Initialize the call back functions */
        ret |= Interrupt_RBx_Callback(int_obj);
        /* This routine sets interrupt enable for the external interrupt , RBx */
        ret |= Interrupt_RBx_Enable(int_obj);
    } 
    return ret;
}

/**
 * @brief DeInitialization the RBx interrupt
 * @param int_obj interrupt object
 * @return status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action 
 */
std_ReturnType Interrupt_RBx_DeInit(const interrupt_RBx_t *int_obj)
{
    std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = Interrupt_RBx_Disable(int_obj);
    } 
    return ret;
}

/**
 * @brief Helper function to enable the interrupt 
 * @param int_obj interrupt object
 * @return status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action 
 */


static std_ReturnType Interrupt_RBx_Enable(const interrupt_RBx_t *int_obj)
{
    std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        EXT_RBx_InterruptEnable();
    }
    return ret;   
}

static std_ReturnType Interrupt_RBx_Disable(const interrupt_RBx_t *int_obj)
{
     std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* This routine clears interrupt disable for the external interrupt , RBx */
        EXT_RBx_InterruptDisable();
        /* This routine clears the interrupt flag for external interrupt , RBx */
        EXT_RBx_InterruptFlagClear();
    }
    return ret;
}

static std_ReturnType Interrupt_RBx_Pin_Init(const interrupt_RBx_t *int_obj)
{
    std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_direction_initialize(&(int_obj->mcu_pin));
    } 
    return ret;
}

static std_ReturnType Interrupt_RBx_Clear_Flag(const interrupt_RBx_t *int_obj)
{
    std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        EXT_RBx_InterruptFlagClear();
    } 
    return ret;
}

static std_ReturnType Interrupt_RBx_Callback(const interrupt_RBx_t *int_obj)
{
    std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch(int_obj->mcu_pin.pin)
        {
            case GPIO_PIN4 :  
                RB4_InterruptHandler_HIGH = int_obj->EXT_InterruptHandler_HIGH;
                RB4_InterruptHandler_LOW = int_obj->EXT_InterruptHandler_LOW;
                ret = E_OK;
                break;
            case GPIO_PIN5 :  
                RB5_InterruptHandler_HIGH = int_obj->EXT_InterruptHandler_HIGH;
                RB5_InterruptHandler_LOW = int_obj->EXT_InterruptHandler_LOW;
                ret = E_OK;
                break;
            case GPIO_PIN6 :  
                RB6_InterruptHandler_HIGH = int_obj->EXT_InterruptHandler_HIGH;
                RB6_InterruptHandler_LOW = int_obj->EXT_InterruptHandler_LOW;
                ret = E_OK;
                break;
            case GPIO_PIN7 :  
                RB7_InterruptHandler_HIGH = int_obj->EXT_InterruptHandler_HIGH;
                RB7_InterruptHandler_LOW = int_obj->EXT_InterruptHandler_LOW;
                ret = E_OK;
                break;
            default :
                ret = E_NOT_OK;
        }
    } 
    return ret;
}
/*=========================== Helper Functions for RBx =============start================= */
/**
 * External interrupt RB4 MCAL Helper function 
 */
void RB4_ISR(uint8 RB4_Source)
{
    /* The INT2 external interrupt occurred (must be cleared in software) */
    EXT_RBx_InterruptFlagClear();
    /* Code */
    
    /* Callback function gets called every time this ISR executes */
    if(0 == RB4_Source)
    {
        if(RB4_InterruptHandler_HIGH){RB4_InterruptHandler_HIGH();} 
        else{/* NOTHING */}
    }
    else if(1 == RB4_Source)
    {
        if(RB4_InterruptHandler_LOW){RB4_InterruptHandler_LOW();} 
        else{/* NOTHING */}
    }
    else{/* NOTHING */}
}
/**
 * External interrupt RB5 MCAL Helper function 
 */
void RB5_ISR(uint8 RB5_Source)
{
    /* The INT2 external interrupt occurred (must be cleared in software) */
    EXT_RBx_InterruptFlagClear();
    /* Code */
    
    /* Callback function gets called every time this ISR executes */
    if(0 == RB5_Source)
    {
        if(RB5_InterruptHandler_HIGH){RB5_InterruptHandler_HIGH();} 
        else{/* NOTHING */}
    }
    else if(1 == RB5_Source)
    {
        if(RB5_InterruptHandler_LOW){RB5_InterruptHandler_LOW();} 
        else{/* NOTHING */}
    }
    else{/* NOTHING */}
}

void RB6_ISR(uint8 RB6_Source)
{
    /* The INT2 external interrupt occurred (must be cleared in software) */
    EXT_RBx_InterruptFlagClear();
    /* Code */
    
    /* Callback function gets called every time this ISR executes */
    if(0 == RB6_Source)
    {
        if(RB6_InterruptHandler_HIGH){RB6_InterruptHandler_HIGH();} 
        else{/* NOTHING */}
    }
    else if(1 == RB6_Source)
    {
        if(RB6_InterruptHandler_LOW){RB6_InterruptHandler_LOW();} 
        else{/* NOTHING */}
    }
    else{/* NOTHING */}
}

void RB7_ISR(uint8 RB7_Source)
{
    /* The INT2 external interrupt occurred (must be cleared in software) */
    EXT_RBx_InterruptFlagClear();
    /* Code */
    
    /* Callback function gets called every time this ISR executes */
    if(0 == RB7_Source)
    {
        if(RB7_InterruptHandler_HIGH){RB7_InterruptHandler_HIGH();} 
        else{/* NOTHING */}
    }
    else if(1 == RB7_Source)
    {
        if(RB7_InterruptHandler_LOW){RB7_InterruptHandler_LOW();} 
        else{/* NOTHING */}
    }
    else{/* NOTHING */}
}
/*=========================== Helper Functions for RBx =============end================= */


/*===================== Helper Functions declaration for RBx =============end================= */







