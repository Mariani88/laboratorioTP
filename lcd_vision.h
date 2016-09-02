#ifndef LCD_VISION_H
#define	LCD_VISION_H
#include "head.h"

typedef enum{
    ACTIVE,DESACTIVE, TRIGGED
} state;

state state_alarm = ACTIVE;
void set_vision();

#endif	/* LCD_VISION_H */

