#include <WiFi.h>
const int triggerPin = 18, echoPin = 5;
const char * WIFI_SSID = "Galaxy S20 5G419c";
const char * WIFI_PASS = "Salame123";

const char * SERVER_ADDRESS = "192.168.24.126";
const int SERVER_PORT = 10000; //YOUR_PORT


long readUltrasonicDistance()
{
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}

void setup()
{
  Serial.begin(9600);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin , INPUT);
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

void loop()
{
  // measure the ping time in cm
  int cm = 0.01723 * readUltrasonicDistance();
  Serial.println(cm);
  delay(2000);

  Serial.print("Connecting to: ");
  Serial.println(SERVER_ADDRESS);

  WiFiClient client;

  if (!client.connect(SERVER_ADDRESS, SERVER_PORT)) {
    Serial.println("Connection failed");
    return;
  }

  String set = "distance=" + String(cm) + "\n";
  client.print(set.c_str());
  String line = client.readStringUntil('\n');
  Serial.println(line);
  Serial.println("Closing connection.");
  client.stop();
}