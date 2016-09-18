

#ifndef HEAD_H
#define	HEAD_H

#include <xc.h>
#include<delays.h>
#include<stdio.h>
#include <unmc_lcd_216.h>
#include <unmc_config_01.h>
#include <unmc_inout_02.h>
#include <unmc_rtcc_01.h>

typedef enum {
    ACTIVE, DESACTIVE, TRIGGED,
} state;

state state_alarm = ACTIVE;

#endif	/* HEAD_H */

