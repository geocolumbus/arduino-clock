#include <Arduino.h>
#include "font6x8/font6x8.h"

void setup() {
    Serial.begin(9600);
}

void loop() {

    Serial.print((int)font[0]);
    Serial.print(" ");
    Serial.print((int)font[1]);
    Serial.print(" ");
    delay(1000);
}
