void getTimeESP()
{
  
  if ( millis() - prevGetTime >= 1800000 || year() < 2022 && bgetTime)
  {
    Serial1.print("|getTime|\r");
    Serial.println("GetTime to ESP32");
    prevGetTime = millis();
    bgetTime = false;
  }
  if ( millis() - prevbgetTime >= 5000 && !bgetTime)
  {
    bgetTime = true;
    prevbgetTime = millis();
  }
}
String getTime()
{
  String getTime = digits(hour());
  getTime +=  ":";
  getTime += digits(minute());
  getTime += ":";
  getTime += digits(second());
  return getTime;
}
String getDate()
{
  String getDate = digits(month());
  getDate += "/";
  getDate += digits(day());
  getDate += "/";
  getDate += String(year());
  return getDate;
}
//2021-08-31 99:99:99

String getFulldate()
{
  String getDate = String(year());
  getDate += "-";
  getDate += digits(month());
  getDate += "-";
  getDate += digits(day());

  String getTime = getDate + " ";
  getTime += digits(hour());
  getTime +=  ":";
  getTime += digits(minute());
  getTime += ":";
  getTime += digits(second());
  return getTime;

}
String digits(int input)
{
  String digit;
  if ( input < 10)
  {
    digit = "0";
    digit += String(input);
  }
  else
  {
    digit = String(input);
  }
  return digit;
}
