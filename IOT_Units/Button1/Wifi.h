#ifndef Wifi_h
#define Wifi_h

#include <TimeLib.h>
#include <Time.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>

ESP8266WiFiMulti WiFiMulti;
time_t lastTimeUpdate;
int lastUpdate;

class Wifi {
public:

  void begin();
  String runURL(String URL);
  void setUrl(String id, String value);
  void iteration();
  void resetLastUpdate();
  bool checkLastUpdate();
  String getIp();

private:

  void updateTime();

  const char* ssid = "The Network";
  const char* password = "3E11A!bb8+";
  const String ip = "192.168.1.2:5000";

    
};

#endif Wifi_h
