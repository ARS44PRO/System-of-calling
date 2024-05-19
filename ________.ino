#define BTN 13
#include <GyverButton.h>
GButton btn(BTN);

#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

const char* ssid = "MTS_Router_166788";
const char* password = "70467277";

void setup() {
  Serial.begin(115200);
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

void loop() {
  HTTPClient http;    //Объявить объект класса HttpClient
  WiFiClient wifiClient;
  http.begin(wifiClient, "http://192.168.1.1:8090/post");      //Укажите адрес запроса
  http.addHeader("Content-Type", "text/plain");  //Укажите заголовок типа содержимого
  btn.tick();
  if (btn.isSingle()){
    http.POST("2");
  }else if (btn.isDouble()){
    http.POST("1");
  }else if (btn.isHolded()){
    http.POST("0");
  }
  //int httpCode = http.POST("ok");   //Отправьте запрос
  //String payload = http.getString();                  //Получите полезную нагрузку ответа

  //Serial.println(httpCode);   //Распечатать код возврата HTTP
  //Serial.println(payload);    //Полезная нагрузка для ответа на запрос печати

  http.end();  //Закрыть соединение


  delay(10);  //Ждем 30 сек.

}
