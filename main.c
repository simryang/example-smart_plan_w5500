#include <SPI.h>
#include <Ethernet.h>
#include <DHT.h>

// 센서 핀 설정
#define DHTPIN 2
#define DHTTYPE DHT22
#define RAIN_SENSOR_PIN A0
#define SOIL_MOISTURE_PIN A1
#define DUST_SENSOR_PIN A2

// 액추에이터 핀 설정
#define WATER_PUMP_PIN 3
#define FAN_PIN 4

// 네트워크 설정
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 1, 177);
EthernetClient client;

// Ubidots 설정
const char* UBIDOTS_TOKEN = "Your_Ubidots_Token";
const char* UBIDOTS_SERVER = "industrial.api.ubidots.com";
const int UBIDOTS_PORT = 80;

// DHT 센서 초기화
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();

  // 액추에이터 핀 모드 설정
  pinMode(WATER_PUMP_PIN, OUTPUT);
  pinMode(FAN_PIN, OUTPUT);

  // Ethernet 초기화
  Ethernet.begin(mac, ip);
  delay(1000);
  Serial.println("Ethernet initialized");
}

void loop() {
  // 센서 데이터 읽기
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  int rainValue = analogRead(RAIN_SENSOR_PIN);
  int soilMoisture = analogRead(SOIL_MOISTURE_PIN);
  int dustLevel = analogRead(DUST_SENSOR_PIN);

  // 센서 데이터 출력
  Serial.print("Temperature: "); Serial.println(temperature);
  Serial.print("Humidity: "); Serial.println(humidity);
  Serial.print("Rain Sensor: "); Serial.println(rainValue);
  Serial.print("Soil Moisture: "); Serial.println(soilMoisture);
  Serial.print("Dust Level: "); Serial.println(dustLevel);

  // Ubidots에 데이터 전송
  if (client.connect(UBIDOTS_SERVER, UBIDOTS_PORT)) {
    String payload = "{\"temperature\":" + String(temperature) +
                     ",\"humidity\":" + String(humidity) +
                     ",\"rain\":" + String(rainValue) +
                     ",\"soil_moisture\":" + String(soilMoisture) +
                     ",\"dust\":" + String(dustLevel) + "}";

    String request = String("POST /api/v1.6/devices/smart-plantfarm HTTP/1.1\r\n") +
                     "Host: " + UBIDOTS_SERVER + "\r\n" +
                     "User-Agent: Arduino/1.0\r\n" +
                     "X-Auth-Token: " + UBIDOTS_TOKEN + "\r\n" +
                     "Content-Type: application/json\r\n" +
                     "Content-Length: " + payload.length() + "\r\n\r\n" +
                     payload;

    client.print(request);
    client.stop();
  } else {
    Serial.println("Connection to Ubidots failed");
  }

  // 환경에 따른 액추에이터 제어
  if (soilMoisture < 300) {
    digitalWrite(WATER_PUMP_PIN, HIGH);
  } else {
    digitalWrite(WATER_PUMP_PIN, LOW);
  }

  if (temperature > 30.0) {
    digitalWrite(FAN_PIN, HIGH);
  } else {
    digitalWrite(FAN_PIN, LOW);
  }

  delay(5000); // 5초 대기
}
