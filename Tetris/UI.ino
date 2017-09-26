#include <delay.h> /////
#include <FillPat.h>
#include <LaunchPad.h>
#include <OrbitBoosterPackDefs.h>
#include <OrbitOled.h>
#include <OrbitOledChar.h>
#include <OrbitOledGrph.h>
#include <Wire.h>






void GameUIInit()
{
  OrbitOledInit();
  OrbitOledClear();
  OrbitOledClearBuffer();
  OrbitOledSetFillPattern(OrbitOledGetStdPattern(iptnSolid));
  OrbitOledSetDrawMode(modOledSet);

}

void page_Welcome(){
  OrbitOledMoveTo(5, 0);
  OrbitOledDrawString("!!!!TETRIS!!!!");
  
  if (buttonPressed(3)){
    if (options == Start) options = Hard;
    else options--;
  }
  else if (buttonPressed(4)){
    if (options == Hard) options = Start;
    else options++;
  }

  OrbitOledMoveTo(0, 10);
  switch (options){
    case Start:
      OrbitOledDrawString("BTN3/4 to change");
      break;
    case Start2:
      OrbitOledDrawString("BTN1 to select");
      break;
    case Tutorial:
      OrbitOledDrawString("-Tutorial-");
      if (buttonPressed(1)) gameUiPage = Tutorial1;
      break;
    case Easy:
      OrbitOledDrawString("-Start: Easy-");
      if (buttonPressed(1)){
        dropRate = 300; updateRate = 70; scoreMultiplier = 0.5;
        gameUiPage = MainGame;
        blockQueue = (millis() + pastTime + random(0, 77) )%7; blockGenerate();
      }
      break;
    case Medium:
      OrbitOledDrawString("-Start: Medium-");
      if (buttonPressed(1)){
        dropRate = 200; updateRate = 70; scoreMultiplier = 3;
        gameUiPage = MainGame;
        blockQueue = (millis() + pastTime + random(0, 77) )%7; blockGenerate();
      }
      break;
    case Hard:
      OrbitOledDrawString("-Start: Hard-");
      if (buttonPressed(1)){
        dropRate = 100; updateRate = 70; scoreMultiplier = 9;
        gameUiPage = MainGame;
        blockQueue = (millis() + pastTime + random(0, 77) )%7; blockGenerate();
      }
      break;
  }

}

void page_MainGame(){
  //border
  for (int i=0; i<30; i++){
    for (int j=0; j<10; j++){
      if (displayArray[j][i]){
        for (int a=0; a<3; a++){
          for (int b=0; b<3; b++){
            //              y           x
            OrbitOledMoveTo(89 - 3*i+a, 3*j+b);
            OrbitOledDrawPixel();
          }
        }
      }
    }
  }
  
    for (int j=0; j<10; j++){
      for (int a=0; a<3; a++){
          for (int b=0; b<3; b++){
      OrbitOledMoveTo(92, 3*j+b);
      OrbitOledDrawPixel();
          }
      }
    }

  for (int i=0; i<4; i++){
    for (int j=0; j<4; j++){
      if (block[blockQueue][0][i][j]){
        for (int a=0; a<3; a++){
          for (int b=0; b<3; b++){
            //              y           x
            OrbitOledMoveTo(104 - 3*i+a, 3 + 3*j+b);
            OrbitOledDrawPixel();
          }
        }
      }
    }
  }
}

void page_Tutorial1(){
  OrbitOledMoveTo(0, 0); OrbitOledDrawString("BTN 1/2");
  OrbitOledMoveTo(0, 10); OrbitOledDrawString("Move Left/Right");
  if (buttonPressed(1)) gameUiPage = Tutorial2;
}
void page_Tutorial2(){
  OrbitOledMoveTo(0, 0); OrbitOledDrawString("Wheel Thingy");
  OrbitOledMoveTo(0, 10); OrbitOledDrawString("Rotate Block");
  if (buttonPressed(1)) gameUiPage = Tutorial3;
}
void page_Tutorial3(){
  OrbitOledMoveTo(0, 0); OrbitOledDrawString("BTN 3");
  OrbitOledMoveTo(0, 10); OrbitOledDrawString("Drop Block Down");
  if (buttonPressed(1)) gameUiPage = Tutorial4;
}
void page_Tutorial4(){
  OrbitOledMoveTo(0, 0); OrbitOledDrawString("BTN 4");
  OrbitOledMoveTo(0, 10); OrbitOledDrawString("One Time Lifeline");
  if (buttonPressed(1)) gameUiPage = Welcome;
}

void page_GameOver(){
  delay(100);
  OrbitOledClear();
  for (int i=20; i>=0; i--){
    OrbitOledMoveTo(10, i); OrbitOledDrawString("GAME OVER"); OrbitOledUpdate();
    delay(50);
    OrbitOledClear();
  }
  delay(40);
  
  OrbitOledMoveTo(0, 0); OrbitOledDrawString("Your Score:");
  char scoreString[15] = "";
  sprintf(scoreString, "%llu", score);
  OrbitOledMoveTo(0, 10);
  OrbitOledDrawString(scoreString);
  OrbitOledUpdate();
  while (!buttonPressed(1) && !buttonPressed(2) && !buttonPressed(3) && !buttonPressed(4)){
    delay(20);
  }
  restart();
}

void GameUI(){
  OrbitOledClear();
  
  
  switch(gameUiPage){
  case Welcome:
    page_Welcome();
  break;
  
  case Tutorial1:
    page_Tutorial1();
  break;
  
  case Tutorial2:
    page_Tutorial2();
  break;

  case Tutorial3:
    page_Tutorial3();
  break;
  
  case Tutorial4:
    page_Tutorial4();
  break;
  
  case MainGame:
    FinalDisplay();
    page_MainGame();
  break;

  case Score:
    page_GameOver();
  break; 
  }
  
  OrbitOledUpdate();
  
}

