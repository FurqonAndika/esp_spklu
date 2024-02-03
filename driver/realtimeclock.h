#include <Wire.h>
#include <RTClib.h>

// rtclib by adafruit 2.1.3 version

DateTime now;
RTC_DS3231 rtc;

void rtc_init(){
    
    rtc.begin();


}

void set_time(int year,int month, int day, int hour, int minute){
    rtc.adjust(DateTime(year, month, day, hour, minute,0));
}

// String get_time(){
//     now = rtc.now();
//     return (String(now.day())+","+String(now.day())+","+String(now.year())+","+
//     String(now.hour())+","+String(now.minute())+","+String(now.second()));

// }

// String get_date(){
//      now = rtc.now();
//     return (String(now.day())+"/"+String(now.month())+"/"+String(now.year()));
// }

// String get_clock(){
//     //  now = rtc.now();
//     return (String(now.hour())+":"+String(now.minute())+":"+String(now.second()));
// }

// String get_hour(){
//     //  now = rtc.now();
//     return (String(now.hour(),DEC));
// }


// String get_minute(){
//      now = rtc.now();
//     return (String(now.minute(),DEC));
// }
