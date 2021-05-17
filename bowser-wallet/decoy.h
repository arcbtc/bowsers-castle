#define TFTW 80 
#define TFTH 160 
#define TFTW2 40 
#define TFTH2 80
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
bool decoy = true;
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
    M5.Lcd.fillRect(0, TFTH2 - 10, TFTW, 1, TFT_WHITE);
    M5.Lcd.fillRect(0, TFTH2 + 15, TFTW, 1, TFT_WHITE);
    M5.Lcd.setTextColor(TFT_WHITE);
    M5.Lcd.setTextSize(1);
    M5.Lcd.setCursor(TFTW2 - 15, TFTH2 - 6);
    M5.Lcd.println("FLAPPY");
    M5.Lcd.setTextSize(1);
    M5.Lcd.setCursor(TFTW2 - 22, TFTH2 + 6);
    M5.Lcd.println("-BOWSER-");
    M5.Lcd.setTextSize(1);
    M5.Lcd.setCursor(15, TFTH2 - 21);
    M5.Lcd.println("Mwahahaha");
    M5.Lcd.setCursor(TFTW2 - 40, TFTH2 + 21);
    M5.Lcd.println(" press btn A");    
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
        M5.Lcd.setTextSize(1);
        M5.Lcd.setCursor(0, TFTH2 - 16);
        M5.Lcd.println("NEW HIGHSCORE");
    }

    M5.Lcd.setTextColor(TFT_WHITE);
    M5.Lcd.setTextSize(1);
    M5.Lcd.setCursor(TFTW2 - 25, TFTH2 - 6);
    M5.Lcd.println("GAME OVER");
    M5.Lcd.setTextSize(1);
    M5.Lcd.setCursor(1, 10);
    M5.Lcd.print("score: ");
    M5.Lcd.print(score);
    M5.Lcd.setCursor(5, TFTH2 + 6);
    M5.Lcd.println("press button");
    M5.Lcd.setCursor(1, 21);
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
    }
  game_init();
  game_loop();
  game_over();
}

//========================================================================

void decoySetup()
{
    game_start();
    resetMaxScore();
    pinMode(M5_BUTTON_HOME, INPUT);
    int starttime = millis();
    while (millis() - starttime < 500)
    {
        if (M5.BtnB.wasReleased())
        {
            decoy = false;
            M5.Lcd.fillScreen(BLACK);
        }
        M5.update();
    }
    if (decoy == true)
    {
        delay(2000);
        while (1)
        {
            decoyRun();
        }
    }
}
