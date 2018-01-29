#include <stdlib.h>
#include <stdio.h>
#include "SoftwareSerial.h"

//RECEPTOR1!-> ARDUINO COM 1 LED VERMELHO
//RX: Arduino pin 2, XBee pin DOUT. TX: Arduino pin 3, XBee pin DIN;


SoftwareSerial XBee(2,3);

byte ACENDE_VERDE[6] = { 0xEC, 0x0A, 0x01, 0x01, 0x0C, 0x05 };
byte LEITURA_LED[6] = { 0xEC, 0x0A, 0x01, 0x01, 0x0B, 0x05 };
                        // 0  1     2     3     4     5
// 0 - Inicio do protocolo
// 1 - Tipo do produto
// 2 - Tipo do protocolo
// 3 - Leitura do sinal
// 4 - Porta que está recebendo
// 5 - Fim do protocolo

boolean toggle = false;
unsigned char LED;
//const int LED = 13; 
byte tx_data[6];
byte rx_data[6];
int n = 0;

void setup(){
  XBee.begin(9600);
  Serial.begin(9600);
  n = 0;
}

void loop (){
  if (XBee.available () > 0){
  
  
  
    rx_data[n] = XBee.read(); //ler da serial;
    //Serial.print(rx_data[n],HEX);
    n++;
  
  if (n>5) {
  
   if((rx_data[0] == LEITURA_LED[0]) && (rx_data[1] == LEITURA_LED[1]) && (rx_data[2] == LEITURA_LED[2]) &&
       (rx_data[3] == LEITURA_LED[3]) && (rx_data[4] == LEITURA_LED[4]) && (rx_data[5] == LEITURA_LED[5])) 
 {
 LED = rx_data[4];
 
    //MANDAR ACENDER LED PARA CONFIRMAÇÃO DA CHEGADA DE DADOS;
    tx_data[0] = 0xEC;
    tx_data[1] = 0x0A;
    tx_data[2] = 0x01;
    tx_data[3] = 0x01; //MSB
    tx_data[4] = 0x0C; //LSB (LED 12)
    tx_data[5] = 0x05;
    XBee.write(tx_data, sizeof(tx_data));

  toggle = ! toggle;
  digitalWrite(LED, toggle);
  Serial.print("LED: ");
  Serial.print(LED);
  Serial.print(" , ");
  Serial.print(toggle);
  Serial.println("");


  }
     //limpa o buffer tx
  for(int i = 0; i < 6; i++){
    tx_data[i] = 0;
  }

  //limpa o buffer rx
   for(int i = 0; i < 6; i++){
    rx_data[i] = 0;
   }
   
  n = 0; 
 }
  }

 }
 

