#include <TimeLib.h>
#include <Time.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>

const char* ssid = "The Network";
const char* password = "3E11A!bb8+";
const String ip = "192.168.1.3:5000";

const String id = "01_001_01";

const int SWITCH = D1;
const int RELAY = D2;

bool lastVariable = false;
time_t lastTimeUpdate;
int lastUpdate;

ESP8266WiFiMulti WiFiMulti;


void WiFiBegin();
String runURL(String URL);
void setURL(String value);
void updateTime();

void setup() {

  pinMode(SWITCH, INPUT);
  pinMode(RELAY, OUTPUT);
  
  delay(2000);
  Serial.begin(115200);
  Serial.println("Begin!");

  setTime(0, 0, 0, 1, 1, 2018);

  WiFiBegin();
  updateTime();  
  lastVariable = digitalRead(SWITCH);
  lastTimeUpdate = now();
  lastUpdate = second();

}

void loop() {
  // put your main code here, to run repeatedly:

    if(!lastVariable && !digitalRead(SWITCH)){
      Serial.println("LOW");
      
      lastVariable = true;

      setURL("1");
      
      digitalWrite(RELAY, HIGH);
      lastUpdate = second();
      
    }
    else if(lastVariable && digitalRead(SWITCH)){
      Serial.println("HIGH");
      
      lastVariable = false;

      setURL("0");

      delay(1000);
      digitalWrite(RELAY, LOW);
      lastUpdate = second();

    }
    else if(lastUpdate != second()){
        lastUpdate = second();

        String value = runURL("http://" + ip + "/variable/id=" + id + "&o=read");

        if(value == "1"){
          digitalWrite(RELAY, HIGH);
        }
        else if(value == "0"){
          digitalWrite(RELAY, LOW);
        }

    }

    if(minute() - minute(lastTimeUpdate) >= 5 || 
      (minute() - minute(lastTimeUpdate) + 60 >= 5 && 
       minute() - minute(lastTimeUpdate) + 60 < 10)){
        
      lastTimeUpdate = now();
      updateTime();
    }
    
    delay(100);

}

void WiFiBegin(){
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
}

String runURL(String URL){

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

void setURL(String value){
  
  uint64_t lastTime = millis();
  String output = "";

  do{
    delay(100);
    output = runURL("http://" + ip + "/variable/id=" + id + "&o=write&v=" + value);
    Serial.println("runURL returned " + output);
    }while(output == "" && millis() - lastTime < 5000);

}

void updateTime(){
  
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





