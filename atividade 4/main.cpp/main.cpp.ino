#include "uart.h"


void setup() {
  configUart();  
  uartTxStr("UART configurada!\n");
  uartTxStr("Padrão de comando a ser enviado:\n");
  uartTxStr("char:int\n");
}

void loop() {

}
