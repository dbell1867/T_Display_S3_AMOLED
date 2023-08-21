#include "rm67162.h"
#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite sprite = TFT_eSprite(&tft);

void setup(){
  sprite.createSprite(240,536);
  //sprite.setSwapBytes(1);//need to understand this. Swaps the byte order for pushImage() and pushPixels() - corrects endianness? 
  rm67162_init();  // amoled lcd initialization
  sprite.fillSprite(TFT_WHITE); //need to have something to see
  lcd_PushColors(0, 0, 240,536, (uint16_t*)sprite.getPointer());
}

void loop(){
  
}
