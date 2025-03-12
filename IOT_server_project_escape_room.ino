#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

IPAddress    apIP(55, 55, 55, 58);

const char* ssid = "MySmartClockMor";
ESP8266WebServer server(80);

void Wifi_setup(){
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP(ssid);
  server.on("/", handleRoot);
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");
}

void wifi_loop() {
	    server.handleClient();
}

void handleNotFound() {
	    String message = "File Not Found \n \n";
	    message += "URI: ";
	    message += server.uri();
	    message += "\nMethod: ";
	    message += (server.method() == HTTP_GET) ? "GET" : "POST";
	    message += "\nArguments: ";
	    message += server.args();
	    message += "\n";
	    for (uint8_t i = 0; i < server.args(); i++) {
	        message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
	    }
	    server.send(404, "text/plain", message);
}

void handleRoot(){
  char html[2000];
  if (server.hasArg("btn")) {
    btn=server.arg("btn");//.ToInt() עבור מספרים
    Serial.println(btn);
  }
  if (server.hasArg("myPassword")) {
    myPassword=server.arg("myPassword");
    Serial.println(myPassword);
  }
  if (server.hasArg("val")) {
    val=server.arg("val");
    Serial.println(val);
  }
  /*if (server.hasArg("num")) {
    number=(server.arg("num").ToInt()*x)+number;
  }*/
  strcat(html,"<!DOCTYPE html>");
  strcat(html,"<html lang='en'>");
  strcat(html,"<head>");
    strcat(html,"<meta charset='UTF-8'>");
    strcat(html,"<meta name='viewport' content='width=device-width, initial-scale=1.0'>");
    strcat(html,"<title>Document</title>");
  strcat(html,"</head>");
  strcat(html,"<body>");
  strcat(html,"<form>");
      strcat(html,"<button name='btn' value='unlock' style='padding:100px;font-size:xx-large;'>Open Lock</button><br>");
      strcat(html,"<input name='myPassword' type='text' ><br>");
  strcat(html,"</form>");
  strcat(html,"</body>");
  strcat(html,"</html>");

  server.send(200,"text/html",html);
}