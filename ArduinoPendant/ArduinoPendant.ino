#include "U8glib.h"
#include <string.h>

U8GLIB_ST7920_128X64_1X u8g(8, 9, 10);	// SPI Com: SCK = en = 18, MOSI = rw = 16, CS = di = 17

#define encoder0PinA  2
#define encoder0PinB  4


int boxWidth = 60;

int xPos = 0;
int yPos = 0;
int zPos = 0;
int writtenX = 0;
int writtenY = 0;
int writtenZ = 0;

void draw(void) {
  char charPos[8];
  sprintf( charPos , "%06i" , xPos );
  writtenX = xPos;
  writtenY = zPos;
  writtenZ = zPos;
  // graphic commands to redraw the complete screen should be placed here  
  u8g.setFont(u8g_font_unifont);
  //u8g.setFont(u8g_font_osb21);;
  u8g.setFont(u8g_font_6x10r);
  u8g.drawStr( 2, 9, "X");
    u8g.drawStr( 11, 9, charPos );
  u8g.drawLine(0, 10, boxWidth, 10 );
  u8g.drawStr( 2, 19, "Y");
    u8g.drawLine(0, 20, boxWidth, 20 );
  u8g.drawLine(8, 0, 8, 30);
  u8g.drawStr( 2, 29, "Z");
    u8g.drawLine(0, 30, boxWidth, 30 );  
        u8g.drawLine(0, 0, boxWidth, 0 );  
    u8g.drawLine(boxWidth, 0, boxWidth, 30 );  

    u8g.drawLine(0, 0, 0, 30 );  
}

void updateScreen(){
  u8g.firstPage();  
  do {
    draw();
  } while( u8g.nextPage() );
}

void setup(void) {
  pinMode(encoder0PinA, INPUT); 
    u8g.setColorIndex(1);       
  pinMode( 13 , OUTPUT );
  attachInterrupt(0, doEncoderA, CHANGE);
  attachInterrupt(1, doEncoderB, CHANGE);
  updateScreen();
}

void loop(void) {
  
  if( xPos !== writtenX ){
    updateScreen();  
  }
  // rebuild the picture after some delay
}


void doEncoderA(){

  // look for a low-to-high on channel A
  if (digitalRead(encoder0PinA) == HIGH) { 
    // check channel B to see which way encoder is turning
    if (digitalRead(encoder0PinB) == LOW) {  
      xPos = xPos + 1;         // CW
    } 
    else {
      xPos = xPos - 1;         // CCW
    }
  }
  else   // must be a high-to-low edge on channel A                                       
  { 
    // check channel B to see which way encoder is turning  
    if (digitalRead(encoder0PinB) == HIGH) {   
      xPos = xPos + 1;          // CW
    } 
    else {
      xPos = xPos - 1;          // CCW
    }
  }
  
  // use for debugging - remember to comment out
}

void doEncoderB(){

  // look for a low-to-high on channel B
  if (digitalRead(encoder0PinB) == HIGH) {   
   // check channel A to see which way encoder is turning
    if (digitalRead(encoder0PinA) == HIGH) {  
      xPos = xPos + 1;         // CW
    } 
    else {
      xPos = xPos - 1;         // CCW
    }
  }
  // Look for a high-to-low on channel B
  else { 
    // check channel B to see which way encoder is turning  
    if (digitalRead(encoder0PinA) == LOW) {   
      xPos = xPos + 1;          // CW
    } 
    else {
      xPos = xPos - 1;          // CCW
    }
  }
}

