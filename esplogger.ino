#include "driver/eeprom.h"
#include "driver/lcd.h"
#include "driver/wifi_.h"
#include "driver/relay.h"
#include "driver/realtimeclock.h"
#include "driver/pzem.h"


#define button_reset D3



String ssid, password,token;

char tokenchar[30];
char serverchar[30];
bool reset_pass = true;
String data_gps = "";

unsigned long waktu = 0;
unsigned long refresh = 0;



void setup() {
  Serial.begin(115200);
  pinMode(button_reset,INPUT_PULLUP);
  Relay_Init();
  Relay_Off();
  rtc_init();
  LCD_Init();

  EEPROM_Init();


  // membaca ssid dan pass di memory eeprom dan token 
  ssid = Read_SSID();
  password = Read_Pass_SSID();
  token = Read_Token();
  String server = Read_Server();

  Serial.println("ssid :" + ssid);
  Serial.println("pass :" + password);
  Serial.println("token :" +token);
  Serial.println("server :" +server);
  token.toCharArray(tokenchar,token.length()+1);
  server.toCharArray(serverchar, server.length()+1);
  Lcd_Set_Display("Connecting to", ssid);

  if (!digitalRead(button_reset)) {  //ketika pin button tekan saat pertama kali dinyalakan maka akan masuk ke mode AP(Access point)
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
    if (!tb.connect(serverchar,tokenchar)){
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


   
  if (millis() - waktu > 10000) {
    Lcd_Set_Display("Send Data","To Server");
    
    tb.sendTelemetryFloat("voltageR",Voltage_R());
    tb.sendTelemetryFloat("voltageS",Voltage_S());
    tb.sendTelemetryFloat("voltageT",Voltage_T());
    tb.sendTelemetryFloat("currentR",Current_R());
    tb.sendTelemetryFloat("currentS",Current_S());
    tb.sendTelemetryFloat("currentT",Current_T());
   
    waktu = millis();
    Lcd_Set_Display("Data","Sent");
   
  }
  if (millis()-refresh>=1000){
    Lcd_Set_Display(get_date(),get_clock());
    if((get_hour()==0) && (get_minute()<=10)){
      Relay_Off();
    }
    else if((get_hour()==0) && (get_minute()>10)){
      Relay_On();
    }
    refresh=millis();
  }
}