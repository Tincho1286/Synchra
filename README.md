# Synchra

**Plataforma experimental de control electrónico para motores brushless y radio control.**

Synchra reúne el desarrollo de un ESC sensorless basado en Arduino, su electrónica asociada y un sistema de control remoto. El trabajo está centrado en explorar conmutación trifásica, lectura de BEMF y la evolución de la comunicación de radio hacia LoRa en 433 MHz.

> Proyecto de diseño electrónico en desarrollo. Los esquemáticos están publicados; el diseño final de las PCB continúa en proceso.

<p align="center">
  <img src="media/experiments/phase-switching-112khz.jpg" width="31%" alt="Medición de conmutación de fase" />
  <img src="media/experiments/motor-drive-waveforms.jpg" width="31%" alt="Ensayo de señales de accionamiento" />
  <img src="media/experiments/multichannel-bench-measurement.jpg" width="31%" alt="Medición multicanal en banco" />
</p>

*Registros de ensayos de conmutación y medición en banco.*

## Alcance

- **ESC sensorless:** firmware Arduino para conmutación de motor BLDC con realimentación por BEMF y ensayos de arranque en lazo abierto y cerrado.
- **Control remoto:** firmware de transmisión y recepción usado durante la etapa de prototipado RF24, con salida para aceleración y dirección.
- **Radio LoRa 433 MHz:** próxima evolución de Synchra, prevista con módulo EBYTE E32 y la nueva antena del proyecto.
- **Hardware:** esquemáticos y fuentes KiCad del ESC y del control remoto; la PCB definitiva aún no está cerrada.

## Estructura

```text
firmware/       Código del ESC, radio de prototipo y experimentos
hardware/       Fuentes KiCad del ESC y del control remoto
archive/        Exportaciones históricas de fabricación
media/          Registros visuales de los ensayos
docs/           Arquitectura, estado y referencias
```

## Estado actual

El núcleo del ESC y sus pruebas de sincronización forman la base activa del proyecto. El enlace RF24 incluido es un prototipo de radio previo; no representa aún la implementación LoRa. La migración a LoRa 433 MHz y el diseño de PCB son las próximas líneas de trabajo.

Más detalle: [arquitectura](docs/architecture.md), [estado de desarrollo](docs/status.md) y [referencias](docs/references.md).

## Créditos y referencias

El vehículo/modelo empleado como plataforma de prueba pertenece a **DukeDoks**. El firmware y la electrónica de Synchra son desarrollos propios; durante la investigación se consultaron los proyectos de **Electronoobs** y otros trabajos públicos de ESC. Ver [referencias](docs/references.md) para el alcance de cada aporte.
