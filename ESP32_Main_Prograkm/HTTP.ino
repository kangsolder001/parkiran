bool getDataHTTP(String url, String &response)
{
  HTTPClient https;
//  Serial.print("[HTTPS] begin...\n");
  if (https.begin(url)) {  // HTTPS
    https.setTimeout(30000);
    https.setConnectTimeout(30000);
    //      https.addHeader("Content-Type", "application/json");
    //    https.addHeader("Authorization", "Bearer 7f1c28150ccdb918b1f4eb63fa9a9d58cd6648ef067ff15c65c8b7c565785239");
//    Serial.print("[HTTPS] POST...\n");
    int httpCode = https.GET();
//    Serial.print("http code  = ");
//    Serial.println(httpCode);
    if (httpCode > 0)
    {
//      Serial.printf("[HTTPS] GET... code: %d\n", httpCode);
      if (httpCode == HTTP_CODE_OK )
      {
        String payload = https.getString();

        StaticJsonDocument<64> doc;
        DeserializationError error = deserializeJson(doc, payload);

        if (error) {
          Serial.print("deserializeJson() failed: ");
          Serial.println(error.c_str());
          return false;
        }
        String gate = doc["gate"];
        String status = doc["status"];
        response = status;
        Serial.println(response);
        
        return true;
      }
      else
      {
        String payload = https.getString();
        Serial.println(payload);
        Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
        return false;
      }
    }
    https.end();
    return false;
  }
  else {
    Serial.println("[HTTPS] Unable to connect data save to SPIFFS");
    return false;
  }
}

bool sendDataHTTP(String url, String dataPost)
{
  HTTPClient https;
  Serial.print("[HTTPS] begin...\n");
  //    if (https.begin(client, url)) {  // HTTPS
  if (https.begin(url)) {
    https.setTimeout(300000);
    https.setConnectTimeout(300000);
    https.addHeader("Content-Type", "application/x-www-form-urlencoded");
    Serial.print("[HTTPS] POST...\n");
    int httpCode = https.POST(dataPost);
    //      int httpCode = https.GET();
    if (httpCode > 0)
    {
      Serial.printf("[HTTPS] GET... code: %d\n", httpCode);
      if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY)
      {
        String payload = https.getString();
        Serial.println(payload);
        //        StaticJsonDocument<96> doc;
        //
        //        DeserializationError error = deserializeJson(doc, payload);
        //
        //        if (error) {
        //          Serial.print("deserializeJson() failed: ");
        //          Serial.println(error.c_str());
        //          return;
        //        }
        //
        //        int status = doc["status"]; // 200
        //        bool error = doc["error"]; // false
        //        String message = doc["message"]; // "Berhasil"
        //
        return true;
      }

    } else {
      String payload = https.getString();
      Serial.println(payload);
      Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
      Serial.print("save to SPIFFS");

      return false;
    }
    https.end();
  } else {
    Serial.println("[HTTPS] Unable to connect data save to SPIFFS");
    return false;
  }
}
