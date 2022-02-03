void readIR()
{
  for (int i = 0; i <= 19; i++) //untuk lantai 2 yang pakai modul IR
  {
    ir_now[i] = digitalRead(ir[i]);
    ir_now[i] = !ir_now[i];
    if ( ir_now[i] == 0)
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
      if ( ir_now[i] == 1 && indexTimeId > 0)
      {
        indexParkId++;
        ParkId[indexParkId] = idParkir.toInt();
        Serial.print("Time Id = ");
        Serial.println(TimeId[indexParkId]);
        Serial.print("Park ID = ");
        Serial.println(ParkId[indexParkId]);
        String datSend;
        datSend += "|addCar|";
        datSend += String(TimeId[indexParkId]);
        datSend += "|";
        datSend += String(ParkId[indexParkId]);
        datSend += "|\r";
        Serial.println(datSend);
        Serial1.print(datSend);
        if ( indexParkId == indexTimeId )
        {
          Serial.println("DONE");
          for ( int i = 0 ; i <= 19; i++)
          {
            TimeId[i] = 0;
            ParkId[i] = 0;
          }
          indexParkId = 0;
          indexTimeId = 0;
        }
      }


      Serial1.print(dataSend);
      Serial.println(dataSend);
    }
  }
}
