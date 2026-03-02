#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define PIR_PIN 4
#define LED_PIN 5 // Changed from BUZZER_PIN to LED_PIN
#define SDA_PIN 21
#define SCL_PIN 22

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
bool lastState = LOW;

void setup() {
  Serial.begin(115200);
  pinMode(PIR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT); // Changed from BUZZER_PIN to LED_PIN
  Wire.begin(SDA_PIN, SCL_PIN);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED not found");
    while (true);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(15, 15);
  display.println("Smart Surveillance");
  display.setCursor(25, 35);
  display.println("Initializing...");
  display.display();
  delay(5000); // PIR warm-up
}

void loop() {
  int motion = digitalRead(PIR_PIN);
  if (motion != lastState) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    if (motion == HIGH) {
      Serial.println("Motion Detected!");
      digitalWrite(LED_PIN, HIGH); // Changed from BUZZER_PIN to LED_PIN
      display.setCursor(20, 20);
      display.println("INTRUDER ALERT!");
      display.setCursor(25, 40);
      display.println("Motion Detected");
    } else {
      Serial.println("Area Safe");
      digitalWrite(LED_PIN, LOW); // Changed from BUZZER_PIN to LED_PIN
      display.setCursor(40, 30);
      display.println("Area Safe");
    }
    display.display();
    lastState = motion;
  }
  delay(100);
}