#include <WiFi.h>
#include <WebServer.h>
#include "auth.h"

// https://qiita.com/mine820/items/01d5b7dbf65296c6f6e8

WebServer server(80); //ポート80番

// WiFi情報
// extern char *ssid = "Buffalo-G-1230";
// extern char *pass = "3iyru46wnpvee";

// HTMLを組み立てる
String html = "<!DOCTYPE html><html><head><meta charset=\"utf-8\"><title>LEDをON/OFFする</title></head><body><p>リンクをクリックするとLEDがON/OFFします</p><ul><li><a href=\"/?button=on\">ON</a></li><li><a href=\"/?button=off\">OFF</a></li></ul></body></html>";

int ledPin = 15;

// LEDのON/OFF
void handleLED()
{
  if (server.hasArg("button"))
  {
    if (server.arg("button").equals("on"))
    {
      digitalWrite(ledPin, HIGH);
    }
    else
    {
      digitalWrite(ledPin, LOW);
    }
    Serial.println(server.arg("button"));
  }
  server.send(200, "text/html", html);
}

// 存在しないアドレスが指定された時の処理
void handleNotFound(void)
{
  server.send(404, "text/plain", "Not Found.");
}

// 初期化
void setup()
{
  // シリアルポートの初期化
  Serial.begin(115200);

  // WiFiのアクセスポイントに接続
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
  }
  // ESP32のIPアドレスを出力
  Serial.println("WiFi Connected.");
  Serial.print("IP = ");
  Serial.println(WiFi.localIP());

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  //このアドレスにアクセスしたときに処理される関数を指定
  server.on("/", handleLED);
  // server.on("/led", handleLED);
  server.onNotFound(handleNotFound);
  // Webサーバーを起動
  server.begin();
}

// 処理ループ
void loop()
{
  server.handleClient();
}