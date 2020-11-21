#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <FS.h>

String getContentType(String filename);
bool handleFileRead(String path);

int stateS1;
int stateS2;
int stateS3;
int total;
int solar = 0;
int wind = 0;
int batt = 0;
int iter = 0;
int dWind = 0;
int dSolar = 0;
int dBatt = 0;
String lastRead;


ESP8266WebServer server(80);

SoftwareSerial mySerial(D5, D6);

void handleRoot() {
  Serial.println("---------------------------------------------");
  dSolar = stateS1 - solar;
  dWind = stateS2 - wind;
  dBatt = stateS3 - batt;
  total = stateS1 + stateS2 + stateS3;
  Serial.print("Switch Total = ");
  Serial.print(total);
  if (total == 5) {
    if (stateS3 == 0 || stateS2 == 0 || stateS1 == 0) {
      handleFileRead("/BadFeedback.html");
      lastRead = "/BadFeedback.html";
    }
    if (stateS1 == 3 && stateS2 == 1 && stateS3 == 1) {
      handleFileRead("/OkayFeedback.html");
      lastRead = "/OkayFeedback.html";
    }
    if (stateS1 == 1 && stateS2 == 2 && stateS3 == 2) {
      handleFileRead("/IdealFeedback.html");
      lastRead = "/IdealFeedback.html";
    }
    else {
      handleFileRead("/GoodFeedback.html");
      lastRead = "/GoodFeedback.html";
    }
    iter = 0;
    return;
  }
  if (total > 5) {
    handleFileRead("/OOPS.html");
    lastRead = "/OOPS.html";
    return;
  }
  Serial.println(" ");
  Serial.println("1");
  if (total == 0) {
    handleFileRead("/Introduction.html");
    lastRead = "/Introduction.html";
    iter = 1;
    return;
  }
  Serial.println("2");
  if (iter == 1) {
    if (dSolar != 0) {
      handleFileRead("/Solar1.html");
      lastRead = "/Solar1.html";
      solar = stateS1;
    }
    else if (dWind != 0) {
      handleFileRead("/Wind1.html");
      lastRead = "/Wind1.html";
      wind = stateS2;
    }
    else if (dBatt != 0) {
      handleFileRead("/Battery1.html");
      lastRead = "/Battery1.html";
      batt = stateS3;
    }
    iter = 2;
    return;
  }
  Serial.println("3");
  if (iter == 2) {
    if (dSolar != 0) {
      handleFileRead("/Solar2.html");
      lastRead = "/Solar2";
      solar = stateS1;
    }
    else if (dWind != 0) {
      handleFileRead("/Wind2.html");
      lastRead = "/Wind2";
      wind = stateS2;
    }
    else if (dBatt != 0) {
      handleFileRead("/Battery2.html");
      lastRead = "/Battery2.html";
      batt = stateS3;
    }
    iter = 3;
    return;
  }
  else {
//    handleFileRead(lastRead);
  }
}
int value;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  mySerial.begin(9600);

  WiFi.mode(WIFI_AP);
  WiFi.softAP("STACY", "alpha");

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("HotSpt IP:");
  Serial.println(myIP);

  server.on("/", handleRoot);
  server.onNotFound([]() {                              // If the client requests any URI
    if (!handleFileRead(server.uri()))                  // send it if it exists
      server.send(404, "text/plain", "404: Not Found"); // otherwise, respond with a 404 (Not Found) error
  });
  server.begin();
  Serial.println("HTTP server started");

  SPIFFS.begin();

}



void loop() {
  server.handleClient();

  if (mySerial.available()) {

    value = mySerial.read();

    if (value == 0) {
      stateS1 = 0;
    }
    if (value == 1) {
      stateS1 = 1;
    }
    if (value == 2) {
      stateS1 = 2;
    }
    if (value == 3) {
      stateS1 = 3;
    }
    if (value == 4) {
      stateS2 = 0;
    }
    if (value == 5) {
      stateS2 = 1;
    }
    if (value == 6) {
      stateS2 = 2;
    }
    if (value == 7) {
      stateS2 = 3;
    }
    if (value == 8) {
      stateS3 = 0;
    }
    if (value == 9) {
      stateS3 = 1;
    }
    if (value == 10) {
      stateS3 = 2;
    }
    if (value == 11) {
      stateS3 = 3;
    }
  }
}
String getContentType(String filename) { // convert the file extension to the MIME type
  if (filename.endsWith(".html")) return "text/html";
  else if (filename.endsWith(".css")) return "text/css";
  else if (filename.endsWith(".js")) return "application/javascript";
  else if (filename.endsWith(".ico")) return "image/x-icon";
  else if (filename.endsWith(".png")) return "image/png";
  else if (filename.endsWith(".jpg")) return "image/jpeg";
  else if (filename.endsWith(".svg")) return "image/svg+xml";
  return "text/plain";
}


bool handleFileRead(String path) { // send the right file to the client (if it exists)
  Serial.println("handleFileRead: " + path);
  if (path.endsWith("/")) path += "index.html";         // If a folder is requested, send the index file
  String contentType = getContentType(path);            // Get the MIME type
  if (SPIFFS.exists(path)) {                            // If the file exists
    File file = SPIFFS.open(path, "r");                 // Open it
    size_t sent = server.streamFile(file, contentType); // And send it to the client
    file.close(); // Then close the file again
    return true;
  }
}
