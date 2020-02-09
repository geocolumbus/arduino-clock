#include <Arduino.h>
#include "font6x8/font6x8.h"
#include <string.h>

void setup() {
    Serial.begin(9600);
}

unsigned int screenBufferLeft[8] = {0, 0, 0, 0, 0, 0, 0, 0};
unsigned int screenBufferRight[8] = {0, 0, 0, 0, 0, 0, 0, 0};

void drawCharacterLine(unsigned char rowBitPattern, int row, int colOffset) {
    unsigned char bitPattern = rowBitPattern;
    for (int col = 0; col < 6; col++) {
        if ((bitPattern & 64) > 0) {
            if (col + colOffset < 16) {
                screenBufferLeft[row] = (1 << (col + colOffset)) | screenBufferLeft[row];
            } else if (col + colOffset < 32) {
                screenBufferRight[row] = (1 << (col + colOffset - 16)) | screenBufferRight[row];
            }
        }
        bitPattern = bitPattern << 1;
    }
}

void drawCharacter(int ascii, int colOffset) {
    for (int row = 0; row < 8; row++) {
        drawCharacterLine(font[(ascii - 32) * 8 + row], row, colOffset);
    }
}

void clearScreenBuffer() {
    for (int row = 0; row < 8; row++) {
        screenBufferLeft[row] = 0;
        screenBufferRight[row] = 0;
    }
}

void printScreenBuffer() {
    char line[66];
    for (int row = 0; row < 8; row++) {
        strcpy(line, "");

        for (int col = 0; col < 16; col++) {
            if ((screenBufferLeft[row] >> col) & 1) {
                strcat(line, "* ");
            } else {
                strcat(line, "  ");
            }
        }

        for (int col = 16; col < 32; col++) {
            if ((screenBufferRight[row] >> (col - 16)) & 1) {
                strcat(line, "* ");
            } else {
                strcat(line, "  ");
            }
        }

        Serial.println(line);
    }
}

void drawWord(char *word) {
    clearScreenBuffer();
    Serial.println("");
    for (int i = 0; i < 5; i++) {
        drawCharacter((int) word[i], i * 7);
    }
    printScreenBuffer();
}

void loop() {
    drawWord("12:34");
    delay(2000);
    drawWord("34~F ");
    delay(2000);
    drawWord("Rain ");
    delay(2000);
}