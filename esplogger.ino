#include "driver/eeprom.h"
#include "driver/lcd.h"
#include "driver/wifi_.h"
#include "driver/relay.h"


#define button_reset 15



String ssid, password,token;

char tokenchar[30];
bool reset_pass = true;
String data_gps = "";

unsigned long waktu = 0;
unsigned long refresh = 0;



void setup() {
  Serial.begin(115200);
  pinMode(button_reset,INPUT);
  Relay_Init();
  Relay_Off();

  EEPROM_Init();


  // membaca ssid dan pass di memory eeprom dan token 
  ssid = Read_SSID();
  password = Read_Pass_SSID();
  token = Read_Token();
  Serial.println("ssid :" + ssid);
  Serial.println("pass :" + password);
  Serial.println("token :" +token);
  token.toCharArray(tokenchar,token.length()+1);
  Lcd_Set_Display("Connecting to", ssid);

  if (digitalRead(button_reset)) {  //ketika pin button tekan saat pertama kali dinyalakan maka akan masuk ke mode AP(Access point)
    AP_Mode();
    
    while (reset_pass) {
      Change_Wifi();
      // Serial.println(digitalRead(button_reset));
      
    }
  }
  // connect to WIFI
  Wifi_Connect(ssid, password);
  Lcd_Set_Display("Connected to ", ssid);
  // pub_init();

 

}

void loop() {

 
  // String longlat = Read_GPS();
  // int delimiter;
  // delimiter = longlat.indexOf('/');
  // String lat = longlat.substring(0,delimiter);
  // String lon = longlat.substring(delimiter+1,-1);
  // Serial.println(longlat);
  // Serial.println(lon);
  // Serial.println(lat);
 

  // char lon_[lon.length()+1];
  // char lat_ [lat.length()+1];

  // lon.toCharArray(lon_,lon.length()+1);
  // lat.toCharArray(lat_, lat.length()+1);


  if (!tb.connected()) {
    if (!tb.connect(THINGSBOARD_SERVER,tokenchar)){
      Serial.println("failed to connect");
      Lcd_Set_Display("Failed", "to connect");
      return;
    }
    if (!tb.RPC_Subscribe(callbacks, COUNT_OF(callbacks))) {
      Serial.println("Failed to subscribe for RPC");
      return;
    }
  }
  
  tb.loop();


   //if (timeElapsed > 10000) { //arduino akan mengirim data setiap 10 detik, jangan lebih kecil dari 5 detik
  if (millis() - waktu > 10000) {
    Lcd_Set_Display("Send Data","To Server");
    
    tb.sendTelemetryFloat("voltageR",random(1, 8));
    tb.sendTelemetryFloat("voltageS",random(1, 8));
    tb.sendTelemetryFloat("voltageT",random(1, 8));
    tb.sendTelemetryFloat("currentR",random(1, 8));
    tb.sendTelemetryFloat("currentS",random(1, 8));
    tb.sendTelemetryFloat("currentT",random(1, 8));
   
    waktu = millis();
    Lcd_Set_Display("Data","Sent");
   
  }

}
