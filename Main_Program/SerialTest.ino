void SerialTest()
{
  if ( Serial.available())
  {
    String in = Serial.readStringUntil('\r');
    if ( in == "pin")
    {
      for (int i = 0; i <= sizeof(pin) / sizeof(pin[0]); i++)
      {
        pinMode(pin[i], 1);
        delay(500);
        pinMode(pin[i], 0);
        delay(500);
      }
    }
    if ( in == "print")
    {
      Serial.println("Print Thermal");
      printText();
    }
    if ( in == "esp")
    {
      Serial.println("test ESP");
      Serial1.print("test\r");
    }

    else
    {
      int i = in.toInt();
      ir_now[i] = digitalRead(ir[i]);
      if ( ir_now[i] == 1)
      {
        ledG(pin[i]);
      }
      else
      {
        ledR(pin[i]);
      }
      if (ir_now[i] != ir_before[i])
      {
        ir_before[i] = ir_now[i];
        Serial.print("room = ");
        Serial.println(room[i]);
        Serial.print("status = ");
        Serial.println(ir_now[i]);
        String idLantai = room[i].substring(0, 2);
        String idParkir = room[i].substring(3, room[i].length());
        String dataSend = "|updateParkir|";
        dataSend += idLantai;
        dataSend += "|";
        dataSend += idParkir;
        dataSend += "|";
        dataSend += String(ir_now[i]);
        dataSend += "|\r";
        Serial1.print(dataSend);
      }
    }
  }
}
