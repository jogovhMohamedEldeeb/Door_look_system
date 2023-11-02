/* 
 * File:   ecu_dc_motor.c
 * Author: m7md
 *
 * Created on 16 July 2023, 17:55
 */

#include "ecu_dc_motor.h"

/**
 * 
 * @brief  Intialize the assigned pin to be OUTPUT and the motor OFF or ON
 * @param _dc_motor pointer to the motor configurations
 * @return status of the function
 *      E_OK : the function done successfully
 *      E_NOT_OK : the function has issue while performing action
 */
Std_ReturnType dc_motor_intialize(const dc_motor_t *_dc_motor){
    Std_ReturnType ret = E_OK;
    if(NULL == _dc_motor){
        ret = E_NOT_OK;
    }
    else{
     gpio_pin_intialize(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN1]));
     gpio_pin_intialize(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN2]));
    }
    return ret; 
}

/**
 * 
 * @brief Move the to the right direction
 * @param _dc_motor pointer to the motor configurations
 * @return status of the function
 *      E_OK : the function done successfully
 *      E_NOT_OK : the function has issue while performing action
 */
Std_ReturnType dc_motor_move_right(const dc_motor_t *_dc_motor){
   Std_ReturnType ret = E_OK;
    if(NULL == _dc_motor){
        ret = E_NOT_OK;
    }
    else{
        gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN1]),GPIO_HIGH);
        gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN2]),GPIO_LOW);
    }
    return ret; 
}

/**
 * 
 * @brief Move the to the left direction
 * @param _dc_motor pointer to the motor configurations
 * @return status of the function
 *      E_OK : the function done successfully
 *      E_NOT_OK : the function has issue while performing action
 */
Std_ReturnType dc_motor_move_left(const dc_motor_t *_dc_motor){
    Std_ReturnType ret = E_OK;
    if(NULL == _dc_motor){
        ret = E_NOT_OK;
    }
    else{
        gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN1]),GPIO_LOW);
        gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN2]),GPIO_HIGH);
    }
    return ret; 
}

/**
 * 
 * @brief Stop the movement motor
 * @param _dc_motor pointer to the motor configurations
 * @return status of the function
 *      E_OK : the function done successfully
 *      E_NOT_OK : the function has issue while performing action
 */
Std_ReturnType dc_motor_stop(const dc_motor_t *_dc_motor){
    Std_ReturnType ret = E_OK;
    if(NULL == _dc_motor){
        ret = E_NOT_OK;
    }
    else{
        gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN1]),GPIO_LOW);
        gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN2]),GPIO_LOW);
    }
    return ret; 
}