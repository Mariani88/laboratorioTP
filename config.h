#ifndef CONFIG_H
#define	CONFIG_H
#include <stdbool.h>
int password = 1234;
int time_to_stop =600000;  //600000 = 10 min
bool checkPass(int pass);
void changePass(int pass);

#endif	/* CONFIG_H */

