#include "bowser.c"
#include <M5StickC.h>
String command;


int arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

void setup(){
  shuffleArray(arr, 10);
  // Initialize the M5StickC object
  M5.begin();
  Serial.begin(115200);
  for (int i = 0; i < 10; i++) {
    Serial.print(arr[i]);
    Serial.print("   ");
  } 
  M5.Lcd.setRotation(3);
  M5.Lcd.drawBitmap(0, 0, 160, 80, (uint8_t *)bowser_map);
  connectDevice();
  
  delay(5000);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.setTextSize(2);
  M5.Lcd.setTextColor(GREEN);
  M5.Lcd.println("Welcome to Bowser!");
  
}
// the loop routine runs over and over again forever
void loop() {

}
void connectDevice() {
  int stoploop = false;
  while(!stoploop){
    if (Serial.available()) {
      command = Serial.readStringUntil('\n');
      command.trim();
      Serial.println(command.substring(0, 7));
      if(command.substring(0, 7) == "CONNECT" ){
        String passReceived = command.substring(8, command.length());
        Serial.println(passReceived);
        M5.Lcd.setCursor(0, 0);
        M5.Lcd.setTextSize(2);
        M5.Lcd.setTextColor(RED);
        M5.Lcd.setCursor(0, 0);
        M5.Lcd.println(passReceived);
      }
    }
  }
}
void shuffleArray(int * array, int size)
{
  int last = 0;
  int temp = array[last];
  for (int i=0; i<size; i++)
  {
    int index = random(size);
    array[last] = array[index];
    last = index;
  }
  array[last] = temp;
}
