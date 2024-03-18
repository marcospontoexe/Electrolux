/*
 * uart.cpp
 *
 *  Created on: Mar 16, 2024
 *      Author: Marcos Santana
 */
#include "uart.h"
#include "analisador.h"
#include <avr/io.h>         // mapeamento dos registradores
#include <avr/interrupt.h>   // mapeamento dos interrupções
#include <Arduino.h>

#define strTamanhoMax 50

//variáveis globais
char strRx[strTamanhoMax];
volatile uint8_t strCont = 0;
volatile bool strCompleta = false;

/**
 * @brief   Configura os registradores da UART do atmega2560
 * @param   void
 * @return  void
 */
void configUart(void){
  UBRR0 = 103;// Configuração do baud rate da uart 0 (9600 bps)
  UCSR0B = 0b10011000;  //controle da  uart (habilita interrupções por recebimento de mensagem, habilita recepção etransmissão)
  UCSR0C = 0b00000110;// define o modo de funcionamento ( modo assincrono, sem bit de paridade, 1 sotp bit, frame de 8 bits)
  sei();    // habilita a interrupção global
  
} 

/**
 * @brief   função para enviar um char pela uart
 * @param   unsigned char
 * @return  void
 */
void uartTx(unsigned char data) {
  while (!(UCSR0A & (1 << UDRE0))); // Aguarda o buffer de transmissão ficar vazio
  UDR0 = data; // Transmite os dados
}

/**
 * @brief   função para enviar uma string pela uart
 * @param   char*
 * @return  void
 */
void uartTxStr(char *str) {
  while (*str) { // Enquanto não atingir o fim da string ('\0')
    uartTx(*str++); // Transmite o caractere e avança para o próximo
  }
}

/**
 * @brief   rotina de interrupção gerada ao receber um frame
 * @param   void
 * @return  void
 */
ISR(USART0_RX_vect){
  char data = 0;      //variável de 8 bits para guardar o frame de dados recebido
  data = UDR0;        // recebe o frame de dados do buffer 

  if (data == '\n') { // Se o caractere de término de linha for recebido
    strRx[strCont] = '\0\n'; // Adiciona o terminador de string e salto de linha
    strCompleta = true; // Marca a string como completa
    strCont = 0;
  } 
  else {
    strRx[strCont++] = data; // Adiciona o caractere ao array
    if(strCont >= strTamanhoMax-1) { // Se excedeu o tamanho máximo
      strCont = strTamanhoMax - 1; // Limita o índice para evitar estouro
    }
  } 

  if(strCompleta == true){
    char substrings[2][50]; // Array para armazenar as substrings
    memset(substrings[0], '\0', sizeof(substrings[0]));  // limpa a substring
    memset(substrings[1], '\0', sizeof(substrings[1]));  // limpa a substring     
    trataStrig(strRx, substrings);      
    memset(strRx, '\0', sizeof(strRx)); //limpa a string
    testeUnitario(substrings[0], substrings[1]);    
    strCompleta = false;
    
  }
  //UDR0 = data;        // o uart1 renvia o mesmo valor recebido (loopback)

}
