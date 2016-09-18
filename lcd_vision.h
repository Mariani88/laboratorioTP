#ifndef LCD_VISION_H
#define	LCD_VISION_H
#include "head.h"
#include "config.h"

void set_vision();
void clear();
void write_Date();
void _delay_s(int millis);
bool is_not_letter(char input);
bool not_fill_pass(short digit);
void next_code(short *digit, char *input);
void review_code(short digit, int pass);
int obtain_pass(int pass, char input, short *digit);

#endif	/* LCD_VISION_H */

