#include <Arduino.h>
#include "font6x8/font6x8.h"
#include <string.h>

void setup() {
    Serial.begin(9600);
}

void drawCharacterLine(unsigned char lineValue /*, row, colOffset */) {
    char line[14] = "";
    unsigned char a = lineValue;
    for (int col = 0; col < 6; col++) {
        if ((a & 64) > 0) {
            strcat(line, "* "); // set(row,col+colOffset)
        } else {
            strcat(line, "  ");
        }
        a = a << 1;
    }
    Serial.println(line);
}

void drawCharacter(int ascii /*, colOffset */) {
    //char buffer[7];
    for (int row = 0; row < 8; row++) {
        drawCharacterLine(font[(ascii - 32) * 8 + row]);
    }
}

void loop() {
    Serial.println("");
    drawCharacter((int)'G');
    drawCharacter((int)'e');
    delay(20000);
}
