/* 
 * File:   hal_adc.h
 * Author: OKTA
 *
 * Created on October 9, 2023, 9:46 AM
 */

#ifndef HAL_ADC_H
#define	HAL_ADC_H

/*---------- section : Includes --------------------*/
#include "hal_adc_cfg.h"
#include "pic18f4620.h"
#include "../MCAL_STD_types.h"
#include "../../MCAL_layer/GPIO/hal_gpio.h"
#include "../../MCAL_layer/interrupt/mcal_internal_interrupt.h"

/*---------- section : Macro Declarations --------------------  */
/**
 * @brief If you chose to make AN4 Analog that mean (AN0,An1,An2,An3,An4)
 * all are analog bits 
 */
#define ADC_AN0_ANALOG_FUNCTIONALITY    0x0E 
#define ADC_AN1_ANALOG_FUNCTIONALITY    0x0D 
#define ADC_AN2_ANALOG_FUNCTIONALITY    0x0C 
#define ADC_AN3_ANALOG_FUNCTIONALITY    0x0B 
#define ADC_AN4_ANALOG_FUNCTIONALITY    0x0A 
#define ADC_AN5_ANALOG_FUNCTIONALITY    0x09 
#define ADC_AN6_ANALOG_FUNCTIONALITY    0x08 
#define ADC_AN7_ANALOG_FUNCTIONALITY    0x07 
#define ADC_AN8_ANALOG_FUNCTIONALITY    0x06 
#define ADC_AN9_ANALOG_FUNCTIONALITY    0x05 
#define ADC_AN10_ANALOG_FUNCTIONALITY   0x04 
#define ADC_AN11_ANALOG_FUNCTIONALITY   0x03 
#define ADC_AN12_ANALOG_FUNCTIONALITY   0x02 
#define ADC_ALL_ANALOG_FUNCTIONALITY    0x00 
#define ADC_ALL_DIGITAL_FUNCTIONALITY   0x0F 


#define ADC_RESULT_RIGHT                0x01U
#define ADC_RESULT_LEFT                 0x00U

#define ADC_VOLTAGE_REFERENCE_ENABLE    0x01U
#define ADC_VOLTAGE_REFERENCE_DISABLE   0x00U

#define ADC_CONVERSION_COMPLETED        1
#define ADC_CONVERSION_INPROGRESS       0 
/*---------- section : Macro Function declarations --------------------*/

/* A/D Conversion Status : A/D conversion in progress / A/D Idle */
#define ADC_CONVERSION_STATUS()   (ADCON0bits.GO_nDONE)

/**
 * @brief Start the analog to digital conversion  
 */
#define ADC_START_CONVERSION()    (ADCON0bits.GODONE = 1)
/**
 * @brief Analog to Digital control 
 * @note   ADC_CONVERTER_ENABLE() : Enable Analog to Digital 
           ADC_CONVERTER_DISABLE(): Disable Analog to Digital
 */
#define ADC_CONVERTER_ENABLE()    (ADCON0bits.ADON = 1)
#define ADC_CONVERTER_DISABLE()   (ADCON0bits.ADON = 0)

/**
 * @brief Voltage reference configuration 
 * @note ADC_ENABLE_VOLTAGE_REFRENCE() : Voltage reference is VREF-(AN2) & VREF+(AN3)
 *       ADC_DISABLE_VOLTAGE_REFRENCE(): Voltage reference is VDD & VSS
 */
#define ADC_ENABLE_VOLTAGE_REFRENCE()   do{ADCON1bits.VCFG1 = 1;\
                                           ADCON1bits.VCFG0 = 1;\
                                        }while(0)
#define ADC_DISABLE_VOLTAGE_REFRENCE()  do{ADCON1bits.VCFG1 = 0;\
                                           ADCON1bits.VCFG0 = 0;\
                                        }while(0)

/**
 * @brief Analog_To_Digital Port Configuration control 
 * @note Example : ADC_ANALOG_DIGITAL_PORT_CONFIG(ADC_AN4_ANALOG_FUNCTIONALITY);
 *                 When ADC_AN4_ANALOG_FUNCTIONALITY is configured ,This means 
 *                 (AN0,An1,An2,An3,An4) are analog functionality.
 *                 @ref Analog_To_Digital Port Configuration control 
 */

#define ADC_ANALOG_DIGITAL_PORT_CONFIG(_CONFIG)  (ADCON1bits.PCFG = _CONFIG)


/**
 * @brief A/D Result format select 
 */
#define ADC_RESULT_RIGHT_FORMAT()     (ADCON2bits.ADFM = 1)
#define ADC_RESULT_LEFT_FORMAT()      (ADCON2bits.ADFM = 0)


/*---------- section : Data Type Declarations --------------------*/
/**
 * @brief Analog channel salect 
 */
typedef enum 
{
    ADC_CHANNEL_AN0 = 0,
    ADC_CHANNEL_AN1,
    ADC_CHANNEL_AN2,
    ADC_CHANNEL_AN3,
    ADC_CHANNEL_AN4,
    ADC_CHANNEL_AN5,
    ADC_CHANNEL_AN6,
    ADC_CHANNEL_AN7,
    ADC_CHANNEL_AN8,
    ADC_CHANNEL_AN9,
    ADC_CHANNEL_AN10,
    ADC_CHANNEL_AN11,
    ADC_CHANNEL_AN12            
}adc_channel_select_t;

/**
 * @brief A/D Acquisition time select 
 * @note Acquisition time (Sampling time) is the time required for the (ADC) to 
 *       Capture thee input voltage during sampling .
 * @note Acquisition time of a successive Approximation Register (SAR) ADC of the amount of time 
 *       required to charge the holding capacitor (CHOLD) on the front end of ADC
 */
typedef enum
{
    ADC_0_TAD = 0,
    ADC_2_TAD,
    ADC_4_TAD,
    ADC_6_TAD,
    ADC_8_TAD,
    ADC_12_TAD,
    ADC_16_TAD,
    ADC_20_TAD
}adc_acquisition_time_t;

/**
 * @brief A/D Conversion Clock Select
 * @note If the A/D FRC clock source is selected, a delay of one TCY (instruction cycle)
 *       is added before the A/D clock starts.   
 * @note This allows the sleep instruction to be executed before starting a conversion. 
 */
typedef enum
{
    ADC_CONVERSION_CLOCK_FOSC_DIV_2 = 0,
    ADC_CONVERSION_CLOCK_FOSC_DIV_8,
    ADC_CONVERSION_CLOCK_FOSC_DIV_32,
    ADC_CONVERSION_CLOCK_FOSC_DIV_FRC,
    ADC_CONVERSION_CLOCK_FOSC_DIV_4,
    ADC_CONVERSION_CLOCK_FOSC_DIV_16,
    ADC_CONVERSION_CLOCK_FOSC_DIV_64,
}adc_conversion_clock_t;

typedef struct
{
#if ADC_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    void (* ADC_InterruptHandler)(void);      /* Call back */
    interrupt_priority_cfg  priority;
#endif
    adc_acquisition_time_t acquisition_time;  /* @ref adc_acquisition_time_t */
    adc_conversion_clock_t conversion_clock;  /* @ref adc_conversion_clock_t */
    adc_channel_select_t   adc_channel;       /* @ref adc_channel_select_t */
    uint8 voltage_reference : 4;              /* Voltage reference configuration */
    uint8 result_format :4;                   /* A/D Result format select */
    uint8 ADC_RESERVED :6;
}adc_config_t;

typedef uint16 adc_result_t;

/*---------- section : Function declarations --------------------*/
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
std_ReturnType ADC_Init(const adc_config_t *_adc);

/**
 * @Summary De-Initialize the ADC
 * @param _adc Pointer to ADC Configuration 
 * @return status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action 
 */
std_ReturnType ADC_DeInit(const adc_config_t *_adc);

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
std_ReturnType ADC_selectChannel(const adc_config_t *_adc, adc_channel_select_t channel);

/**
 * @Summary Starts the conversion 
 * @Description This routine used to start conversion of desired channel.
 * @preconditions  ADC_Init() function should have been called before calling this function 
 * @param _adc Pointer to ADC Configuration 
 * @return status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action 
 */
std_ReturnType ADC_StartConvesion (const adc_config_t *_adc);

/**
 * @Summary Returns when the conversion is completed otherwise false 
 * @Description This routine is used to determine if conversion is completed.
 *              When conversion is complete routine returns true, otherwise false 
 * @preconditions  ADC_Init() function should have been called before calling this function 
 *                 ADC_StartConvesion() should have been called before calling this function
 * @param _adc Pointer to ADC Configuration 
 * @param conversion_status The conversion status
 * @return status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action 
 */
std_ReturnType ADC_IsConversionDone(const adc_config_t *_adc, uint8 *conversion_status);

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
std_ReturnType ADC_GetConversionResult(const adc_config_t *_adc, adc_result_t *conversion_Result);

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
                                 adc_result_t *conversion_Result);


std_ReturnType ADC_StartConversion_Interrupt(const adc_config_t *_adc, adc_channel_select_t channel);

#endif	/* HAL_ADC_H */

