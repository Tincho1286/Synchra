float arranque = 100;
byte valor = 50;
byte Paso = 0;
int a = 700;
unsigned long TiempoArranque = 0;
void setup() {
  TCCR1A = 0;              //Desactivado del funcionamiento del timer 1 con control de PWM
  TCCR1B = 0x01;           //Desactivado del "Prescaler" del timer 1
  TCCR2A = 0;              //Desactivado del funcionamiento del timer 2 con control de PWM
  TCCR2B = 0x01;           //Desactivado del "Prescaler" del timer 2
  DDRD |= B00011100;
  DDRB |= B11011110;
  PORTD = B00000000;
  PORTB &= B11110001;
  OCR1A = valor;  //Colocamos el valor del PWM para D9
  OCR1B = valor;  //Colocamos el valor del PWM para D10
  OCR2A = valor;  //Colocamos el valor del PWM para D11
  TiempoArranque = 10000;   
  while (TiempoArranque > 700) {
    OCR1A = arranque;           //Colocamos el valor del PWM para D9
    OCR1B = arranque;           //Colocamos el valor del PWM para D14
    OCR2A = arranque;           //Colocamos el valor del PWM para D11
    delayMicroseconds(TiempoArranque);
    SiguientePaso();
    arranque -= 0.05;
    Paso++;
    Paso %= 6;
    TiempoArranque = TiempoArranque - 10;
  }
  OCR1A = valor;           //Colocamos el valor del PWM para D9
  OCR1B = valor;           //Colocamos el valor del PWM para D14
  OCR2A = valor;           //Colocamos el valor del PWM para D11
}
void loop() {
    SiguientePaso();
    delayMicroseconds(a);
    Paso++;
    Paso %= 6; 
}

void AH_BL() {
  PORTD = B00011000;  //Se coloca D3 en alto (BL)
  TCCR2A = 0;
  TCCR1A = 0x81;  //Se activa OC1A (D9) en modo PWM de 8 Bits (D9 = 0 cuando el timer llega a OC1A en subida y D9 = 1 cuando el timer llega a OC1A en bajada)
}
void AH_CL() {
  PORTD = B00010100;  //Se coloca D2 en alto (CL)
  TCCR2A = 0;
  TCCR1A = 0x81;  //Se activa OC1A (D9) en modo PWM de 8 Bits (D9 = 0 cuando el timer llega a OC1A en subida y D9 = 1 cuando el timer llega a OC1A en bajada)
}
void BH_CL() {
  PORTD = B00001100;  //Se coloca D2 en alto (CL)
  TCCR2A = 0;
  TCCR1A = 0x21;  //Se activa OC1B (D10) en modo PWM de 8 Bits (D10 = 0 cuando el timer llega a OC1A en subida y D10 = 1 cuando el timer llega a OC1A en bajada)
}
void BH_AL() {
  PORTD = B00011000;  //Se coloca D4 en alto (AL)
  TCCR2A = 0;
  TCCR1A = 0x21;  //Se activa OC1B (D10) en modo PWM de 8 Bits (D10 = 0 cuando el timer llega a OC1A en subida y D10 = 1 cuando el timer llega a OC1A en bajada)
}
void CH_AL() {
  PORTD = B00010100;  //Se coloca D4 en alto (AL)
  TCCR1A = 0;
  TCCR2A = 0x81;  //Se activa OC2A (D11) en modo PWM de 8 Bits (D11 = 0 cuando el timer llega a OC1A en subida y D11 = 1 cuando el timer llega a OC1A en bajada)
}
void CH_BL() {
  PORTD = B00001100;  //Se coloca D3 en alto (BL)
  TCCR1A = 0;
  TCCR2A = 0x81;  //Se activa OC2A (D11) en modo PWM de 8 Bits (D11 = 0 cuando el timer llega a OC1A en subida y D11 = 1 cuando el timer llega a OC1A en bajada)
}
void SiguientePaso() {
  switch (Paso) {
    case 0:
      AH_BL();
      break;
    case 1:
      AH_CL();
      break;
    case 2:
      BH_CL();
      break;
    case 3:
      BH_AL();
      break;
    case 4:
      CH_AL();
      break;
    case 5:
      CH_BL();
      break;
  }
}