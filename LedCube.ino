#include <SPI.h>
#include <WiFi.h>

const uint8_t POSITION_X = 0;
const uint8_t POSITION_Z = 2;
const uint8_t POSITION_Y = 4;
const uint8_t NEG_X = 1;
const uint8_t NEG_Z = 3;
const uint8_t NEG_Y = 5;

//cube
uint8_t cube[8][8];
uint8_t i = 0, j = 0, k = 0;
bool loading = false;
uint8_t currentEffect;
uint16_t timer;

const int TOTAL = 1;

//static effects
const int8_t STATIC_EFFECT = -10;
const int8_t LIGHT = -1;
const int8_t CLEAR = -2;
//dynamic effects
const int8_t TEST_LEDS = -3;
const int8_t TEST_LAYERS = -4;
const uint8_t RAIN = 0;

//frame break times
const uint16_t TEST_LEDS_TIME = 500;
const uint16_t TEST_LAYERS_TIME = 500;
const uint16_t RAIN_TIME = 200;

//server
String  ClientRequest;
IPAddress staticIP642_10(192, 168, 1, 10);
IPAddress gateway642_10(192, 168, 1, 1);
IPAddress subnet642_10(255, 255, 255, 0);
WiFiServer server(80);
WiFiClient client;
String request;

void setup() {
  loading = true;
  currentEffect = 0;
  timer = 0;

  //server
  const char* ssid = "*HotSpot*";
  const char* password = "792756125";
  ClientRequest = "";
  Serial.begin(115200);
  WiFi.disconnect();
  delay(3000);
  Serial.println("START");
  WiFi.begin(ssid, password);
  while (!(WiFi.status() == WL_CONNECTED)) {
    delay(300);
    Serial.print("..");
  }
  Serial.println("Connected");
  WiFi.config(staticIP642_10, gateway642_10, subnet642_10);
  Serial.print("IP:");
  Serial.println((WiFi.localIP()));
  server.begin();

  //cube
  SPI.begin();
  SPI.beginTransaction(SPISettings(8000000, MSBFIRST, SPI_MODE0));
}

void loop() {
  client = server.available();
  if (client) {
    while (!client.available()) {
      switchEffect();
    }
    request = ReadIncomingRequest();
    currentEffect = parseRequest();
  }
  switchEffect();
}

void switchEffect() {
  switch (currentEffect) {
    //dynamic effects
    case TEST_LEDS: testLEDs(); break;
    case TEST_LAYERS: testLayers(); break;

    //static effects
    case LIGHT: lightCube(); currentEffect = STATIC_EFFECT; break;
    case CLEAR: clearCube(); currentEffect = STATIC_EFFECT; break;
  }
  renderCube();
}
