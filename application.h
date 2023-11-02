/* 
 * File:   application.h
 * Author: m7md
 *
 * Created on 16 August 2023, 20:05
 */

#ifndef APPLICATION_H
#define	APPLICATION_H

 
#include "MCAL_layer/GPIO/hal_gpio.h"
#include "ECU_layer/LED/ecu_led.h"
#include "ECU_layer/Motor/ecu_dc_motor.h"
#include "ECU_layer/Chr_lcd/ecu_lcd.h"
#include "ECU_layer/Keypad/ecu_keypad.h"

void app_init(void);

#endif	/* APPLICATION_H */

