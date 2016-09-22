#include "lcd_vision.h"
#include "unmc_rtcc_01.h"
#include "keyboard.h"
#include "config.h"
#include <math.h>

void clear(){
    lcd_comand(0b00000001);
    __delay_ms(5);
}

void write_Date(){
    lcd_setcursor_vb(0,0);
    lcd_gotoxy(9,1);
    sprintf(buffer2,"%02u/%02u/%02u",dia,mes,anio);
    lcd_putrs(buffer2);
    sprintf(buffer2,"%02u:%02u",hora,minuto);
    lcd_gotoxy(1,2);
    lcd_putrs(buffer2);
}

void _delay_s(int millis){
    short it = millis/100;
    short index = 1;
    
    for(index = 1; index <= it; index++){
        __delay_ms(98);
    }
}

bool is_not_letter(char input){
    return input != 16 && input != 11 && input !=12 && input!=13;
}

bool not_fill_pass(short digit){
    return digit !=16;
}


void next_code(short *digit, char *input){
    clear_keyboard();
    *digit = *digit + 1;
    lcd_gotoxy(*digit, 2);
    *input = 18;
}

void change_state(){
    switch (state_alarm){
        case DESACTIVE:state_alarm = ACTIVE;
        break;
        case ACTIVE:state_alarm = DESACTIVE;
        break;
        default:state_alarm = DESACTIVE;
    }
}

void review_code(short digit, int pass){
    if(digit == 16){
        if(checkPass(pass)){
            change_state();
        }
    }
}

int obtain_pass(int pass, char input, short *digit){
    
    if(0<input && input<10){
        pass = pass + input * pow(10, 15 - *digit);
        next_code(digit, &input);
    }
    return pass;
}

void set_desactive_vision(short digit){
    lcd_gotoxy(7,2);
    lcd_putrs("pass:____");
    lcd_gotoxy(digit,2);
    lcd_setcursor_vb(1,1);
}

void input_password(){
    short digit = 12;
    int pass = 0;
        
    set_desactive_vision(digit);
    char input = read_keyboard(); 
        
    while(is_not_letter(input) && not_fill_pass(digit)){
        pass = obtain_pass(pass,input,&digit);
        input = read_keyboard();
        review_code(digit, pass);
    }
}

void twinkle(){
    char input = 1;
    int time = 0; 
    
    while(input != 16 && time < time_to_stop){  
        _delay_s(200);
        lcd_gotoxy(7,2);
        LED_2_Off;
        LED_3_On;
        lcd_putrs("WARNING!!!");
        _delay_s(200);
        LED_3_Off;
        LED_2_On;
        lcd_gotoxy(7,2);
        lcd_putrs("          ");
        input = read_keyboard();
        time +=400;
    }
    
    clear_keyboard();
    
    if(time >= time_to_stop){
        state_alarm = ACTIVE;
    }else{
        input_password();
    }
}






void set_vision(){
    clear();
    write_Date();
    lcd_gotoxy(1,1);
    
    switch (state_alarm){
        case ACTIVE:lcd_putrs("ON");
            LED_3_On;
            //input_password();
        break;
        
        case DESACTIVE:lcd_putrs("OFF");
            LED_3_Off;
            input_password();
        
        break;
        default:lcd_putrs("TRIGGED");
            twinkle();
            //input_password();
    }
    
}