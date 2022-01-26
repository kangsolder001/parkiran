void LCD()
{
  if ( bupdateLCD)
  {
    lcd.clear();
    if (totalparkir >= 20)
    {
      lcd.setCursor(0, 0); lcd.print("   Mohon Maaf   ");
      lcd.setCursor(0, 1); lcd.print("  Parkir Penuh  ");
    }
    else
    {
      int totaltersedia = 20 - totalparkir;
      String datatampil;
      lcd.setCursor(0, 0); lcd.print("Parkir Tersedia");
      if ( totaltersedia < 10)
      {
        datatampil = "0";
        datatampil += String(totaltersedia);
      }
      else
      {
        datatampil = String(totaltersedia);
      }
      lcd.setCursor(7, 1); lcd.print(datatampil);
    }
    bupdateLCD = false;
  }
}
