/* 
 * File:   hal_adc.c
 * Author: OKTA
 *
 * Created on October 9, 2023, 9:46 AM
 */


#include "hal_adc.h"

#if ADC_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
static InterruptHandler ADC_InterruptHandler = NULL;
#endif



static inline void adc_input_channel_port_configure(adc_channel_select_t channel);
static inline void select_result_format(const adc_config_t *_adc);
static inline void configure_voltage_reference(const adc_config_t *_adc);

/**
 * @Summary Initialize the ADC 
 * @Description This routine initialize the ADC.
 *              This routine must be called before any other ADC routine is called. 
 *              This routine should called only once during system initialization.  
 * @param _adc Pointer to ADC Configuration 
 * @return status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action 
 */
std_ReturnType ADC_Init(const adc_config_t *_adc)
{
    std_ReturnType ret = E_NOT_OK;
    if(NULL == _adc)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* Disable the ADC */
        ADC_CONVERTER_DISABLE();
        /* Configure the acquisition time */
        ADCON2bits.ACQT = _adc->acquisition_time;
        /* Configure the conversion clock */
        ADCON2bits.ADCS = _adc->conversion_clock;
        /*Conversion the default channel */
        ADCON0bits.CHS = _adc->adc_channel;
        adc_input_channel_port_configure(_adc->adc_channel);
        /* Configure the interrupt */
#if ADC_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE 
        ADC_InterruptEnable();
        ADC_InterruptflagClear();
        ADC_InterruptHandler = _adc->ADC_InterruptHandler;    
    #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
            /* configure ADC interrupt priority */
            //INTERRUPT_PriotrityLevelsEnable();
            if(INTERRUPT_HIGH_PRIORITY == _adc->priority)
            {
                INTERRUPT_GlobalInterruptHighEnable();
                ADC_SetHighPriority();
            }
            else if(INTERRUPT_LOW_PRIORITY == _adc->priority)
            {
                INTERRUPT_GlobalInterruptLowEnable();
                ADC_SetLowPriority();
            }
            else{/*NOTHING*/}  
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInrerruptEnable();  
    #endif
#endif
        /* Configure the result format */
        select_result_format(_adc);
        /* Configure the voltage reference */
        configure_voltage_reference(_adc);
        /* Enable the ADC */
        ADC_CONVERTER_ENABLE();
        ret = E_OK;
    }
    return ret;
}

/**
 * @Summary De-Initialize the ADC
 * @param _adc Pointer to ADC Configuration 
 * @return status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action 
 */
std_ReturnType ADC_DeInit(const adc_config_t *_adc)
{
    std_ReturnType ret = E_NOT_OK;
    if(NULL == _adc)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* Disable the ADC */
        ADC_CONVERTER_DISABLE();
        /* Disable the interrupt */
        #if ADC_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        ADC_InterruptDisable();
        #endif
        ret = E_OK;
    }
    return ret;
}

/**
 * @Summary Allows selection of a channel for conversion.
 * @Description This routine used to select desired channel for conversion.
 * @preconditions  ADC_Init() function should have been called before calling this function
 * @param _adc Pointer to ADC Configuration 
 * @param channel Defines the channel available for conversion.
 * @return status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action 
 */
std_ReturnType ADC_selectChannel(const adc_config_t *_adc, adc_channel_select_t channel)
{
    std_ReturnType ret = E_NOT_OK;
    if(NULL == _adc)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /*Conversion the default channel */
        ADCON0bits.CHS = channel;
        adc_input_channel_port_configure(channel);
        ret = E_OK;
    }
    return ret;
}

/**
 * @Summary Starts the conversion 
 * @Description This routine used to start conversion of desired channel.
 * @preconditions  ADC_Init() function should have been called before calling this function 
 * @param _adc Pointer to ADC Configuration 
 * @return status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action 
 */
std_ReturnType ADC_StartConvesion (const adc_config_t *_adc)
{
    std_ReturnType ret = E_NOT_OK;
    if(NULL == _adc)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ADC_START_CONVERSION();
        ret = E_OK;
    }
    return ret;
}

/**
 * @Summary Returns when the conversion is completed otherwise false 
 * @Description This routine is used to determine if conversion is completed.
 *              When conversion is complete routine returns true, otherwise false 
 * @preconditions  ADC_Init() function should have been called before calling this function 
 *                 ADC_StartConvesion() should have been called before calling this function
 * @param _adc Pointer to ADC Configuration 
 * @param conversion_status The conversion status
 *          true  - If conversion is complete 
 *          false - If conversion not complete  
 * @return status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action 
 */
std_ReturnType ADC_IsConversionDone(const adc_config_t *_adc, uint8 *conversion_status)
{
    std_ReturnType ret = E_NOT_OK;
    if((NULL == _adc) || (NULL == conversion_status))
    {
        ret = E_NOT_OK;
    }
    else
    {
        *conversion_status = (uint8)(!(ADCON0bits.GO_nDONE));
        ret = E_OK;
    }
    return ret;
}

/**
 * @Summary Returns the ADC conversion value
 * @Description This routine is used to get analog to digital converted value
 *              This routine get the converted values from the channel specified  
 *  @preconditions  This routine returns the conversion value only after the conversion is completed 
 *                  Completion status can be checked using ADC_IsConversionDone() routine 
 * @param _adc Pointer to ADC Configuration 
 * @param conversion_Result The conversion value
 * @return status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action 
 */
std_ReturnType ADC_GetConversionResult(const adc_config_t *_adc, adc_result_t *conversion_Result)
{
    std_ReturnType ret = E_NOT_OK;
    if((NULL == _adc) || (NULL == conversion_Result))
    {
        ret = E_NOT_OK;
    }
    else
    {
        if(ADC_RESULT_RIGHT == _adc->result_format)
        {
            *conversion_Result = (adc_result_t)((ADRESH << 8) + ADRESL);
        }
        else if(ADC_RESULT_LEFT == _adc->result_format)
        {
            *conversion_Result = (adc_result_t)(((ADRESH << 8) + ADRESL) >> 6);
        }
        else
        {
            *conversion_Result = (adc_result_t)((ADRESH << 8) + ADRESL);
        }
        ret = E_OK;
    }
    return ret;
}

/**
 * @Summary Returns the ADC conversion value , also allows selection of channel for conversion 
 * @Description This routine used to select desired channel for conversion.
 *              This routine is used to get analog to digital converted value
 * @preconditions  ADC_Init() function should have been called before calling this function 
 * @param _adc Pointer to ADC Configuration 
 * @param channel Defines the channel available for conversion.
 * @param conversion_Result The conversion value
 * @return status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action 
 */
std_ReturnType ADC_GetConversion_Blocking(const adc_config_t *_adc, adc_channel_select_t channel,
                                 adc_result_t *conversion_Result)
{
    std_ReturnType ret = E_NOT_OK;
    uint8 l_conversion_status = ZERO_INIT;
    if((NULL == _adc) || (NULL == conversion_Result))
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* select A/D channel */
        ret = ADC_selectChannel(_adc, channel);
        /* Start ADC conversion */
        ret = ADC_StartConvesion(_adc);
        /* Check the conversion that is complete or not */
        ret =  ADC_IsConversionDone(_adc, &l_conversion_status);
        while(ADCON0bits.GO_nDONE);
        ret = ADC_GetConversionResult(_adc, conversion_Result);
    }
    return ret;
}

/**
 * @Summary Returns the ADC conversion value , also allows selection of channel for conversion 
 * @Description This routine used to select desired channel for conversion.
 *              This routine is used to get analog to digital converted value
 * @preconditions  ADC_Init() function should have been called before calling this function 
 * @param _adc Pointer to ADC Configuration 
 * @param channel Defines the channel available for conversion.
 * @param conversion_Result The conversion value
 * @return status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action 
 */
std_ReturnType ADC_StartConversion_Interrupt(const adc_config_t *_adc, adc_channel_select_t channel)
{
    std_ReturnType ret = E_NOT_OK;
    uint8 l_conversion_status = ZERO_INIT;
    if(NULL == _adc)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* select A/D channel */
        ret = ADC_selectChannel(_adc, channel);
        /* Start ADC conversion */
        ret = ADC_StartConvesion(_adc);
    }
    return ret;
}





static inline void adc_input_channel_port_configure(adc_channel_select_t channel)
{
    switch(channel)
    {
        case ADC_CHANNEL_AN0  : SET_BIT(TRISA, _TRISA_RA0_POSN); break; /* Disable the digital output driver */
        case ADC_CHANNEL_AN1  : SET_BIT(TRISA, _TRISA_RA1_POSN); break; /* Disable the digital output driver */
        case ADC_CHANNEL_AN2  : SET_BIT(TRISA, _TRISA_RA2_POSN); break; /* Disable the digital output driver */
        case ADC_CHANNEL_AN3  : SET_BIT(TRISA, _TRISA_RA3_POSN); break; /* Disable the digital output driver */
        case ADC_CHANNEL_AN4  : SET_BIT(TRISA, _TRISA_RA5_POSN); break; /* Disable the digital output driver */
        case ADC_CHANNEL_AN5  : SET_BIT(TRISE, _TRISE_RE0_POSN); break; /* Disable the digital output driver */
        case ADC_CHANNEL_AN6  : SET_BIT(TRISE, _TRISE_RE1_POSN); break; /* Disable the digital output driver */
        case ADC_CHANNEL_AN7  : SET_BIT(TRISE, _TRISE_RE2_POSN); break; /* Disable the digital output driver */
        case ADC_CHANNEL_AN8  : SET_BIT(TRISB, _TRISB_RB2_POSN); break; /* Disable the digital output driver */
        case ADC_CHANNEL_AN9  : SET_BIT(TRISB, _TRISB_RB3_POSN); break; /* Disable the digital output driver */
        case ADC_CHANNEL_AN10 : SET_BIT(TRISB, _TRISB_RB1_POSN); break; /* Disable the digital output driver */
        case ADC_CHANNEL_AN11 : SET_BIT(TRISB, _TRISB_RB4_POSN); break; /* Disable the digital output driver */
        case ADC_CHANNEL_AN12 : SET_BIT(TRISB, _TRISB_RB0_POSN); break; /* Disable the digital output driver */
        
    }
}


static inline void select_result_format(const adc_config_t *_adc)
{
    if(ADC_RESULT_RIGHT == _adc->result_format)
    {
        ADC_RESULT_RIGHT_FORMAT();
    }
    else if(ADC_RESULT_LEFT == _adc->result_format)
    {
        ADC_RESULT_LEFT_FORMAT();
    }
    else
    {
        ADC_RESULT_RIGHT_FORMAT();
    }
}

static inline void configure_voltage_reference(const adc_config_t *_adc)
{
    if(ADC_VOLTAGE_REFERENCE_ENABLE == _adc->voltage_reference)
    {
        ADC_ENABLE_VOLTAGE_REFRENCE();
    }
    else if(ADC_VOLTAGE_REFERENCE_DISABLE == _adc->voltage_reference)
    {
        ADC_DISABLE_VOLTAGE_REFRENCE();
    }
    else
    {
        ADC_DISABLE_VOLTAGE_REFRENCE();
    }
}

void ADC_ISR(void)
{
    ADC_InterruptflagClear();
    if(ADC_InterruptHandler)
    {
        ADC_InterruptHandler();
    }
}