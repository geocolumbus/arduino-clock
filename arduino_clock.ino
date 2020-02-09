#include <Arduino.h>
#include "font6x8/font6x8.h"
#include "LedControl/LedControl.h"
#include <string.h>

uint8_t DATA_PIN = 12;
uint8_t CLOCK_PIN = 11;
uint8_t LOAD_PIN = 10;
int NUM_DEVICES = 4;
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

unsigned long memoryBuffer[8] = {0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L};
unsigned long screenBuffer[8] = {0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L};

void drawCharacterLine(unsigned char rowBitPattern, int row, int colOffset) {
    unsigned char bitPattern = rowBitPattern;
    for (int col = 0; col < 6; col++) {
        if ((bitPattern & 64L) > 0) {
            if (col + colOffset < 32) {
                memoryBuffer[row] = (1UL << (col + colOffset)) | memoryBuffer[row];
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
        memoryBuffer[row] = 0UL;
    }
}

void printMemoryBuffer() {
    char line[66];
    for (int row = 0; row < 8; row++) {
        strcpy(line, "");

        for (int col = 0; col < 32; col++) {
            if ((memoryBuffer[row] >> col) & 1UL) {
                strcat(line, "* ");
            } else {
                strcat(line, "  ");
            }
        }
        Serial.println(line);
    }
}

void drawWord(char *word, int length) {
    clearMemoryBuffer();
    Serial.println("");
    int leftShift = 0;
    for (int i = 0; i < length; i++) {
        int offset = length < 5 ? 4 + i * 7 : i * 7;

        // kerning before writing the letter
        if (word[i] == 'i' || word[i] == '-' || word[i] == 'n' || word[i] == '~') {
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
}

// Pixel based updater
void updateLEDDisplay() {
    // Undraw the screenBuffer
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 32; col++) {
            if ((screenBuffer[row] >> col) & 1UL) {
                int displayOffset = col >> 3;
                int displaySelect = 3 - displayOffset;
                ledControl.setLed(displaySelect, row, col - displayOffset * 8, false);
            }
        }
    }

    // Copy the memoryBuffer to the screenBuffer
    for (int row = 0; row < 8; row++) {
        screenBuffer[row] = memoryBuffer[row];
    }

    // Draw the screenBuffer
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 32; col++) {
            if ((screenBuffer[row] >> col) & 1UL) {
                int displayOffset = col >> 3;
                int displaySelect = 3 - displayOffset;
                ledControl.setLed(displaySelect, row, col - displayOffset * 8, true);
            }
        }
    }
}

void loop() {
    drawWord("Clear", 5);
    updateLEDDisplay();
    //printMemoryBuffer();
    delay(5000);

    drawWord("7:51", 4);
    updateLEDDisplay();
    //printMemoryBuffer();
    delay(5000);

    drawWord("28~F", 4);
    updateLEDDisplay();
    //printMemoryBuffer();
    delay(5000);

}