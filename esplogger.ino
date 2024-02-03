#include "driver/eeprom.h"
#include "driver/realtimeclock.h"
#include "driver/lcd.h"
#include "driver/wifi_.h"
#include "driver/relay.h"

#include "driver/pzem.h"
#include "driver/buzzer.h"


#define button_reset D8



String ssid, password,token;

char tokenchar[30];
char serverchar[30];
bool reset_pass = true;
String data_gps = "";

unsigned long waktu = 0;
unsigned long refresh = 0;

String status_relay = "ON";

void setup() {
  Serial.begin(9600);
  pinMode(button_reset,INPUT);
  Relay_Init();
  Relay_Off();
  rtc_init();
  LCD_Init();
  buzzer_init();

  EEPROM_Init();

  Serial.println(Voltage_R());
  Serial.println(Voltage_S());
  Serial.println(Voltage_T());
  Serial.println(Current_R());
  Serial.println(Current_S());
  Serial.println(Current_T());
    
  


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




  // connect to WIFI
  Wifi_Connect(ssid, password);
  // Lcd_Set_Display("Connected to ", ssid);
  // pub_init();


  // ketika dicolokin ke laptop
  // if (Serial.available()){
  //   rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  // }

 

}

void loop() {
  now = rtc.now();

  if (digitalRead(button_reset)) {  //ketika pin button tekan saat pertama kali dinyalakan maka akan masuk ke mode AP(Access point)
    AP_Mode();
    buzzer_once();
    while (reset_pass) {
      Change_Wifi();
      
      // Serial.println(digitalRead(button_reset));
      
    }
  }
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
      buzzer_twice();
      return;
    }
    if (!tb.RPC_Subscribe(callbacks, COUNT_OF(callbacks))) {
      Serial.println("Failed to subscribe for RPC");
      buzzer_twice();
      return;
    }
  }
  
  tb.loop();


   
  if (millis() - waktu > 5000) {
    // Lcd_Set_Display("Send Data","To Server");
    
    tb.sendTelemetryFloat("voltageR",Voltage_R());
    tb.sendTelemetryFloat("voltageS",Voltage_S());
    tb.sendTelemetryFloat("voltageT",Voltage_T());
    tb.sendTelemetryFloat("currentR",Current_R());
    tb.sendTelemetryFloat("currentS",Current_S());
    tb.sendTelemetryFloat("currentT",Current_T());

    char statuschar[status_relay.length()+1];
    status_relay.toCharArray(statuschar, status_relay.length()+1);
    tb.sendTelemetryString("status", statuschar);
   
    waktu = millis();
    // Lcd_Set_Display("Data","Sent");
   
  }
  if (millis()-refresh>=1000){
    Serial.println("hour:"+String(now.hour()));
    Serial.println("minute:"+String(now.minute()));
    //  Serial.println("jam:"+String(now.hour()));
    //  Serial.println("menit:"+String(now.minute()));

    Serial.println(Voltage_R());
    Serial.println(Voltage_S());
    Serial.println(Voltage_T());
    Serial.println(Current_R());
    Serial.println(Current_S());
    Serial.println(Current_T());
    
    // Lcd_Set_Display(get_date(),get_clock());
    if((now.hour()==0) && (now.minute()<=10)){
      Relay_Off();
      status_relay = "OFF";
    }
    else if((now.hour()==0) && (now.minute()>10)){
      Relay_On();
      status_relay="ON";
    }
    refresh=millis();
  }
}