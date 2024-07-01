### Program Deteksi Ketinggian Banjir / Water Level

Proyek ini bertujuan untuk mendeteksi ketinggian banjir menggunakan sensor ultrasonik yang terhubung dengan NodeMCU ESP8266 dan diintegrasikan dengan aplikasi MIT App Inventor melalui koneksi MQTT.

### Fitur Utama
- Mengukur ketinggian air menggunakan sensor ultrasonik.
- Mengontrol relay berdasarkan ketinggian air yang terdeteksi.
- Mengirim data ketinggian air dan status melalui MQTT ke aplikasi MIT App Inventor.

### Persyaratan
- NodeMCU ESP8266
- Sensor Ultrasonik (HC-SR04)
- Relay
- Aplikasi MIT App Inventor
- Broker MQTT (contoh: broker.emqx.io)

### Konfigurasi Hardware
- Trig sensor ultrasonik terhubung ke pin D5.
- Echo sensor ultrasonik terhubung ke pin D6.
- Relay terhubung ke pin D7.

### Konfigurasi Software
- Arduino IDE
- Library: `ESP8266WiFi`, `PubSubClient`, `ArduinoJson`

### Cara Menggunakan
1. **Instalasi Library**:
   Pastikan Anda telah menginstal library yang diperlukan di Arduino IDE:
   - ESP8266WiFi
   - PubSubClient
   - ArduinoJson

2. **Koding Arduino**:
   Salin dan tempel kode kelompok yang ada pada repositori ke dalam Arduino IDE Anda.

3. **Upload Kode**:
   - Sambungkan NodeMCU ke komputer Anda.
   - Pilih board "NodeMCU 1.0 (ESP-12E Module)" di Arduino IDE.
   - Pilih port yang sesuai.
   - Klik tombol "Upload".

4. **Konfigurasi MIT App Inventor**:
   - Buat aplikasi di MIT App Inventor yang dapat menerima data dari broker MQTT.
   - Gunakan blok untuk berlangganan ke topik MQTT yang sama dengan yang digunakan dalam kode Arduino.

### Dokumentasi Tambahan
- **ESP8266WiFi Library**: [ESP8266WiFi Library](https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/readme.html)
- **PubSubClient Library**: [PubSubClient Library](https://pubsubclient.knolleary.net/)
- **MIT App Inventor**: [MIT App Inventor](https://appinventor.mit.edu/)

### Lisensi
Proyek ini dilisensikan di bawah MIT License.

### Kontributor
-

Jika Anda memiliki pertanyaan atau memerlukan bantuan lebih lanjut, jangan ragu untuk menghubungi kami.

Terima kasih telah menggunakan proyek ini!
