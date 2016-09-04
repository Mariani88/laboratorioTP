#include "lcd_vision.h"
#include "unmc_rtcc_01.h"

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


void set_vision(){
    clear();
    lcd_gotoxy(1,1);
    
    switch (state_alarm){
        case ACTIVE:lcd_putrs("ON");
        break;
        case DESACTIVE:lcd_putrs("OFF");
        break;
        default:lcd_putrs("TRIGGED"); 
    }
    
    write_Date();
}