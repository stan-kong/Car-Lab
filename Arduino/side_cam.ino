#include <Pixy2.h>

Pixy2 pixySide;
     
void setup() {
  Serial.begin(115200);  // communication with Serial Monitor and PSoC
  pixySide.init();
}

void loop() {
  sideToPSoC();           // send signal to the PSoC
  delay(100);           // small delay to avoid spamming
}

void sideToPSoC() {
    uint16_t blocks = pixySide.ccc.getBlocks();

    if (blocks) {
        Serial.println("1"); // value when blocks are detected
    } else {
        Serial.println("0");  // value when no blocks are detected
    }
}