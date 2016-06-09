#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
//IFTTT informationer


//WiFi informationer
const char* ssid     = "Mark's iPhone";
const char* password = "LOLl0l69";
HTTPClient http;

void setup() {
  Serial.begin(115200);
  delay(10);
  wifiConnect();
  startHTTP();

      
}


void startHTTP() {
  
  Serial.println("[HTTP] begin...");
  // configure traged server and url
  //http.begin("192.168.1.12", 443, "/test.html", true, "7a 9c f4 db 40 d3 62 5a 6e 21 bc 5c cc 66 c8 3e a1 45 59 38"); //HTTPS
  http.begin("graungaard.com", 80, url); //HTTP
  
}

void loop() {
  wifiCheck(); //Maintain wifi connection
  yield(); //Let the ESPcore handle background tasks
  
}

void wifiConnect() {
  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

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

void wifiCheck()
{
  if (WiFi.status() != WL_CONNECTED) //if wifi is connected: do nothing.
  {
    int tickCount = 0;
    Serial.println("Wifi dropped. Retry in 60 seconds.");
    delay(60000); //wait 60 seconds
    Serial.println("Connecting");
    WiFi.begin(ssid, password); //reconnect

    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.println(".");
      tickCount++;
      if (tickCount > 100) //after awaiting reconnection for 50 seconds
      {
        Serial.println("Wifi fail...");
        //This is where you end up if the connection was lost and unrecoverable
        while (1); //Endless loop...
      }
    }

    //This is the place to do something in case the connection was lost but fixed.

  }
}



int makeGetRequest(String url) {


  
}


void triggerIFTTTevent(String event) {

        String url = "/3D/" + ID; //
        
        Serial.print("[HTTP] GET: ");
        Serial.println(url);
        // start connection and send HTTP header
        int httpCode = http.GET();
        if(httpCode) {
            // HTTP header has been send and Server response header has been handled
            Serial.print("[HTTP] Response! Code: ");
            Serial.println(httpCode);

            // file found at server
            if(httpCode == 200) { //SUCCESS!
              /*
        Code here will be run, when the server has accepted your request.
              */
                String payload = http.getString();
                Serial.println(payload);
            }
        } else {
            Serial.println("[HTTP] GET... failed, no connection or no HTTP server");
        }

}

