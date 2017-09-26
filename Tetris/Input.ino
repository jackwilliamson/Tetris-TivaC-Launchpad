#include <delay.h> ////
#include <FillPat.h>
#include <LaunchPad.h>
#include <OrbitBoosterPackDefs.h>
#include <OrbitOled.h>
#include <OrbitOledChar.h>
#include <OrbitOledGrph.h>
#include <Wire.h>

//0 to 4095
char value[10];

const uint32_t SwitchCount = 2;
const uint32_t ButtonCount = 4;
const uint32_t Switches[SwitchCount] = { PA_7, PA_6 };
const uint32_t Buttons[ButtonCount+1] = {0,PD_2, PE_0, PUSH1, PUSH2 };
const uint32_t Potentiometer = PE_3;

struct ButtonState
{ 
  bool state;
  bool isRising;
};

static struct InputState
{
  bool                switches[2];
  struct ButtonState  buttons[5];
  float               potentiometer;
} gameInputState = {0};


/*
 *   2
 *   1
 * 3   4
 * 
 */


static void inputTick()
{
  for(int i = 0; i < SwitchCount; ++i )
    gameInputState.switches[i] = digitalRead(Switches[i]);
  for(int i = 1; i < ButtonCount+1; ++i )
  {
    // Only look for Rising Edge Signals.
    bool previousState = gameInputState.buttons[i].state;
    gameInputState.buttons[i].state = digitalRead(Buttons[i]);
    gameInputState.buttons[i].isRising = (!previousState && gameInputState.buttons[i].state);
  }
  gameInputState.potentiometer = analogRead(Potentiometer);
}

int ReadP(){
  int Pinput = 0;
  Pinput = analogRead(Potentiometer);
  return Pinput;
}

bool buttonPressed(int n){
  int x = digitalRead(Buttons[n]);
  if (n == 1 || n == 2 ){
    return x;
  }
  else return !x;
}

void inputInit(){

  for(int i = 0; i < SwitchCount; ++i )
    pinMode(Switches[i], INPUT);
    pinMode(Buttons[1], INPUT);
    pinMode(Buttons[2], INPUT);
    pinMode(Buttons[3], INPUT_PULLUP);
    pinMode(Buttons[4], INPUT_PULLUP);

    pot = ReadP();
    prevPot = ReadP();
}


