#include <EEPROM.h>


void EEPROM_Init(){
        EEPROM.begin(50);
        // String data = "ini ssid & ini pass/";
        // for (int x =0; x<data.length(); x++){
        //         EEPROM.write(x, data[x]);
        //         delay(10);
        //         EEPROM.commit();
        // }
}

String Read_SSID(){
        String temp = "";
        String ssid = "";

        for (int x=0; x<50; x++){
        char c = EEPROM.read(x);

        if (c==',')break;
        temp +=c;
        }
  
        ssid = temp.substring(0,temp.indexOf('&'));
        return ssid;
}


String Read_Pass_SSID(){
        String temp = "";
        String password = "";
        for (int x=0; x<50; x++){
                char c = EEPROM.read(x);

                if (c==',')break;
                temp +=c;
        }
  
        // password= temp.substring(0,temp.indexOf('&'));
        password = temp.substring(temp.indexOf('&')+1,temp.indexOf('/'));
        return password; 
}


String Read_Token(){
        String temp = "";
        String password = "";
        for (int x=0; x<50; x++){
        char c = EEPROM.read(x);

        if (c==',')break;
        temp +=c;
        }
  
        // password= temp.substring(0,temp.indexOf('&'));
        password = temp.substring(temp.indexOf('/')+1);
        return password; 
}


