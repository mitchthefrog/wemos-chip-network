#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>

const byte DNS_PORT = 53;
IPAddress apIP(172, 217, 28, 1);
DNSServer dnsServer;
ESP8266WebServer webServer(80);

String responseHTML = "<!DOCTYPE html>"
"<html>"
"<head>"
"<link rel='stylesheet' href='https://maxcdn.bootstrapcdn.com/bootstrap/3.4.1/css/bootstrap.min.css'>"
"<meta charset='utf-8'>"
"<meta name='viewport' content='width=device-width, initial-scale=1'>"
"<title>frogland</title>"

"<style>"
"header { font-size: 45px; text-align: center; }"
"p { font-size: 30px; text-align: center; }"
".button1 { border-radius: 8px; font-size: 20px; text-align: center; transition-duration: 0.4s; }"
".button1:hover {background-color: #4CAF50; color: white;}"
".button2 { border-radius: 8px; font-size: 20px; text-align: center; transition-duration: 0.4s; }"
".button1:hover {background-color: #444336; color: white;}"
"</style>"

"</head>"
"<body>"
"<hr>"
"<br>"
"<div>"
"<header>Welcome to frog land</header>"
"<p>Enter frogland?</p>"
"<br>"
"<button class='button1'>Yes</button>"
"<button class='button2'>No</button>"
"</div>"
"</body>"
"<script src='https://ajax.googleapis.com/ajax/libs/jquery/3.6.1/jquery.min.js'></script>"
"<script src='https://maxcdn.bootstrapcdn.com/bootstrap/3.4.1/js/bootstrap.min.js'></script"
"</html>";

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255,255,255,0));
  WiFi.softAP("frog land");
  dnsServer.start(DNS_PORT, "*", apIP);
  webServer.onNotFound([]() {
    webServer.send(200, "text/html", responseHTML);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
    digitalWrite(LED_BUILTIN, HIGH);
  });
  webServer.begin();
}

void loop() {
 if (WiFi.softAPgetStationNum() == 0)
 {
    delay(100);
 } else {
    delay(100);
    dnsServer.processNextRequest();
    webServer.handleClient();
 }
}