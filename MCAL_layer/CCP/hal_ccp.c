/* 
 * File:   hal_ccp1.c
 * Author: OKTA
 *
 * Created on January 23, 2024, 8:07 PM
 */

#include "hal_ccp.h"

static void CCP_Interrupt_Config(const ccp_t *ccp_obj);
static void CCP_Mode_Timer_Select(const ccp_t *ccp_obj);
static void CCP_PWM_Mode_config(const ccp_t *ccp_obj);
static std_ReturnType CCP_Capture_Mode_Config(const ccp_t *ccp_obj);
static std_ReturnType CCP_Compare_Mode_Config(const ccp_t *ccp_obj);

#if CCP1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
static InterruptHandler CCP1_InterruptHandler = NULL;
#endif

#if CCP2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
static InterruptHandler CCP2_InterruptHandler = NULL;
#endif


/**
 * @brief Initialize the CCP1 module 
 * @param ccp_obj pointer of object that we can go to register from
 * @return Status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action
 */
std_ReturnType CCP_Init(const ccp_t *ccp_obj)
{
    std_ReturnType ret = E_NOT_OK;
        if(NULL == ccp_obj)
        {
            ret = E_NOT_OK;
        }
        else
        {
            if(CCP1_INST == ccp_obj->ccp_inst)
            {
                /* Disable the ccp1 module */
                CCP1_SET_MODE(CCP_MODULE_DISABLE);
            }
            else if(CCP2_INST == ccp_obj->ccp_inst)
            {
                /* Disable the ccp2 module */
                CCP2_SET_MODE(CCP_MODULE_DISABLE);
            }
            else{ /* NOTHING */}

            /* ccp module capture mode initialization */
            if(CCP_CAPTURE_MODE_SELECT == ccp_obj->ccp_mode)
            {
                ret = CCP_Capture_Mode_Config(ccp_obj);
            }
            /* ccp module compare mode initialization */
            else if(CCP_COMPARE_MODE_SELECT == ccp_obj->ccp_mode)
            {
                ret = CCP_Compare_Mode_Config(ccp_obj); 
            }
#if (CCP1_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE_SELECTED) || (CCP2_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE_SELECTED)
            /* ccp1 module pwm mode initialization */
            else if(CCP_PWM_MODE_SELECT == ccp_obj->ccp_mode)
            { 
                CCP_PWM_Mode_config(ccp_obj);             
            }
            else{/* NOTHING */}
#endif        
            /* Pin configurations */
            ret = gpio_pin_initialize(&(ccp_obj->ccp_pin));
            
            /* Interrupt configuration */
            CCP_Interrupt_Config(ccp_obj);                 

            ret = E_OK;
        }
        return ret;
}

/**
 * @brief Initialize the CCP module
 * @param ccp_objpointer of object that we can go to register from
 * @return Status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action
 */
std_ReturnType CCP_DeInit(const ccp_t *ccp_obj)
{
    std_ReturnType ret = E_NOT_OK;
        if(NULL == ccp_obj)
        {
            ret = E_NOT_OK;
        }
        else
        {
            
            if(CCP1_INST == ccp_obj->ccp_inst)
            {
                /* Disable the ccp1 module */
                CCP1_SET_MODE(CCP_MODULE_DISABLE);
                /* Interrupt of ccp1 configuration */
                #if CCP1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
                CCP1_InterruptDisable();    /* Disable interrupt  */
                #endif
            }
            else if(CCP2_INST == ccp_obj->ccp_inst)
            {
                /* Disable the ccp2 module */
                CCP2_SET_MODE(CCP_MODULE_DISABLE);
                /* Interrupt of ccp2 configuration */
                #if CCP2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
                CCP2_InterruptDisable();    /* Disable interrupt  */
                #endif
            }
            else{ /* NOTHING */}

            ret = E_OK;
        }
        return ret;
}



#if (CCP1_CFG_SELECTED_MODE == CCP_CFG_CAPTURE_MODE_SELECTED) || (CCP2_CFG_SELECTED_MODE == CCP_CFG_CAPTURE_MODE_SELECTED)
/**
 * @brief to check that the capture done or not 
 * @param _capture_Status
 * @return Status of the function
 *          CCP_CAPTURE_READY     : The function done successfully
 *          CCP_CAPTURE_NOT_READY : The function has issue to perform this action
 */
   std_ReturnType CCP_IsCapturedDataReady(const ccp_t *ccp_obj, uint8 *_capture_Status)
   {
       std_ReturnType ret = E_NOT_OK;
        if(NULL == _capture_Status)
        {
            ret = E_NOT_OK;
        }
        else
        {
            if(CCP1_INST == ccp_obj->ccp_inst)
            {
                /* Check that the capture ready or not */
                if(CCP_CAPTURE_READY == PIR1bits.CCP1IF)
                {
                    /* If ready return Ready */
                    *_capture_Status = CCP_CAPTURE_READY;
                    /* Then clear the flag */
                    CCP1_InterruptflagClear();
                }
                else
                {
                     *_capture_Status = CCP_CAPTURE_NOT_READY; 
                }
            }
            else if(CCP2_INST == ccp_obj->ccp_inst)
            {
                /* Check that the capture ready or not */
                if(CCP_CAPTURE_READY == PIR2bits.CCP2IF)
                {
                    /* If ready return Ready */
                    *_capture_Status = CCP_CAPTURE_READY;
                    /* Then clear the flag */
                    CCP2_InterruptflagClear();
                }
                else
                {
                     *_capture_Status = CCP_CAPTURE_NOT_READY; 
                }
            }
            else{ /* NOTHING */}
            
            ret = E_OK;
        }
        return ret;
   }

/**
 * @brief to get the value from ccp1 
 * @param _capture_Value To get the value that i need to read it
 * @return Status of the function
 *          CCP_CAPTURE_READY     : The function done successfully
 *          CCP_CAPTURE_NOT_READY : The function has issue to perform this action
 */
   std_ReturnType CCP_Captured_Mode_Read_Value(const ccp_t *ccp_obj, uint16 *_capture_Value)
   {
        std_ReturnType ret = E_NOT_OK;
        CCP_REG_T Capture_temp_value = {.ccpr_low = 0, .ccpr_high = 0};
        if(NULL == _capture_Value)
        {
            ret = E_NOT_OK;
        }
        else
        {
            if(CCP1_INST == ccp_obj->ccp_inst)
            {
                Capture_temp_value.ccpr_low = CCPR1L;
                Capture_temp_value.ccpr_high = CCPR1H;
            }
            else if(CCP2_INST == ccp_obj->ccp_inst)
            {
                Capture_temp_value.ccpr_low = CCPR2L;
                Capture_temp_value.ccpr_high = CCPR2H;
            }
            else{ /* NOTHING */}
            
            *_capture_Value = Capture_temp_value.ccpr_16bit;

            ret = E_OK;
        }
        return ret;
   }
#endif

#if (CCP1_CFG_SELECTED_MODE == CCP_CFG_COMPARE_MODE_SELECTED) || (CCP2_CFG_SELECTED_MODE == CCP_CFG_COMPARE_MODE_SELECTED)
   /**
 * @brief to check that the compare complete or not 
 * @param _compare_Status
 * @return Status of the function
 *          CCP_COMPARE_READY     : The function done successfully
 *          CCP_COMPARE_NOT_READY : The function has issue to perform this action
 */
   std_ReturnType CCP_IscompareComplete(const ccp_t *ccp_obj, uint8 *_compare_Status)
   {
       std_ReturnType ret = E_NOT_OK;
        if(NULL == _compare_Status)
        {
            ret = E_NOT_OK;
        }
        else
        {
            if(CCP1_INST == ccp_obj->ccp_inst)
            {
                /* Check that the compare complete or not */
                if(CCP_COMPARE_READY == PIR1bits.CCP1IF)
                {
                    /* If ready return Ready */
                    *_compare_Status = CCP_COMPARE_READY;
                    /* Then clear the flag */
                    CCP1_InterruptflagClear();
                }
                else
                {
                    *_compare_Status = CCP_COMPARE_NOT_READY; 
                }  
            }
            else if(CCP2_INST == ccp_obj->ccp_inst)
            {
                /* Check that the compare complete or not */
                if(CCP_COMPARE_READY == PIR2bits.CCP2IF)
                {
                    /* If ready return Ready */
                    *_compare_Status = CCP_COMPARE_READY;
                    /* Then clear the flag */
                    CCP2_InterruptflagClear();
                }
                else
                {
                    *_compare_Status = CCP_COMPARE_NOT_READY; 
                }
            }
            else{ /* NOTHING */}
            ret = E_OK;  
        }
        return ret;
   }

/**
 * @brief to get the value from ccp1 
 * @param _compare_Value To get the value that i need to read it
 * @return Status of the function
 *          CCP_COMPARE_READY     : The function done successfully
 *          CCP_COMPARE_NOT_READY : The function has issue to perform this action
 */
   std_ReturnType CCP_compare_Mode_Set_Value(const ccp_t *ccp_obj, uint16 _compare_Value)
   {
       std_ReturnType ret = E_NOT_OK;
       CCP_REG_T Compare_temp_value = {.ccpr_low = 0, .ccpr_high = 0};
       if(NULL == ccp_obj)
        {
            ret = E_NOT_OK;
        }
        else
        {
           /* Set the value */
            Compare_temp_value.ccpr_16bit = _compare_Value;
            if(CCP1_INST == ccp_obj->ccp_inst)
            {
                /* Set the low register */
                CCPR1L = Compare_temp_value.ccpr_low;
                /* Set the high register */
                CCPR1H = Compare_temp_value.ccpr_high;
            }
            else if(CCP2_INST == ccp_obj->ccp_inst)
            {
                /* Set the low register */
                CCPR2L = Compare_temp_value.ccpr_low;
                /* Set the high register */
                CCPR2H = Compare_temp_value.ccpr_high;
            }
            else{ /* NOTHING */}
            ret = E_OK;
        }
       return ret;
   }
#endif

#if (CCP1_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE_SELECTED) || (CCP2_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE_SELECTED)
   
/**
 * @brief To set the duty cycle 
 * @param _duty the value
 * @return Status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action
 */
   std_ReturnType CCP_PWM_Set_Duty(const ccp_t *ccp_obj, const uint8 _duty)
   {
       std_ReturnType ret = E_NOT_OK;
       uint16 l_duty_temp = 0;

       if(NULL == ccp_obj)
        {
            ret = E_NOT_OK;
        }
        else
        {
           /* Get the duty value */
           l_duty_temp = (uint16)((float)4 * ((float)PR2 + 1.0) * ((float)_duty / 100.0));
         
           if(CCP1_INST == ccp_obj->ccp_inst)
           {
               /* Set first two bits */
               CCP1CONbits.DC1B = (uint8)(l_duty_temp & 0X0003);
       
                /* Write the value in 10bits */
                CCPR1L = (uint8)(l_duty_temp >> 2);
           }
           else if(CCP2_INST == ccp_obj->ccp_inst)
           {
               /* Set first two bits */
                CCP2CONbits.DC2B = (uint8)(l_duty_temp & 0X0003);
       
                /* Write the value in 10bits */
                 CCPR2L = (uint8)(l_duty_temp >> 2);
           }
           else{ /* NOTHING */}
           ret = E_OK;
        }

       return ret;
   }
 
/**
 * @brief To start the pwm mode ccp1 and ccp2
 * @return Status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action
 */   
   std_ReturnType CCP_PWM_Start(const ccp_t *ccp_obj)
   {
       std_ReturnType ret = E_NOT_OK;
       if(NULL == ccp_obj)
        {
            ret = E_NOT_OK;
        }
        else
        {
           if(CCP1_INST == ccp_obj->ccp_inst)
           {
               /* Start the pwm mode */
               CCP1CONbits.CCP1M = CCP_PWM_MODE;
           }
           else if(CCP2_INST == ccp_obj->ccp_inst)
           {
               /* Start the pwm mode */
               CCP2CONbits.CCP2M = CCP_PWM_MODE;
           }
           else{ /* NOTHING */}
           ret = E_OK;
        }
 
       return ret;
   }

/**
 * @brief To stop the pwm mode for ccp1 and ccp2
 * @return Status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action
 */   
   std_ReturnType CPP_PWM_Stop(const ccp_t *ccp_obj)
   {
       std_ReturnType ret = E_NOT_OK;
       if(NULL == ccp_obj)
        {
            ret = E_NOT_OK;
        }
        else
        {
           if(CCP1_INST == ccp_obj->ccp_inst)
           {
               /* Stop the CCP1 module */
               CCP1CONbits.CCP1M = CCP_MODULE_DISABLE;
           }
           else if(CCP2_INST == ccp_obj->ccp_inst)
           {
               /* Stop the CCP2 module */
               CCP2CONbits.CCP2M = CCP_MODULE_DISABLE;
           }
           else{ /* NOTHING */}
           ret = E_OK;
        }

       return ret;
   }
#endif
   
/**
 * Call back function
 */
void CCP1_ISR(void)
{
    CCP1_InterruptflagClear();
    if(CCP1_InterruptHandler)
    {
        CCP1_InterruptHandler();
    }
    else{ /* NOTHING */}
}

/**
 * Call back function
 */
void CCP2_ISR(void)
{
    CCP2_InterruptflagClear();
    if(CCP2_InterruptHandler)
    {
        CCP2_InterruptHandler();
    }
    else{ /* NOTHING */}
}

#if (CCP1_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE_SELECTED) || (CCP2_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE_SELECTED)

static void CCP_PWM_Mode_config(const ccp_t *ccp_obj)
{
    /* PWM Frequency initialization */
    PR2 = (uint8)(((float)_XTAL_FREQ / ((float)ccp_obj->PWM_Frequency * 4.0 * (float)ccp_obj->timer2_prescaler_value * 
                    (float)ccp_obj->timer2_postscaler_value)) - 1);
    if(CCP1_INST == ccp_obj->ccp_inst)
    {
        if(CCP_PWM_MODE == ccp_obj->ccp_mode_variant)
        {
            CCP1_SET_MODE(CCP_PWM_MODE);
        }
         else{/* NOTHING */}
    }
    else if(CCP2_INST == ccp_obj->ccp_inst)
    {
        if(CCP_PWM_MODE == ccp_obj->ccp_mode_variant)
        {
            CCP2_SET_MODE(CCP_PWM_MODE);
        }
            else{/* NOTHING */}
    }
    else{ /* NOTHING */}
}
#endif


static void CCP_Interrupt_Config(const ccp_t *ccp_obj)
{
    /*
    // this is the same of doublicate the code 
    #if (CCP1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE) || (CCP2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE) 
            
        if(CCP1_INST == ccp_obj->ccp_inst)
        {   
            CCP1_InterruptEnable();                 // Enable interrupt  
            CCP1_InterruptflagClear();              // Clear interrupt flag 
            CCP1_InterruptHandler = ccp_obj->CCP1_InterruptHandler;
        }
        else if(CCP2_INST == ccp_obj->ccp_inst)
        {
            CCP2_InterruptEnable();                 // Enable interrupt  
            CCP2_InterruptflagClear();              // Clear interrupt flag *
            CCP2_InterruptHandler = ccp_obj->CCP2_InterruptHandler;
        }
        else{  }    

    // Interrupt priority configurations        
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 
        INTERRUPT_PriotrityLevelsEnable();    
        if(CCP1_INST == ccp_obj->ccp_inst)
        {
            if(INTERRUPT_HIGH_PRIORITY == ccp_obj->CCP1_priority)
            {
                INTERRUPT_GlobalInterruptHighEnable();
                CCP1_SetHighPriority();
            }
            else if(INTERRUPT_LOW_PRIORITY == ccp_obj->CCP1_priority)
            {
                INTERRUPT_GlobalInterruptLowEnable();
                CCP1_SetLowPriority();
            }
            else{} 
        }
        else if(CCP2_INST == ccp_obj->ccp_inst)
        {
            if(INTERRUPT_HIGH_PRIORITY == ccp_obj->CCP2_priority)
            {
                INTERRUPT_GlobalInterruptHighEnable();
                CCP2_SetHighPriority();
            }
            else if(INTERRUPT_LOW_PRIORITY == ccp_obj->CCP2_priority)
            {
                INTERRUPT_GlobalInterruptLowEnable();
                CCP2_SetLowPriority();
            }
            else{}
        }
        else{ }
       
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInrerruptEnable();
    #endif
#endif

*/        
        
#if (CCP1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE) 
        CCP1_InterruptEnable();                 /* Enable interrupt  */
        CCP1_InterruptflagClear();              /* Clear interrupt flag */
        CCP1_InterruptHandler = ccp_obj->CCP1_InterruptHandler;
/* Interrupt priority configurations */       
    #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 
        INTERRUPT_PriotrityLevelsEnable();
        if(INTERRUPT_HIGH_PRIORITY == ccp_obj->CCP1_priority)
        {
            INTERRUPT_GlobalInterruptHighEnable();
            CCP1_SetHighPriority();
        }
        else if(INTERRUPT_LOW_PRIORITY == ccp_obj->CCP1_priority)
        {
            INTERRUPT_GlobalInterruptLowEnable();
            CCP1_SetLowPriority();
        }
        else{/*NOTHING*/}  
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInrerruptEnable();
    #endif
#endif

#if (CCP2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE) 
        CCP2_InterruptEnable();                 /* Enable interrupt  */
        CCP2_InterruptflagClear();              /* Clear interrupt flag */
        CCP2_InterruptHandler = ccp_obj->CCP2_InterruptHandler;
/* Interrupt priority configurations */       
    #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 
        INTERRUPT_PriotrityLevelsEnable();
        if(INTERRUPT_HIGH_PRIORITY == ccp_obj->CCP2_priority)
        {
            INTERRUPT_GlobalInterruptHighEnable();
            CCP2_SetHighPriority();
        }
        else if(INTERRUPT_LOW_PRIORITY == ccp_obj->CCP2_priority)
        {
            INTERRUPT_GlobalInterruptLowEnable();
            CCP2_SetLowPriority();
        }
        else{/*NOTHING*/}  
    #else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInrerruptEnable();
    #endif
#endif
}

static void CCP_Mode_Timer_Select(const ccp_t *ccp_obj)
{
    if(CCP1_CCP2_TIMER3 == ccp_obj->ccp_Capture_timer)
    {
        /* Timer3 is the capture/compare clock source for the CCP modules */
        T3CONbits.T3CCP1 = 0; 
        T3CONbits.T3CCP2 = 1;
    }
    else if(CCP1_TIMER1_CCP2_TIEMR3 == ccp_obj->ccp_Capture_timer)
    {
        /* Timer3 is the capture/compare clock source for CCP2 */
        /* Timer1 is the capture/compare clock source for CCP1 */
        T3CONbits.T3CCP1 = 1;
        T3CONbits.T3CCP2 = 0;
    }
    else if(CCP1_CCP2_TIMER1 == ccp_obj->ccp_Capture_timer)
    {
        /* Timer1 is the capture/compare clock source for the CCP modules */
        T3CONbits.T3CCP1 = 0;
        T3CONbits.T3CCP2 = 0;
    }
    else{ /* Nothing */ }
              
        
}

static std_ReturnType CCP_Capture_Mode_Config(const ccp_t *ccp_obj)
{
    std_ReturnType ret = E_OK;
    
    if(CCP1_INST == ccp_obj->ccp_inst)
    {
        /* CCP1 Module Capture variants Mode Initialization */
        switch(ccp_obj->ccp_mode_variant)
        {
            case CCP_CAPTURE_MODE_1_FALLING_EDGE : CCP1_SET_MODE(CCP_CAPTURE_MODE_1_FALLING_EDGE); break;
            case CCP_CAPTURE_MODE_1_RISING_EDGE  : CCP1_SET_MODE(CCP_CAPTURE_MODE_1_RISING_EDGE);  break;
            case CCP_CAPTURE_MODE_4_RISING_EDGE  : CCP1_SET_MODE(CCP_CAPTURE_MODE_4_RISING_EDGE);  break;
            case CCP_CAPTURE_MODE_16_RISING_EDGE : CCP1_SET_MODE(CCP_CAPTURE_MODE_16_RISING_EDGE); break;
            default : ret = E_NOT_OK; /* Not supported variant */
        }
    }
    else if(CCP2_INST == ccp_obj->ccp_inst)
    {
        /* CCP2 Module Capture variants Mode Initialization */
        switch(ccp_obj->ccp_mode_variant)
        {
            case CCP_CAPTURE_MODE_1_FALLING_EDGE : CCP2_SET_MODE(CCP_CAPTURE_MODE_1_FALLING_EDGE); break;
            case CCP_CAPTURE_MODE_1_RISING_EDGE  : CCP2_SET_MODE(CCP_CAPTURE_MODE_1_RISING_EDGE);  break;
            case CCP_CAPTURE_MODE_4_RISING_EDGE  : CCP2_SET_MODE(CCP_CAPTURE_MODE_4_RISING_EDGE);  break;
            case CCP_CAPTURE_MODE_16_RISING_EDGE : CCP2_SET_MODE(CCP_CAPTURE_MODE_16_RISING_EDGE); break;
            default : ret = E_NOT_OK; /* Not supported variant */
        }
    }
    else{ /* Nothing */ }
    
    /* Select Timer with ccp1 and ccp2 */
    CCP_Mode_Timer_Select(ccp_obj);
    
    return ret;
}

static std_ReturnType CCP_Compare_Mode_Config(const ccp_t *ccp_obj)
{
    std_ReturnType ret = E_OK;
    
    if(CCP1_INST == ccp_obj->ccp_inst)
    {
        /* CCP1 Module Capture variants Mode Initialization */
        switch(ccp_obj->ccp_mode_variant)
        {
            case CCP_COMPARE_MODE_SET_PIN_LOW      : CCP1_SET_MODE(CCP_COMPARE_MODE_SET_PIN_LOW);      break;
            case CCP_COMPARE_MODE_SET_PIN_HIGH     : CCP1_SET_MODE(CCP_COMPARE_MODE_SET_PIN_HIGH);     break;
            case CCP_COMPARE_MODE_TOGGLE_ON_MATCH  : CCP1_SET_MODE(CCP_COMPARE_MODE_TOGGLE_ON_MATCH);  break;
            case CCP_COMPARE_MODE_GEN_SW_INTERRUPT : CCP1_SET_MODE(CCP_COMPARE_MODE_GEN_SW_INTERRUPT); break;
            case CCP_COMPARE_MODE_GEN_EVENT        : CCP1_SET_MODE(CCP_COMPARE_MODE_GEN_EVENT);        break;
            default: ret = E_NOT_OK;/* NOT support variant */
        } 
    }
    else if(CCP2_INST == ccp_obj->ccp_inst)
    {
        /* CCP2 Module Capture variants Mode Initialization */
        switch(ccp_obj->ccp_mode_variant)
        {
            case CCP_COMPARE_MODE_SET_PIN_LOW      : CCP2_SET_MODE(CCP_COMPARE_MODE_SET_PIN_LOW);      break;
            case CCP_COMPARE_MODE_SET_PIN_HIGH     : CCP2_SET_MODE(CCP_COMPARE_MODE_SET_PIN_HIGH);     break;
            case CCP_COMPARE_MODE_TOGGLE_ON_MATCH  : CCP2_SET_MODE(CCP_COMPARE_MODE_TOGGLE_ON_MATCH);  break;
            case CCP_COMPARE_MODE_GEN_SW_INTERRUPT : CCP2_SET_MODE(CCP_COMPARE_MODE_GEN_SW_INTERRUPT); break;
            case CCP_COMPARE_MODE_GEN_EVENT        : CCP2_SET_MODE(CCP_COMPARE_MODE_GEN_EVENT);        break;
            default: ret = E_NOT_OK;/* NOT support variant */
        } 
    }
    else{ /* Nothing */ }
    
    /* Select Timer with ccp1 and ccp2 */
    CCP_Mode_Timer_Select(ccp_obj);
    
    return ret;
}