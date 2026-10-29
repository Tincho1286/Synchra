# Referencias y atribuciones

El firmware y la electrónica de Synchra fueron desarrollados específicamente para este proyecto. Durante su investigación y sus ensayos se utilizaron plataformas mecánicas y fuentes de consulta externas, cuyos aportes se detallan a continuación.

## DukeDoks: plataforma mecánica de ensayo

El vehículo y los modelos de **DukeDoks** se utilizaron como plataforma mecánica para las pruebas de Synchra. Esa plataforma permitió disponer de un soporte para los ensayos, mientras que el alcance del desarrollo propio corresponde al firmware y a la electrónica del proyecto.

## Electronoobs y otros proyectos de ESC: investigación y aprendizaje

Para estudiar el funcionamiento de los controladores de motores brushless se consultaron los proyectos de **Electronoobs** y otros ESC públicos. Estas referencias aportaron material conceptual y de aprendizaje durante la investigación; el código incluido en [`firmware/`](../firmware/) y la electrónica de Synchra fueron desarrollados para este proyecto.

## EBYTE E32: referencia para la futura integración LoRa

Como continuación del prototipo de radio RF24, se prevé integrar un enlace LoRa de 433 MHz con un módulo EBYTE E32 y una nueva antena. La documentación técnica de EBYTE sirve de referencia para esa etapa, que todavía no forma parte del firmware publicado.

La [arquitectura](architecture.md) describe cómo se relacionan el ESC, el control remoto y el hardware, mientras que el [estado de desarrollo](status.md) permite ubicar cada uno de estos aportes dentro de la fase experimental actual.
