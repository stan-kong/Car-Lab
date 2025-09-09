#include <Pixy2.h>

Pixy2 pixyRear;

void setup() {
  Serial.begin(115200);  // communication with Serial Monitor and PSoC
  pixyRear.init();
}

void loop() {
  DistanceToPSoC();     // check if the RC car is behind and send distance to PSoC
  delay(100);           // small delay to avoid spamming
}

void DistanceToPSoC() {
  uint16_t blocks = pixyRear.ccc.getBlocks();
  if (blocks) {
    // RC car detected
    int distance = pixyRear.ccc.blocks[0].m_height;  // use block height as proximity measure of car
    Serial.print("rc_detected:1,dist:");
    Serial.println(distance);
  } else {
    // no RC car detected
    Serial.println("rc_detected:0");
  }
} 