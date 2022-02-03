void readPB()
{
  if ( digitalRead(PB) == 1 && bPB && totalparkir < 20)
  {
    indexTimeId++;
    digitalWrite(buzz, 1);
    totalparkir++;
    openGate(Front, serFront);
    statFrontGate = true;
    Serial.println("PB ON ");
    //    printText();
    TimeId [indexTimeId] = now();

    Serial.print("time Id ");
    Serial.print(indexTimeId);
    Serial.print(" = ");
    Serial.println(TimeId[indexTimeId]);

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
