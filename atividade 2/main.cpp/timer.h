/*
 * timer.h
 *
 *  Created on: Mar 16, 2024
 *      Author: Marcos Santana
 */
#ifndef TIMER_H
#define TIMER_H

#define FOSC 16000000   // frequencia do cristal oscilador

void timerConfigure(void);
void timerDelay(unsigned int);
void timerDelayMs(unsigned int);

#endif
