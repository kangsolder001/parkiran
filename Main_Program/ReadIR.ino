void readIR()
{
  for (int i = 0; i <= 11; i++) //untuk lantai 2 yang pakai modul IR
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

      Serial1.print(dataSend);
      //      Serial.println(dataSend);
    }
  }
  for (int i = 12; i <= 19; i++) // untuk lantai 1 yang pakai ADC IR
  {
    int input_ir = analogRead(ir[i]);
    if ( input_ir >= 155)
    {
      ir_now[i] = 1;
    }
    else
    {
      ir_now[i] = 0;
    }
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
      String idParkir = room[i].substring(3,  room[i].length());
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
