#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <Preferences.h>

// Pines
const int ledPin = 2;
const int soundSensorPin = 34;
const int buzzerPin = 5;

// Variables
int soundThreshold = 5;
bool systemActive = true;
bool ledState = false;
bool buzzerState = false;

// Configuración WiFi
const char* ssid = "A";
const char* password = "12345678";

// Servidor y almacenamiento
AsyncWebServer server(80);
Preferences preferences;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(soundSensorPin, INPUT);

  Serial.begin(115200);

  // Conexión WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a WiFi...");
  }
  Serial.println("Conexión establecida.");
  Serial.println(WiFi.localIP());

  // Cargar configuraciones
  preferences.begin("settings", false);
  soundThreshold = preferences.getInt("threshold", 5);
  systemActive = preferences.getBool("active", true);

  // Página HTML
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    String html = R"rawliteral(
      <!DOCTYPE html>
<html>
<head>
  <title>Control de Ruido</title>
  <style>
    body { font-family: Arial, sans-serif; text-align: center; }
    .container { display: inline-block; margin: 20px; }
    .switch { position: relative; display: inline-block; width: 60px; height: 34px; }
    .switch input { display: none; }
    .slider { position: absolute; cursor: pointer; top: 0; left: 0; right: 0; bottom: 0; background-color: #ccc; transition: .4s; }
    .slider:before { position: absolute; content: ""; height: 26px; width: 26px; left: 4px; bottom: 4px; background-color: white; transition: .4s; }
    input:checked + .slider { background-color: #2196F3; }
    input:checked + .slider:before { transform: translateX(26px); }
  </style>
</head>
<body>
  <h1>Monitor de Ruido</h1>
  <p>Nivel de sonido: <span id="soundLevel">0</span> dB</p>

  <div class="container">
    <label>Sistema:</label>
    <label class="switch">
      <input type="checkbox" id="systemSwitch" onchange="toggleSystem()" />
      <span class="slider"></span>
    </label>
  </div>

  <div class="container">
    <label>LED:</label>
    <label class="switch">
      <input type="checkbox" id="ledSwitch" onchange="toggleLed()" />
      <span class="slider"></span>
    </label>
  </div>

  <div class="container">
    <label>Buzzer:</label>
    <label class="switch">
      <input type="checkbox" id="buzzerSwitch" onchange="toggleBuzzer()" />
      <span class="slider"></span>
    </label>
  </div>

  <div class="container">
    <label>Umbral de sonido:</label>
    <input type="range" id="threshold" min="0" max="50" step="1" value="10" onchange="updateThreshold()" />
    <span id="thresholdValue">10</span> dB
  </div>

  <script>
    setInterval(() => fetch('/sound-level').then(res => res.text()).then(data => document.getElementById('soundLevel').innerText = data), 1000);

    function toggleSystem() {
      const state = document.getElementById('systemSwitch').checked;
      fetch(/toggle-system?state=${state});
    }

    function toggleLed() {
      const state = document.getElementById('ledSwitch').checked;
      fetch(/toggle-led?state=${state});
    }

    function toggleBuzzer() {
      const state = document.getElementById('buzzerSwitch').checked;
      fetch(/toggle-buzzer?state=${state});
    }

    function updateThreshold() {
      const value = document.getElementById('threshold').value;
      document.getElementById('thresholdValue').innerText = value;
      fetch(/set-threshold?value=${value});
    }

    // Inicializa los switches con el estado actual
    fetch('/get-status').then(res => res.json()).then(data => {
      document.getElementById('systemSwitch').checked = data.systemActive;
      document.getElementById('ledSwitch').checked = data.ledState;
      document.getElementById('buzzerSwitch').checked = data.buzzerState;
      document.getElementById('threshold').value = data.threshold;
      document.getElementById('thresholdValue').innerText = data.threshold;
    });
  </script>
</body>
</html>)rawliteral";
    request->send(200, "text/html", html);
  });

  // Endpoints de control
  server.on("/sound-level", HTTP_GET, [](AsyncWebServerRequest *request) {
    int soundLevel = analogRead(soundSensorPin);
    int decibels = map(soundLevel, 0, 1023, 0, 100);
    request->send(200, "text/plain", String(decibels));
  });

  server.on("/toggle-led", HTTP_GET, [](AsyncWebServerRequest *request) {
    ledState = !ledState;
    digitalWrite(ledPin, ledState);
    request->send(200, "text/plain", "LED toggled");
  });

  server.on("/toggle-buzzer", HTTP_GET, [](AsyncWebServerRequest *request) {
    buzzerState = !buzzerState;
    digitalWrite(buzzerPin, buzzerState);
    request->send(200, "text/plain", "Buzzer toggled");
  });

  server.on("/toggle-system", HTTP_GET, [](AsyncWebServerRequest *request) {
    systemActive = !systemActive;
    preferences.putBool("active", systemActive);
    if (!systemActive) {
      digitalWrite(ledPin, LOW);
      digitalWrite(buzzerPin, LOW);
    }
    request->send(200, "text/plain", systemActive ? "System activated" : "System deactivated");
  });

  server.on("/set-threshold", HTTP_GET, [](AsyncWebServerRequest *request) {
    if (request->hasParam("value")) {
      soundThreshold = request->getParam("value")->value().toInt();
      preferences.putInt("threshold", soundThreshold);
      request->send(200, "text/plain", "Threshold updated");
    } else {
      request->send(400, "text/plain", "Missing parameter");
    }
  });

  server.on("/get-status", HTTP_GET, [](AsyncWebServerRequest *request) {
  String json = "{";
  json += "\"systemActive\":" + String(systemActive ? "true" : "false") + ",";
  json += "\"ledState\":" + String(ledState ? "true" : "false") + ",";
  json += "\"buzzerState\":" + String(buzzerState ? "true" : "false") + ",";
  json += "\"threshold\":" + String(soundThreshold);
  json += "}";
  request->send(200, "application/json", json);
});

  // Inicia el servidor
  server.begin();
}

void loop() {
  if (systemActive) {
    int soundLevel = analogRead(soundSensorPin);
    int decibels = map(soundLevel, 0, 1023, 0, 100);

    if (decibels > soundThreshold) {
      if (ledState) digitalWrite(ledPin, HIGH);
      if (buzzerState) digitalWrite(buzzerPin, HIGH);
    } else {
      digitalWrite(ledPin, LOW);
      digitalWrite(buzzerPin, LOW);
    }
  }
}
