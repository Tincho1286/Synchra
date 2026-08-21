byte arranque;
byte valor = 30;
byte vfinal = 250;
volatile byte Paso = 0;
int i;
unsigned long TiempoArranque = 0;
bool Motor;
// ====== NUEVO: variables para lock-in por BEMF ======
volatile unsigned long last_zc_time = 0;
volatile unsigned long zc_period = 0;
volatile unsigned long zc_period_prev = 0;
volatile byte zc_stable_count = 0;
volatile bool zc_locked = false;
volatile bool closed_loop = false;
// ===================================================

void setup() {
  TCCR1A = 0;
  TCCR1B = 0x01;   // Timer1 prescaler = 1
  TCCR2A = 0;
  TCCR2B = 0x01;   // Timer2 prescaler = 1
  DDRD |= B00011100;
  DDRB |= B11011110;
  PORTD = B00000000;
  PORTB &= B11110001;
  OCR1A = 0;
  OCR1B = 0;
  OCR2A = 0;
  ACSR = 0x10;   // limpia bandera del comparador
}

void loop() {
  // ====== RESET ESTADO DE ARRANQUE ======
  zc_locked = false;
  closed_loop = false;
  zc_stable_count = 0;
  last_zc_time = 0;
  zc_period_prev = 0;
  ACSR |= 0x10;  // limpia bandera
  // ====== OPEN-LOOP FORZADO ======
  TiempoArranque = 9000;
  while (!zc_locked) {
    if      (TiempoArranque > 2500) { arranque = 180; TiempoArranque -= 20; }
    else if (TiempoArranque > 1200) { arranque = 150; TiempoArranque -= 20; }
    else if (TiempoArranque >  10) { arranque = 150; TiempoArranque -= 20; }
    else                            { arranque = 150; TiempoArranque = 100; ACSR |= 0x08; }   // PAR FUERTE FINAL
    OCR1A = OCR1B = OCR2A = arranque;
    SiguientePaso();
    delayMicroseconds(TiempoArranque);
    Paso = (Paso + 1) % 6;
  }
  // ====== HANDOVER LIMPIO ======
  closed_loop = true;
  ACSR |= 0x10;   // limpia bandera
  // ====== TU LAZO CERRADO ORIGINAL ======
  Motor = 1;
  while (Motor) {
    OCR1A = OCR1B = OCR2A = valor;
    delay(100);
    valor++;
    if (valor > vfinal) valor = vfinal;
  }
}

// ========================= SECUENCIA ========================
void AH_BL() { PORTD = B00011000; TCCR2A = 0; TCCR1A = 0x81; } //Se coloca D3 en alto (BL), se activa OC1A (D9) en modo PWM de 8 Bits (D9 = 0 cuando el timer llega a OC1A en subida y D9 = 1 cuando el timer llega a OC1A en bajada)
void AH_CL() { PORTD = B00010100; TCCR2A = 0; TCCR1A = 0x81; } //Se coloca D2 en alto (CL), se activa OC1A (D9) en modo PWM de 8 Bits (D9 = 0 cuando el timer llega a OC1A en subida y D9 = 1 cuando el timer llega a OC1A en bajada)
void BH_CL() { PORTD = B00001100; TCCR2A = 0; TCCR1A = 0x21; } //Se coloca D2 en alto (CL), se activa OC1B (D10) en modo PWM de 8 Bits (D10 = 0 cuando el timer llega a OC1A en subida y D10 = 1 cuando el timer llega a OC1A en bajada)
void BH_AL() { PORTD = B00011000; TCCR2A = 0; TCCR1A = 0x21; } //Se coloca D4 en alto (AL), se activa OC1B (D10) en modo PWM de 8 Bits (D10 = 0 cuando el timer llega a OC1A en subida y D10 = 1 cuando el timer llega a OC1A en bajada)
void CH_AL() { PORTD = B00010100; TCCR1A = 0; TCCR2A = 0x81; } //Se coloca D4 en alto (AL), se activa OC2A (D11) en modo PWM de 8 Bits (D11 = 0 cuando el timer llega a OC1A en subida y D11 = 1 cuando el timer llega a OC1A en bajada)
void CH_BL() { PORTD = B00001100; TCCR1A = 0; TCCR2A = 0x81; } //Se coloca D3 en alto (BL), se activa OC2A (D11) en modo PWM de 8 Bits (D11 = 0 cuando el timer llega a OC1A en subida y D11 = 1 cuando el timer llega a OC1A en bajada)

void SiguientePaso() {
  switch (Paso) {
    case 0: AH_BL(); BEMF_C_RISING();  break;
    case 1: AH_CL(); BEMF_B_FALLING(); break;
    case 2: BH_CL(); BEMF_A_RISING();  break;
    case 3: BH_AL(); BEMF_C_FALLING(); break;
    case 4: CH_AL(); BEMF_B_RISING();  break;
    case 5: CH_BL(); BEMF_A_FALLING(); break;
  }
}

// ================== ISR COMPARADOR ==================
ISR(ANALOG_COMP_vect) {
  unsigned long now = micros();
  // ====== MODO MEDICIÓN (OPEN-LOOP) ======
  if (!closed_loop) {
    zc_period = now - last_zc_time;
    last_zc_time = now;
    if (zc_period_prev > 0) {
      long diff = (long)zc_period - (long)zc_period_prev;
      if (diff < 0) diff = -diff;
      // tolerancia ±20%
      if (diff < (zc_period_prev / 5)) {
        if (zc_stable_count < 20) zc_stable_count++;
      } else {
        zc_stable_count = 0;
      }
      if (zc_stable_count >= 8) {
        zc_locked = true;
      }
    }
    zc_period_prev = zc_period;
    ACSR |= 0x10;  // limpia bandera
    return;
  }
  // ====== TU ISR ORIGINAL (LAZO CERRADO) ======
  for (i = 0; i < 10; i++) {
    if (Paso & 1) {
      if (!(ACSR & B00100000)) i--;
    } else {
      if ((ACSR & B00100000)) i--;
    }
  }
  SiguientePaso();
  Paso = (Paso + 1) % 6;
}

// ========================================== BEMF ============================================
void BEMF_A_RISING()  { ADCSRA = (0 << ADEN); ADCSRB = (1 << ACME); ADMUX = 2; ACSR |= 0x03; } //Se selecciona A2 como entrada, se coloca la interrupcion en rising edge
void BEMF_A_FALLING() { ADCSRA = (0 << ADEN); ADCSRB = (1 << ACME); ADMUX = 2; ACSR &= ~0x01; } //Se selecciona A2 como entrada, se coloca la interrupcion en falling edge
void BEMF_B_RISING()  { ADCSRA = (0 << ADEN); ADCSRB = (1 << ACME); ADMUX = 1; ACSR |= 0x03; } //Se selecciona A1 como entrada, se coloca la interrupcion en rising edge
void BEMF_B_FALLING() { ADCSRA = (0 << ADEN); ADCSRB = (1 << ACME); ADMUX = 1; ACSR &= ~0x01; } //Se selecciona A1 como entrada, se coloca la interrupcion en falling edge
void BEMF_C_RISING()  { ADCSRA = (0 << ADEN); ADCSRB = (1 << ACME); ADMUX = 0; ACSR |= 0x03; } //Se selecciona A0 como entrada, se coloca la interrupcion en rising edge
void BEMF_C_FALLING() { ADCSRA = (0 << ADEN); ADCSRB = (1 << ACME); ADMUX = 0; ACSR &= ~0x01; } //Se selecciona A0 como entrada, se coloca la interrupcion en falling edge
