#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid         = "WIFI_SSID";
const char* password     = "WIFI_PASSWORD";
const char* mqttServer   = "MQTT_SERVER_HOST";
const int   mqttPort     = 1883;
const char* mqttUser     = "MQTT_USERNAME";
const char* mqttPassword = "MQTT_PASSWORD";

#define mqtt_topic_action "led/action"
#define mqtt_topic_status "led/status"


#define GPIO14_LED 14   // Pin D5
 
WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);
 
void loop() {
    mqttClient.loop();
}

void initWifiStation() {

    WiFi.mode(WIFI_AP_STA);
    WiFi.begin(ssid, password);    
    Serial.print("\nConnecting to WiFi");
    while (WiFi.status() != WL_CONNECTED) {
       delay(1000);        
       Serial.print(".");
    }
    Serial.println(String("\nConnected to the WiFi network (") + ssid + ")" );
}
 
void initMQTTClient() {

    // Connecting to MQTT server
    mqttClient.setServer(mqttServer, mqttPort);
    mqttClient.setCallback(PubSubCallback);
    while (!mqttClient.connected()) {
        Serial.println(String("Connecting to MQTT (") + mqttServer + ")...");
        if (mqttClient.connect("ESP8266Client", mqttUser, mqttPassword)) {
            Serial.println("MQTT client connected");  
        } else {
            Serial.print("\nFailed with state ");
            Serial.println(mqttClient.state());
            
            if (WiFi.status() != WL_CONNECTED) {
               initWifiStation();
            }
            delay(2000);
        }
    }

    // Declare Pub/Sub topics
    mqttClient.publish(mqtt_topic_status, "ESP9266 Connected to MQTT...");

    mqttClient.subscribe(mqtt_topic_action);
}

void setup() {

    Serial.begin(115200);

  // GPIO2 is set OUTPUT
    pinMode(GPIO14_LED, OUTPUT);

    initWifiStation();
    initMQTTClient();
    
}
 
void PubSubCallback(char* topic, byte* payload, unsigned int length) {

    String strTopicGpio2Action = mqtt_topic_action;
    String strPayload = "";
    String strON = "ON";
    String strOFF = "OFF";

    Serial.print("Topic:");
    Serial.println(topic);
    Serial.print("Message:");
    for (int i = 0; i < length; i++) {
        Serial.print((char)payload[i]);
        strPayload += (char)payload[i];
    }
    Serial.println();
    Serial.println("-----------------------");
 
    if (strTopicGpio2Action == topic) {
        if (strON == strPayload) {
            digitalWrite(GPIO14_LED, HIGH);
            mqttClient.publish(mqtt_topic_status, "ON");
        } else if (strOFF == strPayload) {
            digitalWrite(GPIO14_LED, LOW);
            mqttClient.publish(mqtt_topic_status, "OFF");
        }
    }

}
