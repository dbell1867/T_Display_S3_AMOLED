#include "rm67162.h"
#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite background = TFT_eSprite(&tft);
TFT_eSprite dial = TFT_eSprite(&tft);

#define up 21
#define down 0

int angle=0;
int prev=0;

void setup() {
    rm67162_init();
    pinMode(up, INPUT_PULLUP);
    pinMode(down, INPUT_PULLUP);
    background.createSprite(240,536);
    dial.createSprite(120,120);
    //background.setSwapBytes(1);  //need to understand this. Swaps the byte order for pushImage() and pushPixels() - corrects endianness  
    tft.setPivot(120,120); //pivot point of rotated sprites, what if you have multiple rotated sprites?

    draw();//First paint to screen or else draw needs to be triggered by button push.

}

void readButtons() {
    if (digitalRead(up) == 0) {
        angle=angle+2;//button press increases angle by 2
        if(angle>=360)
        angle=0;
    }

    if (digitalRead(down) == 0) {
        angle--;//button press reduces angle by 1
        if(angle<0)
        angle=359;
    }
}

void draw() {
    background.fillSprite(TFT_WHITE);
    background.setTextColor(TFT_BLACK,TFT_WHITE);
    background.setTextDatum(1);//centre top
    background.drawString(String(angle),120,40,4);//need to learn about fonts.  Size and fontstyle.
    dial.fillSprite(TFT_RED);
    dial.pushRotated(&background,angle);
    background.pushSprite(0,0);
    lcd_PushColors(0, 0, 240,536, (uint16_t*)background.getPointer());

}

void loop() {
    readButtons();
    if(angle!=prev){
        draw();
        prev=angle;
    }

}