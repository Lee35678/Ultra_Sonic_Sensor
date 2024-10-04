#include <Arduino.h>
#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();

const int trigPin = 43;
const int echoPin = 44;
long duration;
float distance;

void setup() {
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  delay(500);
  Serial.println("starting...");

  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextSize(2);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.017;

  Serial.printf("Duration = %ld, Distance = %6.2fcm\n", duration, distance);
  

  tft.fillScreen(TFT_BLACK);  
  tft.setCursor(0, 0);
  tft.println("UltraSonic Sensor"); 
  tft.print("Distance : ");
  tft.print(distance);
  tft.print(" cm");  

  delay(1000);
}
