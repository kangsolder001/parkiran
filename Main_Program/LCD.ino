void LCD()
{
  static unsigned long prevPark;
  static unsigned long prevTgl;
  if (bupdateLCD)
  {
    if ( millis() - prevPark >= 1000)
    {
      lcd.clear();
      if (totalparkir >= 20)
      {
        lcd.setCursor(0, 3); lcd.print("   Mohon Maaf   ");
        lcd.setCursor(0, 4); lcd.print("  Parkir Penuh  ");
      }
      else
      {
        int totaltersedia = 20 - totalparkir;
        String datatampil;
        lcd.setCursor(0, 3); lcd.print("Parkir Tersedia");
        if ( totaltersedia < 10)
        {
          datatampil = "0";
          datatampil += String(totaltersedia);
        }
        else
        {
          datatampil = String(totaltersedia);
        }
        lcd.setCursor(7, 4); lcd.print(datatampil);
      }
      prevPark = millis();
    }
    bupdateLCD = false;
  }
  if (second() != secBefore)
  {
    secBefore = second();
    prevTgl = millis();
    String tahun = getFulldate().substring(0, 11);
    String jam = getFulldate().substring(11, 16);

    lcd.setCursor(tahun.length() / 2, 0);
    lcd.print(tahun);
    lcd.setCursor(jam.length() / 2, 1);
    lcd.print(jam);
  }
}
