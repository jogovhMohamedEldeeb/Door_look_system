/* 
 * File:   application.c
 * Author: m7md
 *
 * Created on 16 August 2023, 20:05
 */

#include "application.h"
 
 
led_t led_red = {.port = PORTA_INDEX, .pin =  GPIO_PIN0, .led_status = GPIO_LOW};
led_t led_green = {.port = PORTA_INDEX, .pin =  GPIO_PIN1, .led_status = GPIO_LOW};

dc_motor_t motor_1={
  .dc_motor_pin[0].port = PORTA_INDEX,
  .dc_motor_pin[0].pin = GPIO_PIN2,
  .dc_motor_pin[0].direction = GPIO_direction_output,
  .dc_motor_pin[0].logic = GPIO_LOW,
  .dc_motor_pin[1].port = PORTA_INDEX,
  .dc_motor_pin[1].pin = GPIO_PIN3,
  .dc_motor_pin[1].direction = GPIO_direction_output,
  .dc_motor_pin[1].logic = GPIO_LOW,
 
          
};
 
dc_motor_t motor_2={
  .dc_motor_pin[0].port = PORTA_INDEX,
  .dc_motor_pin[0].pin = GPIO_PIN4,
  .dc_motor_pin[0].direction = GPIO_direction_output,
  .dc_motor_pin[0].logic = GPIO_LOW,
  .dc_motor_pin[1].port = PORTA_INDEX,
  .dc_motor_pin[1].pin = GPIO_PIN5,
  .dc_motor_pin[1].direction = GPIO_direction_output,
  .dc_motor_pin[1].logic = GPIO_LOW,
 
          
};
 
chr_lcd_4bit_t lcd={
  .lcd_rs.port = PORTC_INDEX,
  .lcd_rs.pin = GPIO_PIN0,
  .lcd_rs.direction = GPIO_direction_output,
  .lcd_rs.logic = GPIO_LOW,
  .lcd_en.port = PORTC_INDEX,
  .lcd_en.pin = GPIO_PIN1,
  .lcd_en.direction = GPIO_direction_output,
  .lcd_en.logic = GPIO_LOW,
  .lcd_data[0].port = PORTC_INDEX,
  .lcd_data[0].pin  = GPIO_PIN2,
  .lcd_data[0].direction = GPIO_direction_output,
  .lcd_data[0].logic = GPIO_LOW,
  .lcd_data[1].port = PORTC_INDEX,
  .lcd_data[1].pin  = GPIO_PIN3,
  .lcd_data[1].direction = GPIO_direction_output,
  .lcd_data[1].logic = GPIO_LOW,
  .lcd_data[2].port = PORTC_INDEX,
  .lcd_data[2].pin  = GPIO_PIN4,
  .lcd_data[2].direction = GPIO_direction_output,
  .lcd_data[2].logic = GPIO_LOW,
  .lcd_data[3].port = PORTC_INDEX,
  .lcd_data[3].pin  = GPIO_PIN5,
  .lcd_data[3].direction = GPIO_direction_output,
  .lcd_data[3].logic = GPIO_LOW,
  
};
 
keypad_t keypad = {
  .keypad_row_pins[0].port = PORTD_INDEX,
  .keypad_row_pins[0].pin = GPIO_PIN0,
  .keypad_row_pins[0].logic = GPIO_LOW,
  .keypad_row_pins[0].direction = GPIO_direction_output,
  .keypad_row_pins[1].port = PORTD_INDEX,
  .keypad_row_pins[1].pin = GPIO_PIN1,
  .keypad_row_pins[1].logic = GPIO_LOW,
  .keypad_row_pins[1].direction = GPIO_direction_output,
  .keypad_row_pins[2].port = PORTD_INDEX,
  .keypad_row_pins[2].pin = GPIO_PIN2,
  .keypad_row_pins[2].logic = GPIO_LOW,
  .keypad_row_pins[2].direction = GPIO_direction_output,
  .keypad_row_pins[3].port = PORTD_INDEX,
  .keypad_row_pins[3].pin = GPIO_PIN3,
  .keypad_row_pins[3].logic = GPIO_LOW,
  .keypad_row_pins[3].direction = GPIO_direction_output,
  
  .keypad_columns_pins[0].port = PORTD_INDEX,
  .keypad_columns_pins[0].pin = GPIO_PIN4,
  .keypad_columns_pins[0].logic = GPIO_LOW,
  .keypad_columns_pins[0].direction = GPIO_direction_input,
  .keypad_columns_pins[1].port = PORTD_INDEX,
  .keypad_columns_pins[1].pin = GPIO_PIN5,
  .keypad_columns_pins[1].logic = GPIO_LOW,
  .keypad_columns_pins[1].direction = GPIO_direction_input,
  .keypad_columns_pins[2].port = PORTD_INDEX,
  .keypad_columns_pins[2].pin = GPIO_PIN6,
  .keypad_columns_pins[2].logic = GPIO_LOW,
  .keypad_columns_pins[2].direction = GPIO_direction_input,
   
};


 
Std_ReturnType ret = E_OK;

uint8 keypad_value;

uint32 password = 123456;
uint32 entered_password = 0;
uint8 number_of_clicks = 0;
uint8 lcd_output= 14;

uint8 incorrect_pass = 0;


uint8 keypad_read_value(void);
int main()
{
    app_init();
    
    ret = lcd_4bit_send_string(&lcd, "Enter Password:");
    
    while(1)
    {
        /* Read Keypad value */
        keypad_value = keypad_read_value();
        /* check if the user entered 6 digit number (Max number of password digits) */
        if(6 == number_of_clicks)
        {
            /* resetting variables */
            number_of_clicks = 0;
            lcd_output = 14;
            
            /* if password is valid -> turn on green led and open the door(moving motor) */
            if(entered_password == password)
            {
                ret = led_turn_on(&led_green);
                ret = dc_motor_move_right(&motor_1);
                ret = lcd_4bit_send_command(&lcd, _LCD_CLEAR);
                ret = lcd_4bit_send_string_pos(&lcd , 1, 7, "Door Opened ");
                incorrect_pass = 0;
                __delay_ms(3000);
                
                ret = led_turn_off(&led_green);
                ret = dc_motor_stop(&motor_1);
                ret = lcd_4bit_send_command(&lcd, _LCD_CLEAR);
                ret = lcd_4bit_send_string(&lcd, "Enter Password:");
            }
            /* if password is not valid -> turn on red led */
            else
            {
                ret = led_turn_on(&led_red);
                 
                ret = dc_motor_move_left(&motor_2);
                ret = lcd_4bit_send_command(&lcd, _LCD_CLEAR);
                ret = lcd_4bit_send_string_pos(&lcd, 1, 2, "Incorrect Password!");
                
                incorrect_pass++;
               
                __delay_ms(2000);
                ret = led_turn_off(&led_red);
                
                ret = dc_motor_stop(&motor_2);
                ret = lcd_4bit_send_command(&lcd, _LCD_CLEAR);
                ret = lcd_4bit_send_string(&lcd, "Enter Password:");
            }
            /* If the password entered incorrectly three times wait 60 sec */
            if(3 == incorrect_pass){
                ret = lcd_4bit_send_string_pos(&lcd, 1, 1, "Try again in    sec");
                uint8 value = 0;
                for(uint8 counter = 60 ; counter > 0 ; counter--){
                    value = '0' + (counter % 10);
                    ret = lcd_4bit_send_char_data_pos(&lcd, 1, 16, value);
                    value = '0' + ((counter/10) % 10);
                    ret = lcd_4bit_send_char_data_pos(&lcd, 1, 15, value);
                    ret = led_turn_on(&led_red);
                     
                    ret = dc_motor_move_left(&motor_2);
                    __delay_ms(500);
                    ret = led_turn_off(&led_red);
                     
                    ret = dc_motor_stop(&motor_2);
                    __delay_ms(500);
                }
                incorrect_pass = 0;
                ret = lcd_4bit_send_command(&lcd, _LCD_CLEAR);
                ret = lcd_4bit_send_string(&lcd, "Enter Password:");
            }
            /* Clear previous password */
            entered_password = 0;
        }
        /* Taking password from the user */
        if('0' <= keypad_value && keypad_value <= '9')
        {
            number_of_clicks++;
            /* storing entered password */
           entered_password = (entered_password * 10) + (keypad_value - '0');
           ret = lcd_4bit_send_char_data_pos(&lcd, 2, ++lcd_output, keypad_value);
           __delay_ms(400);
           ret = lcd_4bit_send_char_data_pos(&lcd, 2, lcd_output, '*');
        }
        else{ /* Nothing */ }
    }
    
    return (EXIT_SUCCESS);
}

void app_init(void){
    Std_ReturnType ret = E_OK;
    ret = led_intialiaze(&led_green);
    ret = led_intialiaze(&led_red);
    ret = dc_motor_intialize(&motor_1);
    ret = dc_motor_intialize(&motor_2);
    ret = lcd_4bit_intialize(&lcd);
    ret = keypad_intialize(&keypad);
    
}


uint8 keypad_read_value(void){
    uint8 val;
    
    
    ret = keypad_get_value(&keypad,&val);
    __delay_ms(150);
    
    if(val == '\0'){
        return 0;
    }
    uint8 new_val;
    ret = keypad_get_value(&keypad,&new_val);
    
    if(new_val == val){
        return new_val;
    }
    return 0;
}