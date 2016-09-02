#include "reloj.h"
#include <unmc_rtcc_01.h>
void evalueChanceOfRaw(int8 *x, int8 *y){
	if (*x == 17){
         *x = 1;
         *y = 2;
       }
}
    
void jumpIfNotNumber(int8 *x, int8 y){
	 if(  (*x==11 && y ==1)
       || (*x==14 && y ==1)
	   || (*x==3  && y==2)
       || (*x==6  && y==2)){
         
            lcd_setcursor_vb(0,0);
            *x = *x + 1;
        }
}

void evalueFinal(int8 x,int8 *y){
	if(*y == 2 && x == 9){
            *y = 1;
        }
}


void setClock(int8 x){
    switch (x) {
        case 10:    
          dia++;
          if(dia > 31){
                dia = 1;
          }
          break;
        case 13:
          mes++;
          if(mes > 12){
            mes = 1;
          }
          break;
        case 16:
          anio++;
          break;
        case 2:    
          hora++;
          if(hora > 23){
             hora = 0;
          }
          break;
        case 5:
          minuto++;
            if(minuto > 59){
                minuto = 0;
            }
          break;
        default:
          break;
        }
        Write_RTC();
        __delay_ms(50);
}