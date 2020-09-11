

/**********included files/libraries***************/
#include <Arduboy2.h>
#include <ArduboyTones.h>
#include "tileData.h"




/**************** Variable Declarations *****************/
Arduboy2 arduboy;
ArduboyTones sound(arduboy.audio.enabled);

int numberGrid[4][4];
int tileList[16] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0}; //starting list of numbers used in order. 0 is the blank
unsigned long seed = 64; //seems from documentation that it must be an unsigned long that is given to randomSeed function.

bool aButtonPressed = false;
bool bButtonPressed = false;
bool upButtonPressed = false;
bool downButtonPressed = false;
bool leftButtonPressed = false;
bool rightButtonPressed = false;



/**************** Routine Declarations *****************/

void shuffleArray(unsigned long _inputSeed){  //NOTE removed Array input as playing up, direct reference to tile list. Not an issue for later game (fixed level design), but need too try proper prototyping(?) to use so could be good test software 
  randomSeed(_inputSeed); 
  for(int i=15; i>0; i--){
    int pickedElement = random(0,i+1); //random number between 0 and current end point (i form loop, goes down)
      int tempStore = tileList[i]; //store the current end point
      tileList[i] = tileList[pickedElement]; //move randomly picked element to the end
      tileList[pickedElement] = tempStore; //but the previous end number into array from where pick was form (new shorted list when i is reduced)
  }

  
}

void makeStartingGrid(){

  for(int x=0; x<4; x++){
    for(int y=0; y<4 ;y++){
        //code to loop through the number grid and set values
        numberGrid[x][y] = tileList[(x*4)+y];
    }
  }


  
}



/**************** Setup.Startup Code  *****************/
void setup() {
  arduboy.begin();
  arduboy.setFrameRate(60);     //60 fps
  arduboy.clear();
  arduboy.audio.on();

  shuffleArray(seed);
  makeStartingGrid();
  

}

/**************** Main Code Loop *****************/
void loop() {
 if(!arduboy.nextFrame()) {
    return; 
  }
  arduboy.clear();


  //demo print code: to delete
 arduboy.println(seed);
 for(int i=0; i<16; i=i+3){
  arduboy.print(tileList[i]);
  arduboy.print(";");
  if(i<14){
  arduboy.print(tileList[i+1]);
  arduboy.print(";");
  arduboy.print(tileList[i+2]);
  arduboy.println(";");
  }
 }


   arduboy.display();
}
