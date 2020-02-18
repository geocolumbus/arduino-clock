#include <Arduino.h>
#include "font6x8/font6x8.h"
#include "LedControl/LedControl.h"
#include <string.h>

uint8_t DATA_PIN = 12;
uint8_t CLOCK_PIN = 11;
uint8_t LOAD_PIN = 10;
int NUM_DEVICES = 8;
int INTENSITY = 1;

LedControl ledControl = LedControl(DATA_PIN, CLOCK_PIN, LOAD_PIN, NUM_DEVICES);

void setup() {
    Serial.begin(9600);

    pinMode(DATA_PIN, OUTPUT);
    pinMode(CLOCK_PIN, OUTPUT);
    pinMode(LOAD_PIN, OUTPUT);

    for (int index = 0; index < ledControl.getDeviceCount(); index++) {
        ledControl.shutdown(index, false); // at power up is true
        ledControl.setIntensity(index, INTENSITY); // 0 - 16, at power up is 0
    }
}

unsigned long memoryBufferL[8] = {0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L};
unsigned long memoryBufferR[8] = {0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L};
unsigned long screenBufferL[8] = {0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L};
unsigned long screenBufferR[8] = {0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L};

void drawCharacterLine(unsigned char rowBitPattern, int row, int colOffset) {
    unsigned char bitPattern = rowBitPattern;
    for (int col = 0; col < 6; col++) {
        if ((bitPattern & 64L) > 0) {
            if (col + colOffset < 32) {
                memoryBufferL[row] = (1UL << (col + colOffset)) | memoryBufferL[row];
            } else if (col + colOffset < 64) {
                memoryBufferR[row] = (1UL << (col + colOffset - 32)) | memoryBufferR[row];
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

void clearMemoryBuffer() {
    for (int row = 0; row < 8; row++) {
        memoryBufferL[row] = 0UL;
        memoryBufferR[row] = 0UL;
    }
}

void printMemoryBuffer() {
    char line[130];
    for (int row = 0; row < 8; row++) {
        strcpy(line, "");

        for (int col = 0; col < 64; col++) {
            if (col < 32) {
                if ((memoryBufferL[row] >> col) & 1UL) {
                    strcat(line, "* ");
                } else {
                    strcat(line, "  ");
                }
            } else if (col < 64) {
                if ((memoryBufferR[row] >> (col - 32)) & 1UL) {
                    strcat(line, "* ");
                } else {
                    strcat(line, "  ");
                }
            }
        }
        Serial.println(line);
    }
}

void drawWord(char *word) {
    clearMemoryBuffer();
    Serial.println("");
    int leftShift = 0;
    for (int i = 0; i < strlen(word); i++) {
        //int offset = length < 10 ? 4 + i * 7 : i * 7;
        int offset = i * 7;

        // kerning before writing the letter
        if ((word[i] >= 'a' && word[i] <= 'z') || word[i] == '-' || word[i] == '~' || word[i] == 'I') {
            leftShift += 1;
        }

        if (word[i] >='0' && word[i]<='9') {
            leftShift += 1;
        }

        if (word[i] == '/') {
            leftShift +=1;
        }

        if (word[i] == 'i') {
            leftShift += 1;
        }

        if (word[i] == ' ') {
            leftShift += 3;
        }

        if (word[i] == ':') {
            leftShift += 2;
        }

        // write the letter
        drawCharacter((int) word[i], offset - leftShift);

        // kerning that affects the next letter
        if (word[i] == ':') {
            leftShift += 2;
        }
        if (word[i] == 'i') {
            leftShift += 1;
        }
        if (word[i] == ' ') {
            leftShift += 3;
        }

        if (word[i] == '/') {
            leftShift +=1;
        }
    }
}

// Pixel based updater
void updateLEDDisplay() {
    // Undraw the screenBuffer
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 64; col++) {
            if (col < 32) {
                if ((screenBufferL[row] >> col) & 1UL) {
                    int displayOffset = col >> 3;
                    int displaySelect = 3 - displayOffset;
                    ledControl.setLed(displaySelect, row, col - displayOffset * 8, false);
                }
            } else if (col < 64) {
                if ((screenBufferR[row] >> (col - 32)) & 1UL) {
                    int displayOffset = col >> 3;
                    int displaySelect = 3 - displayOffset;
                    ledControl.setLed(displaySelect, row, col - displayOffset * 8, false);
                }
            }
        }
    }

    // Copy the memoryBuffer to the screenBuffer
    for (int row = 0; row < 8; row++) {
        screenBufferL[row] = memoryBufferL[row];
        screenBufferR[row] = memoryBufferR[row];
    }

    // Draw the screenBuffer
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 64; col++) {
            int displaySelect = col >> 3;
            if (col < 32) {
                if ((screenBufferL[row] >> col) & 1UL) {
                    ledControl.setLed(7 - displaySelect, row, col - displaySelect * 8, true);
                }
            } else if (col < 64) {
                if ((screenBufferR[row] >> (col - 32)) & 1UL) {
                    ledControl.setLed(7 - displaySelect, row, col - displaySelect * 8, true);
                }
            }
        }
    }
}

void loop() {

    drawWord("12-31 12:49 pm");
    updateLEDDisplay();
    printMemoryBuffer();
    delay(50000);
}