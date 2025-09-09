#include <Pixy2.h>

Pixy2 pixyFront;

//map one range of floats to another range of floats
float mapfloat(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
     
void setup() {
  Serial.begin(115200);  // communication with Serial Monitor and PSoC
  pixyFront.init();
}

void loop() {
  CxToPSoC();           // send cx value to the PSoC
  delay(100);           // small delay to avoid spamming
}

void CxToPSoC() {
  uint16_t blocks = pixyFront.ccc.getBlocks();

  if (blocks) {
    int x = pixyFront.ccc.blocks[0].m_x; // get center x-coordinate of car
    float cx = mapfloat(x, 0, 320, -1, 1);  // normalize x to -1 to 1
    int distance = pixyFront.ccc.blocks[0].m_height;  // use block height as proximity measure of car

    if (distance > 0) {
      
    }
    // send cx to PSoC
    Serial.print("cx:");
    Serial.print(cx);
    Serial.print(",dist:");
    Serial.println(distance);
  } else {
    Serial.println("cx:0,dist:0");
  }
}