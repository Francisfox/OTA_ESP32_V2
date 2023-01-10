#include <WebServer.h>
#include <esp_task_wdt.h>
#include "Saida.h";
#include "My_OTA.h";

const char* ssid = "DESKTOP";
const char* password = "12345678";
unsigned long int tempoAnterior = 0;
String old_value, value;
byte limite = 99;                                     //
unsigned long int j; 
Saida LED1(2);

#include "My_WebSocket.h"
//#include "mrdiy.h";

void setup(void) {
  //WDT
  esp_task_wdt_init(20, true);
  esp_task_wdt_add(NULL);
  
  Serial.begin(115200);
  WiFi.begin(ssid,password);
  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(1000);
  }
  WiFi.mode(WIFI_STA);
  Serial.println("Start ESP ");
  Serial.println(WiFi.localIP());
  
  server.on("/",WebSite);
  //server.on("/", handleMain);
  My_updade_OTA();
  server.begin();
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
}

void loop() {
  esp_task_wdt_reset();
  if (millis() - j >= limite){
    j = millis();
    webSocket.loop();
    server.handleClient();
    Evento_server_MyWebSocket();
    //Evento_server_mrdiy();
    //LED1.test_Saida();
  }
  delay(2);//allow the cpu to switch to other tasks
}
