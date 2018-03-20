#include <SPI.h>
#include <SD.h>
#include <Ethernet.h>
#include <Twitter.h>
#include "DHT.h" 
#define DHTPIN A1 // pino que estamos conectado
#define DHTTYPE DHT11 // DHT 11

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x02 };
byte ip2[] = { 192,168,1,230};
Twitter twitter("868270753132793856-DoFPHNXGOKpwyKQ7z7uvu5aWNOx6LWM");
String msg = "-";
int sequencia = 0;

DHT dht(DHTPIN, DHTTYPE);
EthernetClient client;


void setup() {
  pinMode(13, OUTPUT); 
  Serial.begin(9600);  
  Serial.println("Ehternet INICIANDO...");
  Ethernet.begin(mac,ip2);
  Serial.println("Ehternet OK ");
  Serial.println("Dht INICIANDO...");
  // iniciando sensores
  dht.begin();  
  Serial.println("Dht OK ");
}



void twitta(float h, float t){
    stringTwitter(h,t);
    Serial.println(" --> "+msg);
    char buffer_msg[70];
    msg.toCharArray(buffer_msg, 70);
    if (twitter.post(buffer_msg)) {
      int status = twitter.wait();
      if (status == 200) {
        Serial.println(sequencia+" Twitter OK");        
      } else {
        Serial.println("failed : code ");
        Serial.println(status);
      }
    } else {
      Serial.println("connection failed.");
    }

  }

void stringTwitter(float h, float t){
    msg = "Sensor 01: Sequência (";
    msg.concat(sequencia);
    msg.concat("), Temperatura (");
    msg.concat(int(t));
    msg.concat(" C) e Umidade (");
    msg.concat(int(h));
    msg.concat(" %).");
  }

void loop() {
  Serial.println("loop");
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  twitta(h,t);
  delay(180000);
  sequencia++;
}
