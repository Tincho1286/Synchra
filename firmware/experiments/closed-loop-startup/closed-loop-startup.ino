float arranque = 30;
byte valor = 30;
byte valorf = 30;
byte vfinal = 127;
byte Paso = 0;
int i;
unsigned long TiempoArranque = 0;
bool Motor;
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
  ACSR = 0x10;           //Reseteamos la bandera del comparador
}
void loop() {
  TiempoArranque = 6000;
  while (TiempoArranque > 50) {
    OCR1A = arranque;           //Colocamos el valor del PWM para D9
    OCR1B = arranque;           //Colocamos el valor del PWM para D14
    OCR2A = arranque;           //Colocamos el valor del PWM para D11
    SiguientePaso();
    delayMicroseconds(TiempoArranque);
    Paso++;
    Paso %= 6;
    TiempoArranque = TiempoArranque - 20;
  }
  SiguientePaso();
  ACSR |= 0x08;
  delay(3000);
  Motor = 1;
  while (Motor){
    OCR1A = valorf;           //Colocamos el valor del PWM para D9
    OCR1B = valorf;           //Colocamos el valor del PWM para D10
    OCR2A = valorf;           //Colocamos el valor del PWM para D11
    delay(100);
    valorf = valorf + 1;
    if (valorf == vfinal + 1){
      valorf = vfinal;
    }
  }
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
      BEMF_C_RISING();
      break;
    case 1:
      AH_CL();
      BEMF_B_FALLING();
      break;
    case 2:
      BH_CL();
      BEMF_A_RISING();
      break;
    case 3:
      BH_AL();
      BEMF_C_FALLING();
      break;
    case 4:
      CH_AL();
      BEMF_B_RISING();
      break;
    case 5:
      CH_BL();
      BEMF_A_FALLING();
      break;
  }
}
ISR(ANALOG_COMP_vect) {  //Interrupcion para cambio de paso en la secuencia
  for (i = 0; i < 10; i++){
    if (Paso & 1) {        //Si la secuencia esta en un numero impar se cumple (1, 3, 5)
      if (!(ACSR & B00100000)) {
      i -= 1;
      }
    }
    else {  //Si la secuencia es par se cumple (0, 2, 6)
      if ((ACSR & B00100000)) {
      i -= 1;
      }
    }
  }
  SiguientePaso();  //Se coloca el siguiente paso
  Paso++;  //Se agrega uno a la secuencia
  Paso %= 6;
}
void BEMF_A_RISING() {
  ADCSRA = (0 << ADEN);  //Se deshabilita el modulo ADC
  ADCSRB = (1 << ACME);  // Se activa el multiplexor
  ADMUX = 2;             // Se selecciona A2 como entrada
  ACSR |= 0x03;          // Se coloca la interrupcion en rising edge
}
void BEMF_A_FALLING() {
  ADCSRA = (0 << ADEN);
  ADCSRB = (1 << ACME);
  ADMUX = 2;      // Se selecciona A2 como entrada
  ACSR &= ~0x01;  // Se coloca la interrupcion en falling edge
}
void BEMF_B_RISING() {
  ADCSRA = (0 << ADEN);
  ADCSRB = (1 << ACME);
  ADMUX = 1;     // Se selecciona A1 como entrada
  ACSR |= 0x03;  // Se coloca la interrupcion en rising edge
}
void BEMF_B_FALLING() {
  ADCSRA = (0 << ADEN);
  ADCSRB = (1 << ACME);
  ADMUX = 1;      // Se selecciona A1 como entrada
  ACSR &= ~0x01;  // Se coloca la interrupcion en falling edge
}
void BEMF_C_RISING() {
  ADCSRA = (0 << ADEN);
  ADCSRB = (1 << ACME);
  ADMUX = 0;     // Se selecciona A0 como entrada
  ACSR |= 0x03;  // Se coloca la interrupcion en rising edge
}
void BEMF_C_FALLING() {
  ADCSRA = (0 << ADEN);
  ADCSRB = (1 << ACME);
  ADMUX = 0;      // Se selecciona A0 como entrada
  ACSR &= ~0x01;  // Se coloca la interrupcion en falling edge
}