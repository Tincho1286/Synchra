# Arquitectura

Synchra articula el desarrollo de un ESC sensorless, un sistema de control remoto y la electrónica que los integra. El ESC constituye el núcleo de la plataforma, mientras que el enlace de radio permite explorar el envío de las órdenes de control. Ambos se encuentran en fase experimental y se apoyan en proyectos de hardware que continúan en evolución.

## ESC sensorless

El controlador BLDC está basado en Arduino/ATmega328. Su firmware implementa una secuencia de conmutación trifásica y explora la detección de fuerza contraelectromotriz (BEMF) mediante el comparador analógico, con el objetivo de estudiar el control del motor sin sensores de posición.

Para abordar este desarrollo por etapas, los programas de ensayo de [`firmware/experiments/`](../firmware/experiments/) separan las pruebas del comparador, el arranque en lazo abierto, la transición y los ensayos de lazo cerrado. Estos programas complementan el firmware de [`firmware/esc-sensorless/`](../firmware/esc-sensorless/) y registran distintas aproximaciones experimentales; ninguno constituye una versión final.

## Control remoto y prototipo RF24

El sistema de control remoto complementa al ESC mediante las señales de aceleración y dirección. La etapa publicada en [`firmware/radio-prototype-rf24/`](../firmware/radio-prototype-rf24/) contiene los programas de transmisión y recepción con nRF24L01/RF24 utilizados durante el prototipado.

Esta implementación se conserva como registro de la arquitectura de control y como punto de partida para su evolución. A partir de ella se plantea la futura integración de un enlace LoRa de 433 MHz con un módulo EBYTE E32 y una antena específica seleccionada para el proyecto. Esa integración todavía no forma parte del firmware publicado.

## Hardware de la plataforma

Los proyectos KiCad de [`hardware/esc/`](../hardware/esc/) y [`hardware/radio-control/`](../hardware/radio-control/) contienen los esquemáticos y archivos asociados a estas dos áreas. Aunque los esquemáticos están disponibles para revisión, tanto el ruteo como la definición de las PCB continúan en proceso de diseño.

Como registro de etapas anteriores, [`archive/historical-gerbers/`](../archive/historical-gerbers/) conserva exportaciones históricas de fabricación. Su presencia no implica que exista una revisión final de las placas.

## Documentación y evidencia de ensayo

Las fotografías de [`media/experiments/`](../media/experiments/) complementan las fuentes de firmware y hardware con registros de prototipos, montajes y mediciones de banco. Para interpretar ese material dentro de su etapa de desarrollo, el documento de [estado](status.md) resume la situación de cada área, y las [referencias](references.md) identifican las plataformas y fuentes de consulta utilizadas.
