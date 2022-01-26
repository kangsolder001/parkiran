void openGate(Servo Ser, int serPin)
{
  Ser.attach(serPin);
  Ser.write(0);
  delay(500);
  Ser.detach();
}
void closeGate(Servo Ser, int serPin)
{
  Ser.attach(serPin);
  Ser.write(90);
  delay(500);
  Ser.detach();
}

void CloseGate()
{
  if (statFrontGate && digitalRead(irFront) == 1)
  {
    delay (1000);
    closeGate(Front, serFront);
    statFrontGate = false;

    Serial.println("close Front Gate");
  }
  if (statBackGate && digitalRead(irBack) == 1)
  {
    delay (1000);
    closeGate(Back, serBack);
    statBackGate = false;
    Serial.println("close back Gate");

  }
}
