#include "pins.h"
#include "timer.h"


void setup() {
  Serial.begin(9600);
  pinsConfigure();    // configura a direção dos pinos e interrupções  
  timerConfigure();   // configura o timer 

}

void loop() {  

}
