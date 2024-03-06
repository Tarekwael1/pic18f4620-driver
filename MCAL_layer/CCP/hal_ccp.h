/* 
 * File:   hal_ccp1.h
 * Author: OKTA
 *
 * Created on January 23, 2024, 8:07 PM
 */

#ifndef HAL_CCP1_H
#define	HAL_CCP1_H


/*---------- section : Includes --------------------*/
#include "ccp_cfg.h"
#include "pic18f4620.h"
#include "../MCAL_STD_types.h"
#include "../../MCAL_layer/GPIO/hal_gpio.h"
#include "../../MCAL_layer/interrupt/mcal_internal_interrupt.h"
 

/*---------- section : Macro Declarations --------------------  */

    /* Disable the ccp module */
#define CCP_MODULE_DISABLE                 ((uint8)0x00)
    
    /* Mode of capture */
#define CCP_CAPTURE_MODE_1_FALLING_EDGE    ((uint8)0x04)
#define CCP_CAPTURE_MODE_1_RISING_EDGE     ((uint8)0x05)
#define CCP_CAPTURE_MODE_4_RISING_EDGE     ((uint8)0x06)
#define CCP_CAPTURE_MODE_16_RISING_EDGE    ((uint8)0x07)
    
    /* Mode of compare */
#define CCP_COMPARE_MODE_SET_PIN_LOW       ((uint8)0x08)
#define CCP_COMPARE_MODE_SET_PIN_HIGH      ((uint8)0x09)
#define CCP_COMPARE_MODE_TOGGLE_ON_MATCH   ((uint8)0x02)
#define CCP_COMPARE_MODE_GEN_SW_INTERRUPT  ((uint8)0x0A)
#define CCP_COMPARE_MODE_GEN_EVENT         ((uint8)0x0B)
    
    /* PWM mode */
#define CCP_PWM_MODE                       ((uint8)0x0C)

    /* CCP1 Caputre mode state */
#define CCP_CAPTURE_NOT_READY              0x00
#define CCP_CAPTURE_READY                  0x01

    /* CCP1 Compare mode state*/
#define CCP_COMPARE_NOT_READY              0x00
#define CCP_COMPARE_READY                  0x01

    /* Timer2 Input Clock postscaler */
#define CCP_TIMER2_POSTSCALER_DIV_BY_1               1
#define CCP_TIMER2_POSTSCALER_DIV_BY_2               2
#define CCP_TIMER2_POSTSCALER_DIV_BY_3               3
#define CCP_TIMER2_POSTSCALER_DIV_BY_4               4
#define CCP_TIMER2_POSTSCALER_DIV_BY_5               5
#define CCP_TIMER2_POSTSCALER_DIV_BY_6               6
#define CCP_TIMER2_POSTSCALER_DIV_BY_7               7
#define CCP_TIMER2_POSTSCALER_DIV_BY_8               8
#define CCP_TIMER2_POSTSCALER_DIV_BY_9               9
#define CCP_TIMER2_POSTSCALER_DIV_BY_10              10
#define CCP_TIMER2_POSTSCALER_DIV_BY_11              11
#define CCP_TIMER2_POSTSCALER_DIV_BY_12              12
#define CCP_TIMER2_POSTSCALER_DIV_BY_13              13
#define CCP_TIMER2_POSTSCALER_DIV_BY_14              14
#define CCP_TIMER2_POSTSCALER_DIV_BY_15              15
#define CCP_TIMER2_POSTSCALER_DIV_BY_16              16

    /* Timer2 Input Clock Prescaler */
#define CCP_TIMER2_PRESCALER_DIV_BY_1                1
#define CCP_TIMER2_PRESCALER_DIV_BY_4                4
#define CCP_TIMER2_PRESCALER_DIV_BY_16               16

/*---------- section : Macro Function declarations --------------------*/

    /* Set the CCP1 Mode Variant */
#define CCP1_SET_MODE(_CONFIG)      (CCP1CONbits.CCP1M = _CONFIG)  

    /* Set the CCP2 Mode Variant */
#define CCP2_SET_MODE(_CONFIG)      (CCP2CONbits.CCP2M = _CONFIG)  

/*---------- section : Data Type Declarations --------------------*/

/*
  @Summary      Define the values to select the CCP1 Main mode
*/
typedef enum
{
    CCP_CAPTURE_MODE_SELECT = 0,    /* Select CCP1 Capture Mode */
    CCP_COMPARE_MODE_SELECT,       /* Select CCP1 Compare Mode */
    CCP_PWM_MODE_SELECT             /* Select CCP1 PWM Mode */
}ccp_mode_t;


typedef enum
{
    CCP1_INST,
    CCP2_INST
}ccp_inst_t;

typedef enum
{
    CCP1_CCP2_TIMER3 = 0,       //0
    CCP1_TIMER1_CCP2_TIEMR3,    //1
    CCP1_CCP2_TIMER1            //2
}ccp_Capture_timer_t;

/*
  @Summary      Defines the values to convert from 16bit to two 8 bit and vice versa
  @Description  Used to get two 8 bit values from 16bit also two 8 bit value are combine to get 16bit.
*/
typedef union
{
    struct
    {
        uint8 ccpr_low;
        uint8 ccpr_high;
    };
    struct
    {
        uint16 ccpr_16bit;
    };
}CCP_REG_T;


/*
  @Summary      CCP Module configurations
  @Description  This data type used to describe the module initialization configuration
*/
typedef struct
{
    ccp_inst_t ccp_inst;                     /* Chose between ccp1 and ccp2 */
    ccp_mode_t ccp_mode;                     /* ccp main mode (Capture - compare - pwm) */
    uint8 ccp_mode_variant;                  /* ccp variant mode  */
    pin_config_t ccp_pin;                    /* ccp pin i/o configuration  */
    ccp_Capture_timer_t ccp_Capture_timer;   /* ccp chose the timer that will run  */
    
#if CCP1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    void (* CCP1_InterruptHandler)(void);      /* Call back */
    interrupt_priority_cfg  CCP1_priority;
#endif
    
#if CCP2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    void (* CCP2_InterruptHandler)(void);      /* Call back */
    interrupt_priority_cfg  CCP2_priority;
#endif
    
#if (CCP1_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE_SELECTED) || (CCP2_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE_SELECTED)
    uint32 PWM_Frequency;           /* CCP PWM mode frequency */
    uint8 timer2_prescaler_value;
    uint8 timer2_postscaler_value;
#endif
    
}ccp_t;


/*---------- section : Function declarations --------------------*/

/**
 * @brief Initialize the CCP1 module 
 * @param ccp_obj pointer of object that we can go to register from
 * @return Status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action
 */
std_ReturnType CCP_Init(const ccp_t *ccp_obj);

/**
 * @brief Initialize the CCP1 module
 * @param ccp_objpointer of object that we can go to register from
 * @return Status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action
 */
std_ReturnType CCP_DeInit(const ccp_t *ccp_obj);



#if (CCP1_CFG_SELECTED_MODE == CCP_CFG_CAPTURE_MODE_SELECTED)
/**
 * @brief to check that the capture done or not 
 * @param _capture_Status
 * @return Status of the function
 *          CCP_CAPTURE_READY     : The function done successfully
 *          CCP_CAPTURE_NOT_READY : The function has issue to perform this action
 */
   std_ReturnType CCP_IsCapturedDataReady(const ccp_t *ccp_obj, uint8 *_capture_Status);

/**
 * @brief to get the value from ccp1 
 * @param _capture_Value To get the value that i need to read it
 * @return Status of the function
 *          CCP_CAPTURE_READY     : The function done successfully
 *          CCP_CAPTURE_NOT_READY : The function has issue to perform this action
 */
   std_ReturnType CCP_Captured_Mode_Read_Value(const ccp_t *ccp_obj, uint16 *_capture_Value);
#endif

#if (CCP1_CFG_SELECTED_MODE == CCP_CFG_COMPARE_MODE_SELECTED)
   /**
 * @brief to check that the compare complete or not 
 * @param _compare_Status
 * @return Status of the function
 *          CCP_COMPARE_READY     : The function done successfully
 *          CCP_COMPARE_NOT_READY : The function has issue to perform this action
 */
   std_ReturnType CCP_IscompareComplete(const ccp_t *ccp_obj, uint8 *_compare_Status);

/**
 * @brief to get the value from ccp1 
 * @param _compare_Value To get the value that i need to read it
 * @return Status of the function
 *          CCP_COMPARE_READY     : The function done successfully
 *          CCP_COMPARE_NOT_READY : The function has issue to perform this action
 */
   std_ReturnType CCP_compare_Mode_Set_Value(const ccp_t *ccp_obj, uint16 _compare_Value);
#endif

#if (CCP1_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE_SELECTED)
   
/**
 * @brief To set the duty cycle
 * @param _duty the value
 * @return Status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action
 */
   std_ReturnType CCP_PWM_Set_Duty(const ccp_t *ccp_obj, const uint8 _duty);
 
/**
 * @brief To start the pwm mode
 * @return Status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action
 */   
   std_ReturnType CCP_PWM_Start(const ccp_t *ccp_obj);

/**
 * @brief To stop the pwm mode
 * @return Status of the function
 *          E_OK     : The function done successfully
 *          E_NOT_OK : The function has issue to perform this action
 */   
   std_ReturnType CPP_PWM_Stop(const ccp_t *ccp_obj);
#endif

#endif	/* HAL_CCP1_H */

