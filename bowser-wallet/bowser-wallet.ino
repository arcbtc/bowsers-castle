
#include <M5StickC.h>
#include <EEPROM.h>
#include <Electrum.h>
#include "decoy.h"
#include "Bitcoin.h"
#include "Hash.h"
#include "SPIFFS.h"
#include "PSBT.h"
#include "bowser_map.c"

bool buttonA = false;
String seedGenerateStr;
String savedSeed;
String seedGenerateArr[24];
String command;
int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

//========================================================================

void setup(){
  M5.begin();
  Serial.begin(115200);
  decoySetup();
  M5.Lcd.setRotation(3);
  M5.Lcd.drawBitmap(0, 0, 160, 80, (uint8_t *)bowser_map);
  connectDevice();
  delay(1000);
}

//========================================================================

void loop() {

}

//========================================================================

void randoPinPad() {
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.setTextSize(2);
  M5.Lcd.setTextColor(GREEN);
  
  M5.Lcd.drawRect(50, 10, 20, 20, GREEN);
  M5.Lcd.setCursor(55, 13);
  M5.Lcd.println(arr[0]);
  M5.Lcd.drawRect(70, 10, 20, 20, GREEN);
  M5.Lcd.setCursor(75, 13);
  M5.Lcd.println(arr[1]);
  M5.Lcd.drawRect(90, 10, 20, 20, GREEN);
  M5.Lcd.setCursor(95, 13);
  M5.Lcd.println(arr[2]);

  M5.Lcd.drawRect(50, 30, 20, 20, GREEN);
  M5.Lcd.setCursor(55, 33);
  M5.Lcd.println(arr[3]);
  M5.Lcd.drawRect(70, 30, 20, 20, GREEN);
  M5.Lcd.setCursor(75, 33);
  M5.Lcd.println(arr[4]);
  M5.Lcd.drawRect(90, 30, 20, 20, GREEN);
  M5.Lcd.setCursor(95, 33);
  M5.Lcd.println(arr[5]);

  M5.Lcd.drawRect(50, 50, 20, 20, GREEN);
  M5.Lcd.setCursor(55, 53);
  M5.Lcd.println(arr[6]);
  M5.Lcd.drawRect(70, 50, 20, 20, GREEN);
  M5.Lcd.setCursor(75, 53);
  M5.Lcd.println(arr[7]);
  M5.Lcd.drawRect(90, 50, 20, 20, GREEN);
  M5.Lcd.setCursor(95, 53);
  M5.Lcd.println(arr[8]);
}

//========================================================================

void connectDevice() {
  int stoploop = false;
  while(!stoploop){
    if (Serial.available()) {
      command = Serial.readStringUntil('\n');
      command.trim();
      Serial.println(command.substring(0, 3));
      //if(command.substring(0, 7) == "CONNECT" ){
      //  passReceived();
      //}
      if(command == "CONNECT" ){
        shuffleArray(arr, 9);
        randoPinPad();
      }
      if(command.substring(0, 3) == "PIN" ){
        String thePin = command.substring(4, command.length());
        for (int i = 0; i < 8; i++) {
          int temp = String(thePin[i]).toInt();
          Serial.print(arr[temp - 1]);
        } 
      }
      if(command == "PROCESS"){
        processing();
        delay(1000);
      }
      if(command == "HARD RESET" ){
        hardReset();
      }
    }
  }
}

//========================================================================

void processing() {
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setTextSize(2);
    M5.Lcd.setTextColor(RED);
    M5.Lcd.setCursor(0, 20);
    M5.Lcd.println("");
    M5.Lcd.println(" PROCESSING");
}

//========================================================================

void hardReset() {
    processing();
    delay(2000);
    wipeSpiffs();
    seedMaker();
    //pinMaker();
}
//========================================================================

void wipeSpiffs()
{
  File fileKey = SPIFFS.open("/key.txt", FILE_WRITE);
  fileKey.print("\n");
  fileKey.close();
  File fileNum = SPIFFS.open("/num.txt", FILE_WRITE);
  fileNum.print("\n");
  fileNum.close();
  File filePass = SPIFFS.open("/pass.txt", FILE_WRITE);
  filePass.print("\n");
  filePass.close();
}

//========================================================================

void passReceived() {
        String passReceived = command.substring(8, command.length());
        Serial.println(passReceived[1]);
        M5.Lcd.setCursor(0, 0);
        M5.Lcd.fillScreen(BLACK);
        M5.Lcd.setTextSize(2);
        M5.Lcd.setTextColor(RED);
        M5.Lcd.setCursor(0, 0);
        M5.Lcd.println(passReceived);
}

//========================================================================

void shuffleArray(int * arr, int arrsize)
{
  int last = 0;
  int temp = arr[last];
  for (int i=0; i<arrsize; i++)
  {
    int index = random(arrsize);
    arr[last] = arr[index];
    last = index;
  }
  arr[last] = temp;
}

//========================================================================

void seedMaker()
{
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 10);
  M5.Lcd.setTextColor(GREEN);
  M5.Lcd.setTextSize(1);
  M5.Lcd.println("");
  M5.Lcd.println("");
  M5.Lcd.println("");
  M5.Lcd.println("  Generating seed...");
  M5.Lcd.println("  Write them down!");
  delay(6000);
  buttonA = false;

  byte arr[32];
  for (int i = 0; i < sizeof(arr); i++)
  { 
    arr[i] = esp_random() % 256;
  }
  seedGenerateStr = mnemonicFromEntropy(arr, sizeof(arr));

  for (int z = 0; z < 24; z++)
  {
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setCursor(0, 10);
    M5.Lcd.setTextSize(1);
    M5.Lcd.println("");
    M5.Lcd.println("  Word " + String(z + 1));
    M5.Lcd.println("");
    M5.Lcd.setTextSize(3);
    M5.Lcd.setTextColor(BLUE);
    M5.Lcd.println(getValue(seedGenerateStr, ' ', z));
    M5.Lcd.setTextSize(1);
    M5.Lcd.println("");
    M5.Lcd.setTextColor(GREEN);
    M5.Lcd.println("  Btn A, next");
    M5.Lcd.println("");
    
    while (buttonA == false)
    {
      if (M5.BtnA.wasReleased())
      {
        buttonA = true;
      }
      M5.update();
    }
    buttonA = false;
  }
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 10);
  M5.Lcd.setTextSize(1);
  M5.Lcd.println("");
  M5.Lcd.println("");
  M5.Lcd.println("");
  M5.Lcd.println("  Time to check");
  M5.Lcd.println("  the words!");
  delay(6000);
  for (int z = 0; z < 24; z++)
  {
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setCursor(0, 10);
    M5.Lcd.setTextSize(1);
    M5.Lcd.println("");
    M5.Lcd.println("  Word " + String(z + 1));
    M5.Lcd.println("");
    M5.Lcd.setTextSize(3);
    M5.Lcd.setTextColor(BLUE);
    M5.Lcd.println(getValue(seedGenerateStr, ' ', z));
    M5.Lcd.setTextSize(1);
    M5.Lcd.println("");
    M5.Lcd.setTextColor(GREEN);
    M5.Lcd.println("  Btn A, next");
    M5.Lcd.println("");

    while (buttonA == false)
    {
      if (M5.BtnA.wasReleased())
      {
        buttonA = true;
      }
      M5.update();
    }
    buttonA = false;
  }
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 10);
  M5.Lcd.println("");
  M5.Lcd.println("");
  M5.Lcd.println("");
  M5.Lcd.println(" Keep word backup");
  M5.Lcd.println(" very secure and private!");

  File file = SPIFFS.open("/key.txt", FILE_WRITE);
  file.print(seedGenerateStr.substring(0, seedGenerateStr.length()) + "\n");
  file.close();

  String seedGen = "Keep you seed phrase safe but dont lose them! \n" + seedGenerateStr + "\n To learn more about seed phrases visit https://en.bitcoin.it/wiki/Seed_phrase";
  int str_len = seedGen.length() + 1;
  char char_array[str_len];
  seedGen.toCharArray(char_array, str_len);

  File otherFile = SPIFFS.open("/key.txt");
  savedSeed = otherFile.readStringUntil('\n');
  otherFile.close();

  Serial.println(char_array);

  delay(6000);
}

//========================================================================

String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++)
  {
    if (data.charAt(i) == separator || i == maxIndex)
    {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }

  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}


//========================================================================

void writeFile(fs::FS &fs, const char *path, const char *message)
{

  File file = fs.open(path, FILE_WRITE);
  if (!file)
  {
    M5.Lcd.println("   Failed to open file for writing");
    return;
  }
  if (file.print(message))
  {
  }
  else
  {
    M5.Lcd.println("   Write failed");
  }
}
