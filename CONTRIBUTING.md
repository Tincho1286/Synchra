# Contribuir a TRUGGY

## Principios

- No modificar firmware de potencia sin registrar objetivo, hardware, parametros y resultado de la prueba.
- Conservar los archivos fuente de KiCad y CAD; los Gerbers y archivos comprimidos son exportaciones, no la fuente de verdad.
- Mantener separadas las referencias externas del desarrollo propio.
- No declarar una funcion como lista sin una prueba documentada y repetible.

## Flujo de trabajo

1. Crear una rama por cambio: `docs/...`, `firmware/...`, `hardware/...` o `mechanical/...`.
2. Documentar el cambio y el resultado de validacion en `docs/PROJECT_STATUS.md` o en un registro de ensayo.
3. Para PCBs, incluir esquematico, PCB, BOM y archivos de posicion actualizados cuando correspondan.
4. Para firmware, indicar placa objetivo, librerias, version de IDE y procedimiento de prueba.
5. Abrir una solicitud de cambio con contexto, riesgos y evidencia.

## Seguridad

El ESC conmuta potencia trifasica. Usar fuente con limitacion de corriente, fusible, proteccion ocular, ventilacion y el motor firmemente sujeto. No probar una configuracion nueva con el vehiculo apoyado sobre sus ruedas.
