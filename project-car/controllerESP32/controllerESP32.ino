#include <WiFi.h>
#include <WebServer.h>

// Configuración de la red WiFi
const char* ssid = "Juli2004";  // Nombre de la red WiFi
const char* password = "1043641799";  // Contraseña de la red WiFi

// Pines de control del L298N
const int motor1A = 12;  // Motor A hacia adelante
const int motor1B = 13;  // Motor A hacia atrás
const int motor2A = 14;  // Motor B hacia adelante
const int motor2B = 27;  // Motor B hacia atrás

WebServer server(80); // Puerto para el servidor web

void setup() {
  // Inicia la comunicación serial
  Serial.begin(115200);

  // Conexión a la red WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a WiFi...");
  }
  Serial.println("Conexión WiFi exitosa");
  Serial.print("IP del ESP32: ");
  Serial.println(WiFi.localIP());

  // Configuración de pines de control del motor
  pinMode(motor1A, OUTPUT);
  pinMode(motor1B, OUTPUT);
  pinMode(motor2A, OUTPUT);
  pinMode(motor2B, OUTPUT);

  // Manejar las solicitudes de movimiento
  server.on("/move", HTTP_GET, handleMove);

  // Inicia el servidor web
  server.begin();
}

void loop() {
  // Maneja las solicitudes del servidor web
  server.handleClient();
}

void handleMove() {
  // Obtener el parámetro "direction" de la URL
  String direction = server.arg("direction");

  if (direction == "up") {
    // Mover hacia adelante
    digitalWrite(motor1A, HIGH);
    digitalWrite(motor1B, LOW);
    digitalWrite(motor2A, HIGH);
    digitalWrite(motor2B, LOW);
    Serial.println("Movimiento: Adelante");
  }
  else if (direction == "down") {
    // Mover hacia atrás
    digitalWrite(motor1A, LOW);
    digitalWrite(motor1B, HIGH);
    digitalWrite(motor2A, LOW);
    digitalWrite(motor2B, HIGH);
    Serial.println("Movimiento: Atrás");
  }
  else if (direction == "left") {
    // Girar a la izquierda
    digitalWrite(motor1A, LOW);
    digitalWrite(motor1B, HIGH);
    digitalWrite(motor2A, HIGH);
    digitalWrite(motor2B, LOW);
    Serial.println("Movimiento: Izquierda");
  }
  else if (direction == "right") {
    // Girar a la derecha
    digitalWrite(motor1A, HIGH);
    digitalWrite(motor1B, LOW);
    digitalWrite(motor2A, LOW);
    digitalWrite(motor2B, HIGH);
    Serial.println("Movimiento: Derecha");
  }
  else if (direction == "stop") {
    // Detener los motores
    digitalWrite(motor1A, LOW);
    digitalWrite(motor1B, LOW);
    digitalWrite(motor2A, LOW);
    digitalWrite(motor2B, LOW);
    Serial.println("Movimiento: Detenido");
  }

  // Responde al cliente con un mensaje
  server.send(200, "text/plain", "Comando recibido: " + direction);
}
