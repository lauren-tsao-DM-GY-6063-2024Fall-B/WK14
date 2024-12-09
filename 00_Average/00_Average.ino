int lastSend;

void setup() {
  Serial.begin(9600);
  lastSend = 0;
}

void loop() {
  int a0Val = analogRead(A0);

  if (millis() - lastSend > 50) {
    Serial.println(a0Val);
    lastSend = millis();
  }

  delay(2);
}
