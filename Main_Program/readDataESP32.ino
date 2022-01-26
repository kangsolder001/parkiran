void readDataESP()
{
  if ( Serial1.available())
  {
    String in = Serial1.readStringUntil('\r');
    int ind1, ind2, ind3, ind4, ind5;
    String data1, data2, data3, data4;
    Serial.println(in);
    ind1 = in.indexOf("|");
    ind2 = in.indexOf("|", ind1 + 1);
    ind3 = in.indexOf("|", ind2 + 1);
    ind4 = in.indexOf("|", ind3 + 1);
    ind5 = in.indexOf("|", ind4 + 1);
    data1 = in.substring(ind1 + 1, ind2);
    data2 = in.substring(ind2 + 1, ind3);
    data3 = in.substring(ind3 + 1, ind4);
    data4 = in.substring(ind4 + 1, ind5);
    if ( data1 == "timenow")
    {
      Serial.println(data2);
      uint32_t timeT = atol(data2.c_str());
      setTime(timeT);
    }
    else if ( data1 == "openGate" && !statBackGate)
    {
      statBackGate = true;
      Serial.println("gateDibuka dari Server");
      openGate(Back, serBack);
      statBackGate = true;
      if (totalparkir > 0)
      {
        totalparkir--;
      }
      bupdateLCD = true;
    }
  }
}
