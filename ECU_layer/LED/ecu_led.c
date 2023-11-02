/* 
 * File:   ecu_led.c
 * Author: m7md
 *
 * Created on 16 August 2023, 23:40
 */

#include "ecu_led.h"



Std_ReturnType led_intialiaze(const led_t *led){
    Std_ReturnType ret = E_OK;
    if(led == NULL){
        ret = E_NOT_OK;
    }
    else{
        pin_config_t pin_config_obj = {.port = led->port, .pin = led->pin,
                                    .direction = GPIO_direction_output, .logic = led->led_status};
        ret = gpio_pin_intialize(&pin_config_obj);
    }
    return ret;
}

/**
 * @breif turn on led 
 * @param led
 * @return status of the function
 *         (E_OK): The function done successfully
 *         (E_NOT_OK): The function has issue to perform this action
 */
Std_ReturnType led_turn_on(const led_t *led){
    Std_ReturnType ret = E_OK;
    if(led == NULL){
        ret = E_NOT_OK;
    }
    else{
        pin_config_t pin_config_obj = {.port = led->port, .pin = led->pin,
                                    .direction = GPIO_direction_output, .logic = led->led_status};
        ret = gpio_pin_write_logic(&pin_config_obj, GPIO_HIGH);
    }
    return ret;
}

/**
 * @breif turn off led 
 * @param led
 * @return status of the function
 *         (E_OK): The function done successfully
 *         (E_NOT_OK): The function has issue to perform this action
 */
Std_ReturnType led_turn_off(const led_t *led){
    Std_ReturnType ret = E_OK;
    if(led == NULL){
        ret = E_NOT_OK;
    }
    else{
        pin_config_t pin_config_obj = {.port = led->port, .pin = led->pin,
                                    .direction = GPIO_direction_output, .logic = led->led_status};
        ret = gpio_pin_write_logic(&pin_config_obj, GPIO_LOW);
    }
    return ret;
}