/*
 * maquinaEstado.cpp
 *
 *  Created on: Mar 16, 2024
 *      Author: Marcos Santana
 */
#include "maquinaEstado.h"
#include <Arduino.h>
#include <avr/io.h>     // mapeamento dos registradores
#include "timer.h"

//variáveis globais
volatile unsigned short int estadoAtualPassagens = ESTATE_OFF; // Estado inicial da máquina de estado

/**
 * @brief   máquina de estado do botão
 * @param   void
 * @return  void
 */
void maquinaEstado(void){ 
  
  switch(estadoAtualPassagens){
    
  case ESTATE_OFF:  // estado zero 
    estadoAtualPassagens = ESTATE_ON;
    PORTB = 0b00000100;   // GPIOs de saida do estado on ligado
                     
    break;

  case ESTATE_ON:    // estado um 
    estadoAtualPassagens = ESTATE_PROTECTED;
    PORTB = 0b00001000;   // GPIOs de saida do estado protegido ligado
                
    break;

  case ESTATE_PROTECTED:      // estado dois 
    estadoAtualPassagens = ESTATE_OFF;
    PORTB = 0b00000010;   // GPIOs de saida do estado off ligado
                 
    break;

  default:
  //gera um aviso luminoso de erro
    PORTB = 0b00000000;
    PORTB = 0b00000010;   
    timerDelayMs(50);
    PORTB = 0b00000000;
    timerDelayMs(50);
    PORTB = 0b00000100;  
    timerDelayMs(50);
    PORTB = 0b00000000;
    timerDelayMs(50);
    PORTB = 0b00001000;   
    timerDelayMs(50);
    PORTB = 0b00000000;
    timerDelayMs(50);

    PORTB = 0b00000010;   
    timerDelayMs(50);
    PORTB = 0b00000000;
    timerDelayMs(50);
    PORTB = 0b00000100;  
    timerDelayMs(50);
    PORTB = 0b00000000;
    timerDelayMs(50);
    PORTB = 0b00001000;   
    timerDelayMs(50);
    PORTB = 0b00000000;
    timerDelayMs(50);

    PORTB = 0b00000010;   
    timerDelayMs(50);
    PORTB = 0b00000000;
    timerDelayMs(50);
    PORTB = 0b00000100;  
    timerDelayMs(50);
    PORTB = 0b00000000;
    timerDelayMs(50);
    PORTB = 0b00001000;   
    timerDelayMs(50);
    PORTB = 0b00000000;
    timerDelayMs(50);
  
    break;  
  }
  
}
