#include "../src/lcd/LiquidCrystal_I2C.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);

// untuk pin yang digunakan pada pin i2c esp32

/*
PIN I2C NODE MCU
D1 -> SCL
S2 -> SDA

*/

void Lcd_Set_Display(String title, String body){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(title);
  lcd.setCursor(0,1);
  lcd.print(body);  
}


void LCD_Init(){
  lcd.begin();
  lcd.backlight();
}