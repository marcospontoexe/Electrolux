/*
   pins.cpp

    Created on: Mar 16, 2024
        Author: Marcos Santana
*/
#include "pins.h"
#include <avr/io.h>     // mapeamento dos registradores do atmega2560-16au
#include <Arduino.h>
#include "maquinaEstado.h"
#include "timer.h"

/**
   @brief   Eventos chamados pelas interrupções
   @param   void
   @return  void
*/
//------------------interrupções-------------------------
// PCINT0_vect monitora as interrupções ocorridas pelos pinos PCINT0 até PCINT7
ISR(PCINT0_vect) { // a interrupção é gerada tanto para borda de subida quando para borda de descida
  delay(500);   //tratamento de debounce
  
  if(!((PINB & 0b00000001) == 0b00000001)){// quando o botão PB0 for para LOW (apenas na borda de descida )   
    maquinaEstado();
    unsigned short int contTimer = 0;     
    while(!((PINB & 0b00000001) == 0b00000001)){  //enquanto o botão estiver pressionado
      if((TIFR1 & (1 << TOV1)) == 1){ // se ocorreu um estouro de timer
        TIFR1 |= (1 << TOV1); // Limpa a flag de overflow do timer
        contTimer++;
      }
    } 
    Serial.print("Tempo em que o botão ficou pressionado: ");
    Serial.print(contTimer);
    Serial.println(" segundos.");
    maquinaEstado();
    timerDelay(10);
    maquinaEstado();
     
  }  
}

/**
   @brief    Configura os pinos inicializando como INPUT e atribui as interrupções em pinos que necessitam
   @param   void
   @return  void
*/
void pinsConfigure(void) {
  // Configura a direção dos GPIOs
  DDRB = 0b00001110;   // GPIOs como pinos de entrada 
  /*
  Configurar todos os pinos não usados como GPIOs de entrada é uma boa maneira de proteger os pinos contra
  um curto cirtuito acidental com o GND. Caso isso ocorra com um GPIO de saida, em teoria, a corrente tende ao infinito
  e isto pode danificar definitivamente o GPIO onde ocorreu o curto circuito com o GND.
  */

  // Configura o estado logico inicial 
  PORTB = 0b00000010;   // GPIOs de saida do estado off ligado (estado inicial)
  /*
  PB1 (led vermelho) indica o STAT_OFF
  PB2 (led verde) indica o STAT_ON
  PB3 (led amarelo) indica o STAT_PROTECTED
  */

  // configura pinos de interrupção
  PCICR = 0b00000001;     // habilita a o registrador PCIE0 (responsável pelos pinos PCINT0 até PCINT7)
  // PCMSK0 é responsável pelos registradores PCINT0 até PCINT7
  PCMSK0 = 0b00000001;      // Interrupção no PCINT0 (pino PB0) habilitada
  sei();      // set Global Interrupt Enable (habilita a chavel geral das interrupções)
}
