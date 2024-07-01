// Library
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

// Mendefinisikan pin untuk ultrasonic dan relay
#define TRIG D5
#define ECHO D6
#define RELAY D7

// Deklarasi variable condition
int condition;

/****** WiFi Connection Details *******/
const char* ssid = "Rexa";
const char* password = "AryaFadly2014";

/******* MQTT Broker Connection Details *******/
const char* mqtt_server = "broker.emqx.io";
const char* mqtt_username = "emqx";
const char* mqtt_password = "public";
const int mqtt_port =1883;

/**** Secure WiFi Connectivity Initialisation *****/
WiFiClient espClient;

/**** MQTT Client Initialisation Using WiFi Connection *****/
PubSubClient client(espClient);

unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE (50)
char msg[MSG_BUFFER_SIZE];

/************* Connect to WiFi ***********/
void setup_wifi() {
  delay(10);
  Serial.print("\nConnecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  randomSeed(micros());
  Serial.println("\nWiFi connected\nIP address: ");
  Serial.println(WiFi.localIP());
}

/************* Connect to MQTT Broker ***********/
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP8266Client-";   // Create a random client ID
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str(), mqtt_username, mqtt_password)) {
      Serial.println("connected");

    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");   // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

/**** Method for Publishing MQTT Messages **********/
void publishMessage(const char* topic, String payload , boolean retained){
  if (client.publish(topic, payload.c_str(), true))
      Serial.println("Message publised ["+String(topic)+"]: "+payload);
}

void setup() {
  // Mengatur pin trig dan echo
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  // Mengatur pin relay sebagai output
  pinMode(RELAY, OUTPUT);
  // Memastikan relay dalam keadaan mati saat memulai
  digitalWrite(RELAY, LOW);
  
  // Memulai komunikasi serial dengan baud rate 9600
  Serial.begin(9600);
  while (!Serial) delay(1);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
}

void loop() {

  if (!client.connected()) reconnect(); // check if client is connected
  client.loop();

  // Mengatur trigPin LOW selama 2 mikrodetik untuk memastikan tidak ada sinyal
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  
  // Mengatur trigPin HIGH selama 10 mikrodetik untuk mengirim sinyal trigger
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  
  // Membaca durasi sinyal yang diterima pada echoPin
  long duration = pulseIn(ECHO, HIGH);
  
  // Menghitung jarak dalam cm
  // Kecepatan suara di udara adalah 343 m/s atau 0.0343 cm/µs
  // Jarak dihitung dari waktu pulang-pergi sehingga harus dibagi 2
  float distance = (duration * 0.0343) / 2;
  
  // Menampilkan hasil pada Serial Monitor
  Serial.print("Jarak: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Menampilkan nilai condition pada Serial Monitor
  Serial.print("Condition: ");
  Serial.println(condition);

  // Mengatur condition dan relay berdasarkan jarak
  if (distance >= 30) {
    digitalWrite(RELAY, HIGH);
    condition = 1; //safe
  } else {
    digitalWrite(RELAY, LOW);
    condition = 0; //danger
  }
  
  // Jeda sebelum pengukuran berikutnya
// Up to MQTT
  String msgStr = String(distance) + "," + String(condition);
  byte arrSize = msgStr.length() + 1;
  char msg[arrSize];

  Serial.print("PUBLISH DATA:");
  Serial.println(msgStr);
  msgStr.toCharArray(msg, arrSize);
  publishMessage("water_data", msg, true);
  msgStr = "";

  delay(1000);
}
