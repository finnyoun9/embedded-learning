#include <Arduino.h>

#include <Wire.h>
#include "SSD1306.h"
#include <LittleFS.h>
#include <WiFi.h>
#include <WebServer.h>

SSD1306 oled(0x3C);
WebServer server(80);

const int ledPin = 2;
String wifiSSID, wifiPass;

// ---- LittleFS 工具函数 ----
String readFile(const char* path) {
  File f = LittleFS.open(path, "r");
  if (!f) return "";
  String content = f.readString();
  f.close();
  return content;
}

void writeFile(const char* path, const char* content) {
  File f = LittleFS.open(path, "w");
  if (f) { f.print(content); f.close(); }
}

// ---- 首次启动创建默认文件 ----
void createDefaultFiles() {
  if (!LittleFS.exists("/wifi.conf")) {
    writeFile("/wifi.conf", "YOUR_SSID\nYOUR_PASSWORD");
  }
  if (!LittleFS.exists("/index.html")) {
    String html = "<!DOCTYPE html><html><head><meta charset='utf-8'>"
      "<meta name='viewport' content='width=device-width,initial-scale=1'>"
      "<style>body{font-family:sans-serif;text-align:center;margin-top:60px}"
      "a{display:inline-block;margin:10px;padding:20px 40px;color:#fff;"
      "text-decoration:none;border-radius:8px;font-size:18px}"
      "a.on{background:#34c759}a.off{background:#ff3b30}</style></head>"
      "<body><h1>ESP32 FileServer</h1>"
      "<p>这个网页来自 Flash 文件</p>"
      "<p><a href='/on' class='on'>开灯</a> "
      "<a href='/off' class='off'>关灯</a></p>"
      "<p><a href='/log'>查看日志</a></p></body></html>";
    writeFile("/index.html", html.c_str());
  }
}

// ---- Web 路由 ----
void handleRoot() {
  File f = LittleFS.open("/index.html", "r");
  server.streamFile(f, "text/html; charset=utf-8");
  f.close();
}

void handleOn() {
  digitalWrite(ledPin, HIGH);
  writeFile("/led_state.txt", "ON");
  server.sendHeader("Location", "/", true);
  server.send(302);
}

void handleOff() {
  digitalWrite(ledPin, LOW);
  writeFile("/led_state.txt", "OFF");
  server.sendHeader("Location", "/", true);
  server.send(302);
}

void handleLog() {
  String log = readFile("/boot_log.txt");
  server.send(200, "text/plain; charset=utf-8", log);
}

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  oled.begin();

  // 1. 挂载文件系统
  if (!LittleFS.begin(true)) {
    oled.setCursor(0, 0); oled.print("FS FAIL"); oled.display();
    return;
  }
  createDefaultFiles();

  // 2. 从文件读取 WiFi 配置
  String cfg = readFile("/wifi.conf");
  int nl = cfg.indexOf('\n');
  wifiSSID = cfg.substring(0, nl);
  wifiPass = cfg.substring(nl + 1);
  wifiPass.trim();
  wifiSSID.trim();

  oled.clear();
  oled.setCursor(0, 0);
  oled.print("WiFi from file:");
  oled.setCursor(0, 16);
  oled.print(wifiSSID.c_str());
  oled.display();

  // 3. 连接 WiFi
  WiFi.begin(wifiSSID.c_str(), wifiPass.c_str());
  Serial.printf("连接 %s ...\n", wifiSSID.c_str());
  while (WiFi.status() != WL_CONNECTED) { delay(500); Serial.print("."); }
  Serial.printf("\nIP: %s\n", WiFi.localIP().toString().c_str());

  // 4. Web 服务器 — HTML 来自文件
  server.on("/", handleRoot);
  server.on("/on", handleOn);
  server.on("/off", handleOff);
  server.on("/log", handleLog);
  server.begin();

  // 5. 记录启动日志
  int boot = 1;
  File f = LittleFS.open("/boot_count.txt", "r");
  if (f) { boot = f.parseInt() + 1; f.close(); }
  writeFile("/boot_count.txt", String(boot).c_str());

  f = LittleFS.open("/boot_log.txt", "a");
  f.printf("Boot #%d  IP=%s\n", boot, WiFi.localIP().toString().c_str());
  f.close();

  // 6. 恢复上次 LED 状态
  String lastLed = readFile("/led_state.txt");
  if (lastLed == "ON") digitalWrite(ledPin, HIGH);

  oled.setCursor(0, 32);
  oled.print("IP:");
  oled.print(WiFi.localIP().toString().c_str());
  oled.setCursor(0, 48);
  oled.print("Boot#");
  oled.print(boot);
  oled.setCursor(0, 56);
  oled.print("HTML from Flash!");
  oled.display();

  // 列出文件
  Serial.println("--- / 目录 ---");
  File root = LittleFS.open("/");
  File file = root.openNextFile();
  while (file) {
    Serial.printf("  %s  %d bytes\n", file.name(), file.size());
    file = root.openNextFile();
  }
}

void loop() {
  server.handleClient();
  delay(10);
}
