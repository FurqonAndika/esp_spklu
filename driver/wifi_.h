#include <ArduinoJson.h>
// #include <PubSubClient.h>
#include <ESP8266WiFi.h>
// #include <WiFiClientSecure.h>
// Helper macro to calculate array size
#define COUNT_OF(x) ((sizeof(x)/sizeof(0[x])) / ((size_t)(!(sizeof(x) % sizeof(0[x])))))


// URL 
// https://blog.thingsboard.io/2017/01/esp8266-gpio-control-over-mqtt-using.html


// #include "../src/ThingsBoard/src/ThingsBoard.h"
#include <ThingsBoard.h> //0.10.2


// #define TOKEN "l7rljv4es3zkc8cxdtli"
#define TOKEN "LbpOLuEtFWhx3GM70A3d" 
        // OLuEtFWhx3GM70A3d
// #define TOKEN "xue4das4ob60kvn0i3gv"  //CLOUD
#define THINGSBOARD_SERVER "demo.thingsboard.io"
// #define THINGSBOARD_SERVER "thingsboard.cloud"

const char* APssid        = "myesp"; //ssid default
const char* APpassword    = "1234567890"; //pass default 


WiFiServer server(80); 
WiFiClient client;
ThingsBoard tb(client);
// PubSubClient pub(client);

String http;
int status = 1000;

String txt= "<form action=\"/get\">\n"
             "    nama_wifi: <input type=\"text\" name=\"nama_wifi\">\n"
             "    password: <input type=\"text\" name=\"password\">\n <br>"
              "    token: <input type=\"text\" name=\"token\">\n"
              "    server: <input type=\"text\" name=\"token\">\n"
             "    <input type=\"submit\" value=\"Submit\">\n"
             "  </form><br>\n"
             "  </form>";

extern bool reset_pass;
extern String token;
extern void Relay_On();
extern void Relay_Off();
extern void Relay_Starter_On();
extern void Relay_Starter_Off();
extern void  Lcd_Set_Display(String title, String body);



RPC_Response processDelayChange(const RPC_Data &data)
{
  Serial.println("Received the set delay RPC method");

  // Process data

  status = data;

  Serial.print("Set new value: ");
  Serial.println(status);
  if (status==1){
        Lcd_Set_Display("Relay","On");
        Relay_On();
  }
  else if (status==0){
        Lcd_Set_Display("Relay","Off");
        Relay_Off();

  }


  return RPC_Response(NULL, status);
}

// Processes function for RPC call "getValue"
// RPC_Data is a JSON variant, that can be queried using operator[]
// See https://arduinojson.org/v5/api/jsonvariant/subscript/ for more details
RPC_Response processGetDelay(const RPC_Data &data)
{
  Serial.println("Received the get value method");
  Serial.println("start");
  status = data;
  Serial.println(status);

  return RPC_Response(NULL, status);
}

// Processes function for RPC call "setGpioStatus"
// RPC_Data is a JSON variant, that can be queried using operator[]
// See https://arduinojson.org/v5/api/jsonvariant/subscript/ for more details
RPC_Response processSetGpioState(const RPC_Data &data)
{
  Serial.println("Received the set GPIO RPC method");

  int pin = data["pin"];
  bool enabled = data["enabled"];

//   if (pin < COUNT_OF(leds_control)) {
//     Serial.print("Setting LED ");
//     Serial.print(pin);
//     Serial.print(" to state ");
//     Serial.println(enabled);

//     digitalWrite(leds_control[pin], enabled);
//   }

  return RPC_Response(data["pin"], (bool)data["enabled"]);
}

// RPC handlers
RPC_Callback callbacks[] = {
  { "setValue",         processDelayChange },
  { "getValue",         processGetDelay },
  { "setGpioStatus",    processSetGpioState },
};



void AP_Mode(){
        Lcd_Set_Display("Please Wait", "RESET MODE");
        delay(2000);
        WiFi.mode(WIFI_AP_STA);
        WiFi.softAP(APssid, APpassword);
        Serial.println( "IP address: " );  
        Serial.println( WiFi.softAPIP() );
        server.begin();
        Lcd_Set_Display("IP ADDRESS","");  
        lcd.setCursor(0,1);
        lcd.print(WiFi.softAPIP());
       
}

void sendResponse() {  
  // Send the HTTP response headers  
      client.println("HTTP/1.1 200 OK");  
      client.println("Content-type:text/html");  
      client.println("Connection: close");  
      client.println();   
}  

void updateWebpage() {  

  // Send the whole HTML  
      client.println("<!DOCTYPE html><html>");  
      client.println("<head>");  
      client.println("<title>ESP32 WiFi Station</title>");  
      client.println("</head>");  

  // Web Page Heading  
      client.println("<body><h1>CHANGE WIFI CONFIGURATION</h1>");  
  // client.println("<body><h3>avoid using special character</h3>");  

      client.println(txt);
      client.print("<hr>");  

}


void Change_Wifi(){
        String name;
                if ( client = server.available() ) {  // Checks if a new client tries to connect to our server  
                        String clientData = "";  
                        while ( client.connected() ) {    // Wait until the client finish sending HTTP request  
                                if ( client.available() ) {     // If there is a data,  
                                        char c = client.read();      //  read one character  
                                        http += c;            //  then parse it  
                                        Serial.write(c);    
                                        if (c == '\n') {         // If the character is carriage return,   
                                                //  it means end of http request from client  
                                                if (clientData.length() == 0) { //  Now that the clientData is cleared,  
                                                        sendResponse();        //    perform the necessary action  
                                                        updateWebpage();  
                                                        break;  
                                                } 
                                                else {  
                                                        clientData = "";       //  First, clear the clientData  
                                                }  
                                        } 
                                        else if (c != '\r') {      // Or if the character is NOT new line  
                                                clientData += c;        //  store the character to the clientData variable  
                                        }  
                                }  
                        }

                        // Serial.println(http);
                        int mark;

                        String pass,token, server;
                        int start,end;
                        start = http.indexOf("nama_wifi=");
                        mark = start;
                        // Serial.println(mark);
                        if (mark>10){
                                end = http.indexOf('\r');
                                http= http.substring(start-1+1);
                                // Serial.println(http);
                                start = http.indexOf("=");
                                end = http.indexOf("&");
                                name = http.substring(start+1,end);

                                http = http.substring(end+1,http.indexOf('\r'));
                                Serial.println(http);
                                start = http.indexOf("=");
                                end = http.indexOf("&");
                                
                                pass = http.substring(start+1,end);

                                // Serial.println(pass);
                                http = http.substring(end+1,http.indexOf('\r'));
                                Serial.println(http);
                                start = http.indexOf("=");
                                end = http.indexOf("&");
                                token = http.substring(start+1,end);


                                http = http.substring(end+1,http.indexOf('\r'));
                                Serial.println(http);
                                start = http.indexOf("=");
                                end = http.indexOf("&");
                                server = http.substring(start+1,-1);
                                // Serial.println(token);
                                // Serial.println(token);
                                // Serial.println(password);
                                char c;
                                for (int x=0; x<name.length(); x++){
                                        c = name[x];
                                         if (c=='+')name[x]=' ';

                                }
                                for (int x=0; x<pass.length(); x++){
                                        c = pass[x];
                                        if (c=='+')pass[x]=' ';
                                }
                                //  for (int x=0; x<token.length(); x++){
                                //         c = token[x];
                                //         if (c=='+')token[x]=' ';
                                // }
                                Serial.println("name="+ name);
                                Serial.println("pass="+pass);
                                Serial.println("token="+token);
                                Serial.println("server="+server);
                                reset_pass=false;
                                String name_=name;
                                name +='&';
                                name +=pass;
                                name +='/';
                                name +=token;
                                name +=',';
                                name +=server;
                                name +=';';

                                for (int x = 0; x<=90; x++){
                                        EEPROM.write(x,0);
                                        delay(10);
                                }
                                EEPROM.commit();
                                if (name.length()<=90){
                                        for (int x=0; x<name.length(); x++){
                                              EEPROM.write(x, name[x]);
                                        }
                                        EEPROM.commit();
                                        // Lcd_Set_Display(name_, pass);
                                        // delay(3000);
                                }
                        }
                        http = "";  
                        client.stop();            // Disconnect the client.  
                }

        }

void Wifi_Connect(String ssid, String password){
        WiFi.begin(ssid.c_str(), password.c_str());
        unsigned long time_break =millis();
        while (WiFi.status() != WL_CONNECTED) {
                delay(500);
                Serial.print(".");
                // if (millis()-time_break>10000){
                //         break;
                // }
        }
        // Serial.println();
        Serial.println("WiFi connected");


}