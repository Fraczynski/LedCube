#include <SPI.h>
#include <WiFi.h>

//cube
uint8_t cube[8][8];
bool loading;

//server
String  ClientRequest;
IPAddress staticIP642_10(192, 168, 1, 10);
IPAddress gateway642_10(192, 168, 1, 1);
IPAddress subnet642_10(255, 255, 255, 0);
WiFiServer server(80);
WiFiClient client;
String myresultat;

String ReadIncomingRequest() {
  while (client.available()) {
    ClientRequest = (client.readStringUntil('\r'));
    if ((ClientRequest.indexOf("HTTP/1.1") > 0) && (ClientRequest.indexOf("/favicon.ico") < 0)) {
      myresultat = ClientRequest;
    }
  }
  return myresultat;
}

void setup() {
  loading = true;

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
  if (!client) {
    return;
  }
  while (!client.available()) {
    delay(1);
  }

  //main code here
  String request = ReadIncomingRequest();
  request.remove(0, 5);
  request.remove(request.length() - 9, 9);
  Serial.println("Incoming request: " + request);
  if (request == "clear") {
    clearCube();
  }
  else if (request == "light") {
    lightCube();
  }
  else if(request.length() == 1){
    lightLayer(request.toInt());
  }
  else if(request.length() == 3){
    setVoxel((int)request[0], (int)request[1], (int)request[2]);
  }

  giveResponse();
  renderCube();
}

void renderCube() {
  for (uint8_t i = 0; i < 8; i++) {
    digitalWrite(SS, LOW);
    SPI.transfer(0x01 << i);
    for (uint8_t j = 0; j < 8; j++) {
      SPI.transfer(cube[i][j]);
    }
    digitalWrite(SS, HIGH);
  }
}

void setVoxel(uint8_t x, uint8_t y, uint8_t z) {
  cube[7 - y][7 - z] |= (0x01 << x);
}

void clearVoxel(uint8_t x, uint8_t y, uint8_t z) {
  cube[7 - y][7 - z] ^= (0x01 << x);
}

bool getVoxel(uint8_t x, uint8_t y, uint8_t z) {
  return (cube[7 - y][7 - z] & (0x01 << x)) == (0x01 << x);
}

void lightCube() {
  for (uint8_t i = 0; i < 8; i++) {
    for (uint8_t j = 0; j < 8; j++) {
      cube[i][j] = 0xFF;
    }
  }
}

void lightLayer(int layer){
  clearCube();
  for (int i = 0; i < 8; i++){
    for (int j = 0; j < 8; j++){
      setVoxel(i, layer, j);
    }
  }
}

void clearCube() {
  for (uint8_t i = 0; i < 8; i++) {
    for (uint8_t j = 0; j < 8; j++) {
      cube[i][j] = 0;
    }
  }
}

void giveResponse() {
  String html = "Ok";
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");
  client.println(html);
  client.stop();
  delay(1);
  client.flush();
}
