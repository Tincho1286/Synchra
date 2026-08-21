# Plan de ensayos: FluxLink 433

## Regla de seguridad

Probar primero el enlace RF, luego el receptor y finalmente el ESC. El motor debe estar sujeto y la alimentacion debe contar con limite de corriente y fusible.

## Registro minimo por ensayo

| Campo | Descripcion |
| --- | --- |
| Fecha y responsable | Quien realiza el ensayo. |
| Version de hardware/firmware | Commit de Git y revision de PCB. |
| Configuracion | Bateria/fuente, motor, carga, limites de corriente. |
| Variables medidas | Tension, corriente, temperatura, RPM, alcance y perdida de paquetes. |
| Resultado | Aprobado, fallido u observado. |
| Evidencia | Foto, video, grafico o archivo de datos. |

## Secuencia recomendada

1. **LoRa 433 MHz:** medir alcance, latencia y failsafe en posicion segura.
2. **Direccion:** confirmar limites mecanicos y centro del servo.
3. **ESC sin carga:** validar salidas, secuencia de fases y consumo en reposo.
4. **ESC con motor sujeto:** ensayar arranque con tension/corriente limitadas y registrar BEMF.
5. **Carga controlada:** medir corriente, temperatura y estabilidad a tres niveles de PWM.
6. **Vehiculo elevado:** validar traccion y direccion sin contacto con el suelo.
7. **Rodaje:** medir autonomia, alcance y temperatura; documentar fallos.

No se debe pasar al siguiente nivel si el anterior no tiene resultado documentado.
