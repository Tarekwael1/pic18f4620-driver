/* 
 * File:   hal_gpio.c
 * Author: Tarek.wael
 *
 * Created on September 14, 2023, 8:16 PM
 */
#include "hal_gpio.h"
/*Reference to the data direction control registers */
volatile uint8 *tris_registers[] = {&TRISA, &TRISB, &TRISC, &TRISD, &TRISE};  //array (tris_registers[]) of addresses (*) each address is 8 bit (uint8 )
/*Reference th the data latch register (read and write to the data latch)*/
volatile uint8 *lat_registers[] =  {&LATA , &LATB , &LATC , &LATD , &LATE};
/*Reference to the port status register */
volatile uint8 *port_registers[] = {&PORTA, &PORTB, &PORTC, &PORTD, &PORTE};  



#if GPIO_PORT_PIN_CONFIGURATIONS==CONFIG_ENABLE
std_ReturnType gpio_pin_initialize(const pin_config_t *_pin_config)
{
     std_ReturnType ret = E_OK;
    if((NULL == _pin_config) || (_pin_config->pin > PORT_PIN_MAX_NUMBER-1))
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_direction_initialize(_pin_config);
        ret = gpio_pin_write_logic(_pin_config, _pin_config->logic);
    }
}
#endif


#if GPIO_PORT_PIN_CONFIGURATIONS==CONFIG_ENABLE
std_ReturnType gpio_pin_direction_initialize(const pin_config_t *_pin_config)
{
    std_ReturnType ret = E_OK;
    if((NULL == _pin_config) || (_pin_config->pin > PORT_PIN_MAX_NUMBER-1))
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch(_pin_config->direction)
          {
            case GPIO_DIRECTION_OUTPUT :
                CLEAR_BIT(*tris_registers[_pin_config->port], _pin_config->pin );

                break;
            case GPIO_DIRECTION_INPUT :
                SET_BIT(*tris_registers[_pin_config->port], _pin_config->pin);

                break;
            default : ret = E_NOT_OK;
         }
    }
    return ret;
}
#endif


#if GPIO_PORT_PIN_CONFIGURATIONS==CONFIG_ENABLE
std_ReturnType gpio_pin_get_direction_status(const pin_config_t *_pin_config, direction_t *direction_status)
{
    std_ReturnType ret = E_OK;
    if((NULL == _pin_config) || (NULL == direction_status) || (_pin_config->pin > PORT_PIN_MAX_NUMBER-1))
    {
        ret = E_NOT_OK;
    }
    else
    {
        *direction_status = READ_BIT(*tris_registers[_pin_config->port], _pin_config->pin);
    }
    return ret;
}
#endif


#if GPIO_PORT_PIN_CONFIGURATIONS==CONFIG_ENABLE
std_ReturnType gpio_pin_write_logic(const pin_config_t *_pin_config, logic_t logic)
{
    std_ReturnType ret = E_OK;
    if((NULL == _pin_config) || (_pin_config->pin > PORT_PIN_MAX_NUMBER-1))
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch(logic)
        {
            case GPIO_LOW  :
                CLEAR_BIT(*lat_registers[_pin_config->port], _pin_config->pin);
                break;
            case GPIO_HIGH :  
                SET_BIT(*lat_registers[_pin_config->port], _pin_config->pin);
                break;
            default : ret = E_NOT_OK ;
        }
    }
    return ret;
}
#endif


#if GPIO_PORT_PIN_CONFIGURATIONS==CONFIG_ENABLE
std_ReturnType gpio_pin_read_logic(const pin_config_t *_pin_config, logic_t *logic)
{
    std_ReturnType ret = E_OK;
    if((NULL == _pin_config) || (NULL == logic) || (_pin_config->pin > PORT_PIN_MAX_NUMBER-1))
    {
        ret = E_NOT_OK;
    }
    else
    {
        *logic = READ_BIT(*port_registers[_pin_config->port], _pin_config->pin);        
    }
    return ret;
}
#endif


#if GPIO_PORT_PIN_CONFIGURATIONS==CONFIG_ENABLE
std_ReturnType gpio_pin_toggle_logic(const pin_config_t *_pin_config)
{
    std_ReturnType ret = E_OK;
    if((NULL == _pin_config) || (_pin_config->pin > PORT_PIN_MAX_NUMBER-1))
    {
        ret = E_NOT_OK;
    }
    else
    {
        TOGGLE_BIT(*lat_registers[_pin_config->port], _pin_config->pin);
    }
    return ret;
}
#endif


#if GPIO_PORT_CONFIGURATIONS==CONFIG_ENABLE
std_ReturnType gpio_port_direction_initialize(port_index_t port, uint8 direction)
{
    std_ReturnType ret = E_OK;
    if(port > PORT_MAX_NUMBER-1)
    {
        ret = E_NOT_OK;
    }
    else
    {
        *tris_registers[port] = direction;
    }
    return ret;
}
#endif


#if GPIO_PORT_CONFIGURATIONS==CONFIG_ENABLE
std_ReturnType gpio_port_get_direction_status(port_index_t port, uint8 *direction_status)
{
    std_ReturnType ret = E_OK;
    if((NULL == direction_status) && (port > PORT_MAX_NUMBER-1))
    {
        ret = E_NOT_OK;
    }
    else
    {
        *direction_status = *tris_registers[port];
    }
    return ret;
}
#endif


#if GPIO_PORT_CONFIGURATIONS==CONFIG_ENABLE
std_ReturnType gpio_port_write_logic(port_index_t port, uint8 logic)
{
    std_ReturnType ret = E_OK;
    if(port > PORT_MAX_NUMBER-1)
    {
        ret = E_NOT_OK;
    }
    else
    {
        *lat_registers[port] = logic;
    }
    return ret;
}
#endif


#if GPIO_PORT_CONFIGURATIONS==CONFIG_ENABLE
std_ReturnType gpio_port_read_logic(port_index_t port, uint8 *logic)
{
    std_ReturnType ret = E_OK;
    if((NULL == logic) && (port > PORT_MAX_NUMBER-1))
    {
        ret = E_NOT_OK;
    }
    else
    {
        *logic = *lat_registers[port];
    }
    return ret;
}
#endif


#if GPIO_PORT_CONFIGURATIONS==CONFIG_ENABLE
std_ReturnType gpio_port_toggle_logic(port_index_t port)
{
    std_ReturnType ret = E_OK;
    if(port > PORT_MAX_NUMBER-1)
    {
        ret = E_NOT_OK;
    }
    else
    {
        *lat_registers[port] ^= PORTC_MASK;
    }
    return ret;
}
#endif
