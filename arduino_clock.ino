#include <Arduino.h>
#include "font6x8/font6x8.h"
#include <string.h>

void setup() {
    Serial.begin(9600);
}

unsigned long screenBuffer[8] = {0, 0, 0, 0, 0, 0, 0, 0};

void drawCharacterLine(unsigned char rowBitPattern, int row, int colOffset) {
    unsigned char bitPattern = rowBitPattern;
    for (int col = 0; col < 6; col++) {
        if ((bitPattern & 64L) > 0) {
            if (col + colOffset < 32) {
                screenBuffer[row] = (1UL << (col + colOffset)) | screenBuffer[row];
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
        screenBuffer[row] = 0UL;
    }
}

void printScreenBuffer() {
    char line[66];
    for (int row = 0; row < 8; row++) {
        strcpy(line, "");

        for (int col = 0; col < 32; col++) {
            if ((screenBuffer[row] >> col) & 1UL) {
                strcat(line, "* ");
            } else {
                strcat(line, "  ");
            }
        }
        Serial.println(line);
    }
}

void drawWord(char *word, int length) {
    clearScreenBuffer();
    Serial.println("");
    int leftShift = 0;
    for (int i = 0; i < length; i++) {
        int offset = length < 5 ? 4 + i * 7 : i * 7;

        // kerning before writing the letter
        if (word[i] == 'i' || word[i] == '-' || word[i]=='n' || word[i]=='~') {
            leftShift = 1;
        }

        // write the letter
        drawCharacter((int) word[i], offset - leftShift);

        // kerning that affects the next letter
        if (word[i] == ':') {
            leftShift = 1;
        }
        if (word[i] == 'i') {
            leftShift = 2;
        }
    }
    printScreenBuffer();
}

void loop() {
    drawWord("7:51", 4);
    drawWord("28~F", 4);
    delay(60000);
}