#include "Wifi.h"

void Wifi::begin(){
  
  setTime(0, 0, 0, 1, 1, 2018);
  
  Serial.print("Loading wifi interface");
  for(uint8_t t = 4; t > 0; t--) {
       Serial.print(".");
       delay(1000);
  }
  Serial.println("");

  while(true){

    WiFi.mode(WIFI_STA);
    WiFiMulti.addAP(ssid, password);
    
    Serial.print("Checking connection");
    for(uint8_t t = 4; t > 0; t--) {
         Serial.print(".");
         delay(1000);
    }
    Serial.println("");

    if(WiFiMulti.run() == WL_CONNECTED){
      Serial.println("Sucess!");
      break;
    }
    else{
      Serial.println("Could not connect to wifi");
    }
  }

  updateTime();  
  lastTimeUpdate = now();
  lastUpdate = second();

}

String Wifi::runURL(String URL){

  if(WiFiMulti.run() == WL_CONNECTED) {

    HTTPClient http;
    http.begin(URL);

    if(http.GET() > 0){
      return http.getString();
    }
    else{
      Serial.println("Failed to connect.");
      return "";
    }
  }
  else{
    Serial.println("Could not run WiFi module.");
    return "";
  }
  
}

void Wifi::setUrl(String id, String value){
  
  uint64_t lastTime = millis();
  String output = "";

  do{
    delay(100);
    output = runURL("http://" + ip + "/variable/id=" + id + "&o=write&v=" + value);
    Serial.println("runURL returned " + output);
    }while(output == "" && millis() - lastTime < 5000);

}

void Wifi::iteration(){
  
  if(minute() - minute(lastTimeUpdate) >= 5 || 
      (minute() - minute(lastTimeUpdate) + 60 >= 5 && 
       minute() - minute(lastTimeUpdate) + 60 < 10)){
        
      lastTimeUpdate = now();
      updateTime();
    }
    
}

void Wifi::resetLastUpdate(){
  
  lastUpdate = second();

}

bool Wifi::checkLastUpdate(){

  return lastUpdate != second();
  
}

String Wifi::getIp(){
  return ip;
}

void Wifi::updateTime(){
  
  String currentTime = "";
  uint64_t lastTime = millis();

  do{
    currentTime = runURL("http://" + ip + "/getTime");
  }while(currentTime == "" && millis() - lastTime < 5000);

  if(currentTime == ""){
    return;
  }

  setTime(0, 0, 0, 1, 1, 1970);
  adjustTime(currentTime.toInt());


  Serial.print("Set time to Hour: ");
  Serial.print(hour());

  Serial.print(" Minute: ");
  Serial.print(minute());

  Serial.print(" Second: ");
  Serial.println(second());
  
}
