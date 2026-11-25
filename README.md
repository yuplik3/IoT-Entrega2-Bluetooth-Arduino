# Entrega 2 (Escenario 5) - Comunicación Serial Inalámbrica Bluetooth No Bloqueante en Arduino

**Institución:** Politécnico Grancolombiano  
**Facultad:** Ingeniería, Diseño e Innovación  
**Módulo:** Internet de las Cosas (IoT)  
**Autores:**  
* Iván de Jesús Cantor Marín  
* Andrea Ochoa Bolaños  

## Enlace Directo a la Simulación
* **Tinkercad Circuits:** [Abrir simulación interactiva en Tinkercad](https://www.tinkercad.com/things/g53gMwcqUrq/editel?returnTo=%2Fthings%2FadsBwrUBH9G-shiny-wolt-maimu&sharecode=LvKrRWWgoX_75L0GzXrA-PVBbnz4tvN4XiS2zi6Xlxw
)

## Estructura del Repositorio
* `entrega2_bluetooth_millis.ino`: Código fuente documentado en C/C++ para Arduino (arquitectura no bloqueante con `millis()`).
* `datos_experimentales.csv`: Registro original de las 10 tramas transmitidas, tiempos de arribo y latencia de procesamiento en CPU.

## Resumen de Resultados Experimentales
* **Latencia promedio de procesamiento:** `130.4 µs` (reducción >99.9% frente a arquitectura bloqueante).
* **Consumo de recursos en sistema anfitrión:** `0.1% CPU` y `1,736.5 MB RAM` en Google Chrome.
