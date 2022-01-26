void readPB()
{
  if ( digitalRead(PB) == 1 && bPB && totalparkir < 20)
  {
    digitalWrite(buzz, 1);
    totalparkir++;
    openGate(Front, serFront);
    statFrontGate = true;
    Serial.println("PB ON ");
    String dataSend = "|addCar|";
    dataSend += String(now());
    dataSend += "|\r";
    Serial.println(dataSend);
    Serial1.print(dataSend);
    printText();
    bPB = false;
    bupdateLCD = true;
    delay(500);
    digitalWrite(buzz, 0);
  }
  else if ( digitalRead(PB) == 0 && !bPB)
  {
    bPB = true;
  }
}
