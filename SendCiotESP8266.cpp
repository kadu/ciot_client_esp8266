#include <ESP8266WiFi.h>
#include "SendCiotESP8266.h"


String dataString = "";
WiFiClient client;
char ciotServer[] = "ciot.thegarage.ciandt.com";

String SendCiotESP8266::send(String array[][2], int elements, String apikey, String device){
  String key;
  String value;
  String msg;

  if (client.connect(ciotServer, 80)) {
    Serial.println(F("connected"));
    dataString = "{\"device\":\"";
    dataString += device;
    dataString += "\",\"data\":{";
    for (int i=0; i<elements;i++){
      key=array[i][0];
      value=array[i][1];
      dataString += "\""+key+"\":";
      dataString += "\""+value+"\"";
      if (elements>1 && i!=elements-1){
         dataString += ",";
      }
    }
    dataString += "}}";
    Serial.print("\n\nDataString:\n");
    Serial.println(dataString);

    client.println("POST /v1/streams/new HTTP/1.1");
    client.println("Host: ciot.thegarage.ciandt.com");
    client.println("Accept: application/json");
    client.println("User-Agent: Arduino-CIOT");
    client.println("Content-Type: application/json");
    client.print("key: ");
    client.println(apikey);
    client.print("Content-Length: ");
    int thisLength = dataString.length();
    client.println(thisLength);
    client.println("Connection: close");
    client.println();
    client.println(dataString);
    Serial.println("end of connection!");

   }
   delay(5);
  while (client.available()) {
      char c = client.read();
      msg += c;
  }
  if (!client.connected()) {
      client.stop();
  }
  return msg;
}