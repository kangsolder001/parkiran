const int PACKET_SIZE = 48; // NTP time is in the first 48 bytes of message
byte packetBuffer[PACKET_SIZE]; //buffer to hold incoming & outgoing packets

time_t getNtpTime()
{
  IPAddress ntpServerIP;
  while (Udp.parsePacket() > 0) ; // discard any previously received packets
  Serial.println("Transmit NTP Request");
  // get a random server from the pool
  WiFi.hostByName(ntpServerName, ntpServerIP);
  Serial.print(ntpServerName);
  Serial.print(": ");
  Serial.println(ntpServerIP);
  sendNTPpacket(ntpServerIP);
  uint32_t beginWait = millis();
  while (millis() - beginWait < 1500) {
    int size = Udp.parsePacket();
    if (size >= PACKET_SIZE) {
      Serial.println("Receive NTP Response");
      Udp.read(packetBuffer, PACKET_SIZE);  // read packet into the buffer
      unsigned long secsSince1900;
      // convert four bytes starting at location 40 to a long integer
      secsSince1900 =  (unsigned long)packetBuffer[40] << 24;
      secsSince1900 |= (unsigned long)packetBuffer[41] << 16;
      secsSince1900 |= (unsigned long)packetBuffer[42] << 8;
      secsSince1900 |= (unsigned long)packetBuffer[43];
      unsigned long resulttime = secsSince1900 - 2208988800UL + (timeZone * SECS_PER_HOUR);
      Serial.print("result time = ");
      Serial.println(resulttime);
      for ( int i = 0 ; i <= PACKET_SIZE;i++)
      {
        Serial.write(packetBuffer[i]);
      }
      return resulttime;
    }
  }
  Serial.println("No NTP Response :-(");
  return 0; // return 0 if unable to get the time
}

// send an NTP request to the time server at the given address
void sendNTPpacket(IPAddress &address)
{
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, PACKET_SIZE);
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12] = 49;
  packetBuffer[13] = 0x4E;
  packetBuffer[14] = 49;
  packetBuffer[15] = 52;
  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:
  Udp.beginPacket(address, 123); //NTP requests are to port 123
  Udp.write(packetBuffer, PACKET_SIZE);
  Udp.endPacket();
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
void ntpBegin()
{
  Udp.begin(localPort);
  Serial.println("waiting for sync");
  setTime(getNtpTime());
  Serial.println(getDate());
  Serial.println(getTime());
}
