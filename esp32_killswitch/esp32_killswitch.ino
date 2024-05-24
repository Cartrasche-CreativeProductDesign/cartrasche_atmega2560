#include <Arduino.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include <PubSubClient.h>

#define buttonPin 25

const char* ssid = "cartrasche";
const char* password = "cart1234";

const char* mqtt_server = "192.168.0.4"; // MQTT broker IP 
const int mqtt_port = 1883; // MQTT port 1883
const char* mqtt_topic = "kill";
char buffer[16];

WiFiClient espClient; 
PubSubClient client(espClient);

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP32Client")) {
      Serial.println("connected");
      client.subscribe(mqtt_topic);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  pinMode(buttonPin, INPUT);

}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  int state = digitalRead(buttonPin);
  Serial.println(state);
  if(state){
    memset(buffer, 0x00, sizeof(buffer));
    sprintf(buffer, "kill");
    Serial.println("kill");
    client.publish(mqtt_topic, buffer);
  }
  delay(100);
}
