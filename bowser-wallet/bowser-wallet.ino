
#include <M5StickC.h>
#include <EEPROM.h>
#include <Electrum.h>
#include "bowser.c"
#include "decoy.h"
#include "Bitcoin.h"
#include "Hash.h"
#include "SPIFFS.h"
#include "FS.h"
#include "PSBT.h"

bool isWallet = false;
bool confirm = false;
bool buttonA = false;
bool buttonB = false;
bool firstWallet = false;
String passKey;
String seedGenerateStr;
String savedSeed;
String seedGenerateArr[24];
String command;
String privateKey;
String pubKey;
String passkey;
String hashed;
String savedPinHash;
String freshPub;
int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

//========================================================================

void setup(){
  M5.begin();
  Serial.begin(115200);
  Serial.print("bowser,");
  decoySetup();
  if (!SPIFFS.begin(true))
  {
    return;
  }
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

void connectDevice() {
  int stoploop = false;
  while(!stoploop){
    readCommands();
  }
}

//========================================================================

void readCommands() {
      if (Serial.available()) {
      command = Serial.readStringUntil('\n');
      command.trim();
      if(command == "CONNECT" ){
        checkForWallet();
        if(isWallet) {
          shuffleArray(arr, 9);
          randoPinPad();
        }
      }
      //for logging in
      if(command.substring(0, 3) == "PIN" && isWallet){
        String thePin = command.substring(4, command.length());
        for (int i = 0; i < 8; i++) {
          int temp = String(thePin[i]).toInt();
          passkey = passkey + String(arr[temp - 1]);
        }
        //Set true just to verify
        enterPin(true);
      }
      //first submitting
      if(command.substring(0, 3) == "PIN" && !isWallet){
        String thePin = command.substring(4, command.length());
        for (int i = 0; i < 8; i++) {
          int temp = String(thePin[i]).toInt();
          passkey = passkey + String(arr[temp - 1]);
        } 
        //Set false to write pin to SPIFFS
        enterPin(false);
        if (!confirm){
          randoPinPad();
        }
      }
      if(command == "PROCESS"){
        processing();
        delay(1000);
      }
      if(command == "HARD RESET" ){
        hardReset();
      }
      if(command == "SOFT RESET" ){
        M5.Lcd.drawBitmap(0, 0, 160, 80, (uint8_t *)bowser_map);
      }
      if(command.substring(0, 7) == "RESTORE") {
        restore();
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
    shuffleArray(arr, 9);
    randoPinPad();
    connectDevice();
}

void restore() {
    restoreFromSeed(command.substring(8, command.length()));
}
//========================================================================

void checkForWallet() {
  File otherFile = SPIFFS.open("/key.txt");
  savedSeed = otherFile.readStringUntil('\n');
  otherFile.close();
  isWallet = false;
  if (savedSeed.length() < 30)
  {
      M5.Lcd.fillScreen(BLACK);
      M5.Lcd.setCursor(0, 10);
      M5.Lcd.setTextSize(2);
      M5.Lcd.setTextColor(RED);
      M5.Lcd.println("ERROR:");
      M5.Lcd.println("No wallet");
      M5.Lcd.println("`HARD RESET`");
   }
   else{
     isWallet = true;
   }
}
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
   M5.Lcd.setCursor(0, 0);
   M5.Lcd.fillScreen(BLACK);
   M5.Lcd.setTextSize(2);
  M5.Lcd.setTextColor(RED);
   M5.Lcd.setCursor(0, 0);
    M5.Lcd.println(passReceived);
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
    Serial.print(String(z + 1) + ",");
    
    while (buttonA == false)
    {
      if (M5.BtnA.wasReleased())
      {
        buttonA = true;
      }
      M5.update();
      readCommands();
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
    Serial.print(String(z + 1) + ",");

    while (buttonA == false)
    {
      if (M5.BtnA.wasReleased())
      {
        buttonA = true;
      }
      M5.update();
      readCommands();
    }
    buttonA = false;
  }
  
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
  isWallet = false;
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 10);
  M5.Lcd.println("");
  M5.Lcd.println("");
  M5.Lcd.println("");
  M5.Lcd.println(" Now its time to set an 8 digit pin!");
  Serial.flush();
  Serial.print("PINSTART,");
  delay(3000);
  Serial.print("PINSTART,");
  Serial.flush();
}

//========================================================================

void enterPin(bool set)
{
   uint8_t newPassKeyResult[32];
   sha256(passKey, newPassKeyResult);
   hashed = toHex(newPassKeyResult, 32);

   if (set == false){
     File file = SPIFFS.open("/pass.txt", FILE_WRITE);
     file.print(hashed + "\n");
     file.close();
   }
   File otherFile = SPIFFS.open("/pass.txt");
   savedPinHash = otherFile.readStringUntil('\n');
   otherFile.close();

   if (savedPinHash == hashed)
   {
     isWallet = true;
     getKeys(savedSeed, passKey);
     confirm = true;
     getAddress();
     M5.Lcd.fillScreen(BLACK);
     M5.Lcd.setTextSize(2);
     M5.Lcd.setTextColor(GREEN);
     M5.Lcd.setCursor(0, 30);
     M5.Lcd.println("Sending zpub");
     M5.Lcd.println("to web-wallet");
     delay(2000);
     Serial.print("%P1" + pubKey.substring(0, 50) + ",");
     delay(1000);
     Serial.print("%P2" + pubKey.substring(50, 100) + ",");
     delay(1000);
     Serial.print("%P3" + pubKey.substring(100, 150) + ",");
     delay(1000);
     Serial.print("%P1" + pubKey.substring(0, 50) + ",");
     delay(1000);
     Serial.print("%P2" + pubKey.substring(50, 100) + ",");
     delay(1000);
     Serial.print("%P3" + pubKey.substring(100, 150) + ",");
     delay(1000);
     Serial.print(freshPub + ",");
     M5.Lcd.fillScreen(BLACK);
     M5.Lcd.setTextSize(2);
     M5.Lcd.setTextColor(GREEN);
     M5.Lcd.setCursor(0, 10);
     M5.Lcd.println("Connected");
     M5.Lcd.println("Bwahahaha!");
     M5.Lcd.setTextSize(1);
     M5.Lcd.println("Latest address:");
     M5.Lcd.println(freshPub);
     Serial.print(pubKey + ",");
     Serial.print("PINPASS,");
     delay(2000);
     Serial.print("PINPASS,");
     return;
   }
   else if (savedPinHash != hashed)
   {
     M5.Lcd.fillScreen(BLACK);
     M5.Lcd.setTextSize(2);
     M5.Lcd.setTextColor(RED);
     M5.Lcd.setCursor(0, 20);
     M5.Lcd.println("Wrong pin!");
     M5.Lcd.println("Try again");
     passKey = "";
     Serial.print("PINFAIL,");
     delay(3000);
     Serial.print("PINFAIL,");
     shuffleArray(arr, 9);
     randoPinPad();
   }
  M5.update();
  confirm = false;
}

//========================================================================

void updateAddress()
{
  HDPublicKey hd(pubKey);

  File otherFile = SPIFFS.open("/num.txt");
  String pubNum = otherFile.readStringUntil('\n');
  otherFile.close();
  
  int pubNumm = pubNum.toInt() + 1;
  File file = SPIFFS.open("/num.txt", FILE_WRITE);
  file.print(pubNumm);
  file.close();
}

//========================================================================

void getAddress()
{
  HDPublicKey hd(pubKey);

  File otherFile = SPIFFS.open("/num.txt");
  String pubNum = otherFile.readStringUntil('\n');
  otherFile.close();

  int pubNumm = pubNum.toInt();
  String path = String("m/0/") + pubNumm;
  freshPub = hd.derive(path).address();
  
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
    delay(2000);
    return;
  }
  if (file.print(message))
  {
  }
  else
  {
    M5.Lcd.println("   Write failed");
    delay(2000);
  }
}

//========================================================================

void getKeys(String mnemonic, String password)
{

  HDPrivateKey hd(mnemonic, password);

  if (!hd)
  { // check if it is valid
    return;
  }

  HDPrivateKey account = hd.derive("m/84'/0'/0'/");

  privateKey = account;

  pubKey = account.xpub();

}

//========================================================================

void seedChecker()
{
  File otherFile = SPIFFS.open("/key.txt");
  savedSeed = otherFile.readStringUntil('\n');
  otherFile.close();
  int seedCount = 0;

  for (int x = 0; x < 24; x++)
  {
    for (int z = 0; z < 2048; z++)
    {
      if (getValue(savedSeed, ' ', x) == seedWords[z])
      {
        seedCount = seedCount + 1;
      }
    }
  }

  if (int(seedCount) != 24)
  {
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setCursor(0, 90);
    M5.Lcd.setTextColor(RED);
    M5.Lcd.setTextSize(2);
    M5.Lcd.println("   Error: Reset device");
    M5.Lcd.println("   or restore from seed");
    M5.Lcd.println("   (See documentation)");
    delay(99999999999999999999999);
  }
  else
  {
    return;
  }
}

//========================================================================

void restoreFromSeed(String theSeed)
{

  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 20);
  M5.Lcd.setTextSize(3);
  M5.Lcd.setTextColor(GREEN);
  M5.Lcd.println("RESTORE FROM SEED");
  M5.Lcd.setCursor(0, 85);
  M5.Lcd.setTextColor(RED);
  M5.Lcd.setTextSize(2);
  M5.Lcd.println("Device will be wiped");
  M5.Lcd.println("then restored from seed");
  M5.Lcd.println("are you sure?");
  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(0, 220);
  M5.Lcd.println("A to continue, B to cancel");

  while (buttonA == false && buttonB == false)
  {
    if (M5.BtnA.wasReleased())
    {
      buttonA = true;
    }
    if (M5.BtnB.wasReleased())
    {
      buttonB = true;
    }
    M5.update();
  }
  if (buttonA == true)
  {
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setCursor(0, 100);
    M5.Lcd.setTextColor(GREEN);
    M5.Lcd.setTextSize(2);
    M5.Lcd.println("     Saving seed...");
    delay(2000);
    File file = SPIFFS.open("/key.txt", FILE_WRITE);
    file.print(theSeed + "\n");
    file.close();
    File otherFile = SPIFFS.open("/key.txt");
    savedSeed = otherFile.readStringUntil('\n');
    otherFile.close();
  }

  buttonA = false;
  buttonB = false;
}
