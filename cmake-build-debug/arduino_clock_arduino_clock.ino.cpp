// automatically generated by arduino-cmake
#line 1 "/Users/georgecampbell/arduino/arduino-clock/arduino_clock.ino"
#include <Arduino.h>
#include "font6x8/font6x8.h"
#include <string.h>

#line 7 "/Users/georgecampbell/arduino/arduino-clock/cmake-build-debug/arduino_clock_arduino_clock.ino.cpp"
#include "Arduino.h"

//=== START Forward: /Users/georgecampbell/arduino/arduino-clock/arduino_clock.ino
 void setup() ;
 void setup() ;
 void drawCharacterLine(unsigned char lineValue, int row, int colOffset) ;
 void drawCharacterLine(unsigned char lineValue, int row, int colOffset) ;
 void drawCharacter(int ascii, int colOffset) ;
 void drawCharacter(int ascii, int colOffset) ;
 void drawWord(char *word) ;
 void drawWord(char *word) ;
 void loop() ;
 void loop() ;
//=== END Forward: /Users/georgecampbell/arduino/arduino-clock/arduino_clock.ino
#line 3 "/Users/georgecampbell/arduino/arduino-clock/arduino_clock.ino"


void setup() {
    Serial.begin(9600);
}

void drawCharacterLine(unsigned char lineValue, int row, int colOffset) {
    char line[14] = "";
    char buffer[32];
    unsigned char a = lineValue;
    for (int col = 0; col < 6; col++) {
        if ((a & 64) > 0) {
            strcat(line, "* "); // set(row,col+colOffset)
            sprintf(buffer, "(%d, %2d)", row, col + colOffset);
            Serial.println(buffer);
        } else {
            strcat(line, "  ");
        }
        a = a << 1;
    }
}

void drawCharacter(int ascii, int colOffset) {
    for (int row = 0; row < 8; row++) {
        drawCharacterLine(font[(ascii - 32) * 8 + row], row, colOffset);
    }
}

void drawWord(char *word) {
    for (int i = 0; i < 5; i++) {
        drawCharacter((int) word[i], i * 7);
    }
}

void loop() {
    drawWord("12:34");
    delay(60000);
}
