#include <RF24.h>
#include <RF24_config.h>
#include <nRF24L01.h>
#include <printf.h>
const uint64_t codigo = 0xE8E8F0F0E1LL;                   //Codigo Transmisor/Receptor
RF24 Emisora(9,10);
struct Datos {                                            //Estructura de datos
  byte ch1;
  byte ch2;
};
Datos datosE;
void setup() {
  Emisora.begin();
  Emisora.setAutoAck(false);
  Emisora.setDataRate(RF24_250KBPS);
  Emisora.openWritingPipe(codigo);
  datosE.ch1 = 0;                                         //Se resetean los canales
  datosE.ch2 = 127;
}

void loop() {
datosE.ch1 = map( analogRead(A0), 0, 1024, 0, 255);       //Se leen las entradas y escriben los datos
datosE.ch2 = map( analogRead(A2), 0, 1024, 0, 255);
Emisora.write(&datosE, sizeof(Datos));
}
