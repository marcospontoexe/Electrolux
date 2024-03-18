/*
 * timer.cpp
 *
 *  Created on: Mar 16, 2024
 *      Author: Marcos Santana
 */
#include "timer.h"
#include <avr/io.h>     // mapeamento dos registradores
#include <Arduino.h>
#include "maquinaEstado.h"

//variáveis globais
volatile unsigned int cont_inicial_1 = (65536) - ((1*FOSC)/256);    // para um tempo de estouro de 1 segundo -> 3036
volatile unsigned short int cont_inicial_2 = (256) - ((0.001*FOSC)/128);    // para um tempo de estouro de 1 mili segundo -> 131

/**
 * @brief   Rotina chamada pela interrupção do estouro do timer1
 * @param   void
 * @return  void
 */
ISR(TIMER1_OVF_vect){   //a cada 1s  
  TCNT1 = cont_inicial_1;      // Configura o valor inicial do contador do timer1 para que ocorra um estouro a cada 1 segundo
   
}

/**
 * @brief   Rotina chamada pela interrupção do estouro do timer2
 * @param   void
 * @return  void
 */
ISR(TIMER2_OVF_vect){   //a cada 1s  
  TCNT2 = cont_inicial_2;      // Configura o valor inicial do contador do timer1 para que ocorra um estouro a cada 1 segundo
   
}

/**
 * @brief    Habilita e configura o timer
 * @param   void
 * @return  void
 */
void timerConfigure(void){
  /*-----------CONTAGEM DE ESTOURO DO TIMER 1(16 bits)----
  para um contador de 16 bits
  tempo = (65536 * prescaler) / (Fosc)  
  tempo = (65536 * 256) / (16000000) = 1,048576 s
  ------------------------------------------------------*/

  /*-----------CONTAGEM DE TEMPO DO TIMER 1(16 bits)------
  valor inicial da contagem = (65536) - ((tempo desejado*Fosc)/prescaler)
  estoura a cada 1 s para Fosc de 16Mhz -> valor inicial = (65536) - ((1*16000000)/64) = 3036
  ------------------------------------------------------*/
 
  //*********Configurando o TIMER1**************
  TCCR1A = 0;                //configura timer1 para operação normal pinos OC1A e OC1B desconectados
  TCCR1B = 0b00000100;       //Controla o prescaler do timer1 (prescaler 256)
  TCNT1 = cont_inicial_1;    // Configura o valor inicial do contador do timer1
  TIMSK1 = 0b00000001;       // habilita interrupção por estouro de tempo no timer1  

  //*********Configurando o TIMER2**************
  TCCR2A = 0;                //configura timer1 para operação normal pinos OC1A e OC1B desconectados
  TCCR2B = 0b00000110;       //Controla o prescaler (Prescaling de 128)do timer2
  TCNT2 = cont_inicial_2;    // Configura o valor inicial do contador do timer2
  TIMSK2 = 0b00000001;  // habilita interrupção por estouro de tempo no timer2
}
  
/**
 * @brief   fica travado em um loop até que o contador de segundos seja igual ao ao parâmetro recebido 
 * @param   int
 * @return  void
 */
void timerDelay(unsigned int tempo) {
  unsigned int i;
  for(i = 1; i <= tempo; i++) {        
    while ((TIFR1 & (1 << TOV1)) == 0); // Aguarda o estouro do timer        
    TIFR1 |= (1 << TOV1); // Limpa a flag de overflow do timer
  }
}

/**
 * @brief   fica travado em um loop até que o contador de segundos seja igual ao ao parâmetro recebido 
 * @param   int
 * @return  void
 */
void timerDelayMs(unsigned int tempoMs){
  unsigned int i;
  for(i = 1; i <= tempoMs; i++) {        
    while ((TIFR2 & (1 << TOV2)) == 0); // Aguarda o estouro do timer        
    TIFR2 |= (1 << TOV2); // Limpa a flag de overflow do timer
  }
}
