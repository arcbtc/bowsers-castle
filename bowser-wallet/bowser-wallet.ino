//Comment out/in the M5Stick you have
#define m5stickplusdef
//#define m5stickdef

#ifdef m5stickplusdef
  #include <M5StickCPlus.h>
  #include "bowser_plus.c"
  #define TFTW 135
  #define TFTH 240
  #define TFTW2 67
  #define TFTH2 120
  #define SMFONT 2
  #define LGFONT 3
  #define XLFONT 4
  #define PAD 40
#endif

#ifdef m5stickdef
  #include <M5StickC.h>
  #include "bowser.c"
  #define TFTW 80 
  #define TFTH 160 
  #define TFTW2 40 
  #define TFTH2 80
  #define SMFONT 1
  #define LGFONT 2
  #define XLFONT 3
  #define PAD 20
#endif

#include <EEPROM.h>
#include <Electrum.h>
#include "Bitcoin.h"
#include "Hash.h"
#include "SPIFFS.h"
#include "FS.h"
#include "PSBT.h"
#include "just_bowser.c"

String seedWords[2048] = {"abandon","ability","able","about","above","absent","absorb","abstract","absurd","abuse","access","accident","account","accuse","achieve","acid","acoustic","acquire","across","act","action","actor","actress","actual","adapt","add","addict","address","adjust","admit","adult","advance","advice","aerobic","affair","afford","afraid","again","age","agent","agree","ahead","aim","air","airport","aisle","alarm","album","alcohol","alert","alien","all","alley","allow","almost","alone","alpha","already","also","alter","always","amateur","amazing","among","amount","amused","analyst","anchor","ancient","anger","angle","angry","animal","ankle","announce","annual","another","answer","antenna","antique","anxiety","any","apart","apology","appear","apple","approve","april","arch","arctic","area","arena","argue","arm","armed","armor","army","around","arrange","arrest","arrive","arrow","art","artefact","artist","artwork","ask","aspect","assault","asset","assist","assume","asthma","athlete","atom","attack","attend","attitude","attract","auction","audit","august","aunt","author","auto","autumn","average","avocado","avoid","awake","aware","away","awesome","awful","awkward","axis","baby","bachelor","bacon","badge","bag","balance","balcony","ball","bamboo","banana","banner","bar","barely","bargain","barrel","base","basic","basket","battle","beach","bean","beauty","because","become","beef","before","begin","behave","behind","believe","below","belt","bench","benefit","best","betray","better","between","beyond","bicycle","bid","bike","bind","biology","bird","birth","bitter","black","blade","blame","blanket","blast","bleak","bless","blind","blood","blossom","blouse","blue","blur","blush","board","boat","body","boil","bomb","bone","bonus","book","boost","border","boring","borrow","boss","bottom","bounce","box","boy","bracket","brain","brand","brass","brave","bread","breeze","brick","bridge","brief","bright","bring","brisk","broccoli","broken","bronze","broom","brother","brown","brush","bubble","buddy","budget","buffalo","build","bulb","bulk","bullet","bundle","bunker","burden","burger","burst","bus","business","busy","butter","buyer","buzz","cabbage","cabin","cable","cactus","cage","cake","call","calm","camera","camp","can","canal","cancel","candy","cannon","canoe","canvas","canyon","capable","capital","captain","car","carbon","card","cargo","carpet","carry","cart","case","cash","casino","castle","casual","cat","catalog","catch","category","cattle","caught","cause","caution","cave","ceiling","celery","cement","census","century","cereal","certain","chair","chalk","champion","change","chaos","chapter","charge","chase","chat","cheap","check","cheese","chef","cherry","chest","chicken","chief","child","chimney","choice","choose","chronic","chuckle","chunk","churn","cigar","cinnamon","circle","citizen","city","civil","claim","clap","clarify","claw","clay","clean","clerk","clever","click","client","cliff","climb","clinic","clip","clock","clog","close","cloth","cloud","clown","club","clump","cluster","clutch","coach","coast","coconut","code","coffee","coil","coin","collect","color","column","combine","come","comfort","comic","common","company","concert","conduct","confirm","congress","connect","consider","control","convince","cook","cool","copper","copy","coral","core","corn","correct","cost","cotton","couch","country","couple","course","cousin","cover","coyote","crack","cradle","craft","cram","crane","crash","crater","crawl","crazy","cream","credit","creek","crew","cricket","crime","crisp","critic","crop","cross","crouch","crowd","crucial","cruel","cruise","crumble","crunch","crush","cry","crystal","cube","culture","cup","cupboard","curious","current","curtain","curve","cushion","custom","cute","cycle","dad","damage","damp","dance","danger","daring","dash","daughter","dawn","day","deal","debate","debris","decade","december","decide","decline","decorate","decrease","deer","defense","define","defy","degree","delay","deliver","demand","demise","denial","dentist","deny","depart","depend","deposit","depth","deputy","derive","describe","desert","design","desk","despair","destroy","detail","detect","develop","device","devote","diagram","dial","diamond","diary","dice","diesel","diet","differ","digital","dignity","dilemma","dinner","dinosaur","direct","dirt","disagree","discover","disease","dish","dismiss","disorder","display","distance","divert","divide","divorce","dizzy","doctor","document","dog","doll","dolphin","domain","donate","donkey","donor","door","dose","double","dove","draft","dragon","drama","drastic","draw","dream","dress","drift","drill","drink","drip","drive","drop","drum","dry","duck","dumb","dune","during","dust","dutch","duty","dwarf","dynamic","eager","eagle","early","earn","earth","easily","east","easy","echo","ecology","economy","edge","edit","educate","effort","egg","eight","either","elbow","elder","electric","elegant","element","elephant","elevator","elite","else","embark","embody","embrace","emerge","emotion","employ","empower","empty","enable","enact","end","endless","endorse","enemy","energy","enforce","engage","engine","enhance","enjoy","enlist","enough","enrich","enroll","ensure","enter","entire","entry","envelope","episode","equal","equip","era","erase","erode","erosion","error","erupt","escape","essay","essence","estate","eternal","ethics","evidence","evil","evoke","evolve","exact","example","excess","exchange","excite","exclude","excuse","execute","exercise","exhaust","exhibit","exile","exist","exit","exotic","expand","expect","expire","explain","expose","express","extend","extra","eye","eyebrow","fabric","face","faculty","fade","faint","faith","fall","false","fame","family","famous","fan","fancy","fantasy","farm","fashion","fat","fatal","father","fatigue","fault","favorite","feature","february","federal","fee","feed","feel","female","fence","festival","fetch","fever","few","fiber","fiction","field","figure","file","film","filter","final","find","fine","finger","finish","fire","firm","first","fiscal","fish","fit","fitness","fix","flag","flame","flash","flat","flavor","flee","flight","flip","float","flock","floor","flower","fluid","flush","fly","foam","focus","fog","foil","fold","follow","food","foot","force","forest","forget","fork","fortune","forum","forward","fossil","foster","found","fox","fragile","frame","frequent","fresh","friend","fringe","frog","front","frost","frown","frozen","fruit","fuel","fun","funny","furnace","fury","future","gadget","gain","galaxy","gallery","game","gap","garage","garbage","garden","garlic","garment","gas","gasp","gate","gather","gauge","gaze","general","genius","genre","gentle","genuine","gesture","ghost","giant","gift","giggle","ginger","giraffe","girl","give","glad","glance","glare","glass","glide","glimpse","globe","gloom","glory","glove","glow","glue","goat","goddess","gold","good","goose","gorilla","gospel","gossip","govern","gown","grab","grace","grain","grant","grape","grass","gravity","great","green","grid","grief","grit","grocery","group","grow","grunt","guard","guess","guide","guilt","guitar","gun","gym","habit","hair","half","hammer","hamster","hand","happy","harbor","hard","harsh","harvest","hat","have","hawk","hazard","head","health","heart","heavy","hedgehog","height","hello","helmet","help","hen","hero","hidden","high","hill","hint","hip","hire","history","hobby","hockey","hold","hole","holiday","hollow","home","honey","hood","hope","horn","horror","horse","hospital","host","hotel","hour","hover","hub","huge","human","humble","humor","hundred","hungry","hunt","hurdle","hurry","hurt","husband","hybrid","ice","icon","idea","identify","idle","ignore","ill","illegal","illness","image","imitate","immense","immune","impact","impose","improve","impulse","inch","include","income","increase","index","indicate","indoor","industry","infant","inflict","inform","inhale","inherit","initial","inject","injury","inmate","inner","innocent","input","inquiry","insane","insect","inside","inspire","install","intact","interest","into","invest","invite","involve","iron","island","isolate","issue","item","ivory","jacket","jaguar","jar","jazz","jealous","jeans","jelly","jewel","job","join","joke","journey","joy","judge","juice","jump","jungle","junior","junk","just","kangaroo","keen","keep","ketchup","key","kick","kid","kidney","kind","kingdom","kiss","kit","kitchen","kite","kitten","kiwi","knee","knife","knock","know","lab","label","labor","ladder","lady","lake","lamp","language","laptop","large","later","latin","laugh","laundry","lava","law","lawn","lawsuit","layer","lazy","leader","leaf","learn","leave","lecture","left","leg","legal","legend","leisure","lemon","lend","length","lens","leopard","lesson","letter","level","liar","liberty","library","license","life","lift","light","like","limb","limit","link","lion","liquid","list","little","live","lizard","load","loan","lobster","local","lock","logic","lonely","long","loop","lottery","loud","lounge","love","loyal","lucky","luggage","lumber","lunar","lunch","luxury","lyrics","machine","mad","magic","magnet","maid","mail","main","major","make","mammal","man","manage","mandate","mango","mansion","manual","maple","marble","march","margin","marine","market","marriage","mask","mass","master","match","material","math","matrix","matter","maximum","maze","meadow","mean","measure","meat","mechanic","medal","media","melody","melt","member","memory","mention","menu","mercy","merge","merit","merry","mesh","message","metal","method","middle","midnight","milk","million","mimic","mind","minimum","minor","minute","miracle","mirror","misery","miss","mistake","mix","mixed","mixture","mobile","model","modify","mom","moment","monitor","monkey","monster","month","moon","moral","more","morning","mosquito","mother","motion","motor","mountain","mouse","move","movie","much","muffin","mule","multiply","muscle","museum","mushroom","music","must","mutual","myself","mystery","myth","naive","name","napkin","narrow","nasty","nation","nature","near","neck","need","negative","neglect","neither","nephew","nerve","nest","net","network","neutral","never","news","next","nice","night","noble","noise","nominee","noodle","normal","north","nose","notable","note","nothing","notice","novel","now","nuclear","number","nurse","nut","oak","obey","object","oblige","obscure","observe","obtain","obvious","occur","ocean","october","odor","off","offer","office","often","oil","okay","old","olive","olympic","omit","once","one","onion","online","only","open","opera","opinion","oppose","option","orange","orbit","orchard","order","ordinary","organ","orient","original","orphan","ostrich","other","outdoor","outer","output","outside","oval","oven","over","own","owner","oxygen","oyster","ozone","pact","paddle","page","pair","palace","palm","panda","panel","panic","panther","paper","parade","parent","park","parrot","party","pass","patch","path","patient","patrol","pattern","pause","pave","payment","peace","peanut","pear","peasant","pelican","pen","penalty","pencil","people","pepper","perfect","permit","person","pet","phone","photo","phrase","physical","piano","picnic","picture","piece","pig","pigeon","pill","pilot","pink","pioneer","pipe","pistol","pitch","pizza","place","planet","plastic","plate","play","please","pledge","pluck","plug","plunge","poem","poet","point","polar","pole","police","pond","pony","pool","popular","portion","position","possible","post","potato","pottery","poverty","powder","power","practice","praise","predict","prefer","prepare","present","pretty","prevent","price","pride","primary","print","priority","prison","private","prize","problem","process","produce","profit","program","project","promote","proof","property","prosper","protect","proud","provide","public","pudding","pull","pulp","pulse","pumpkin","punch","pupil","puppy","purchase","purity","purpose","purse","push","put","puzzle","pyramid","quality","quantum","quarter","question","quick","quit","quiz","quote","rabbit","raccoon","race","rack","radar","radio","rail","rain","raise","rally","ramp","ranch","random","range","rapid","rare","rate","rather","raven","raw","razor","ready","real","reason","rebel","rebuild","recall","receive","recipe","record","recycle","reduce","reflect","reform","refuse","region","regret","regular","reject","relax","release","relief","rely","remain","remember","remind","remove","render","renew","rent","reopen","repair","repeat","replace","report","require","rescue","resemble","resist","resource","response","result","retire","retreat","return","reunion","reveal","review","reward","rhythm","rib","ribbon","rice","rich","ride","ridge","rifle","right","rigid","ring","riot","ripple","risk","ritual","rival","river","road","roast","robot","robust","rocket","romance","roof","rookie","room","rose","rotate","rough","round","route","royal","rubber","rude","rug","rule","run","runway","rural","sad","saddle","sadness","safe","sail","salad","salmon","salon","salt","salute","same","sample","sand","satisfy","satoshi","sauce","sausage","save","say","scale","scan","scare","scatter","scene","scheme","school","science","scissors","scorpion","scout","scrap","screen","script","scrub","sea","search","season","seat","second","secret","section","security","seed","seek","segment","select","sell","seminar","senior","sense","sentence","series","service","session","settle","setup","seven","shadow","shaft","shallow","share","shed","shell","sheriff","shield","shift","shine","ship","shiver","shock","shoe","shoot","shop","short","shoulder","shove","shrimp","shrug","shuffle","shy","sibling","sick","side","siege","sight","sign","silent","silk","silly","silver","similar","simple","since","sing","siren","sister","situate","six","size","skate","sketch","ski","skill","skin","skirt","skull","slab","slam","sleep","slender","slice","slide","slight","slim","slogan","slot","slow","slush","small","smart","smile","smoke","smooth","snack","snake","snap","sniff","snow","soap","soccer","social","sock","soda","soft","solar","soldier","solid","solution","solve","someone","song","soon","sorry","sort","soul","sound","soup","source","south","space","spare","spatial","spawn","speak","special","speed","spell","spend","sphere","spice","spider","spike","spin","spirit","split","spoil","sponsor","spoon","sport","spot","spray","spread","spring","spy","square","squeeze","squirrel","stable","stadium","staff","stage","stairs","stamp","stand","start","state","stay","steak","steel","stem","step","stereo","stick","still","sting","stock","stomach","stone","stool","story","stove","strategy","street","strike","strong","struggle","student","stuff","stumble","style","subject","submit","subway","success","such","sudden","suffer","sugar","suggest","suit","summer","sun","sunny","sunset","super","supply","supreme","sure","surface","surge","surprise","surround","survey","suspect","sustain","swallow","swamp","swap","swarm","swear","sweet","swift","swim","swing","switch","sword","symbol","symptom","syrup","system","table","tackle","tag","tail","talent","talk","tank","tape","target","task","taste","tattoo","taxi","teach","team","tell","ten","tenant","tennis","tent","term","test","text","thank","that","theme","then","theory","there","they","thing","this","thought","three","thrive","throw","thumb","thunder","ticket","tide","tiger","tilt","timber","time","tiny","tip","tired","tissue","title","toast","tobacco","today","toddler","toe","together","toilet","token","tomato","tomorrow","tone","tongue","tonight","tool","tooth","top","topic","topple","torch","tornado","tortoise","toss","total","tourist","toward","tower","town","toy","track","trade","traffic","tragic","train","transfer","trap","trash","travel","tray","treat","tree","trend","trial","tribe","trick","trigger","trim","trip","trophy","trouble","truck","true","truly","trumpet","trust","truth","try","tube","tuition","tumble","tuna","tunnel","turkey","turn","turtle","twelve","twenty","twice","twin","twist","two","type","typical","ugly","umbrella","unable","unaware","uncle","uncover","under","undo","unfair","unfold","unhappy","uniform","unique","unit","universe","unknown","unlock","until","unusual","unveil","update","upgrade","uphold","upon","upper","upset","urban","urge","usage","use","used","useful","useless","usual","utility","vacant","vacuum","vague","valid","valley","valve","van","vanish","vapor","various","vast","vault","vehicle","velvet","vendor","venture","venue","verb","verify","version","very","vessel","veteran","viable","vibrant","vicious","victory","video","view","village","vintage","violin","virtual","virus","visa","visit","visual","vital","vivid","vocal","voice","void","volcano","volume","vote","voyage","wage","wagon","wait","walk","wall","walnut","want","warfare","warm","warrior","wash","wasp","waste","water","wave","way","wealth","weapon","wear","weasel","weather","web","wedding","weekend","weird","welcome","west","wet","whale","what","wheat","wheel","when","where","whip","whisper","wide","width","wife","wild","will","win","window","wine","wing","wink","winner","winter","wire","wisdom","wise","wish","witness","wolf","woman","wonder","wood","wool","word","work","world","worry","worth","wrap","wreck","wrestle","wrist","write","wrong","yard","year","yellow","you","young","youth","zebra","zero","zone","zoo"};
bool isWallet = false;
bool confirm = false;
bool buttonA = false;
bool buttonB = false;
bool firstWallet = false;
bool decoy = true;
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
String freshAddress;
String pubNumm = "0";
int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

//========================================================================

void setup(){
  M5.begin();
  M5.Axp.ScreenBreath(10);
  Serial.begin(115200);
  Serial.print("bowser,");
  
  if (!SPIFFS.begin(true))
  {
    return;
  }
  decoySetup();
}

//========================================================================

void loop() {

}

//========================================================================

void randoPinPad() {
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.setTextSize(LGFONT);
  M5.Lcd.setTextColor(GREEN);
  
  M5.Lcd.drawRect(50, 10, PAD, PAD, GREEN);
  M5.Lcd.setCursor(55, 13);
  M5.Lcd.println(arr[0]);
  M5.Lcd.drawRect(50 + PAD, 10, PAD, PAD, GREEN);
  M5.Lcd.setCursor(55 + PAD, 13);
  M5.Lcd.println(arr[1]);
  M5.Lcd.drawRect(50 + PAD + PAD, 10, PAD, PAD, GREEN);
  M5.Lcd.setCursor(55 + PAD + PAD, 13);
  M5.Lcd.println(arr[2]);

  M5.Lcd.drawRect(50, 10 + PAD, PAD, PAD, GREEN);
  M5.Lcd.setCursor(55, 13 + PAD);
  M5.Lcd.println(arr[3]);
  M5.Lcd.drawRect(50 + PAD, 10 + PAD, PAD, PAD, GREEN);
  M5.Lcd.setCursor(55 + PAD, 13 + PAD);
  M5.Lcd.println(arr[4]);
  M5.Lcd.drawRect(50 + PAD + PAD, 10 + PAD, PAD, PAD, GREEN);
  M5.Lcd.setCursor(55 + PAD + PAD, 13 + PAD);
  M5.Lcd.println(arr[5]);

  M5.Lcd.drawRect(50, 10 + PAD + PAD, PAD, PAD, GREEN);
  M5.Lcd.setCursor(55, 13 + PAD + PAD);
  M5.Lcd.println(arr[6]);
  M5.Lcd.drawRect(50 + PAD, 10 + PAD + PAD, PAD, PAD, GREEN);
  M5.Lcd.setCursor(55 + PAD, 13 + PAD + PAD);
  M5.Lcd.println(arr[7]);
  M5.Lcd.drawRect(50 + PAD + PAD, 10 + PAD + PAD, PAD, PAD, GREEN);
  M5.Lcd.setCursor(55 + PAD + PAD, 13 + PAD + PAD);
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
        decoy = false;
        M5.Lcd.setRotation(3);
        M5.Lcd.fillScreen(BLACK);
        #ifdef m5stickplusdef
          M5.Lcd.drawBitmap(0, 0, TFTH, TFTW, (uint8_t *)bowser_plus_map);
        #endif
        #ifdef m5stickdef
          M5.Lcd.drawBitmap(0, 0, TFTH, TFTW, (uint8_t *)bowser_map);
        #endif
        checkForWallet();
        connectDevice();
      }
      if(command == "HANDSHAKE" ){
        if(isWallet) {
          shuffleArray(arr, 9);
          randoPinPad();
        }
      }
      //for logging in
      if(command.substring(0, 3) == "PIN"){
        String passKeyTemp;
        String thePin = command.substring(3, command.length());
        for (int i = 0; i < 8; i++) {
          int temp = String(thePin[i]).toInt();
          passKeyTemp = passKeyTemp + String(arr[temp - 1]);
        }
        passkey = passKeyTemp;
        Serial.print(thePin + ",");
        delay(1000);
        Serial.print(passkey + ",");
        delay(1000);
        Serial.print(passkey + ",");
        if(isWallet){
          //Set true just to verify
          enterPin(true);
        }
        else{
          //Set false to write pin to SPIFFS
          enterPin(false);
          if (!confirm){
            randoPinPad();
          }
        }
      }
      if(command == "PROCESS"){
        processing();
        delay(1000);
      }
      if(command == "HARDRESET" ){
        hardReset();
      }
      if(command == "ADR" ){
        addrUpdate();
      }
      if(command == "SOFTRESET" ){
        M5.Lcd.fillScreen(BLACK);
        #ifdef m5stickplusdef
          M5.Lcd.drawBitmap(0, 0, TFTH, TFTW, (uint8_t *)bowser_plus_map);
        #endif
        #ifdef m5stickdef
          M5.Lcd.drawBitmap(0, 0, TFTH, TFTW, (uint8_t *)bowser_map);
        #endif
      }
      if(command.substring(0, 7) == "RESTORE") {
        restore();
      }
    }
     else if (!Serial) {
      M5.Lcd.fillScreen(BLACK);
      M5.Lcd.setTextSize(LGFONT);
      M5.Lcd.setTextColor(RED);
      M5.Lcd.setCursor(0, 20);
      M5.Lcd.println("");
      M5.Lcd.println(" CONNECTION");
      M5.Lcd.println(" LOST :(");
      delay(2000);
      M5.Lcd.fillScreen(BLACK);
        #ifdef m5stickplusdef
          M5.Lcd.drawBitmap(0, 0, TFTH, TFTW, (uint8_t *)bowser_plus_map);
        #endif
        #ifdef m5stickdef
          M5.Lcd.drawBitmap(0, 0, TFTH, TFTW, (uint8_t *)bowser_map);
        #endif
    }
}
//========================================================================

void processing() {
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setTextSize(LGFONT);
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
  if (savedSeed.length() < 30)
  {   
      Serial.print("NOHWW,");
      delay(1000);
      Serial.print("NOHWW,");
      delay(1000);
      Serial.print("NOHWW,");
      delay(1000);
      Serial.print("NOHWW,");
      isWallet = false;
      M5.Lcd.fillScreen(BLACK);
      M5.Lcd.setCursor(0, 10);
      M5.Lcd.setTextSize(LGFONT);
      M5.Lcd.setTextColor(RED);
      M5.Lcd.println("ERROR:");
      M5.Lcd.println("No wallet");
      M5.Lcd.println("`HARD RESET`");
      
   }
   else{
     isWallet = true;
     Serial.print("YESHWW,");
     delay(1000);
     Serial.print("YESHWW,");
     delay(1000);
     Serial.print("YESHWW,");
     delay(1000);
     Serial.print("YESHWW,");
   }
}

//========================================================================

void addrUpdate(){
  File otherFile = SPIFFS.open("/num.txt");
  String pubNumm = otherFile.readStringUntil('\n');
  otherFile.close();
  
  int pubNum = pubNumm.toInt() + 1;
  File file = SPIFFS.open("/num.txt", FILE_WRITE);
  file.print(pubNum);
  file.close();
  
  delay(1000);
  Serial.print("ADR" + String(pubNum) + ",");
  delay(1000);
  Serial.print("ADR" + String(pubNum) + ",");
  delay(1000);
  Serial.print("ADR" + String(pubNum) + ",");
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
   M5.Lcd.setCursor(0, 0);
   M5.Lcd.fillScreen(BLACK);
   M5.Lcd.setTextSize(LGFONT);
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
  M5.Lcd.setTextSize(SMFONT);
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
    M5.Lcd.setTextSize(SMFONT);
    M5.Lcd.println("");
    M5.Lcd.println("  Word " + String(z + 1));
    M5.Lcd.println("");
    M5.Lcd.setTextSize(XLFONT);
    M5.Lcd.setTextColor(BLUE);
    M5.Lcd.println(getValue(seedGenerateStr, ' ', z));
    M5.Lcd.setTextSize(SMFONT);
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
  M5.Lcd.setTextSize(SMFONT);
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
    M5.Lcd.setTextSize(SMFONT);
    M5.Lcd.println("");
    M5.Lcd.println("  Word " + String(z + 1));
    M5.Lcd.println("");
    M5.Lcd.setTextSize(XLFONT);
    M5.Lcd.setTextColor(BLUE);
    M5.Lcd.println(getValue(seedGenerateStr, ' ', z));
    M5.Lcd.setTextSize(SMFONT);
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
   hashed = "";
   savedPinHash = "1";
   uint8_t newPassKeyResult[32];
   sha256(passKey, newPassKeyResult);
   hashed = toHex(newPassKeyResult, 32);
   if (set == false){
     uint8_t newPassKeyResult[32];
     sha256(passKey, newPassKeyResult);
     hashed = toHex(newPassKeyResult, 32);
     
     File file = SPIFFS.open("/pass.txt", FILE_WRITE);
     file.print(hashed + "\n");
     file.close();

     File file2 = SPIFFS.open("/key.txt", FILE_WRITE);
     file2.print(seedGenerateStr.substring(0, seedGenerateStr.length()) + "\n");
     file2.close();

     int pubNum = 1;
     File file3 = SPIFFS.open("/num.txt", FILE_WRITE);
     file3.print(pubNum);
     file3.close();

     File otherFile = SPIFFS.open("/key.txt");
     savedSeed = otherFile.readStringUntil('\n');
     otherFile.close();
     
     addrUpdate();
   }
   File otherFile = SPIFFS.open("/pass.txt");
   savedPinHash = otherFile.readStringUntil('\n');
   otherFile.close();

   File otherFile2 = SPIFFS.open("/num.txt");
   pubNumm = otherFile2.readStringUntil('\n');
   otherFile.close();

   if (savedPinHash == hashed)
   {
     isWallet = true;
     getKeys(savedSeed, passKey);
     confirm = true;
     getAddress(true);
     M5.Lcd.fillScreen(BLACK);
     M5.Lcd.setTextSize(LGFONT);
     M5.Lcd.setTextColor(GREEN);
     M5.Lcd.setCursor(0, 30);
     M5.Lcd.println("Sending zpub");
     M5.Lcd.println("to web-wallet");
     delay(2000);
     Serial.print("zpub,%P1" + pubKey.substring(0, 50) + ",");
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
     M5.Lcd.fillScreen(BLACK);
     M5.Lcd.setTextSize(LGFONT);
     M5.Lcd.setTextColor(GREEN);
     M5.Lcd.setCursor(0, 10);
     M5.Lcd.println("Connected");
     M5.Lcd.println("Bwahahaha!");
     M5.Lcd.setTextSize(SMFONT);
     M5.Lcd.setTextColor(BLUE);
     M5.Lcd.println("Verify address:");
     M5.Lcd.setTextColor(WHITE);
     M5.Lcd.println(freshAddress);
     Serial.print(pubKey + ",");
     Serial.print("PINPASS,");
     delay(2000);
     Serial.print("PINPASS,");
     return;
   }
   else if (savedPinHash != hashed)
   {
     M5.Lcd.fillScreen(BLACK);
     M5.Lcd.setTextSize(LGFONT);
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

void getAddress(bool first)
{
  HDPublicKey hd(pubKey);
  if(first){
    String path = String("m/0/") + 1;
    freshAddress = hd.derive(path).address();
    return;
  }
  else{
  File otherFile = SPIFFS.open("/num.txt");
  String pubNum = otherFile.readStringUntil('\n');
  otherFile.close();

  int pubNumm = pubNum.toInt();
  String path = String("m/0/") + pubNumm;
  freshAddress = hd.derive(path).address();
  return;
  }
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
    M5.Lcd.setTextSize(LGFONT);
    M5.Lcd.println("   Error: Reset device");
    M5.Lcd.println("   or restore from seed");
    M5.Lcd.println("   (See documentation)");
    delay(999999999);
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
  M5.Lcd.setTextSize(XLFONT);
  M5.Lcd.setTextColor(GREEN);
  M5.Lcd.println("RESTORE FROM SEED");
  M5.Lcd.setCursor(0, 85);
  M5.Lcd.setTextColor(RED);
  M5.Lcd.setTextSize(LGFONT);
  M5.Lcd.println("Device will be wiped");
  M5.Lcd.println("then restored from seed");
  M5.Lcd.println("are you sure?");
  M5.Lcd.setTextSize(LGFONT);
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
    M5.Lcd.setTextSize(LGFONT);
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

//========================================================================
//========================================================================
//========================================================================
//=============================DECOY GAME STUFF===========================
//========================================================================
//========================================================================
//========================================================================



#define SPEED 1
#define GRAVITY 9.8
#define JUMP_FORCE 2.15
#define SKIP_TICKS 20.0 
#define MAX_FRAMESKIP 5
#define BIRDW 8
#define BIRDH 8
#define BIRDW2 4
#define BIRDH2 4
#define PIPEW 15
#define GAPHEIGHT 30
#define FLOORH 20
#define GRASSH 4
int maxScore = 0;
const int buttonPin = 2;
const unsigned int BCKGRDCOL = M5.Lcd.color565(138, 235, 244);
const unsigned int BIRDCOL = M5.Lcd.color565(255, 254, 174);
const unsigned int PIPECOL = M5.Lcd.color565(99, 255, 78);
const unsigned int PIPEHIGHCOL = M5.Lcd.color565(250, 255, 250);
const unsigned int PIPESEAMCOL = M5.Lcd.color565(0, 0, 0);
const unsigned int FLOORCOL = M5.Lcd.color565(246, 240, 163);
const unsigned int GRASSCOL = M5.Lcd.color565(141, 225, 87);
const unsigned int GRASSCOL2 = M5.Lcd.color565(156, 239, 88);
#define C0 BCKGRDCOL
#define C1 M5.Lcd.color565(195, 165, 75)
#define C2 BIRDCOL
#define C3 TFT_WHITE
#define C4 TFT_RED
#define C5 M5.Lcd.color565(251, 216, 114)
static unsigned int birdcol[] =
    {C0, C0, C1, C1, C1, C1, C1, C0, C0, C0, C1, C1, C1, C1, C1, C0,
     C0, C1, C2, C2, C2, C1, C3, C1, C0, C1, C2, C2, C2, C1, C3, C1,
     C0, C2, C2, C2, C2, C1, C3, C1, C0, C2, C2, C2, C2, C1, C3, C1,
     C1, C1, C1, C2, C2, C3, C1, C1, C1, C1, C1, C2, C2, C3, C1, C1,
     C1, C2, C2, C2, C2, C2, C4, C4, C1, C2, C2, C2, C2, C2, C4, C4,
     C1, C2, C2, C2, C1, C5, C4, C0, C1, C2, C2, C2, C1, C5, C4, C0,
     C0, C1, C2, C1, C5, C5, C5, C0, C0, C1, C2, C1, C5, C5, C5, C0,
     C0, C0, C1, C5, C5, C5, C0, C0, C0, C0, C1, C5, C5, C5, C0, C0};
static struct BIRD
{
    long x, y, old_y;
    long col;
    float vel_y;
} bird;
static struct PIPES
{
    long x, gap_y;
    long col;
} pipes;
int score;
static short tmpx, tmpy;
#define drawPixel(a, b, c)            \
    M5.Lcd.setAddrWindow(a, b, a, b); \
    M5.Lcd.pushColor(c)

//========================================================================

void game_loop()
{
    unsigned char GAMEH = TFTH - FLOORH;
    M5.Lcd.drawFastHLine(0, GAMEH, TFTW, TFT_BLACK);
    M5.Lcd.fillRect(0, GAMEH + 1, TFTW2, GRASSH, GRASSCOL);
    M5.Lcd.fillRect(TFTW2, GAMEH + 1, TFTW2, GRASSH, GRASSCOL2);
    M5.Lcd.drawFastHLine(0, GAMEH + GRASSH, TFTW, TFT_BLACK);
    M5.Lcd.fillRect(0, GAMEH + GRASSH + 1, TFTW, FLOORH - GRASSH, FLOORCOL);
    long grassx = TFTW;
    double delta, old_time, next_game_tick, current_time;
    next_game_tick = current_time = millis();
    int loops;
    bool passed_pipe = false;
    unsigned char px;
    while (1)
    {
        loops = 0;
        while (millis() > next_game_tick && loops < MAX_FRAMESKIP)
        {
            if (digitalRead(M5_BUTTON_HOME) == LOW)
            {
                //while(digitalRead(M5_BUTTON_HOME) == LOW);
                if (bird.y > BIRDH2 * 0.5)
                    bird.vel_y = -JUMP_FORCE;
                // else zero velocity
                else
                    bird.vel_y = 0;
            }
            old_time = current_time;
            current_time = millis();
            delta = (current_time - old_time) / 1000;
            bird.vel_y += GRAVITY * delta;
            bird.y += bird.vel_y;
            pipes.x -= SPEED;
            if (pipes.x < -PIPEW)
            {
                pipes.x = TFTW;
                pipes.gap_y = random(10, GAMEH - (10 + GAPHEIGHT));
            }
            next_game_tick += SKIP_TICKS;
            loops++;
        }
        if (pipes.x >= 0 && pipes.x < TFTW)
        {
            M5.Lcd.drawFastVLine(pipes.x + 3, 0, pipes.gap_y, PIPECOL);
            M5.Lcd.drawFastVLine(pipes.x + 3, pipes.gap_y + GAPHEIGHT + 1, GAMEH - (pipes.gap_y + GAPHEIGHT + 1), PIPECOL);
            M5.Lcd.drawFastVLine(pipes.x, 0, pipes.gap_y, PIPEHIGHCOL);
            M5.Lcd.drawFastVLine(pipes.x, pipes.gap_y + GAPHEIGHT + 1, GAMEH - (pipes.gap_y + GAPHEIGHT + 1), PIPEHIGHCOL);
            drawPixel(pipes.x, pipes.gap_y, PIPESEAMCOL);
            drawPixel(pipes.x, pipes.gap_y + GAPHEIGHT, PIPESEAMCOL);
            drawPixel(pipes.x, pipes.gap_y - 6, PIPESEAMCOL);
            drawPixel(pipes.x, pipes.gap_y + GAPHEIGHT + 6, PIPESEAMCOL);
            drawPixel(pipes.x + 3, pipes.gap_y - 6, PIPESEAMCOL);
            drawPixel(pipes.x + 3, pipes.gap_y + GAPHEIGHT + 6, PIPESEAMCOL);
        }
#if 1
        if (pipes.x <= TFTW)
            M5.Lcd.drawFastVLine(pipes.x + PIPEW, 0, GAMEH, BCKGRDCOL);
#endif
        tmpx = BIRDW - 1;
        do
        {
            px = bird.x + tmpx + BIRDW;
            tmpy = BIRDH - 1;
            do
            {
                drawPixel(px, bird.old_y + tmpy, BCKGRDCOL);
            } while (tmpy--);
            tmpy = BIRDH - 1;
            do
            {
                drawPixel(px, bird.y + tmpy, birdcol[tmpx + (tmpy * BIRDW)]);
            } while (tmpy--);
        } while (tmpx--);
        bird.old_y = bird.y;
        grassx -= SPEED;
        if (grassx < 0)
            grassx = TFTW;
        M5.Lcd.drawFastVLine(grassx % TFTW, GAMEH + 1, GRASSH - 1, GRASSCOL);
        M5.Lcd.drawFastVLine((grassx + 64) % TFTW, GAMEH + 1, GRASSH - 1, GRASSCOL2);
        if (bird.y > GAMEH - BIRDH)
            break;
        if (bird.x + BIRDW >= pipes.x - BIRDW2 && bird.x <= pipes.x + PIPEW - BIRDW)
        {
            if (bird.y < pipes.gap_y || bird.y + BIRDH > pipes.gap_y + GAPHEIGHT)
                break;
            else
                passed_pipe = true;
        }
        else if (bird.x > pipes.x + PIPEW - BIRDW && passed_pipe)
        {
            passed_pipe = false;
            M5.Lcd.setTextColor(BCKGRDCOL);
            M5.Lcd.setCursor(TFTW2, 4);
            M5.Lcd.print(score);
            M5.Lcd.setTextColor(TFT_WHITE);
            score++;
        }
        M5.Lcd.setCursor(2, 4);
        M5.Lcd.print(score);
    }
    delay(1200);
}

//========================================================================

void game_init()
{
    M5.Lcd.fillScreen(BCKGRDCOL);
    score = 0;
    bird.x = 30;
    bird.y = bird.old_y = TFTH2 - BIRDH;
    bird.vel_y = -JUMP_FORCE;
    tmpx = tmpy = 0;
    randomSeed(analogRead(0));
    pipes.x = 0;
    pipes.gap_y = random(20, TFTH - 60);
}

//========================================================================

void game_start()
{
    M5.Lcd.fillScreen(TFT_BLACK);
    M5.Lcd.setTextColor(TFT_WHITE);
    M5.Lcd.drawBitmap(TFTW2 - 25, 0, 55, 55, (uint8_t *)just_bowser_map);
    M5.Lcd.setTextSize(SMFONT);
    M5.Lcd.setCursor(40 - 15, TFTH2 - 6);
    M5.Lcd.println("");
    M5.Lcd.println("   FLAPPY");
    M5.Lcd.setTextSize(SMFONT);
    M5.Lcd.setCursor(40 - 22, TFTH2 + 6);
    M5.Lcd.println("");
    M5.Lcd.println("  -BOWSER-");
    M5.Lcd.setTextSize(SMFONT);
    M5.Lcd.setCursor(15, TFTH2 - 21);
    M5.Lcd.println("Mwahahaha");
    M5.Lcd.setCursor(40 - 40, TFTH2 + 21);
    M5.Lcd.println("");
    M5.Lcd.println("");
    M5.Lcd.println("  press A");    
}

//========================================================================

void EEPROM_Write(int *num, int MemPos)
{
    byte ByteArray[2];
    memcpy(ByteArray, num, 2);
    for (int x = 0; x < 2; x++)
    {
        EEPROM.write((MemPos * 2) + x, ByteArray[x]);
    }
}

//========================================================================

void EEPROM_Read(int *num, int MemPos)
{
    byte ByteArray[2];
    for (int x = 0; x < 2; x++)
    {
        ByteArray[x] = EEPROM.read((MemPos * 2) + x);
    }
    memcpy(num, ByteArray, 2);
}

//========================================================================

void game_over()
{
    M5.Lcd.fillScreen(TFT_BLACK);
    EEPROM_Read(&maxScore, 0);

    if (score > maxScore)
    {
        EEPROM_Write(&score, 0);
        maxScore = score;
        M5.Lcd.setTextColor(TFT_RED);
        M5.Lcd.setTextSize(SMFONT);
        M5.Lcd.setCursor(0, TFTH2 - 16);
        M5.Lcd.println("HIGHSCORE");
    }

    M5.Lcd.setTextColor(TFT_WHITE);
    M5.Lcd.setTextSize(SMFONT);
    M5.Lcd.setCursor(40 - 25, TFTH2 - 6);
    M5.Lcd.println("");
    M5.Lcd.println(" GAME OVER");
    M5.Lcd.setTextSize(SMFONT);
    M5.Lcd.setCursor(1, 10);
    M5.Lcd.setTextSize(1);
    M5.Lcd.print("score: ");
    M5.Lcd.print(score);
    M5.Lcd.setCursor(5, TFTH2 + 6);
    M5.Lcd.setTextSize(SMFONT);
    M5.Lcd.println("");
    M5.Lcd.println("  press A");
    M5.Lcd.setCursor(1, 21);
    M5.Lcd.setTextSize(1);
    M5.Lcd.print("Max Score:");
    M5.Lcd.print(maxScore);
    while (1)
    {
        if (digitalRead(M5_BUTTON_HOME) == LOW)
        {
            while (digitalRead(M5_BUTTON_HOME) == LOW)
                ;
            break;
        }
    }
}

//========================================================================

void resetMaxScore()
{
    EEPROM_Write(&maxScore, 0);
}

//========================================================================

void decoyRun(){
  game_start();
      while (1)
    {
        if (digitalRead(M5_BUTTON_HOME) == LOW)
        {
            while (digitalRead(M5_BUTTON_HOME) == LOW)
                ;
            break;
        }
        readCommands();   
        if(!decoy){
          break;
        }
    }
  if(decoy){  
    game_init();
    game_loop();
    game_over();
  }
}

//========================================================================

void decoySetup()
{
    game_start();
    resetMaxScore();
    pinMode(M5_BUTTON_HOME, INPUT);
    while (decoy)
    {
      decoyRun();
      
    }
}
