void setup() {
  Serial.begin(115200);
}

void loop() {
  Serial.print("X: "); Serial.print(1); Serial.print("  ");
  Serial.print("Y: "); Serial.print(2); Serial.print("  ");
  Serial.print("Z: "); Serial.print(3); Serial.print("  ");
  Serial.println("uT");
}
