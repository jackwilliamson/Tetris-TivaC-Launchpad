#include <delay.h> ////
#include <FillPat.h>
#include <LaunchPad.h>
#include <OrbitBoosterPackDefs.h>
#include <OrbitOled.h>
#include <OrbitOledChar.h>
#include <OrbitOledGrph.h>
#include <Wire.h>
#include <stdbool.h>

/*2 - border
 * 6 -  hold and future
 * 2 middle border
 * 30 - main game
 * 2 - bottom border
 */

 // total dimensions: 128x32


 /*       
  *       + - - - > +
  *       |
  *       |
  *       |
  *       v
  *       +
  *       
  */


//oblock - 0
//lblock - 1
//iblock - 2
//jblock - 3
//sblock - 4
//zblock - 5
//tblock - 6

//[block type][rotations][y][x]

bool block[7][4][4][4] = {{{{1,1,0,0},  //oblock
                           {1,1,0,0},
                           {0,0,0,0},
                           {0,0,0,0}},
                    
                            {{1,1,0,0},
                             {1,1,0,0},
                             {0,0,0,0},
                             {0,0,0,0}},
                    
                            {{1,1,0,0},
                             {1,1,0,0},
                             {0,0,0,0},
                             {0,0,0,0}},
                             
                            {{1,1,0,0},
                             {1,1,0,0},
                             {0,0,0,0},
                             {0,0,0,0}}},

                      {{{0,0,1,0},  //lblock
                        {1,1,1,0},
                        {0,0,0,0},
                        {0,0,0,0}},

                        
                        {{0,1,0,0},
                         {0,1,0,0},
                         {0,1,1,0},
                         {0,0,0,0}},
                        
                        {{0,0,0,0},
                         {1,1,1,0},
                         {1,0,0,0},
                         {0,0,0,0}},
                        
                        {{1,1,0,0},
                         {0,1,0,0},
                         {0,1,0,0},
                         {0,0,0,0}}},

                         {{{0,1,0,0},  //iblock
                           {0,1,0,0},
                           {0,1,0,0},
                           {0,1,0,0}},
                        
                        {{0,0,0,0},
                         {1,1,1,1},
                         {0,0,0,0},
                         {0,0,0,0}},
                         
                         {{0,1,0,0},
                          {0,1,0,0},
                          {0,1,0,0},
                          {0,1,0,0}},
                        
                        {{0,0,0,0},
                         {1,1,1,1},
                         {0,0,0,0},
                         {0,0,0,0}}},


                         {{{1,0,0,0}, //jblock
                           {1,1,1,0},
                           {0,0,0,0},
                           {0,0,0,0}},


                        {{0,1,1,0},
                         {0,1,0,0},
                         {0,1,0,0},
                         {0,0,0,0}},

                        {{0,0,0,0},
                         {1,1,1,0},
                         {0,0,1,0},
                         {0,0,0,0}},

                        {{0,1,0,0},
                         {0,1,0,0},
                         {1,1,0,0},
                         {0,0,0,0}}},

                         {{{0,0,0,0}, //sblock
                           {0,1,1,0},
                           {1,1,0,0},
                           {0,0,0,0}},
                        
                        {{0,1,0,0},
                         {0,1,1,0},
                         {0,0,1,0},
                         {0,0,0,0}},
                         
                         {{0,0,0,0},
                          {0,1,1,0},
                          {1,1,0,0},
                          {0,0,0,0}},
                        
                        {{0,1,0,0},
                         {0,1,1,0},
                         {0,0,1,0},
                         {0,0,0,0}}},


                         {{{0,0,0,0}, //zblock
                           {1,1,0,0},
                           {0,1,1,0},
                           {0,0,0,0}},

                    {{0,1,0,0},
                     {1,1,0,0},
                     {1,0,0,0},
                     {0,0,0,0}},
                     
                     
                        {{0,0,0,0},
                         {1,1,0,0},
                         {0,1,1,0},
                         {0,0,0,0}},

                    {{0,1,0,0},
                     {1,1,0,0},
                     {1,0,0,0},
                     {0,0,0,0}}},

                      {{{0,1,0,0}, //tblock
                        {1,1,1,0},
                        {0,0,0,0},
                        {0,0,0,0}},
                    
                        {{0,1,0,0},
                         {0,1,1,0},
                         {0,1,0,0},
                         {0,0,0,0}},

                        {{0,0,0,0},
                         {1,1,1,0},
                         {0,1,0,0},
                         {0,0,0,0}},

                        {{0,1,0,0},
                         {1,1,0,0},
                         {0,1,0,0},
                         {0,0,0,0}}}};




int checkFreeSpace();





int Bsquare[2][2] = { {1,1}, 
                      {1,1} };



struct Block{
  int kind;
  bool shape[4][4];
  int x;
  int y;
  int rotation;
} current;

int endCheck(){
  int collisionFlag = 0;
  for (int i=0; i<4; i++){
    for (int j=0; j<4; j++){
      if (mainArray[current.x+i][current.y+j] && current.shape[i][j])
        collisionFlag = 1;
     }
  }
  if (collisionFlag) gameUiPage = Score;
}

int blockGenerate(){
  int num = blockQueue;
  blockQueue = (millis() + pastTime + random(0, 77) )%7;
  for (int i=0; i<4; i++){
    for (int j=0; j<4; j++){
      current.shape[i][j] = block[num][0][j][i];
    }
  }
  current.kind = num;
  current.x = 4;
  current.y = 0;
  current.rotation = 0;
  endCheck();
}

void clearNthRow(int n){
  for(int i = n; i > 0; i--){
    for(int j = 0; j < 10; j++){
      mainArray[j][i] = mainArray[j][i-1];
    }
  }
  score += 76*scoreMultiplier;
}

int checkClearedRow(int y){
  for(int i = 0; i < 4; i++){
    int fullRow = 1;
    for(int j = 0; j < 10 && fullRow; j++){
      fullRow = mainArray[j][y+i];
    }
    if(fullRow){
      clearNthRow(y+i);
    }
  }
}

void Hshift(){
  int xchange = 0;
  if (buttonPressed(2)) xchange = -1;
  else if (buttonPressed(1)) xchange = 1;
  else return;
  

  for (int i=0; i<4; i++){
    for (int j=0; j<4; j++){
      if(current.shape[i][j] && (current.x+i+xchange < 0 || current.x+i+xchange >= 10))
      return;
      if (mainArray[current.x+i+xchange][current.y+j] && current.shape[i][j])
      return;
     }
  }
  
  
  current.x += xchange;
}

int lowest(bool shape[4][4]){
  for (int i=3; i>=0; i--){
    for (int j=0; j<4; j++){
      if (current.shape[j][i]){
        return i;
      }
     }
  }
}

int Vshift(){
  int collisionFlag = 0;
  for (int i=0; i<4; i++){
    for (int j=0; j<4; j++){
      if (mainArray[current.x+i][current.y+j+1] && current.shape[i][j])
        collisionFlag = 1;
     }
  }
  if (collisionFlag || lowest(current.shape) + current.y >= 29) {
    for (int i=0; i<4 && current.x+i<=9; i++){
      for (int j=0; j<4 && current.y+j <=29 ; j++){
        mainArray[current.x+i][current.y+j] += current.shape[i][j];
       }
    }
    checkClearedRow(current.y);
    blockGenerate();
    score += 9*scoreMultiplier;
    return 0;
  }
  current.y++;
  return 1;
}

void rotate(){

  int newRotation = current.rotation;
  
  if(pot - prevPot > 50){
    //rotate right
    newRotation = current.rotation + 1;
    if(newRotation > 3){
      newRotation = 0;
    }

    
  }
  if(pot - prevPot < -50){
    //rotate left
    newRotation = current.rotation - 1;
    if(newRotation < 0){
      newRotation = 3;
    }
  }

  for(int i = 0; i < 4; i++){
    for(int j = 0; j < 4; j++){
      if(block[current.kind][newRotation][j][i]){
        if(j+current.y > 29 || i+current.x > 9 || j+current.y < 0 || i+current.x < 0 || mainArray[current.x+i][current.y+j]){
          return;
        }
      }
    }
  }

  current.rotation = newRotation;

  for (int i=0; i<4; i++){
    for (int j=0; j<4; j++){
      current.shape[i][j] = block[current.kind][current.rotation][j][i];
    }
  }
  score += 1 * scoreMultiplier;
}

void drop(){
  if (buttonPressed(3)&& current.y > 1) while(Vshift()) {};
}

void lifeLine(){
  if (lifeLineFlag && buttonPressed(4)){
  for (int i=0; i<5; i++) clearNthRow(29);
  blockGenerate();
  lifeLineFlag = 0;
  }
}

void FinalDisplay(){
  for (int i=0; i<10; i++){
    for (int j=0; j<30; j++){
      displayArray[i][j] = mainArray[i][j];
     }
  }
  for (int i=0; i<4; i++){
    for (int j=0; j<4; j++){
      if(i+current.x <= 9 && j+current.y <= 29){
        displayArray[i+current.x][j+current.y] = (displayArray[i+current.x][j+current.y] || current.shape[i][j]);
      }
     }
  }
  //return &tempArray[0][0];
}

void GameTick(){
  
  Hshift();
  lifeLine();
  drop();
  prepot = tempPot;
  tempPot = pot;
  pot = ReadP();
  
  if (millis() - pastTime >= dropRate){

    rotate();
    Vshift();
    pastTime = millis();
  }
  FinalDisplay();
}



