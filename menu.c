/* 
 * File:   menu.c
 * Author: seba
 *
 * Created on 9 de septiembre de 2016, 17:54
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "menu.h"
#include "lcd_vision.h"

char menu = 1;
int newpass = 0;

bool input_old_pass(){
    short digit = 12;
    int pass = 0;
    char input = read_keyboard(); 
    while(not_fill_pass(digit)){
        if(0<input && input<10){
            pass = pass + input * pow(10, 15 - digit);
            lcd_gotoxy(digit,1);
            _delay_s(50);
            clear_keyboard();
            digit = digit +1;
            input = 18;
        }
        
        input = read_keyboard();
    }
    return checkPass(pass);
}

void show_success(){
    clear();
    lcd_gotoxy(1,1);
    lcd_putrs("pass success");
    lcd_gotoxy(1,2);
    lcd_putrs("changed");
    _delay_s(1000);
}

void show_error(){
    clear();
    lcd_gotoxy(1,1);
    lcd_putrs("old pass wrong");
    lcd_gotoxy(1,2);
    lcd_putrs("nothing changed");
    _delay_s(1000);
}

void input_new_pass(){
    short digit = 12;
    newpass = 0;
    char input = read_keyboard(); 
    while(not_fill_pass(digit)){
        if(0<input && input<10){
            newpass = newpass + input * pow(10, 15 - digit);
            lcd_gotoxy(digit,2);
            _delay_s(50);
            clear_keyboard();
            digit = digit +1;
            input = 18;
        }
        input = read_keyboard();
    }
}

void ver_opcion_cambio(){
    clear();
    bool old_correct = false;
    lcd_gotoxy(2,1);
    lcd_putrs("Old pass:____");
    lcd_gotoxy(2,2);
    lcd_putrs("New pass:____");
    lcd_gotoxy(11,1);
    old_correct = input_old_pass();
    lcd_gotoxy(11,2);
    input_new_pass();
    char input = 0;
    while (input != 16){
        input = read_keyboard();
    }
    if (old_correct)
    {
        changePass(newpass);
        show_success();
    }else{
        show_error();
    }
}

void ver_info(){
    clear();
    char input = 18;
    while (input != 16){
        lcd_gotoxy(1,1);
        lcd_putrs("Sensor: ");
        sprintf(buffer2,"%02u",sensorDisparado);
        lcd_putrs(buffer2);
        lcd_gotoxy(1,2);
        lcd_putrs("Date:");
        sprintf(buffer2,"%02u/%02u",diaDisparo,mesDisparo);
        lcd_putrs(buffer2);
        lcd_putrs(" ");
        sprintf(buffer2,"%02u:%02u",horaDisparo,minDisparo);
        lcd_putrs(buffer2);
        input = read_keyboard();
    }
    menu = 18;
}


void dispararSensor(int sensor){
    Read_RTC();
    state_alarm = TRIGGED;
    sensorDisparado = sensor;
    diaDisparo = dia;
    mesDisparo = mes;
    horaDisparo = hora;
    minDisparo = minuto;
}


void select_menu(){
    if (state_alarm == DESACTIVE){
        menu = read_keyboard(); 
        switch (menu){
            case 11:ver_opcion_cambio();
                break;
            case 12:configurar_reloj();
            break;
            case 13:ver_info();
            break;
            default: ;
        }
    }else{
        if (state_alarm == ACTIVE){
            menu = read_keyboard(); 
            switch (menu){
                case 11:dispararSensor(1);
                break;
                case 12:dispararSensor(2);
                break;
                case 13:dispararSensor(3);
                break;
                default: ;
            } 
        }
    }    
    menu = 18;
}