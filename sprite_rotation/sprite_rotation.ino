#include "rm67162.h"
#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite background = TFT_eSprite(&tft);
TFT_eSprite dial = TFT_eSprite(&tft);


void setup(){
    rm67162_init();
    background.createSprite(240,536);
    dial.createSprite(120,120);
    //background.setSwapBytes(1);  //need to understand this. Swaps the byte order for pushImage() and pushPixels() - corrects endianness  
    tft.setPivot(120,120); //pivot point of rotated sprites, what if you have multiple rotated sprites?

}

int angle=0;//why does this sit outside the 'setup'?

void loop(){
    background.fillSprite(TFT_WHITE);
    background.setTextColor(TFT_BLACK,TFT_WHITE);
    background.setTextDatum(1);//centre top
    background.drawString("TEST",120,40,4);//need to learn about fonts.  Size and fontstyle.
    dial.fillSprite(TFT_RED);
    dial.pushRotated(&background,angle);
    background.pushSprite(0,0);
    angle++;
    if(angle==360)
    angle=0;
    lcd_PushColors(0, 0, 240,536, (uint16_t*)background.getPointer());
}