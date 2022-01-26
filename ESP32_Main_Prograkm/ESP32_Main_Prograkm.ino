#include<WiFi.h>
#include<TimeLib.h>
#include <WiFiUdp.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
const char* ssid = "iPhone"; // IT-DEV
const char* password = "aldiridho";

//==========================HTTP====================================
String updateParkir = "https://tirtawangi.com/index.php/Arduino/updateParkir";
String insertID = "https://tirtawangi.com/index.php/Arduino/addMobil";
String getGate = "https://tirtawangi.com/index.php/Arduino/openGate";
String UpdateGate = "https://tirtawangi.com/index.php/Arduino/closeGate";
//==========================NTP====================================
static const char ntpServerName[] = "pool.ntp.org";
//IPAddress ntpServerIP(192, 168, 9, 20);
const int timeZone = 7;
WiFiUDP Udp;
unsigned int localPort = 8888;
time_t getNtpTime();
void sendNTPpacket(IPAddress &address);
void setup() {
  Serial.begin(115200);
  Serial2.begin(115200);
  wifi();

  // put your setup code here, to run once:

}
uint32_t before, prevMqtt, prevGet;
void loop() {
  if (millis() - prevGet >= 1000)
  {
    //getDatagate;
    String res;
    prevGet = millis();
    if (getDataHTTP(getGate, res))
    {
      if (res == "1")
      {
        String dataSend = "|openGate|";
        dataSend += res;
        dataSend += "|\r";
        Serial2.print(dataSend);
        //buka gerbang
        String datSend = "gate=A&status=0";
        sendDataHTTP(UpdateGate, datSend);
      }

    }

  }
  
  if ( year() == 1970 )
  {
    ntpBegin();
  }
  if ( now() != before)
  {
    Serial.println(now());
    before = now();
  }

  if (Serial2.available())
  {
    String in = Serial2.readStringUntil('\r');
    Serial.println(in);
    int ind1, ind2, ind3, ind4, ind5;
    String data1, data2, data3, data4;
    ind1 = in.indexOf("|");
    ind2 = in.indexOf("|", ind1 + 1);
    ind3 = in.indexOf("|", ind2 + 1);
    ind4 = in.indexOf("|", ind3 + 1);
    ind5 = in.indexOf("|", ind4 + 1);
    data1 = in.substring(ind1 + 1, ind2);
    data2 = in.substring(ind2 + 1, ind3);
    data3 = in.substring(ind3 + 1, ind4);
    data4 = in.substring(ind4 + 1, ind5);
    Serial.print("data 1 = ");
    Serial.println(data1);
    Serial.print("data 2 = ");
    Serial.println(data2);
    Serial.print("data 3 = ");
    Serial.println(data3);

    if ( data1 == "addCar")
    {
      //      String dataSend = toJson(data2);
      String dataSend = "id=";
      dataSend += data2;
      sendDataHTTP(insertID, dataSend);
      //      sendDataMQTT(topicSendID, dataSend);
      //sendData
    }
    else if ( data1 == "updateParkir")
    {
      String dataSend = "idLantai=";
      dataSend += String(data2);
      dataSend += "&idParkir=";
      dataSend += data3;
      dataSend += "&status=";
      dataSend += data4;
      sendDataHTTP(updateParkir, dataSend);
      //      String dataSend = toJsonLokasiParkir(data2, data3, data4);
      //      sendDataMQTT(topicSendStatus, dataSend);
    }
    else if ( data1 == "getTime")
    {
      Serial.println(now());
      String dataSend = "|timenow|";
      dataSend += String(now());
      dataSend += "|\r";
      Serial2.print(dataSend);
      //sendData
    }
  }
  if (Serial.available())
  {
    String in = Serial.readStringUntil('\r');
    Serial.println(in);
    int ind1, ind2, ind3, ind4, ind5;
    String data1, data2, data3, data4;
    ind1 = in.indexOf("|");
    ind2 = in.indexOf("|", ind1 + 1);
    ind3 = in.indexOf("|", ind2 + 1);
    ind4 = in.indexOf("|", ind3 + 1);
    ind5 = in.indexOf("|", ind4 + 1);
    data1 = in.substring(ind1 + 1, ind2);
    data2 = in.substring(ind2 + 1, ind3);
    data3 = in.substring(ind3 + 1, ind4);
    data4 = in.substring(ind4 + 1, ind5);
    Serial.print("data 1 = ");
    Serial.println(data1);
    Serial.print("data 2 = ");
    Serial.println(data2);
    Serial.print("data 3 = ");
    Serial.println(data3);

    if ( data1 == "addCar")
    {
      //      String dataSend = toJson(data2);
      String dataSend = "id=";
      dataSend += String(now());
      sendDataHTTP(insertID, dataSend);
      //      sendDataMQTT(topicSendID, dataSend);
      //sendData
    }
    else if ( data1 == "updateParkir")
    {
      String dataSend = "idLantai=";
      dataSend += String(data2);
      dataSend += "&idParkir=";
      dataSend += data3;
      dataSend += "&status=";
      dataSend += data4;
      sendDataHTTP(updateParkir, dataSend);
      //      String dataSend = toJsonLokasiParkir(data2, data3, data4);
      //      sendDataMQTT(topicSendStatus, dataSend);
    }
    else if ( data1 == "updateGate")
    {
      String dataSend = "gate=A&status=1";
      sendDataHTTP(UpdateGate, dataSend);
      //update status gate jadi 1
    }
    else if ( data1 == "getTime")
    {
      Serial.println(now());
      String dataSend = "|timenow|";
      dataSend += String(now());
      dataSend += "|\r";
      Serial2.print(dataSend);
      //sendData
    }
    else if (data1 == "get")
    {
      String res;
      getDataHTTP(getGate, res);
    }
  }

}
