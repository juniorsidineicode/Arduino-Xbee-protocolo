//EMISSOR
#include "SoftwareSerial.h"
//EMISSOR É O ARDUINO COM A PROTOBOARD E 1 LED VERMELHO (pin 12) E 1 LED VERDE (pin 10)
// RX: Arduino pin 2, XBee pin DOUT. TX: Arduino pin 3, XBee pin DIN

SoftwareSerial XBee(2,3);

byte rx_data[6];
byte tx_data[6];
byte LEITURA_COM[6] = {0xAB, 0xAA, 0x02, 0x03, 0xAA, 0x07};
byte ACENDE_VERDE[6] = {0xEC, 0x0A, 0x01, 0x01, 0x0C, 0x05};
byte LEITURA_LED[6] = {0xEC, 0x0A, 0x01, 0x01, 0x0B, 0x05};
                       // 0    1     2     3     4     5
// 0 - Inicio do protocolo
// 1 - Tipo do produto
// 2 - Tipo do protocolo
// 3 - Leitura do sinal
// 4 - Porta que está recebendo 
// 5 - Fim do protocolo
boolean toogle = false;
unsigned char vermelho;
unsigned char verde;
int n = 0 ;

void setup(){
  XBee.begin(9600);
  Serial.begin(9600);
  n = 0;
}

void loop(){
//espera comando do teclado mandar p receptor 1 ou 2
  if(Serial.available() > 0){
    char c = Serial.read();
    if ( c == 'F'){

    tx_data[0] = 0xEC;
    tx_data[1] = 0x0A;
    tx_data[2] = 0x01;
    tx_data[3] = 0x01; //MSB
    tx_data[4] = 0x0B; //LSB (LED 11)
    tx_data[5] = 0x05;
    XBee.write(tx_data, sizeof(tx_data));
    }
  
    if ( c == 'S'){
      tx_data[0] = 0xAB;
      tx_data[1] = 0xAA;
      tx_data[2] = 0x02;
      tx_data[3] = 0x03;
      tx_data[4] = 0xAA;
      tx_data[5] = 0x07;
      XBee.write(tx_data, sizeof(tx_data));
    }
  }

  //espera a resposta do receptor
    if(XBee.available () >0){

    rx_data[n] = XBee.read(); //ler da serial;

    n++;

      if(n>5){

        if((rx_data[0] == ACENDE_VERDE[0]) && (rx_data[1] == ACENDE_VERDE[1]) && (rx_data[2] == ACENDE_VERDE[2]) &&
           (rx_data[3] == ACENDE_VERDE[3]) && (rx_data[4] == ACENDE_VERDE[4]) && (rx_data[5] == ACENDE_VERDE[5]))
              {
              vermelho = rx_data[4];

                Serial.print("ok!");
                toogle =! toogle;
                digitalWrite(vermelho, toogle);
                //delay(100);
                
             //limpa o buffer tx
                for(int i = 0; i < 6; i++){
                  tx_data[i] = 0;
                }
              
                //limpa o buffer rx
                 for(int i = 0; i < 6; i++){
                  rx_data[i] = 0;
                }
           }
          n = 0; 
      }
      
    }
    
   }

