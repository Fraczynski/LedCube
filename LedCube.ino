#include <WiFi.h>

#define BIT_CHECK(n, i) (n >> i & 1)

//pins configuration
const uint8_t pinsNumber = 64;
const uint8_t SER = 13;
const uint8_t RCLK = 15;
const uint8_t SRCLK = 14;
uint8_t layer = 0;

//cube
uint8_t cube[8][8];
uint8_t i = 0, j = 0, k = 0;
bool loading = false;
int timer;
uint64_t randomTimer;
const uint8_t POSITION_X = 0;
const uint8_t POSITION_Z = 2;
const uint8_t POSITION_Y = 4;
const uint8_t NEG_X = 1;
const uint8_t NEG_Z = 3;
const uint8_t NEG_Y = 5;
uint8_t selX = 0;
uint8_t selY = 0;
uint8_t selZ = 0;
uint8_t X_axis = 0;
uint8_t Y_axis = 1;
uint8_t Z_axis = 2;

String currentEffect;
//static effects
//const String STATIC_EFFECT = "NULL";
const String LIGHT = "-1";
const String CLEAR = "-2";
const String STATIC_EFFECT = "-10";

//dynamic effects
const String RAIN = "0";
const String PLANE_BOING = "1";
const String SEND_VOXELS = "2";
const String WOOP_WOOP = "3";
const String CUBE_JUMP = "4";
const String GLOW = "5";
const String TEXT = "6";
const String FIREWORKS = "7";
const String STROBOSCOPE = "8";
const String ANTS = "9";
const String AXIS_UPDOWN_RANDSUSPEND = "10";
const String SHOW_CUBE = "11";

//frame break times
String textToDisplay = String("TEST");
double timeScale = 1.0;
uint16_t currentEffectTime = 0;
uint16_t currentEffectOriginalTime = 0;
const uint16_t RAIN_TIME = 2000;
const uint16_t PLANE_BOING_TIME = 3000;
const uint16_t SEND_VOXELS_TIME = 1400;
const uint16_t WOOP_WOOP_TIME = 3500;
const uint16_t CUBE_JUMP_TIME = 2000;
const uint16_t GLOW_TIME = 80;
const uint16_t TEXT_TIME = 3000;
const uint16_t CLOCK_TIME = 5000;
const uint16_t FIREWORKS_TIME = 2000;
const uint16_t STROBOSCOPE_TIME = 400;
const uint16_t ANTS_TIME = 500;
const uint16_t AXIS_UPDOWN_RANDSUSPEND_TIME = 2000;
const uint16_t SHOW_CUBE_TIME = 2000;

//server
String ClientRequest;
uint8_t staticIP = 170;
WiFiServer server(80);
WiFiClient client;
String request;

void setup()
{
  loading = true;
  currentEffect = "0";
  timer = 0;

  //server
  char ssid[] = "*HotSpot*";
  const char *password = "792756125";
  ClientRequest = "";
  Serial.begin(115200);
  WiFi.disconnect();
  delay(3000);
  Serial.println("START");
  WiFi.begin(ssid, password);
  while (!(WiFi.status() == WL_CONNECTED))
  {
    delay(300);
    Serial.print("..");
  }
  Serial.println("Connected");
  IPAddress ip = WiFi.localIP();
  ip[3] = staticIP;
  WiFi.config(ip, WiFi.gatewayIP(), WiFi.subnetMask());
  Serial.print("IP:");
  Serial.println((WiFi.localIP()));
  server.begin();

  pinMode(SER, OUTPUT);
  pinMode(RCLK, OUTPUT);
  pinMode(SRCLK, OUTPUT);
}

void loop()
{
  client = server.available();

  if (client)
  {
    while (client.connected())
    {
      if (client.available())
      {
        request = ReadIncomingRequest();
        parseRequest();
      }
      switchEffect();
    }
    client.stop();
  }
  switchEffect();
}
