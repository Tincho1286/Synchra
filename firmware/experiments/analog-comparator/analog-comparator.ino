byte Cambio = 0;
void setup() {
  PRR &= (0 << PRADC);
  ACSR &= B11011111;
  ACSR |= 0x10;           //Reseteamos la bandera del comparador
  ADCSRA = (0 << ADEN);  //Se deshabilita el modulo ADC
  ADCSRB = (1 << ACME);  // Se activa el multiplexor
  ADMUX = B000;
  DDRD |= B00011100;       //Puertos 2, 3 y 4 como salidas (Or Logico)
  DDRB |= B00001111;       //Puertos 8, 9, 10 y 11 como salidas (Or Logico)
  PORTD = B00000000;       //Puertos del 0 al 7 en LOW
  PORTB &= B00110000;      //Puertos 8, 9, 10 y 11 en LOW (And Logico)
  C_RISING();
}

void loop() {
  ACSR |= 0x08;
}
void C_RISING() {
  ACSR |= 0x03;          // Se coloca la interrupcion en rising edge
}
void C_FALLING() {
  ACSR &= ~0x01;  // Se coloca la interrupcion en falling edge
}
ISR(ANALOG_COMP_vect) {  //Interrupcion del Comparador
  digitalWrite(8,HIGH);
  delay(10);
  digitalWrite(8,LOW);
  CambioComp();  //Se coloca la siguiente comparacion
  Cambio++;  //Se agrega uno a la secuencia
  Cambio %= 2;
}
void CambioComp() {
  switch (Cambio) {
    case 0:
      C_RISING();
      break;
    case 1:
      C_FALLING();
      break;
  }
}