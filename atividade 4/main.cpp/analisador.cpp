/*
 * analisador.cpp
 *
 *  Created on: Mar 16, 2024
 *      Author: Marcos Santana
 */
#include "analisador.h"
#include "uart.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Arduino.h>


//variáveis globais
int comandoA = 0;
int comandoB = 0;
int comandoC = 0;
int comandoD = 0;
int comandoE = 0;

/**
 * @brief   Função para dividir uma string (comando:carga) em duas substrings 
 * @param   char str[], char substrings[][]
 * @return  void
 */
void trataStrig(char str[], char substrings[][50]) {  
  char* delimiter_position = strchr(str, ':');  // Encontra a posição do caractere ':'
  if (delimiter_position == NULL) {
      uartTxStr("Erro: Delimitador ':' não encontrado na string\n");      
      return;
  }

  // Calcula o tamanho da primeira substring e copia
  strncpy(substrings[0], str, delimiter_position - str);
  substrings[0][delimiter_position - str] = '\0';

  // Calcula o tamanho da segunda substring e copia
  strcpy(substrings[1], delimiter_position + 1);
    
}

/**
 * @brief   Função que recebe um comando e o valor de sua carga
 * @param   char, char
 * @return  void
 */
void testeUnitario(char str1[], char str2[]){
  int numeroInt = 0;
  numeroInt = atoi(str2);   //converter a string para um inteiro
  if( (strcmp(str1, "a") == 0) || (strcmp(str1, "A") == 0)){
    comandoA = comandoA + numeroInt;
    uartTxStr(str1);
    uartTx(':');      
    sprintf(str2, "%d", comandoA); // converte inteiro para string
    uartTxStr(str2);
    uartTx('\n');
  }
  else if( (strcmp(str1, "b") == 0) || (strcmp(str1, "B") == 0)){
    comandoB = comandoB + numeroInt;
    uartTxStr(str1);
    uartTx(':');      
    sprintf(str2, "%d", comandoB); // converte inteiro para string
    uartTxStr(str2);
    uartTx('\n');
  }
  else if( (strcmp(str1, "c") == 0) || (strcmp(str1, "C") == 0)){
    comandoC = comandoC + numeroInt;
    uartTxStr(str1);
    uartTx(':');      
    sprintf(str2, "%d", comandoC); // converte inteiro para string
    uartTxStr(str2);
    uartTx('\n');
  }
  else if( (strcmp(str1, "d") == 0) || (strcmp(str1, "D") == 0)){
    comandoD = comandoD + numeroInt;
    uartTxStr(str1);
    uartTx(':');      
    sprintf(str2, "%d", comandoD); // converte inteiro para string
    uartTxStr(str2);
    uartTx('\n');
  }
  else if( (strcmp(str1, "e") == 0) || (strcmp(str1, "E") == 0)){
    comandoE = comandoE + numeroInt;
    uartTxStr(str1);
    uartTx(':');      
    sprintf(str2, "%d", comandoE); // converte inteiro para string
    uartTxStr(str2);
    uartTx('\n');
  }
  else{
    uartTxStr("comando inválido!\n");
    uartTxStr("comandos válidos: a, A, b, B, c, C, d, D, e, E\n");
  }
  
}
