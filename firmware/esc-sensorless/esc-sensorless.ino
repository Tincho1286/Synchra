#include <EEPROM.h>
#define MaximoMotor 255
#define MinimoMotor 35
#define Arranque 35
int PWMmax = 2000;             //Valor PWM maximo por defecto
int PWMmin = 1000;             //Valor PWM minimo por defecto
int PWM;                       //Valor del PWM recibido
int PWMmaxC;                   //Valor para PWM maximo de configuracion
int PWMminC;                   //Valor para PWM minimo de configuracion
bool Encendido;                //Variable para el estado del ESC
bool ConfiguracionPWM;         //Variable para el estado de la configuracion
int CuentaConfig;              //Variable para la espera de la configuracion
byte Paso = 0;                 //Variable que establece el paso de la secuencia
byte VelocidadMotor;           //Variable para la velocidad del motor
unsigned long CuentaActual;    //Variable para la lectura del PWM
unsigned long CuentaAnterior;  //Variable para la lectura del PWM
bool EstadoC;                  //Variable para el estado de la cuenta de PWM
bool Motor;                    //Variable para el estado del motor
int CuentaApagado;             //Variable para el tiempo de apagado del motor
int TiempoArranque;            //Variable para el tiempo de arranque del motor
int i;                         //Variable utilizada para la deteccion de cruce por 0

void setup() {
  if (EEPROM.read(1) != 1) {
    EEPROM.put(2, PWMmax);  //Al ser una variable tipo INT ocupa 4 direcciones (2, 3, 4 y 5)
    EEPROM.put(6, PWMmin);  //Al ser una variable tipo INT ocupa 4 direcciones (6, 7, 8 y 9)
    EEPROM.write(1, 1);
  }
  DDRD |= B00011100;       //Puertos 2, 3 y 4 como salidas (Or Logico)
  DDRB |= B00001110;       //Puertos 9, 10 y 11 como salidas (Or Logico)
  PORTD = B00000000;       //Puertos del 0 al 7 en LOW
  PORTB &= B00110001;      //Puertos 9, 10 y 11 en LOW (And Logico)
  TCCR1A = 0;              //Desactivado del funcionamiento del timer 1 con control de PWM
  TCCR1B = 0x01;           //Desactivado del "Prescaler" del timer 1
  TCCR2A = 0;              //Desactivado del funcionamiento del timer 2 con control de PWM
  TCCR2B = 0x01;           //Desactivado del "Prescaler" del timer 2
  ACSR   = 0x10;           //Reseteamos la bandera del comparador
  PCICR |= (1 << PCIE0);   //Activado de interrupciones en el puerto "B"
  PCMSK0 |= (1 << PCINT0); //Activado de interrupciones en el pin "D8"
  delay(200);
  if (PWM > PWMmin + 500) {
    Encendido = 0;
    while (ConfiguracionPWM == 0) {
      if (PWM > PWMmax) {
        PWMmaxC = PWM;
      }
      if (PWM < 1200) {
        if (CuentaConfig > 1000) {
          PWMminC = PWM;
          EEPROM.put(2, PWMmaxC);
          EEPROM.put(6, PWMminC);
          ConfiguracionPWM = 1;
          Encendido = 1;
        }
        CuentaConfig = CuentaConfig + 1;
        delay(1);
      } 
      else {
       CuentaConfig = 0;
      }
    }
  } 
  else {
   Encendido = 1;
  }
  EEPROM.get(2, PWMmax);
  EEPROM.get(6, PWMmin);
}

void loop() {
  if (PWM > (PWMmin + 115) && Encendido == 1) {
    Motor = 1;
    CuentaApagado = 0;
  }
  if (Motor) {
    Velocidad(Arranque);
    TiempoArranque = 2000;
    while (TiempoArranque > 500) {
      delayMicroseconds(TiempoArranque);
      SiguientePaso();
      Paso++;
      Paso %= 6;
      TiempoArranque = TiempoArranque - 10;
    }
    VelocidadMotor = Arranque;
    SiguientePaso();
    ACSR |= 0x08;     //Activamos la interrupcion del comparador
    while (Motor) {
      PWM = constrain(PWM, PWMmin, PWMmax);
      VelocidadMotor = map(PWM, PWMmin, PWMmax, MinimoMotor, MaximoMotor);
      Velocidad(VelocidadMotor);
      if (PWM < (PWMmin + 30)) {
        if (CuentaApagado > 10000) {
          Motor = 0;
          CuentaApagado = 0;
          PORTD = B00000000;  //Apagado del motor
          PORTB &= B11110001;
          TCCR1A = 0;
          TCCR2A = 0;
        } 
        else {
          CuentaApagado = CuentaApagado + 1;
        }
      }
    }
  }
  if (!Motor) {
    ACSR = B00010000;
    TCCR1A = 0;
    TCCR2A = 0;
    PORTD = B00000000;
    PORTB &= B11110001;
  }
}

ISR(ANALOG_COMP_vect) {  //Interrupcion para cambio de paso en la secuencia
  for (i = 0; i < 10; i++){
    delayMicroseconds(5);
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

ISR(PCINT0_vect) {          //Interrupcion sobre el pin D8 que se activa en un cambio de estado
  CuentaActual = micros();  //Se toma el tiempo actual en microsegundos
  if (PINB & B00000001) {   //Se cumple si D8 esta en alto
    if (EstadoC == 0) {     //Se cumple si antes D8 estaba en bajo
      EstadoC = 1;
      CuentaAnterior = CuentaActual;  //Se guarda la cuenta en otra variable
    }
  } 
  else if (EstadoC == 1) {              //Se cumple si se detecto un cambio y el estado anterior es 1
    EstadoC = 0;                          //Se resetea el estado anterior
    PWM = CuentaActual - CuentaAnterior;  //Se almacena en PWM el valor recibido (Si cuenta anterior 1000 y cuenta actual 1200, la diferencia es 200 y es el valor de pwm recibido)
  }
}

void Velocidad(byte valor) {
  if (valor < MinimoMotor) {  //PWM de 8bits por lo que lo mantenemos minimo en 10
    valor = MinimoMotor;
  }
  if (valor > MaximoMotor) {  //PWM de 8bits por lo que lo mantenemos maximo en 255
    valor = MaximoMotor;
  }
  OCR1A = valor;  //Colocamos el valor del PWM para D9
  OCR1B = valor;  //Colocamos el valor del PWM para D10
  OCR2A = valor;  //Colocamos el valor del PWM para D11
}

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

// ========================================== BEMF ============================================
void BEMF_A_RISING()  { ADCSRA = (0 << ADEN); ADCSRB = (1 << ACME); ADMUX = 2; ACSR |= 0x03; } //Se selecciona A2 como entrada, se coloca la interrupcion en rising edge
void BEMF_A_FALLING() { ADCSRA = (0 << ADEN); ADCSRB = (1 << ACME); ADMUX = 2; ACSR &= ~0x01; } //Se selecciona A2 como entrada, se coloca la interrupcion en falling edge
void BEMF_B_RISING()  { ADCSRA = (0 << ADEN); ADCSRB = (1 << ACME); ADMUX = 1; ACSR |= 0x03; } //Se selecciona A1 como entrada, se coloca la interrupcion en rising edge
void BEMF_B_FALLING() { ADCSRA = (0 << ADEN); ADCSRB = (1 << ACME); ADMUX = 1; ACSR &= ~0x01; } //Se selecciona A1 como entrada, se coloca la interrupcion en falling edge
void BEMF_C_RISING()  { ADCSRA = (0 << ADEN); ADCSRB = (1 << ACME); ADMUX = 0; ACSR |= 0x03; } //Se selecciona A0 como entrada, se coloca la interrupcion en rising edge
void BEMF_C_FALLING() { ADCSRA = (0 << ADEN); ADCSRB = (1 << ACME); ADMUX = 0; ACSR &= ~0x01; } //Se selecciona A0 como entrada, se coloca la interrupcion en falling edge

// ========================= SECUENCIA ========================
void AH_BL() { PORTD = B00011000; TCCR2A = 0; TCCR1A = 0x81; } //Se coloca D3 en alto (BL), se activa OC1A (D9) en modo PWM de 8 Bits (D9 = 0 cuando el timer llega a OC1A en subida y D9 = 1 cuando el timer llega a OC1A en bajada)
void AH_CL() { PORTD = B00010100; TCCR2A = 0; TCCR1A = 0x81; } //Se coloca D2 en alto (CL), se activa OC1A (D9) en modo PWM de 8 Bits (D9 = 0 cuando el timer llega a OC1A en subida y D9 = 1 cuando el timer llega a OC1A en bajada)
void BH_CL() { PORTD = B00001100; TCCR2A = 0; TCCR1A = 0x21; } //Se coloca D2 en alto (CL), se activa OC1B (D10) en modo PWM de 8 Bits (D10 = 0 cuando el timer llega a OC1A en subida y D10 = 1 cuando el timer llega a OC1A en bajada)
void BH_AL() { PORTD = B00011000; TCCR2A = 0; TCCR1A = 0x21; } //Se coloca D4 en alto (AL), se activa OC1B (D10) en modo PWM de 8 Bits (D10 = 0 cuando el timer llega a OC1A en subida y D10 = 1 cuando el timer llega a OC1A en bajada)
void CH_AL() { PORTD = B00010100; TCCR1A = 0; TCCR2A = 0x81; } //Se coloca D4 en alto (AL), se activa OC2A (D11) en modo PWM de 8 Bits (D11 = 0 cuando el timer llega a OC1A en subida y D11 = 1 cuando el timer llega a OC1A en bajada)
void CH_BL() { PORTD = B00001100; TCCR1A = 0; TCCR2A = 0x81; } //Se coloca D3 en alto (BL), se activa OC2A (D11) en modo PWM de 8 Bits (D11 = 0 cuando el timer llega a OC1A en subida y D11 = 1 cuando el timer llega a OC1A en bajada)