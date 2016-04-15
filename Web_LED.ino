#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

const char* ssid = "YourSSID";
const char* password = "YourSSIDPassword";
const char* host = "LED"; //Changing this will result in a different URL. Default: led = http://led.local

ESP8266WebServer server(80);
const char* serverIndex = "<!DOCTYPE html><html lang='en'><head><meta charset='UTF-8'><title>LED</title><script src='https://ajax.googleapis.com/ajax/libs/jquery/1.12.0/jquery.min.js'></script><script>$(document).ready(function(){$('#on').click(function(){$.get('/on', function(data, status){$('#status').html('on'); }); }); $('#off').click(function(){$.get('/off', function(data, status){$('#status').html('off'); }); });  }); function update(){$.get('/status', function(data, status){$('#status').html(data); $('title').html('LED '+data);}); } var refresh = setInterval(function() { update() }, 500); </script></head><body><p style='display: inline;'>LED is currently <div id='status' style='display:inline;'>?? </div>. </p><button id='on'>Turn LED On</button><button id='off'>Turn LED Off</button></body></html>";

const int led = 13;

void handleRoot() {
  //digitalWrite(led, 1);
  

}

void handleNotFound(){
  digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(led, 0);
}

void setup(void){
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin(host)) {
    Serial.println("MDNS responder started");
  }

  server.on("/", [](){
    server.send(200, "text/html", serverIndex);
  });

  server.on("/on", [](){
    digitalWrite(led, 1);
    server.send(200, "text/plain", "LED is On");
  });

  server.on("/off", [](){
    digitalWrite(led, 0);
    server.send(200, "text/plain", "LED is Off");
  });

  server.on("/status", [](){
    if(digitalRead(led) == 0){
      server.send(200, "text/plain", "off");
    } else {
      server.send(200, "text/plain", "on");
    }
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void){
  server.handleClient();
}
