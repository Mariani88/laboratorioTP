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
    
    //PEDIR PASSWORD ACA PARA DESACTIVAR
    state_alarm = ACTIVE;
}

void set_vision(){
    clear();
    write_Date();
    lcd_gotoxy(1,1);
    
    switch (state_alarm){
        case ACTIVE:lcd_putrs("ON");
        break;
        case DESACTIVE:lcd_putrs("OFF");
        lcd_gotoxy(7,2);
        lcd_putrs("pass:____");
        short digit = 12;
        lcd_gotoxy(digit,2);
        lcd_setcursor_vb(1,1);
        
        char input = read_keyboard(); 
        int pass = 0;
        
        while(input != 16 && input != 11 && input !=12 && input!=13 && digit !=16){
            
            if(0<input && input<10){
                
                pass = pass + input * pow(10, 15 - digit);
    
                clear_keyboard();
                digit++;
                lcd_gotoxy(digit, 2);
                input = 18;
            }
            input = read_keyboard();
            
            if(digit == 16){
                if(checkPass(pass)){
                    state_alarm = ACTIVE;
                    
                }
            }
        }
        
        break;
        default:lcd_putrs("TRIGGED");
                twinkle();
    }
}