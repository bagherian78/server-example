#include <Arduino.h>
#include <Wire.h>
#ifdef ESP32
  #include <WiFi.h>
  #include <AsyncTCP.h>
#else
  #include <ESP8266WiFi.h>
  #include <ESPAsyncTCP.h>
#endif
#include <ESPAsyncWebServer.h>

AsyncWebServer server(8099);

const char* PARAM_INPUT_1 = "input1";
const char* PARAM_INPUT_2 = "input2";
const char* PARAM_INPUT_3 = "input3";

// HTML web page to handle 3 input fields (input1, input2, input3)
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html><head>
  <title>Fun project for us</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  </head><body style="background:#1b252d url(https://bagherian1999.ir/media/images/Untitled-1.png);">
  <center>
  <p style="color:white">i'm working on this project</p><br>
  <p style="color:white">this roject is based on esp8266 & ST32f407vg</p>
  <form action="/get">
    <p style="color:white;">please send me little sentences</p>
    <input type="text" name="input1"><br>
    <input type="submit" value="Submit" style="border: 2px solid #4CAF50;">
  </form><br>
  <p style="text-align:center !important;color:white;">made with<span style="color:#e81224;"> &#x2665;</span> by © 2020 mohammad hosein bagherian</p>
  <center>
</body></html>)rawliteral";

void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}

void setup() {
  Serial.begin ( 115200 );
  //WiFi.mode ( WIFI_STA );
  WiFi.begin("Soroush", "yahosein038,");
  Serial.println ( "" );

  // Wait for connection
  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }

  Serial.println ( "IP address: " );
  Serial.println ( WiFi.localIP() );
  // Send web page with input fields to client
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  });

  // Send a GET request to <ESP_IP>/get?input1=<inputMessage>
  server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String inputMessage;
    String inputParam;
    // GET input1 value on <ESP_IP>/get?input1=<inputMessage>
    if (request->hasParam(PARAM_INPUT_1)) {
      inputMessage = request->getParam(PARAM_INPUT_1)->value();
      inputParam = PARAM_INPUT_1;
    }
    // GET input2 value on <ESP_IP>/get?input2=<inputMessage>
    else if (request->hasParam(PARAM_INPUT_2)) {
      inputMessage = request->getParam(PARAM_INPUT_2)->value();
      inputParam = PARAM_INPUT_2;
    }
    // GET input3 value on <ESP_IP>/get?input3=<inputMessage>
    else if (request->hasParam(PARAM_INPUT_3)) {
      inputMessage = request->getParam(PARAM_INPUT_3)->value();
      inputParam = PARAM_INPUT_3;
    }
    else {
      inputMessage = "No message sent";
      inputParam = "none";
    }
    Serial.println(inputMessage);
    request->send(200, "text/html", "HTTP GET request sent to your ESP on input field (" 
                                     + inputParam + ") with value: " + inputMessage +
                                     "<br><a href=\"/\">Return to Home Page</a>"+"<br><p>to see me folow<a href=\"https://bagherian1999.ir\">Click me</a> </p>");
  });
  server.onNotFound(notFound);
  server.begin();

}

void loop() {
  
}
