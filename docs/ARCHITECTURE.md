# Arquitectura de FluxLink 433

## Flujo funcional

```text
Control remoto -> Transmisor LoRa 433 MHz -> Enlace LoRa -> Receptor
                                                    |-> PWM de acelerador -> ESC -> Motor brushless
                                                    |-> Senal de servo -> Direccion
```

## Radio control LoRa de 433 MHz

El sistema utiliza un transmisor LoRa de 433 MHz y un control remoto para enviar las ordenes de aceleracion y direccion. El receptor debe convertir esas ordenes en PWM de acelerador y senal de servo, con una condicion de seguridad ante perdida de enlace. Las implementaciones de prueba presentes en `[PROGRAMAS]` documentan la evolucion del software y sus referencias tecnicas.

La proxima actualizacion contempla integrar un modulo de la familia **EBYTE E32** para LoRa de 433 MHz. La carpeta local `[ANTENA]` conserva el manual, ejemplos y recursos de encapsulado/PCB de esa familia como base de integracion; la documentacion publica conserva esta decision de diseno y su procedencia.

## ESC

El firmware propio usa un Arduino basado en ATmega328P para:

- Medir el PWM de acelerador mediante interrupcion en D8.
- Conmutar las tres fases a traves de PWM en D9, D10 y D11 y senales de lado bajo.
- Detectar la fuerza contraelectromotriz (BEMF) de la fase flotante usando el comparador analogico interno.
- Ejecutar arranque en lazo abierto y conmutacion por cruces de cero en lazo cerrado.
- Almacenar calibracion de PWM en EEPROM.

El esquema del ESC define un bloque de potencia con tres drivers IR2101 y seis MOSFET IRF1404. El PCB se encuentra en proceso de diseno; no debe presentarse como una placa terminada o fabricada sin validacion electrica completa.

## Plataforma mecanica de prueba

El conjunto mecanico es un modelo de **DukeDoks**, usado para probar el sistema de ESC y radio control. No es parte del desarrollo original de FluxLink 433. Las piezas y sus marcas `OK`, `OLD` o `NADA` se conservan como historial de la plataforma de ensayo.
