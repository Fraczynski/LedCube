#include <SPI.h>
#include <WiFi.h>

//cube
uint8_t cube[8][8];
uint8_t i = 0, j = 0, k = 0;
bool loading = false;
uint8_t currentEffect;
uint16_t timer;

//frame break times
const int TEST_LEDS_TIME = 500;
const int TEST_LAYERS_TIME = 500;

const int TOTAL = 1;

//static effects
const int STATIC_EFFECT = -10;
const int LIGHT = -1;
const int CLEAR = -2;
//dynamic effects
const int TEST_LEDS = -3;
const int TEST_LAYERS = -4;
//const int RAIN = 0;

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

void switchEffect(){
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
