#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include "CTBot.h"
CTBot myBot ;


String ssid = "DS";
String pass = "120704Gradiass";
const char* host = "dicky20unisma.000webhostapp.com";
String token = "5739755409:AAFzJ_QfzKAsr5kna4FndOk8OUSdW_ZhyBo";
const int id = -898454510 ;



void setup() {
  Serial.begin(9600);
  Serial.println("koneksi");
  myBot.wifiConnect(ssid, pass); 
  myBot.setTelegramToken(token);
  
if(myBot.testConnection())
   Serial.println("berhasil");
else
   Serial.println("gagal");   
}
void loop() {
  String sensor = "";
  while(Serial.available()>0)
  {
    sensor += char(Serial.read());        
  }
  sensor.trim();
  
  if(String (sensor) > "2000" ){ 
    String tmp = "Token Habis Silahkan Isi Ulang Token";
    tmp += String(sensor);
    myBot.sendMessage(id, tmp);
    Serial.println(sensor);
        
        
  }
     
  TBMessage msg ;
  if(myBot.getNewMessage(msg)){
    Serial.println("Pesan Masuk : " + msg.text);
  }
        
  String pesan = msg.text;
  if(pesan == "/start")
  { 
    //int s = sensor;
    //String tmp = "FFT = ";
    //tmp += sensor;
         
    //myBot.sendMessage(id, tmp, "");
    //Serial.println(sensor);       
  }
    
  WiFiClient client ;  
 
  String Link ;
  HTTPClient http;    
  Link = "http://dicky20unisma.000webhostapp.com/kirimdata.php?sensor=" + String (sensor);
  http.begin(client, Link);
  http.GET();
  http.end();
  delay(50);
}
