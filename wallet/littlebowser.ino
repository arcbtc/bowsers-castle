#include "bowser.c"
#include <M5StickC.h>
String command;
// the setup routine runs once when M5StickC starts up
void setup(){
  // Initialize the M5StickC object
  M5.begin();
  M5.Lcd.setRotation(3);
  // LCD display
  M5.Lcd.print("Hello World");
  M5.Lcd.drawBitmap(0, 0, 160, 80, (uint8_t *)bowser_map);
  delay(2000);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextSize(3);
  M5.Lcd.setTextColor(RED);
  Serial.begin(115200);
  Serial.println("Welcome to Bowser!");
}
// the loop routine runs over and over again forever
void loop() {
    if (Serial.available()) {
    command = Serial.readStringUntil('\n');
    command.trim();
    M5.Lcd.setCursor(0, 0);
    M5.Lcd.println(command);
    }
}
