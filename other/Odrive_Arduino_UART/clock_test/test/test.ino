unsigned long real_time;
static int time;

void setup() {
  Serial.begin(115200);

}

void loop() {
  real_time = millis()/1000;
  time = real_time % 10;
//  if (time > 10) {
//    time = 0;
//  }
  Serial.println(time+1);
  delay(1000);
}
