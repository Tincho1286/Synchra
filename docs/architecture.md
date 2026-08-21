# Arquitectura

Synchra se organiza en tres dominios que se desarrollan en paralelo.

## ESC sensorless

El núcleo es un controlador BLDC basado en Arduino/ATmega328. El firmware implementa una secuencia de conmutación trifásica y explora la detección de fuerza contraelectromotriz (BEMF) mediante el comparador analógico. Los programas de ensayo documentan etapas de comparación, arranque a lazo abierto, transición y pruebas de lazo cerrado.

## Control remoto

La etapa de radio publicada contiene el prototipo de transmisión y recepción con nRF24L01/RF24. Genera la señal de aceleración para el ESC y la señal de dirección. Se conserva como evidencia de la arquitectura de control y como punto de partida de integración.

## Próxima radio: LoRa 433 MHz

La siguiente actualización incorpora un enlace LoRa de 433 MHz, previsto alrededor de un módulo EBYTE E32 y una antena específica ya seleccionada para el proyecto. Esta integración aún no forma parte del firmware publicado: el código RF24 no debe interpretarse como una implementación LoRa.

## Hardware

`hardware/esc` y `hardware/radio-control` contienen los proyectos KiCad y sus archivos de apoyo. Los esquemáticos están disponibles para revisión; el ruteo y la definición de PCB siguen en evolución.
