#include <WiFi.h>

const char * WIFI_SSID = "Galaxy S20 5G419c";
const char * WIFI_PASS = "Salame123";

const char * SERVER_ADDRESS = "192.168.24.126";
const int SERVER_PORT = 10000; //YOUR_PORT

void setup() {
  pinMode(25, OUTPUT);
  pinMode(26, OUTPUT);
  pinMode(27, OUTPUT);

  Serial.begin(115200);
  Serial.print("Connecting to: ");
  Serial.print(WIFI_SSID);

  WiFi.begin(WIFI_SSID, WIFI_PASS);

  while (WiFi.status() != WL_CONNECTED) {
    delay(200);
    Serial.print(".");
  }

  Serial.print("\nIP address: ");
  Serial.println(WiFi.localIP());
}

int counter = 0;

void loop() {
  delay(2000);
  digitalWrite(25, LOW);
  digitalWrite(26, LOW);
  digitalWrite(27, LOW);
  Serial.print("Connecting to: ");
  Serial.println(SERVER_ADDRESS);

  WiFiClient client;

  if (!client.connect(SERVER_ADDRESS, SERVER_PORT)) {
    Serial.println("Connection failed");
    return;
  }
  
  String get = "GET\n";
  client.print(get.c_str());

  unsigned long previousMillis = millis();
  while (!client.available() && millis() - previousMillis < 1000);

  if (client.available() > 0) {
    String line = client.readStringUntil('\n');
    int pos = line.toInt();
    Serial.println(line);
    if (pos == 0) {
      digitalWrite(25, HIGH);
    } else if (pos == 1) {
      digitalWrite(26, HIGH);
    } else {
      digitalWrite(27, HIGH);
    }

  } else Serial.println("Server timeout.");

  Serial.println("Closing connection.");
  client.stop();
}
