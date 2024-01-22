---Furqon Andika---
Bandung 21 Januari 2024

->Codingan ini di gunakan untuk ESP8366 yang terhubung dengan pzem, relay, push button dan lcd 16x2 i2c

->ESP32 akan mengirim data tegangan, arus dan daya ke server thingsboard, dan juga menerima perintah untuk menghidupkan atau mematikan relay

->Reset ssid dan pass wifi dilakukan dengan cara menekan tombol reset, lalu matikan arduino, lalu hidupkan kembali arduino sambil menekan tombol reset,
    kemudian hubungkan hp dengan wifi yang sesuai pada esp32. Lalu masuk ke browser dengan alamat yang ada di serial monitor, 
    alamat defaultnya adalah 192.198.4.1

-> Untuk melihart GPIO yang digunakan, buka driver maka di masing-masing file akan di sebutkan GPIO yang digunakan (#define)


