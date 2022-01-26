String toJson (String id)
{
  String jsonData;
  DynamicJsonDocument datjs(400);
  datjs["id"] = id;
  serializeJson(datjs, jsonData);
  datjs.clear();
  return jsonData;
}
String toJsonLokasiParkir(String idLantai, String idParkir, String stat)
{
  String jsonData;
  DynamicJsonDocument datjs(400);
  datjs["idLantai"] = idLantai;
  datjs["idParkir"] = idParkir;
  datjs["status"] = stat;
  serializeJson(datjs, jsonData);
  datjs.clear();
  return jsonData;
}
