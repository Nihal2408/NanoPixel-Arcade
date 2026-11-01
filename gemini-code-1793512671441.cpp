#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Button & Buzzer Pins
const int PIN_JUMP = 2;   // Button 1: Jump (Active LOW)
const int PIN_DUCK = 3;   // Button 2: Duck (Active LOW)
const int PIN_BUZZER = 8; // Optional audio feedback

// Physics & Player Settings
const int GROUND_Y = 56;
const int PLAYER_X = 16;
const int NORMAL_W = 8;
const int NORMAL_H = 12;
const int DUCK_W = 12;
const int DUCK_H = 6;

float playerY = GROUND_Y - NORMAL_H;
float velocityY = 0;
const float GRAVITY = 0.85;
const float JUMP_FORCE = -6.8;
bool isJumping = false;
bool isDucking = false;

// Obstacles
enum ObstacleType { GROUND_CACTUS, FLYING_BIRD };
ObstacleType obsType = GROUND_CACTUS;

float obsX = 128;
int obsW = 6;
int obsH = 12;
int obsY = GROUND_Y - 12;
float gameSpeed = 3.5;

int score = 0;
bool gameOver = false;

void spawnObstacle() {
  obsX = 128;
  // Randomly spawn a ground cactus or an overhead flying obstacle
  if (random(0, 2) == 0) {
    obsType = GROUND_CACTUS;
    obsW = 6;
    obsH = 12;
    obsY = GROUND_Y - obsH;
  } else {
    obsType = FLYING_BIRD;
    obsW = 10;
    obsH = 5;
    obsY = GROUND_Y - NORMAL_H - 2; // Flies right at standing head height
  }
}

void setup() {
  pinMode(PIN_JUMP, INPUT_PULLUP);
  pinMode(PIN_DUCK, INPUT_PULLUP);
  pinMode(PIN_BUZZER, OUTPUT);

  randomSeed(analogRead(A0)); // Seed random generator with floating analog pin

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    while (true); // Lock if OLED fails to start
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(18, 18);
  display.print(F("DUAL-BUTTON RUNNER"));
  display.setCursor(20, 34);
  display.print(F("D2: JUMP | D3: DUCK"));
  display.setCursor(22, 50);
  display.print(F("Press any key..."));
  display.display();

  // Wait for either button to be pressed
  while (digitalRead(PIN_JUMP) == HIGH && digitalRead(PIN_DUCK) == HIGH);
  delay(200);
}

void loop() {
  if (gameOver) {
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(12, 14);
    display.print(F("GAME OVER"));
    
    display.setTextSize(1);
    display.setCursor(35, 36);
    display.print(F("Score: "));
    display.print(score);

    display.setCursor(14, 50);
    display.print(F("Press Jump to Play"));
    display.display();

    tone(PIN_BUZZER, 180, 250);

    delay(400);
    while (digitalRead(PIN_JUMP) == HIGH);
    
    // Reset Game Variables
    spawnObstacle();
    score = 0;
    gameSpeed = 3.5;
    playerY = GROUND_Y - NORMAL_H;
    velocityY = 0;
    isJumping = false;
    isDucking = false;
    gameOver = false;
    delay(200);
    return;
  }

  // --- 1. Read Inputs ---
  bool jumpPressed = (digitalRead(PIN_JUMP) == LOW);
  bool duckPressed = (digitalRead(PIN_DUCK) == LOW);

  // Jump logic (can only jump if on ground and not ducking)
  if (jumpPressed && !isJumping && !duckPressed) {
    velocityY = JUMP_FORCE;
    isJumping = true;
    tone(PIN_BUZZER, 1000, 35);
  }

  // Duck logic (only when on the ground)
  if (duckPressed && !isJumping) {
    isDucking = true;
  } else {
    isDucking = false;
  }

  // --- 2. Update Physics ---
  velocityY += GRAVITY;
  playerY += velocityY;

  // Ground collision check
  int currentH = isDucking ? DUCK_H : NORMAL_H;
  if (playerY >= GROUND_Y - currentH) {
    playerY = GROUND_Y - currentH;
    velocityY = 0;
    isJumping = false;
  }

  // --- 3. Move Obstacle ---
  obsX -= gameSpeed;
  if (obsX < -obsW) {
    score++;
    spawnObstacle();
    if (gameSpeed < 7.5) {
      gameSpeed += 0.15; // Speed ramps up gradually
    }
  }

  // --- 4. Collision Detection (AABB) ---
  int currentW = isDucking ? DUCK_W : NORMAL_W;
  if ((PLAYER_X < obsX + obsW) &&
      (PLAYER_X + currentW > obsX) &&
      (playerY < obsY + obsH) &&
      (playerY + currentH > obsY)) {
    gameOver = true;
  }

  // --- 5. Render to Screen ---
  display.clearDisplay();

  // Horizon Line
  display.drawFastHLine(0, GROUND_Y, 128, SSD1306_WHITE);

  // Draw Player
  display.fillRect(PLAYER_X, (int)playerY, currentW, currentH, SSD1306_WHITE);

  // Draw Obstacle
  if (obsType == GROUND_CACTUS) {
    display.fillRect((int)obsX, obsY, obsW, obsH, SSD1306_WHITE);
  } else {
    // Flying Bird (Drawn with simple wings)
    display.fillRect((int)obsX, obsY, obsW, obsH, SSD1306_WHITE);
    display.drawPixel((int)obsX - 1, obsY + 2, SSD1306_WHITE); // Beak
  }

  // HUD Score
  display.setTextSize(1);
  display.setCursor(90, 2);
  display.print(F("SC:"));
  display.print(score);

  display.display();
  delay(15);
}