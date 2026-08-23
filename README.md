# Synchra

**Plataforma experimental de control electrónico para motores brushless y radio control.**

Synchra reúne el desarrollo de un ESC sensorless basado en Arduino, su electrónica asociada y un sistema de control remoto. El trabajo está centrado en explorar conmutación trifásica, lectura de BEMF y la evolución de la comunicación de radio hacia LoRa en 433 MHz.

> Proyecto de diseño electrónico en desarrollo. Todo el firmware, los esquemáticos y las PCB siguen en proceso de diseño, ensayo y evolución; ninguno de los programas debe considerarse una versión final.

## Registro visual del proceso

<table>
  <tr>
    <td width="50%" align="center"><img src="media/experiments/phase-switching-112khz.jpg" width="100%" alt="Medición de conmutación de fase" /><br /><sub>Conmutación de fase medida en banco.</sub></td>
    <td width="50%" align="center"><img src="media/experiments/motor-drive-waveforms.jpg" width="100%" alt="Ensayo de señales de accionamiento" /><br /><sub>Ensayo de señales de accionamiento.</sub></td>
  </tr>
  <tr>
    <td colspan="2" align="center"><img src="media/experiments/multichannel-bench-measurement.jpg" width="62%" alt="Medición multicanal en banco" /><br /><sub>Medición multicanal con instrumentación de laboratorio.</sub></td>
  </tr>
</table>

<table>
  <tr>
    <td width="33%" align="center"><img src="media/experiments/early-esc-prototype.jpg" width="100%" alt="Prototipo previo de ESC" /><br /><sub>Prototipo previo de ESC.</sub></td>
    <td width="33%" align="center"><img src="media/experiments/early-pcb-layout.jpg" width="100%" alt="PCB de prototipo previo" /><br /><sub>PCB de prototipo previo.</sub></td>
    <td width="33%" align="center"><img src="media/experiments/dukedoks-test-platform.jpg" width="100%" alt="Plataforma de ensayo DukeDoks" /><br /><sub>Plataforma de ensayo DukeDoks.</sub></td>
  </tr>
</table>

<table>
  <tr>
    <td width="33%" align="center"><img src="media/experiments/early-esc-assembly.jpg" width="100%" alt="Montaje previo de ESC" /><br /><sub>Montaje previo de ESC.</sub></td>
    <td width="33%" align="center"><img src="media/experiments/drivetrain-test-assembly.jpg" width="100%" alt="Conjunto de transmisión en ensayo" /><br /><sub>Conjunto mecánico en ensayo.</sub></td>
    <td width="33%" align="center"><img src="media/experiments/remote-control-prototype.jpg" width="100%" alt="Control remoto de prototipo" /><br /><sub>Control remoto de prototipo.</sub></td>
  </tr>
</table>

*Las imágenes documentan etapas de experimentación; no representan una versión final del sistema.*

## Alcance

- **ESC sensorless:** firmware Arduino en desarrollo para conmutación de motor BLDC con realimentación por BEMF y ensayos de arranque en lazo abierto y cerrado.
- **Control remoto:** firmware de transmisión y recepción en desarrollo, utilizado durante la etapa de prototipado RF24 con salida para aceleración y dirección.
- **Radio LoRa 433 MHz:** próxima evolución de Synchra, prevista con módulo EBYTE E32 y la nueva antena del proyecto; su firmware aún está en desarrollo.
- **Hardware:** esquemáticos y fuentes KiCad del ESC y del control remoto; el diseño de las PCB continúa en proceso.

## Estructura

```text
firmware/       Código del ESC, radio de prototipo y experimentos
hardware/       Fuentes KiCad del ESC y del control remoto
archive/        Exportaciones históricas de fabricación
media/          Registros visuales de los ensayos
docs/           Arquitectura, estado y referencias
```

## Estado actual

Todos los programas publicados son material de desarrollo y se encuentran sujetos a cambios. El núcleo del ESC y sus pruebas de sincronización forman la base activa del proyecto. El enlace RF24 incluido es un prototipo de radio previo; no representa aún la implementación LoRa. La migración a LoRa 433 MHz y el diseño de PCB son las próximas líneas de trabajo.

Más detalle: [arquitectura](docs/architecture.md), [estado de desarrollo](docs/status.md) y [referencias](docs/references.md).

## Créditos y referencias

El vehículo/modelo empleado como plataforma de prueba pertenece a **DukeDoks**. El firmware y la electrónica de Synchra son desarrollos propios; durante la investigación se consultaron los proyectos de **Electronoobs** y otros trabajos públicos de ESC. Ver [referencias](docs/references.md) para el alcance de cada aporte.
