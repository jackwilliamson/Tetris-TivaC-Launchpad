#include <delay.h> /////
#include <FillPat.h>
#include <LaunchPad.h>
#include <OrbitBoosterPackDefs.h>
#include <OrbitOled.h>
#include <OrbitOledChar.h>
#include <OrbitOledGrph.h>
#include <Wire.h>

bool displayArray[10][30] = {{0},{0}};
bool mainArray[10][30] = {{0},{0}}; // [x][y] by player perspective, (0,0) is in the top left corner
int dropRate = 200;
int updateRate = 130;
double scoreMultiplier = 0.5;
unsigned long pastTime = 0;
unsigned long long score = 0;
int lifeLineFlag = 1;



int prevPot = 0;
int tempPot = 0;
int pot = 0;

int blockQueue = 0;



static enum GamePages
{
  Welcome       = 0,
  Tutorial1     = 1,
  Tutorial2     = 2,
  Tutorial3     = 3,
  Tutorial4     = 4,
  Tutorial5     = 5,
  MainGame      = 6,
  Score         = 7,
} gameUiPage = Welcome;


#define  Start         0
#define  Tutorial      1
#define  Easy          2
#define  Medium        3
#define  Hard          4
int options = Start;



//--------------------------------------------------------------------------------------------------

void restart(){
  for (int i=0; i<10; i++){
    for (int j=0; j<30; j++){
      displayArray[i][j] = 0;
      mainArray[i][j] = 0;
    }
  }
  dropRate = 200;
  updateRate = 130;
  
  pastTime = 0;
  scoreMultiplier = 0.5;
  score = 0;
  prevPot = 0;
  pot = 0;
  tempPot = 0;
  lifeLineFlag = 1;
  
  gameUiPage = Welcome;
  options = Start;
}

void setup(){
  
  Serial.begin(9600);
  WireInit();
  GameUIInit();
  inputInit();
  delay(100);
  
}

void loop(){
  
  if (gameUiPage == MainGame) GameTick();
  GameUI();
  delay(updateRate);
}

