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

void review_code(short digit, int pass){
    if(digit == 16){
        if(checkPass(pass)){
            state_alarm = ACTIVE;
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


void twinkle(){
    char input = 1;
    
    while(input != 16){
        _delay_s(500);
        lcd_gotoxy(7,2);
        lcd_putrs("WARNING!!!");
        _delay_s(500);
        lcd_gotoxy(7,2);
        lcd_putrs("          ");
        input = read_keyboard();
    }
    clear_keyboard();
}

void set_desactive_vision(short digit){
    lcd_gotoxy(7,2);
    lcd_putrs("pass:____");
    lcd_gotoxy(digit,2);
    lcd_setcursor_vb(1,1);
}

void set_vision(){
    clear();
    write_Date();
    lcd_gotoxy(1,1);
    
    switch (state_alarm){
        case ACTIVE:lcd_putrs("ON");
        break;
        
        case DESACTIVE:lcd_putrs("OFF");
        short digit = 12;
        int pass = 0;
        set_desactive_vision(digit);
        
        char input = read_keyboard(); 
        
        while(is_not_letter(input) && not_fill_pass(digit)){
            pass = obtain_pass(pass,input,&digit);
            input = read_keyboard();
            review_code(digit, pass);
        }
        
        break;
        default:lcd_putrs("TRIGGED");
                twinkle();
                //PEDIR PASSWORD ACA PARA DESACTIVAR
                short digit = 12;
                int pass = 0;
                set_desactive_vision(digit);
        
                char input = 18; 
        
                while(is_not_letter(input) && not_fill_pass(digit)){
                    pass = obtain_pass(pass,input,&digit);
                    input = read_keyboard();
                    review_code(digit, pass);
                }
    }
}