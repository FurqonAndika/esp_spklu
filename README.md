---Furqon Andika---
Bandung 21 Januari 2024

-> Codingan ini di gunakan untuk ESP8266 yang terhubung dengan pzem, relay, push button dan lcd 16x2 i2c

-> ESP8266 akan mengirim data dari 3 module pzem, tegangan, arus ke server thingsboard, dan juga menerima perintah untuk menghidupkan
    atau mematikan relay

-> Reset ssid dan pass wifi dilakukan dengan cara menekan tombol reset, lalu matikan arduino, lalu hidupkan kembali arduino sambil
    menekan tombol reset,kemudian hubungkan hp dengan wifi yang sesuai pada esp yakni myesp dengan pass 123456780. Lalu masuk ke browser dengan alamat yang ada di serial monitor, 
    alamat defaultnya adalah 192.198.4.1

-> Untuk melihart GPIO yang digunakan, buka driver maka di masing-masing file akan di sebutkan GPIO yang digunakan (#define)

-> https://arduino.esp8266.com/stable/package_esp8266com_index.json

-> thingsboard version 0.10.2

-> rtclib by adafruit 2.1.3 version

-> token thingsboard saat ini LbpOLuEtFWhx3GM70A3d
