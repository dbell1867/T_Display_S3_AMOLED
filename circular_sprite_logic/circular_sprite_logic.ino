#include "rm67162.h"
#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite sprite = TFT_eSprite(&tft);

double rad=0.01745;

float ox[360]; //outer point
float oy[360];
float ix[360]; //short inner point
float iy[360];
float lx[360]; //long inner point
float ly[360];

int r=280;
int sx=-170;
int sy=268;


void setup(){  
  rm67162_init();  // amoled lcd initialization
  sprite.createSprite(240, 536);
  sprite.setSwapBytes(1);
  sprite.setTextDatum(1);//anchor point at centre top
  sprite.drawString("Hello World",120,20,4);//centre top of screen

  for(int i=0;i<360;i++)
  {
       ox[i]=(r*cos(rad*i))+sx;
       oy[i]=(r*sin(rad*i))+sy;
       ix[i]=((r-14)*cos(rad*i))+sx;
       iy[i]=((r-14)*sin(rad*i))+sy;
       lx[i]=((r-28)*cos(rad*i))+sx;
       ly[i]=((r-28)*sin(rad*i))+sy;
  }     
}

void draw(){
 for(int i=0;i<360;i++)
  if (i%10==0) //important to put the less frequent occurrence first in logic.
  {
  sprite.drawWedgeLine(ox[i],oy[i],lx[i],ly[i],2,2,TFT_WHITE,TFT_BLACK);
  }
  else if(i%5==0)
  {
  sprite.drawWedgeLine(ox[i],oy[i],ix[i],iy[i],2,2,TFT_WHITE,TFT_BLACK);
  }
  lcd_PushColors(0, 0, 240, 536, (uint16_t*)sprite.getPointer());

 }

void loop(){
  draw();
}