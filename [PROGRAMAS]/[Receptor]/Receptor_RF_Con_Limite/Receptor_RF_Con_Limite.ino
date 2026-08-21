#include <Servo.h>
#include <RF24.h>
#include <RF24_config.h>
#include <nRF24L01.h>
#include <printf.h>
#define limite 1600 //Limite del 60%
const uint64_t codigo = 0xE8E8F0F0E1LL;    //Codigo de Transmisor/Receptor  
RF24 Receptora(9,10);
struct Datos {                             //Estructura de datos
  byte ch1;
  byte ch2;
};
Datos datosR;
Servo canal_1;                             //Se declaran las salidas como "Servo" para convertirlas en PWM
Servo canal_2;
int ch1_valor = 0;
int ch2_valor = 0;
unsigned long TiempoR = 0;                 //Tiempo en el cual se recivio el mensaje
unsigned long Tiempo = 0;                  //Tiempo actual
void setup() {
  canal_1.attach(8);
  canal_2.attach(4);
  datosR.ch1 = 0;                          //Se resetean los canales
  datosR.ch2 = 127;
  Receptora.begin();
  Receptora.setAutoAck(false);
  Receptora.setDataRate(RF24_250KBPS);  
  Receptora.openReadingPipe(1,codigo);
  Receptora.startListening();
}

void loop() {
  Recibir();
  Tiempo = millis();
  if (Tiempo - TiempoR > 1200){            //Si no se recibe señal durante un tiempo se resetean los canales
    datosR.ch1 = 0;
    datosR.ch2 = 127;
  }
  ch1_valor = map(datosR.ch1, 8, 238, 1000, limite);
  if (ch1_valor < 1000){
    ch1_valor = 1000;
  }
  else if (ch1_valor > 2000){
    ch1_valor = 2000;
  }
  ch2_valor = map(datosR.ch2, 0, 255, 14, 55);
  canal_1.writeMicroseconds(ch1_valor);
  canal_2.write(ch2_valor);
}
void Recibir() {                        //Funcion para recibir los datos
  while (Receptora.available()) {
  Receptora.read(&datosR, sizeof(Datos));
  TiempoR = millis();
}}