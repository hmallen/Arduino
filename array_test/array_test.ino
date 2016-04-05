void setup() {
  Serial.begin(9600);
  Serial.println();
  
  int x[15] = {5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75};

  for (int i = 0; i < 15; i++) {
    Serial.println(x[i]);
  }
}

void loop() {

}
