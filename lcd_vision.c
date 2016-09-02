#include "lcd_vision.h"


void set_vision(){
    
    if (state_alarm == ACTIVE){
        lcd_gotoxy(1,1);
        lcd_putrs("Alarm on");
    }
    
    if (state_alarm == DESACTIVE){
        lcd_gotoxy(1,1);
        lcd_putrs("Alarm off");
    }
    
    if (state_alarm == TRIGGED){
        lcd_gotoxy(1,1);
        lcd_putrs("Alarm trigged");
    }
    
}