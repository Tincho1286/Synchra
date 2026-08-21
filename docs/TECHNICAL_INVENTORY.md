# Inventario tecnico inicial: FluxLink 433

## Fuente de diseno

| Dominio | Archivos principales | Nota |
| --- | --- | --- |
| Plataforma mecanica | 94 STL, STEP y F3D de DukeDoks | Usada para probar el ESC; no forma parte del desarrollo original. |
| Esquematico principal | `PCB.kicad_pro`, `.kicad_sch`, `PCB.csv` | El PCB esta en proceso de diseno; exportaciones existentes son historicas o de trabajo. |
| Esquematico de radio | `PCB Rc.kicad_pro`, `.kicad_sch` | El PCB esta en proceso de diseno. |
| Firmware | 8 sketches Arduino propios | RF, receptor, ESC y pruebas de conmutacion. |
| Referencias ESC | Electronoobs V3/V4 y otros programas | Sirvieron para investigacion; el firmware propio fue escrito desde cero. |

## Componentes relevantes identificados

| Subsistema | Componentes |
| --- | --- |
| Control | ATmega328P, cristales de 16 MHz, EEPROM interna. |
| Radio control | Transmisor LoRa de 433 MHz y control remoto. |
| Potencia | 3 × IR2101, 6 × IRF1404, reguladores LM7805/AMS1117/LM317. |
| Referencia ESC SMD | 3 × IR2101STRPBF, 6 × IRLR7843TRPBF, MP2307DN-LF-Z. |
| Mecanica | PETG y TPU; engranajes metalicos previstos en transmision/diferencial. |

## Pendientes de completar

- Numero de parte, proveedor y disponibilidad de todos los componentes propios.
- Revision del esquematico y criterios de fabricacion para los PCBs aun en diseno.
- Lista de piezas impresas aprobadas, cantidad y material.
- Especificacion de motor, bateria, servo y radio usados en el prototipo.
