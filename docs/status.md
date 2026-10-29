# Estado de desarrollo

Synchra se encuentra en fase de diseño y validación experimental. Por ese motivo, el firmware, los esquemáticos y las PCB publicados deben interpretarse como registros de un trabajo en evolución. Ninguno de los programas constituye una versión final lista para uso.

Dentro de ese marco, el desarrollo se concentra en el ESC sensorless y sus ensayos de conmutación, lectura de BEMF y arranque. El prototipo de radio RF24 acompaña esta etapa, mientras que la integración LoRa y la evolución de las PCB forman parte de las próximas líneas de trabajo.

| Área | Situación actual |
| --- | --- |
| Firmware del ESC | En desarrollo, con pruebas de BEMF, conmutación y arranque en lazo abierto y cerrado. |
| Firmware de radio RF24 | Prototipo de transmisión y recepción en desarrollo, conservado como etapa previa. |
| Radio LoRa de 433 MHz | Integración prevista con EBYTE E32 y una nueva antena; todavía no está incorporada al firmware publicado. |
| Esquemáticos | Disponibles en formato KiCad y sujetos a revisión durante el desarrollo. |
| PCB | En proceso de diseño y ruteo, sin una revisión final de fabricación. |
| Registros de ensayo | Fotografías de prototipos, montajes y mediciones de banco disponibles en [`media/experiments/`](../media/experiments/). |

Los registros visuales acompañan este proceso y permiten consultar distintas etapas de experimentación; por sí solos no acreditan la validación del sistema completo. Del mismo modo, los archivos de [`archive/historical-gerbers/`](../archive/historical-gerbers/) se conservan por su valor histórico y no representan una liberación final de PCB.

Para relacionar estas áreas con la organización del proyecto, puede consultarse la [arquitectura](architecture.md). Las [referencias y atribuciones](references.md) completan ese contexto al distinguir el desarrollo propio de las plataformas y fuentes utilizadas durante la investigación.
