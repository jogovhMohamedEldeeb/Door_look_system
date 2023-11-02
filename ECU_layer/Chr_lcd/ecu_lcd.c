/* 
 * File:   ecu_lcd.c
 * Author: m7md
 *
 * Created on 18 August 2023, 09:33
 */

#include "ecu_lcd.h"


static Std_ReturnType lcd_4bit_send_enable(const chr_lcd_4bit_t *lcd);
static Std_ReturnType lcd_4bit_send(const chr_lcd_4bit_t *lcd,uint8 data_command);
static Std_ReturnType lcd_4bit_set_cursor(const chr_lcd_4bit_t *lcd,uint8 row, uint8 column);

Std_ReturnType lcd_4bit_intialize(const chr_lcd_4bit_t *lcd){
    Std_ReturnType ret = E_OK;
    uint8 l_counter = 0;
    if(lcd == NULL){
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_intialize(&(lcd->lcd_rs));
        ret = gpio_pin_intialize(&(lcd->lcd_en));
       for(l_counter = 0; l_counter < 4; l_counter++){
           ret = gpio_pin_intialize(&(lcd->lcd_data[l_counter]));
       }
        __delay_ms(20);
        ret = lcd_4bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        __delay_ms(5);
        ret = lcd_4bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        __delay_us(150);
        ret = lcd_4bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        
        ret = lcd_4bit_send_command(lcd, _LCD_CLEAR);
        ret = lcd_4bit_send_command(lcd, _LCD_RETURN_HOME);
        //ret = lcd_4bit_send_command(lcd, _LCD_ENTRY_MODE_INC_SHIFT_OFF);
        ret = lcd_4bit_send_command(lcd, _LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF);
        ret = lcd_4bit_send_command(lcd, _LCD_4BIT_MODE_2_LINE);
        ret = lcd_4bit_send_command(lcd, 0x80);
    }
    return ret;
}

Std_ReturnType lcd_4bit_send_command(const chr_lcd_4bit_t *lcd, uint8 command){
    Std_ReturnType ret = E_OK;
    if(lcd == NULL){
        ret = E_NOT_OK;
    }
    else{
        /* write logic (0) to 'RS' to select 'Instruction Register' */
        ret = gpio_pin_write_logic(&(lcd->lcd_rs),GPIO_LOW);
        /* Send command through data lines*/
        ret = lcd_4bit_send(lcd,command >> 4);
        /* Send enable signal on the 'E' pin*/
        ret = lcd_4bit_send_enable(lcd);
        /* Send command through data lines*/
        ret = lcd_4bit_send(lcd,command);
        /* Send enable signal on the 'E' pin*/
        ret = lcd_4bit_send_enable(lcd);
    }
    return ret;
}

Std_ReturnType lcd_4bit_send_char_data(const chr_lcd_4bit_t *lcd, uint8 data){
    Std_ReturnType ret = E_OK;
    if(lcd == NULL){
        ret = E_NOT_OK;
    }
    else{
        /* write logic (1) to 'RS' to select 'Instruction Register' */
        ret = gpio_pin_write_logic(&(lcd->lcd_rs),GPIO_HIGH);
        /* Send data through data lines*/
        ret = lcd_4bit_send(lcd,data >> 4);
        /* Send enable signal on the 'E' pin*/
        ret = lcd_4bit_send_enable(lcd);
        /* Send data through data lines*/
        ret = lcd_4bit_send(lcd,data);
        /* Send enable signal on the 'E' pin*/
        ret = lcd_4bit_send_enable(lcd);
    }
    return ret;
}

Std_ReturnType lcd_4bit_send_char_data_pos(const chr_lcd_4bit_t *lcd,uint8 row, uint8 column, uint8 data){
    Std_ReturnType ret = E_OK;
    if(lcd == NULL){
        ret = E_NOT_OK;
    }
    else{
        ret = lcd_4bit_set_cursor(lcd,row,column);
        ret = lcd_4bit_send_char_data(lcd,data);
    }
    return ret;
}

Std_ReturnType lcd_4bit_send_string(const chr_lcd_4bit_t *lcd, uint8 *str){
    Std_ReturnType ret = E_OK;
     
   if((lcd == NULL) || (str == NULL)){
        ret = E_NOT_OK;
    }
    else{
       while(*str != '\0'){
           ret = lcd_4bit_send_char_data(lcd,*str++);
       }
    }
    return ret;
}
Std_ReturnType lcd_4bit_send_string_pos(const chr_lcd_4bit_t *lcd, uint8 row, uint8 column, uint8 *str){
    Std_ReturnType ret = E_OK;
    if((lcd == NULL) || (str == NULL)){
        ret = E_NOT_OK;
    }
    else{
         ret = lcd_4bit_set_cursor(lcd,row,column);
         while(*str != '\0'){
           ret = lcd_4bit_send_char_data(lcd,*str++);
       }
    }
    return ret;
}
Std_ReturnType lcd_4bit_send_custom_char(const chr_lcd_4bit_t *lcd, uint8 row, uint8 column, 
                                         const uint8 _chr[], uint8 mem_pos){
    Std_ReturnType ret = E_OK;
    uint8 l_counter = 0;
    if(lcd == NULL){
        ret = E_NOT_OK;
    }
    else{
        ret = lcd_4bit_send_command(lcd,(_LCD_CGRAM_START+(mem_pos*8)));
        for(l_counter = 0; l_counter < 4; l_counter++){
            ret = lcd_4bit_send_char_data(lcd,_chr[l_counter]);
       }
        ret = lcd_4bit_send_char_data_pos(lcd,row,column,mem_pos);
    }
    return ret;
}

static Std_ReturnType lcd_4bit_send_enable(const chr_lcd_4bit_t *lcd ){
    Std_ReturnType ret = E_OK;
    ret = gpio_pin_write_logic(&(lcd->lcd_en),GPIO_HIGH);
    __delay_us(5);
    ret = gpio_pin_write_logic(&(lcd->lcd_en),GPIO_LOW);
    return ret;
}

static Std_ReturnType lcd_4bit_send(const chr_lcd_4bit_t *lcd,uint8 data_command){
    Std_ReturnType ret = E_OK;
    ret = gpio_pin_write_logic(&(lcd->lcd_data[0]), (data_command >> 0) & (uint8)0x01);
    ret = gpio_pin_write_logic(&(lcd->lcd_data[1]), (data_command >> 1) & (uint8)0x01);
    ret = gpio_pin_write_logic(&(lcd->lcd_data[2]), (data_command >> 2) & (uint8)0x01);
    ret = gpio_pin_write_logic(&(lcd->lcd_data[3]), (data_command >> 3) & (uint8)0x01);
    return ret;
}

static Std_ReturnType lcd_4bit_set_cursor(const chr_lcd_4bit_t *lcd,uint8 row, uint8 column){
    Std_ReturnType ret = E_OK;
    switch(row){
        case ROW1 : ret = lcd_4bit_send_command(lcd,(0x80 + --column));break;
        case ROW2 : ret = lcd_4bit_send_command(lcd,(0xc0 + --column));break;
        case ROW3 : ret = lcd_4bit_send_command(lcd,(0x94 + --column));break;
        case ROW4 : ret = lcd_4bit_send_command(lcd,(0xd4 + --column));break;
        default : ;
    }
    return ret;
}