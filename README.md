# Synchra

**Plataforma experimental de control electrónico para motores brushless y radio control.**

Synchra reúne el desarrollo de un controlador electrónico de velocidad (ESC) sensorless basado en Arduino/ATmega328, su electrónica asociada y un sistema de control remoto. El objetivo principal es estudiar la conmutación trifásica y la detección de fuerza contraelectromotriz (BEMF) para ensayar el arranque y el funcionamiento de motores BLDC en lazo abierto y cerrado. Como parte de esta plataforma, también se explora la comunicación de radio y su futura evolución hacia LoRa en 433 MHz.

> Todo el firmware, los esquemáticos y las PCB se encuentran en desarrollo. Los archivos publicados registran etapas de diseño y ensayo; ninguno de los programas constituye una versión final lista para uso.

## Alcance del proyecto

El ESC constituye el núcleo de Synchra. Su firmware permite explorar la secuencia de conmutación del motor y la lectura de BEMF mediante el comparador analógico, mientras que los programas de ensayo abordan por separado el arranque, la sincronización y las pruebas de lazo cerrado.

Para controlar esta etapa se desarrolló un prototipo de transmisión y recepción con nRF24L01/RF24, con señales de aceleración y dirección. Ese trabajo sirve como punto de partida para la futura integración de un enlace LoRa de 433 MHz con un módulo EBYTE E32 y una nueva antena. La integración LoRa está prevista y todavía no forma parte del firmware publicado.

Ambas áreas se apoyan en los proyectos KiCad del ESC y del control remoto. Sus esquemáticos están disponibles para revisión, mientras que el diseño y el ruteo de las PCB continúan en proceso.

## Registro visual del proceso

Las siguientes imágenes muestran distintas etapas del desarrollo. Se agrupan por su contenido y orientación para relacionar los prototipos electrónicos, su montaje en la plataforma de prueba y las mediciones realizadas en banco. Cada fotografía enlaza con su archivo original para consultar los detalles.

### Prototipos y plataforma de prueba

Los prototipos del ESC y sus placas documentan las primeras etapas de construcción. Junto a ellos se presenta el vehículo de **DukeDoks** utilizado como plataforma mecánica para los ensayos del proyecto.

<table>
  <tr>
    <td width="33%" align="center" valign="top"><a href="media/experiments/early-esc-prototype.jpg"><img src="media/experiments/early-esc-prototype.jpg" width="100%" alt="Vista de un prototipo previo del ESC con sus componentes montados" /></a></td>
    <td width="33%" align="center" valign="top"><a href="media/experiments/early-pcb-layout.jpg"><img src="media/experiments/early-pcb-layout.jpg" width="100%" alt="Vista de las pistas de una PCB de prototipo previo" /></a></td>
    <td width="34%" align="center" valign="top"><a href="media/experiments/dukedoks-test-platform.jpg"><img src="media/experiments/dukedoks-test-platform.jpg" width="100%" alt="Vehículo de DukeDoks empleado como plataforma mecánica de ensayo" /></a></td>
  </tr>
  <tr>
    <td align="center"><sub>Prototipo previo del ESC.</sub></td>
    <td align="center"><sub>PCB correspondiente a una etapa previa.</sub></td>
    <td align="center"><sub>Plataforma mecánica de DukeDoks.</sub></td>
  </tr>
</table>

### Montajes experimentales

Estas etapas de construcción se complementan con los registros del montaje electrónico, el conjunto de transmisión y el control remoto de prototipo. Las fotografías permiten observar los elementos utilizados durante las pruebas, sin representar una configuración final del sistema.

<table>
  <tr>
    <td width="33%" align="center" valign="top"><a href="media/experiments/early-esc-assembly.jpg"><img src="media/experiments/early-esc-assembly.jpg" width="100%" alt="Detalle vertical del montaje de un prototipo previo del ESC" /></a></td>
    <td width="33%" align="center" valign="top"><a href="media/experiments/drivetrain-test-assembly.jpg"><img src="media/experiments/drivetrain-test-assembly.jpg" width="100%" alt="Conjunto de transmisión montado en la plataforma de ensayo" /></a></td>
    <td width="34%" align="center" valign="top"><a href="media/experiments/remote-control-prototype.jpg"><img src="media/experiments/remote-control-prototype.jpg" width="100%" alt="Control remoto utilizado durante la etapa de prototipado" /></a></td>
  </tr>
  <tr>
    <td align="center"><sub>Montaje previo del ESC.</sub></td>
    <td align="center"><sub>Conjunto de transmisión en ensayo.</sub></td>
    <td align="center"><sub>Control remoto de prototipo.</sub></td>
  </tr>
</table>

### Mediciones de banco

Además de documentar los montajes, el registro incluye mediciones de conmutación y señales de accionamiento. Estas capturas muestran las observaciones realizadas durante la experimentación y se complementan con una medición multicanal, presentada a mayor tamaño para facilitar la lectura de la pantalla.

<table>
  <tr>
    <td width="50%" align="center" valign="top"><a href="media/experiments/phase-switching-112khz.jpg"><img src="media/experiments/phase-switching-112khz.jpg" width="32%" alt="Registro de conmutación de fase en un osciloscopio portátil" /></a></td>
    <td width="50%" align="center" valign="top"><a href="media/experiments/motor-drive-waveforms.jpg"><img src="media/experiments/motor-drive-waveforms.jpg" width="100%" alt="Señales de accionamiento observadas en un osciloscopio portátil" /></a></td>
  </tr>
  <tr>
    <td align="center"><sub>Medición de conmutación de fase.</sub></td>
    <td align="center"><sub>Señales de accionamiento del motor.</sub></td>
  </tr>
</table>

<p align="center">
  <a href="media/experiments/multichannel-bench-measurement.jpg"><img src="media/experiments/multichannel-bench-measurement.jpg" width="640" alt="Pantalla de osciloscopio con una medición multicanal realizada en banco" /></a><br />
  <sub>Medición multicanal con instrumentación de laboratorio.</sub>
</p>

## Organización del repositorio

El código, las fuentes de hardware y los registros de ensayo se conservan en áreas separadas para facilitar su revisión. La documentación describe cómo se relacionan, mientras que las exportaciones históricas de fabricación permanecen identificadas en el archivo del proyecto.

| Directorio | Contenido |
| --- | --- |
| [`firmware/`](firmware/) | Firmware del ESC, prototipo de radio RF24 y programas de ensayo. |
| [`hardware/`](hardware/) | Proyectos KiCad del ESC y del control remoto. |
| [`archive/`](archive/) | Gerbers históricos de etapas anteriores. |
| [`media/`](media/) | Fotografías de prototipos, montajes y mediciones. |
| [`docs/`](docs/) | Arquitectura, estado de desarrollo y referencias. |

## Estado actual y continuidad

El núcleo del ESC y sus pruebas de sincronización forman la base activa del proyecto. A partir de este trabajo, las próximas líneas de desarrollo incluyen la integración LoRa de 433 MHz y la evolución de las PCB. El enlace RF24 se conserva como prototipo previo, y los Gerbers de `archive/historical-gerbers/` son registros históricos que no representan una revisión final de fabricación.

La [arquitectura](docs/architecture.md) explica la relación entre los componentes, y el [estado de desarrollo](docs/status.md) detalla la situación de cada área. Ambos documentos se complementan con las [referencias y atribuciones](docs/references.md), donde se identifica el alcance de los aportes externos.

## Créditos y referencias

El vehículo y los modelos empleados como plataforma de prueba pertenecen a **DukeDoks**. Sobre esa plataforma mecánica se ensaya la electrónica de Synchra, cuyo firmware y diseño electrónico fueron desarrollados específicamente para este proyecto.

Durante la investigación se consultaron los proyectos de **Electronoobs** y otros ESC públicos como referencias de aprendizaje. Para la futura integración LoRa también se utiliza la documentación técnica de EBYTE E32. El alcance de estas referencias se describe en [`docs/references.md`](docs/references.md).
