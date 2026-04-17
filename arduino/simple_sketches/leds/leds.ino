void setup()
{
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(14, OUTPUT);
}

void loop()
{
  digitalWrite(0, LOW);
  digitalWrite(1, LOW);
  digitalWrite(14, LOW);
  delay(1000);
  digitalWrite(0, HIGH);
  digitalWrite(1, HIGH);
  digitalWrite(14, HIGH);
  delay(500);
}
