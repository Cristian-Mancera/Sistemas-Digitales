
#include <WiFi.h>
#include <PubSubClient.h>

WiFiClient esp32Client;
PubSubClient mqttClient(esp32Client);

const char* ssid     = "A";
const char* password = "12345678";

char *server = "broker.emqx.io";
int port = 1883;

int ledpin = 2;
int soundpin = 34;

int var = 0;
int ledval = 0;
int soundval = 0;
char datos[40];
String resultS = "";

// Define un límite para el nivel de sonido
const int soundThreshold = 30; // Ajusta este valor según tus necesidades

void wifiStaticInit() {
    Serial.println("Starting...");
    WiFi.begin(ssid, password);
  
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Wifi not connected");
    }
  
    Serial.println("Wifi connected succesfully!");
    Serial.println("Local IP: " + String(WiFi.localIP()));
    WiFi.mode(WIFI_STA);
}

void wifiInit() {
    Serial.print("Conectándose a ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);  
    }
    Serial.println("");
    Serial.println("Conectado a WiFi");
    Serial.println("Dirección IP: ");
    Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
    Serial.print("Mensaje recibido [");
    Serial.print(topic);
    Serial.print("] ");

    char payload_string[length + 1];
    int resultI;

    memcpy(payload_string, payload, length);
    payload_string[length] = '\0';
    resultI = atoi(payload_string);
  
    var = resultI;

    resultS = "";
  
    for (int i = 0; i < length; i++) {
        resultS += (char)payload[i];
    }
    Serial.println();
}

void reconnect() {
    while (!mqttClient.connected()) {
        Serial.print("Intentando conectarse MQTT...");

        if (mqttClient.connect("arduinoClient")) {
            Serial.println("Conectado");
            mqttClient.subscribe("Entrada/01");
        } else {
            Serial.print("Fallo, rc=");
            Serial.print(mqttClient.state());
            Serial.println(" intentar de nuevo en 5 segundos");
            delay(5000);
        }
    }
}

void setup() {
    pinMode(ledpin, OUTPUT);
    Serial.begin(115200);
    delay(10);
    wifiStaticInit();
    mqttClient.setServer(server, port);
    mqttClient.setCallback(callback);
}

void loop() {
    if (!mqttClient.connected()) {
        reconnect();
    }
    mqttClient.loop();

    Serial.print("String: ");
    Serial.println(resultS);

    // Encender o apagar el LED según el valor de var
    if (var == 0) {
        digitalWrite(ledpin, LOW);
    } else if (var == 1) {
        digitalWrite(ledpin, HIGH);
    }

    soundval = analogRead(soundpin);
    Serial.print("Sonido: ");
    Serial.println(soundval);

    // Encender el LED si el nivel de sonido supera el límite
     if (soundval > soundThreshold) {
        digitalWrite(ledpin, HIGH); // Enciende el LED
   } else {
       digitalWrite(ledpin, LOW); // Apaga el LED
   }

    sprintf(datos, "Valor sonido: %d ", soundval);
    mqttClient.publish("biblio/01", datos);
    delay(50);  
}
