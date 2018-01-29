#include <stdlib.h>
#include <stdio.h>
#include "SoftwareSerial.h"

//RECEPTOR2 É O ARDUINO SEM LEDS
//RX: Arduino pin 2, XBee pin DOUT. TX: Arduino pin 3, XBee pin DIN;

SoftwareSerial XBee(2,3);

byte tx_data[6];
byte rx_data[6];
int n = 0;
byte LEITURA_COM[6] = { 0xAB, 0xAA, 0x02, 0x03, 0xAA, 0x07};
                      //  0    1      2     3     4     5
// 0 - Inicio do protocolo
// 1 - Tipo do produto
// 2 - Tipo do protocolo
// 3 - Leitura do sinal
// 4 - tipo de comando (0xAA -> printa uma string na serial);
// 5 - Fim do protocolo

void setup (){
  XBee.begin(9600);
  Serial.begin(9600);
  n = 0;
}

void loop(){
  if(XBee.available() > 0){
    
    rx_data[n] = XBee.read(); //ler da serial
    n++;
      
      if(n>5){

            if((rx_data[0] == LEITURA_COM[0]) && (rx_data[1] == LEITURA_COM[1]) && (rx_data[2] == LEITURA_COM[2]) &&
               (rx_data[3] == LEITURA_COM[3]) && (rx_data[4] == LEITURA_COM[4]) && (rx_data[5] == LEITURA_COM[5]))
               {
                
                Serial.print("OK!");
              //novo
                  tx_data[0] = 0xEC;
                  tx_data[1] = 0x0A;
                  tx_data[2] = 0x01;
                  tx_data[3] = 0x01;
                  tx_data[4] = 0x0C;
                  tx_data[5] = 0x05;
                  XBee.write(tx_data, sizeof(tx_data));
                //novo
                
                //limpar o buffer tx
                for(int i = 0; i < 6; i++){
                  tx_data[i] = 0;
                  }

                 //limpar o buffer rx
                 for(int i = 0; i < 6; i++){
                  rx_data[i] = 0;
                  }
               }
              n = 0;
            }
    
  }
    
  }
  



