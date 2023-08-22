#include "rm67162.h"
#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite background = TFT_eSprite(&tft);
TFT_eSprite dial = TFT_eSprite(&tft);

#define up 21
#define down 0

int col=0;
int prev=0;
char colourarray[] = {
    TFT_BLACK,
    TFT_NAVY,
    TFT_DARKGREEN,
    TFT_DARKCYAN,
    TFT_MAROON,//4
    TFT_PURPLE,
    TFT_OLIVE,
    TFT_LIGHTGREY
    };

void setup(){
    rm67162_init();
    pinMode(up, INPUT_PULLUP);
    pinMode(down, INPUT_PULLUP);
    background.createSprite(240,536);
    dial.createSprite(120,120);
    background.setSwapBytes(1);  //need to understand this. Swaps the byte order for pushImage() and pushPixels() - corrects endianness  

    draw();
}

void readButtons(){
    if (digitalRead(up) == 0) {
        col=col+1;//button press
        if(col>=7)
        col=7;
        delay(100);
    }

    if (digitalRead(down) == 0) {
        col=col-1;//button press 
        if(col<=0)
        col=0;
        delay(100);
    }
}

void draw(){
    background.fillSprite(TFT_WHITE);
    background.setTextColor(TFT_BLACK,TFT_WHITE);
    background.setTextDatum(1);//centre top
    background.drawString(String(colourarray[col]),120,40,4);//need to learn about fonts.  Size and fontstyle.
    dial.fillSprite(colourarray[col]);
    dial.pushToSprite(&background,60,208,TFT_WHITE);
    lcd_PushColors(60, 208, 120,120, (uint16_t*)dial.getPointer());
    background.pushSprite(0,0);
    lcd_PushColors(0, 0, 240,536, (uint16_t*)background.getPointer());

}

void loop(){
    readButtons();
    if(col!=prev){
        draw();
        prev=col;
    }

}