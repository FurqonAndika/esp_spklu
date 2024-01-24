#include <Wire.h>
#include <RTClib.h>

// rtclib by adafruit 2.1.3 version

DateTime now;
RTC_DS3231 rtc;

void rtc_init(){
    
    rtc.begin();


}

String get_time(){

    return (String(now.day())+","+String(now.day())+","+String(now.year())+","+
    String(now.hour())+","+String(now.minute())+","+String(now.second()));

}

String get_date(){
    return (String(now.day())+"/"+String(now.month())+"/"+String(now.year()));
}

String get_clock(){
    return (String(now.hour())+":"+String(now.minute())+":"+String(now.second()));
}

int get_hour(){
    return now.hour();
}


int get_minute(){
    return now.minute();
}