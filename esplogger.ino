#include "driver/eeprom.h"
#include "driver/realtimeclock.h"
#include "driver/lcd.h"
#include "driver/wifi_.h"
#include "driver/relay.h"
#include "driver/pzem.h"
#include "driver/buzzer.h"


#define button_reset D8



String ssid, password,token;
String status_relay = "ON";

char tokenchar[30];
char serverchar[30];
bool reset_pass = true;


unsigned long waktu = 0;
unsigned long refresh = 0;



void setup() {

  // inisiasi semua periperal
  Serial.begin(9600);
  pinMode(button_reset,INPUT);
  Relay_Init();
  Relay_Off();
  rtc_init();
  LCD_Init();
  buzzer_init();
  EEPROM_Init();

  // fungsi ini dilakukan untuk handle error pada pzem karena menggunakan serial0
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

  // print(ssid, pass, token dan server)
  Serial.println("ssid :" + ssid);
  Serial.println("pass :" + password);
  Serial.println("token :" +token);
  Serial.println("server :" +server);

  // mengubah string menjadi char
  token.toCharArray(tokenchar,token.length()+1);
  server.toCharArray(serverchar, server.length()+1);
  Lcd_Set_Display("Connecting to", ssid);

  // connect to WIFI
  Wifi_Connect(ssid, password); 

}

void loop() {
  now = rtc.now();
  
   //ketika pin button tekan maka akan masuk ke mode AP(Access point) untuk mengubah ssid, pass, token, server, dan set waktu
  if (digitalRead(button_reset)) { 
    AP_Mode();
    buzzer_once();
    while (reset_pass) {
      Change_Wifi();
      
    }
  }

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


  // callback thingsboard
  tb.loop();



  // mengirim data setiap 20 detik 
  if (millis() - waktu > 20000) {
    // Lcd_Set_Display("Send Data","To Server");
    

    // mengirim data ke thingsboard
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

  // cek waktu setiap detik, kalau di antara jam 0:00-0:10 maka relay akan OFF
  if (millis()-refresh>=1000){
    Serial.println("hour:"+String(now.hour()));
    Serial.println("minute:"+String(now.minute()));

    // PRINT NILAI PZEM UNTUK DEBUG
    Serial.println(Voltage_R());
    Serial.println(Voltage_S());
    Serial.println(Voltage_T());
    Serial.println(Current_R());
    Serial.println(Current_S());
    Serial.println(Current_T());
    
    // Lcd_Set_Display(get_date(),get_clock());
    if((now.hour()==0) && (now.minute()<=10) && (Current_R()<1)&& (Current_S()<1)&& (Current_T()<1)){
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