# Estado de avance: FluxLink 433

Actualizado: 2026-08-21

| Area | Estado | Evidencia disponible | Siguiente hito |
| --- | --- | --- | --- |
| Plataforma DukeDoks | Recurso de prueba | Modelos STL y reporte historico de armado | Mantener atribucion y separar de la autoria del ESC. |
| Control remoto LoRa 433 MHz | En desarrollo | Manuales de antena y programas de prueba | Probar alcance, perdida de paquetes y autonomia. |
| Receptor y direccion | En desarrollo | Variantes de receptor y failsafe | Validar limites de servo y respuesta ante perdida de enlace. |
| Esquematico de radio | En desarrollo | Archivos KiCad de trabajo | Revisar esquema y definir PCB. |
| Esquematico principal / ESC | En desarrollo | KiCad, BOM y posiciones de referencia | Completar diseno de PCB y auditoria electrica. |
| ESC sensorless | Experimental / no validado | Firmware propio y pruebas de lazo abierto/cerrado | Lograr arranque repetible y conmutacion BEMF estable. |
| Datos de ensayo | No disponible | No hay registros tabulares de medicion | Crear y completar bitacora de pruebas. |
| Comunicacion y difusion | Inicial | Informe, dos imagenes de fases y renders | Producir fotos, video y ficha tecnica. |

## Riesgos abiertos

1. No existe evidencia de ensayo reproducible para corriente, temperatura, RPM, eficiencia o autonomia.
2. El firmware del ESC usa registros de bajo nivel y requiere revision de temporizadores, dead-time, protecciones y secuencia de arranque.
3. El PCB esta en proceso de diseno; los archivos existentes no deben interpretarse como evidencia de una placa final fabricada.
4. La licencia de los recursos externos y del proyecto aun no esta definida.

## Criterios para declarar una version operativa

- Enlace LoRa de 433 MHz probado con perdida de senal y failsafe.
- Servo dentro de limites mecanicos.
- ESC con arranque repetible, apagado seguro y proteccion ante perdida de PWM.
- Corriente y temperatura registradas en banco para al menos tres niveles de acelerador.
- Prueba estatica y prueba de rodaje documentadas.
