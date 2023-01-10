# Kode Final untuk Rangkaian ESP32 dengan sensor pH, Suhu, Gas, Hujan, Kekeruhan Air, dan TDS

## Kebutuhan

* ESP32
* Sensor pH
* Sensor Suhu
* Sensor Gas
* Sensor Hujan
* Sensor Kekeruhan Air
* Sensor TDS
* Kabel Jumper
* Breadboard

## Koneksi Pin

* pH: 35
* Suhu: 33
* Gas: 32
* Hujan: 34
* Kekeruhan Air: 39
* TDS: 36

## Library yang digunakan

* wifi.h
* wifiClient.h
* HTTPClient.h
* DFRobot_ESP_PH.h (<https://github.com/greenponik/DFRobot_ESP_PH_BY_GREENPONIK>)
* EEPROM.h
* GravityTDS.h (<https://codeload.github.com/DFRobot/GravityTDS/zip/master>)
* OneWire.h
* DallasTemperature.h
* ESP32 Board library (<https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json>)
🔰Anda dapat menggunakan library yang sudah saya upload di drive atau github ini, atau bisa juga mengunduhnya dari link yang sudah saya cantumkan diatas.

## Cara menggunakan

1. Download dan install Arduino IDE
2. Install ESP32 Board library, caranya bisa dilihat di link ini: <https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-windows-instructions/>
3. Download library yang dibutuhkan, dan letakkan di folder library Arduino IDE. Anda dapat menggunakan library yang telah saya siapkan
4. Buka file ESP_Gabungan.ino di Arduino IDE
5. Ubah SSID dan Password WiFi sesuai dengan WiFi yang digunakan
6. Pasangkan sensor sesuai dengan koneksi pin yang sudah saya cantumkan diatas, dan sesuaikan dengan pin yang digunakan di file ESP_Gabungan.ino. Jangan lupa untuk sambungkan koneksi 3,3V, 5V, dan GND untuk tiap sensor
7. Upload file ESP_Gabungan.ino ke ESP32
8. Buka serial monitor, dan lihat hasilnya
