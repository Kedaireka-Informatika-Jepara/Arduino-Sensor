Dalam repo ini, ada beberapa tes kode untuk melakukan percobaan sensor yang digunakan. 
Sensor yang digunakan adalah
1. Sensor pH dengan DFRobot Gravity: Analog pH Sensor Kit V2.0
2. Sensor suhu DS18B20 Waterproof Digital Temperature Sensor
3. Sensor kekeruhan dengan DFRobot Gravity: Analog Turbidity Sensor
4. Sensor gas dengan MQ-135
5. Sensor tetesan hujan dengan MH-RD

Otak yang digunakan dalam projek ini adalah ESP32. Harap install library ESP32 di Arduino IDE sebelum melakukan percobaan. 
Untuk menginstall library ESP32, silahkan ikuti langkah-langkah berikut:
1. Buka Arduino IDE
2. Pilih menu 'File' -> 'Preferences'
3. Di bagian 'Additional Boards Manager URLs', masukkan link berikut: https://dl.espressif.com/dl/package_esp32_index.json
4. Pilih menu 'Tools' -> 'Board' -> 'Boards Manager'
5. Cari 'esp32' dan install library 'esp32 by Espressif Systems'
6. Pilih menu 'Tools' -> 'Board' -> 'ESP32 Dev Module'


Untuk melakukan percobaan Sensor pH, silahkan ikuti langkah-langkah berikut:
1. Download library 'DFRobot_PH' di laman berikut: https://github.com/greenponik/DFRobot_ESP_PH_BY_GREENPONIK dan download file zipnya
2. Buka Arduino IDE
3. Pilih menu 'Sketch' -> 'Include Library' -> 'Add .ZIP Library'
4. Pilih file zip yang sudah diunduh
5. Pilih menu 'File' -> 'Examples' -> 'DFRobot_ESP_PH_BY_GREENPONIK' -> 'DFRobot_ESP_PH_BY_GREENPONIK'
6. Pilih menu 'Tools' -> 'Board' -> 'ESP32 Dev Module'
7. Pilih menu 'Tools' -> 'Port' -> pilih port yang digunakan
8. Pilih menu 'Sketch' -> 'Upload'
9. Buka serial monitor dengan baud rate 115200
10. Pada serial monitor, akan muncul nilai pH yang terbaca
11. Lakukan kalibrasi pH dengan menggunakan solusi pH 4 dan pH 7
12. Pada serial monitor, akan muncul nilai pH yang terbaca setelah dilakukan kalibrasi
Untuk pin yang digunakan dalam percobaan ini adalah:
| Sensor pH | ESP32 |
|-----------|-------|
| VCC       | 3.3V  |
| GND       | GND   |
| A         | GPIO 35 |

Untuk melakukan percobaan Sensor suhu, silahkan ikuti langkah-langkah berikut:
1. Install library OneWire library by Paul Stoffregen dan DallasTemperature library by Miles Burton di Arduino IDE
2. Buatlah file baru di Arduino IDE dan salin kode berikut:
```c++
#include <OneWire.h>
#include <DallasTemperature.h>

// GPIO where the DS18B20 is connected to
const int oneWireBus = 4;     

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(oneWireBus);

// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);

void setup() {
  // Start the Serial Monitor
  Serial.begin(115200);
  // Start the DS18B20 sensor
  sensors.begin();
}

void loop() {
  sensors.requestTemperatures(); 
  float temperatureC = sensors.getTempCByIndex(0);
  float temperatureF = sensors.getTempFByIndex(0);
  Serial.print(temperatureC);
  Serial.println("ºC");
  Serial.print(temperatureF);
  Serial.println("ºF");
  delay(5000);
}
```
3. Pilih menu 'Sketch' -> 'Upload'
4. Buka serial monitor dengan baud rate 115200
5. Pada serial monitor, akan muncul nilai suhu yang terbaca
Untuk pin yang digunakan dalam percobaan ini adalah:
| Sensor suhu | ESP32 |
|-------------|-------|
| VCC         | 3.3V  |
| GND         | GND   |
| DATA        | GPIO 4 |

