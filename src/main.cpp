#include <Arduino.h>
#include <M5Core2.h>

int geigerPin = 32;
volatile uint32_t counter = 0;


void IRAM_ATTR geigerISR()
{
  counter++; 
}

void setup() {
  M5.begin(true, true, true, false);
  Wire.end();
  M5.Lcd.setTextColor(YELLOW);
 
  M5.Lcd.setTextSize(2);
  
  pinMode(geigerPin, INPUT_PULLDOWN);
  attachInterrupt(digitalPinToInterrupt(geigerPin), geigerISR, RISING);
  // put your setup code here, to run once:
}

uint32_t lastCount = 0;

void loop() {
  M5.update();
  if(counter != lastCount)
  {
    M5.Lcd.fillScreen(0);
    M5.Lcd.setCursor(10, 40);
    M5.Lcd.print(counter);
  }
  lastCount = counter;
  //vTaskDelay(5);
  
  // put your main code here, to run repeatedly:
}