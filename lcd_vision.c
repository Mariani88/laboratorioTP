#include "lcd_vision.h"
#include "unmc_rtcc_01.h"
#include "keyboard.h"

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

void _delay_s(int8 seg){
    short it = 10 * seg;
    short index = 1;
    
    for(index = 1; index <= it; index++){
        __delay_ms(98);
    }
}

void twinkle(){
    char input = 1;
    
    while(input != 16){
        input = read_keyboard();
        lcd_gotoxy(7,2);
        lcd_putrs("WARNING!!!");
        _delay_s(1);
        lcd_gotoxy(7,2);
        lcd_putrs("          ");
    }
}

void set_vision(){
    clear();
    write_Date();
    lcd_gotoxy(1,1);
    
    switch (state_alarm){
        case ACTIVE:lcd_putrs("ON");
        break;
        case DESACTIVE:lcd_putrs("OFF");
        break;
        default:lcd_putrs("TRIGGED");
                twinkle();
    }
}