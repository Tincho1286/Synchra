# FluxLink 433

**FluxLink 433** es un controlador electronico de velocidad (ESC) sensorless para motor brushless, basado en Arduino y operado por un control remoto con radio LoRa de 433 MHz.

> Estado actual: el esquema del hardware esta en desarrollo. El firmware propio del ESC, las pruebas de conmutacion y el control remoto forman la base experimental. No usar el sistema de potencia sin banco de pruebas y medidas de seguridad.

## Objetivo

Desarrollar y documentar un ESC sensorless de bajo costo, con radio control LoRa de 433 MHz, orientado al aprendizaje de electronica de potencia, control embebido y comunicaciones inalambricas.

## Componentes del proyecto

- **ESC:** control trifasico sensorless para motor brushless, basado en Arduino/ATmega328P, drivers IR2101 y deteccion de BEMF.
- **Radio control:** transmisor LoRa de 433 MHz y control remoto para comandar aceleracion y direccion.
- **Plataforma de prueba:** vehiculo RC impreso en 3D empleado para validar el sistema, no el objeto principal de desarrollo.

## Estructura actual

| Ruta | Contenido |
| --- | --- |
| `[MODELOS DUKEDOKS]` | Material local de DukeDoks, usado solo como plataforma de prueba; no se redistribuye. |
| `[PCB AUTO V1]` | Esquematico y archivos de trabajo del ESC; el PCB aun esta en diseno. |
| `[PCB RADIO CONTROL]` | Esquematico y archivos de trabajo del control remoto; el PCB aun esta en diseno. |
| `[PROGRAMAS]` | Firmware propio para emisor, receptor, ESC y pruebas. |
| `[OPEN ESC´S]` | Referencias locales de Electronoobs y otros autores; no se redistribuyen. |
| `[ANTENA]` | Manuales locales de referencia para el enlace LoRa; no se redistribuyen. |
| `LIBRERIA KICAD` | Dependencias locales de KiCad; no se redistribuyen. |
| `[INFORMES EETP]` | Informe historico privado; no se publica. |
| `docs/` | Documentacion mantenida del proyecto. |

## Inicio rapido

1. Abrir los proyectos `.kicad_pro` con una version compatible de KiCad.
2. Abrir cada `.ino` desde su carpeta para que Arduino IDE encuentre sus archivos auxiliares.
3. Configurar el modulo LoRa de 433 MHz de acuerdo con su manual y firmware correspondiente.
4. Validar el control remoto y el enlace de radio sin motor conectado.
5. Realizar pruebas del ESC exclusivamente con fuente limitada, fusible, motor asegurado y medicion de corriente.

## Documentacion

- [Arquitectura](docs/ARCHITECTURE.md)
- [Estado de avance](docs/PROJECT_STATUS.md)
- [Inventario tecnico](docs/TECHNICAL_INVENTORY.md)
- [Plan de ensayos](docs/TEST_PLAN.md)
- [Guia de contribucion](CONTRIBUTING.md)

## Creditos y procedencia

Los modelos del vehiculo pertenecen a **DukeDoks** y se utilizan exclusivamente como plataforma de prueba del ESC. La carpeta `[OPEN ESC´S]` contiene programas de referencia, incluido material de Electronoobs y otros autores, estudiados durante el desarrollo. El firmware del ESC alojado en `[PROGRAMAS]` fue escrito integramente para este proyecto. Antes de redistribuir recursos externos, verificar sus licencias y condiciones.

Los archivos originales de terceros y el informe EETP se mantienen fuera de la version publica. La procedencia, alcance y referencias tecnicas se documentan en [Referencias y atribuciones](docs/REFERENCES.md).

## Licencia

Pendiente de definicion por el autor. Hasta que se publique una licencia explicita, no se conceden permisos adicionales de uso, redistribucion o comercializacion.
