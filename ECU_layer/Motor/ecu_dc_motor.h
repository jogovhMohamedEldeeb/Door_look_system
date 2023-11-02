/* 
 * File:   ecu_dc_motor.h
 * Author: m7md
 *
 * Created on 16 July 2023, 17:55
 */

#ifndef ECU_DC_MOTOR_H
#define	ECU_DC_MOTOR_H


/************************ Includes ************************/

#include "../../MCAL_layer/GPIO/hal_gpio.h"

/************************  Macro Declaration ************************/
#define DC_MOTOR_ON_STATUS 0x01U
#define DC_MOTOR_OFF_STATUS 0x00U

#define DC_MOTOR_PIN1 0x00U
#define DC_MOTOR_PIN2 0x01U

/************************  Macro Function Declaration ************************/


/************************  Data Type Declaration ************************/
 
typedef struct{
    pin_config_t dc_motor_pin[2];
}dc_motor_t;

/************************  Software interface Declaration ************************/
Std_ReturnType dc_motor_intialize(const dc_motor_t *_dc_motor);
Std_ReturnType dc_motor_move_right(const dc_motor_t *_dc_motor);
Std_ReturnType dc_motor_move_left(const dc_motor_t *_dc_motor);
Std_ReturnType dc_motor_stop(const dc_motor_t *_dc_motor);
 

#endif	/* ECU_DC_MOTOR_H */

