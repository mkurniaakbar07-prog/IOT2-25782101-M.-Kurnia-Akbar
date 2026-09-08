#include <Arduino.h>

// Deklarasi Pin (GPIO 4 = D2 NodeMCU, GPIO 5 = D1 NodeMCU)
const int buttonPin = 4; 
const int ledPin = 5;    

// 1. STATE TRACKING: Variabel memori untuk menyimpan status LED dan Tombol
bool ledState = false;      // Menyimpan kondisi LED (false = MATI, true = MENYALA)
int lastButtonState = LOW;  // Menyimpan kondisi pembacaan tombol sebelumnya

void setup() {
  Serial.begin(115200);
  
  // Konfigurasi pin input (Rangkaian Pull-Down Eksternal 10k Ohm)
  pinMode(buttonPin, INPUT); 
  pinMode(ledPin, OUTPUT);
  
  // Kriteria 1: Memastikan LED dalam keadaan MATI saat pertama kali dinyalakan
  digitalWrite(ledPin, LOW);
}

void loop() {
  // Membaca status logika tombol saat ini
  int currentButtonState = digitalRead(buttonPin);

  // LOGIKA STATE TRACKING & RISING EDGE DETECTION:
  // Memeriksa hanya saat terjadi perubahan dari LOW ke HIGH (saat tombol BARU DITEKAN)
  if (currentButtonState == HIGH && lastButtonState == LOW) {
    
    // Toggle Status: Membalikkan nilai boolean (True -> False, False -> True)
    ledState = !ledState;
    
    // Memperbarui kondisi fisik LED sesuai nilai ledState
    digitalWrite(ledPin, ledState ? HIGH : LOW);

    // Menampilkan status pada Serial Monitor
    if (ledState) {
      Serial.println("Tombol Ditekan 1x -> LED MENYALA (Latching ON)");
    } else {
      Serial.println("Tombol Ditekan 1x -> LED MATI (Latching OFF)");
    }

    // 2. DEBOUNCING: Memberikan jeda 200 ms untuk meredam pantulan mekanis tombol fisik
    //    Mencegah efek flickering (perubahan status acak/berkedip saat ditekan)
    delay(200);
  }

  // Menyimpan pembacaan saat ini untuk dibandingkan pada iterasi loop berikutnya
  lastButtonState = currentButtonState;
}