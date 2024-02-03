#include <EEPROM.h>


// iniasisasi eeproom sampai alamat 90 saja
/*
1.      ssid
2.      pass
3.      token 
4.       server
Total ke 4 data ini panjang nya tidak boleh lebih dari 90 karakter 
*/


void EEPROM_Init(){
        EEPROM.begin(90);
}

// membaca nama wifi (ssid)
String Read_SSID(){
        String temp = "";
        String ssid = "";

        for (int x=0; x<90; x++){
        char c = EEPROM.read(x);

        if (c==';')break;
        temp +=c;
        }
  
        ssid = temp.substring(0,temp.indexOf('&'));
        return ssid;
}

// membaca password wifi
String Read_Pass_SSID(){
        String temp = "";
        String password = "";
        for (int x=0; x<90; x++){
                char c = EEPROM.read(x);

                if (c==';')break;
                temp +=c;
        }
  
        // password= temp.substring(0,temp.indexOf('&'));
        password = temp.substring(temp.indexOf('&')+1,temp.indexOf('/'));
        return password; 
}

// membaca token
String Read_Token(){
        String temp = "";
        String token = "";
        for (int x=0; x<90; x++){
        char c = EEPROM.read(x);

        if (c==';')break;
        temp +=c;
        }
  
        // token= temp.substring(0,temp.indexOf('&'));
        token = temp.substring(temp.indexOf('/')+1,temp.indexOf(','));
        return token; 
}

// membaca alamat server
String Read_Server(){
        String temp = "";
        String server = "";
        for (int x=0; x<90; x++){
        char c = EEPROM.read(x);

        if (c==';')break;
        temp +=c;
        }
  
        // server= temp.substring(0,temp.indexOf('&'));
        server = temp.substring(temp.indexOf(',')+1);
        return server; 
}

