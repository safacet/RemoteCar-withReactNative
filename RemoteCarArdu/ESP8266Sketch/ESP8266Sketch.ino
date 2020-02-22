#include <WebSocketsServer.h>
#include <ESP8266WiFi.h>

IPAddress ip(192, 168, 1, 100);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

char ssid[] = "Acet2";
char pass[]= "ankara06";

WiFiServer server(80);

WebSocketsServer webSocket(81);

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("Connecting to WiFi");
  Serial.println();

  WiFi.config(ip, gateway, subnet);
  WiFi.begin(ssid, pass);
  while ( WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("CONNECTED");

  server.begin();

  webSocket.begin();
  webSocket.onEvent(webSocketEvent);

}

void loop() {

  webSocket.loop();

  WiFiClient client = server.available();
  if (!client) { return; }

  client.flush();
  delay(5);

}

void webSocketEvent(byte num, WStype_t type, uint8_t* payload, size_t length) {

  if (type == WStype_TEXT) {
    String recvMessage="";
    for (int i =0; i < length; i++) {
      recvMessage += (char)payload[i];
    }
    Serial.println(recvMessage);
  }
}
