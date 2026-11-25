/*
 * Proyecto: Sistema de Control Inalámbrico Bluetooth/UART No Bloqueante
 * Módulo: Internet de las Cosas - Entrega 2 (Escenario 5)
 * Institución: Politécnico Grancolombiano
 * Autores: Iván de Jesús Cantor Marín & Andrea Ochoa Bolaños
 */

// --- Definición de Pines de Salida (Actuadores) ---
const int PIN_LED_VERDE = 7;  // Estado de conexión / Control directo
const int PIN_LED_ROJO  = 8;  // Alerta / Control por temporización

// --- Variables de Control Temporal No Bloqueante (millis) ---
unsigned long tiempoPrevioParpadeo = 0;
const unsigned long INTERVALO_MS = 500; // Periodo de 500 ms (2 Hz)
bool estadoLedRojo = LOW;
bool parpadeoActivo = false;

// --- Variables para Telemetría y Métricas ---
unsigned long contadorTramas = 0;

void setup() {
  pinMode(PIN_LED_VERDE, OUTPUT);
  pinMode(PIN_LED_ROJO, OUTPUT);

  // Configuración de interfaz UART a 9600 baudios (Estándar HC-05/HC-06)
  Serial.begin(9600);
  
  Serial.println("=======================================================");
  Serial.println(" SISTEMA IOT INICIADO - ENLACE SERIAL / BLUETOOTH (UART)");
  Serial.println("=======================================================");
  Serial.println("Comandos disponibles:");
  Serial.println("  [A] Encender LED Verde     | [B] Apagar LED Verde");
  Serial.println("  [P] Parpadeo LED Rojo      | [S] Apagar LED Rojo");
  Serial.println("-------------------------------------------------------");
}

void loop() {
  unsigned long tiempoActual = millis();

  // 1. Escucha activa del buffer Serial/Bluetooth (Latencia < 1 ms)
  if (Serial.available() > 0) {
    char datoRecibido = Serial.read();

    // Filtrar caracteres de retorno de carro o salto de línea
    if (datoRecibido != '\n' && datoRecibido != '\r') {
      unsigned long inicioProceso = micros(); // Medición precisa en microsegundos
      contadorTramas++;
      procesarTrama(datoRecibido, tiempoActual, inicioProceso);
    }
  }

  // 2. Ejecución concurrente del parpadeo sin detener el procesador
  if (parpadeoActivo) {
    if (tiempoActual - tiempoPrevioParpadeo >= INTERVALO_MS) {
      tiempoPrevioParpadeo = tiempoActual;
      estadoLedRojo = !estadoLedRojo;
      digitalWrite(PIN_LED_ROJO, estadoLedRojo);
    }
  }
}

void procesarTrama(char cmd, unsigned long t_ms, unsigned long t_us_inicio) {
  String accion = "";

  switch (cmd) {
    case 'A':
    case 'a':
      digitalWrite(PIN_LED_VERDE, HIGH);
      accion = "LED Verde -> ON";
      break;
    case 'B':
    case 'b':
      digitalWrite(PIN_LED_VERDE, LOW);
      accion = "LED Verde -> OFF";
      break;
    case 'P':
    case 'p':
      parpadeoActivo = true;
      accion = "LED Rojo -> PARPADEO (500 ms)";
      break;
    case 'S':
    case 's':
      parpadeoActivo = false;
      estadoLedRojo = LOW;
      digitalWrite(PIN_LED_ROJO, LOW);
      accion = "LED Rojo -> OFF";
      break;
    default:
      accion = "COMANDO INVALIDO";
      break;
  }

  unsigned long latencia_us = micros() - t_us_inicio;

  // Registro estructurado para exportación de datos
  Serial.print("Trama #");
  Serial.print(contadorTramas);
  Serial.print(" | T_sistema: ");
  Serial.print(t_ms);
  Serial.print(" ms | RX: '");
  Serial.print(cmd);
  Serial.print("' | Latencia_CPU: ");
  Serial.print(latencia_us);
  Serial.print(" us | ");
  Serial.println(accion);
}
