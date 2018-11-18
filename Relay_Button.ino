/* Comment this out to disable prints and save space */
//test

#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define RELAYPIN D1
#define LEDPIN LED_BUILTIN
char auth[] = "5e4ef8cc78ba4479bfa06ffa414c51a7";

char ssid[] = "PLE";
char pass[] = "bilanwpa";

SimpleTimer timer;
int CountdownRemainReset;
int CountdownRemain;
int CountdownTimer;

void setup()
{
  // Debug console
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  pinMode(RELAYPIN, OUTPUT);
  pinMode(LEDPIN, OUTPUT);
  digitalWrite(LEDPIN, HIGH);
  
  CountdownTimer = timer.setInterval(1000, CountdownTimerFunction);
  timer.disable(CountdownTimer); // disable it on boot
}

BLYNK_WRITE(V1) 
{
  digitalWrite(RELAYPIN, HIGH);
  digitalWrite(LEDPIN, LOW);
  timer.enable(CountdownTimer);
  CountdownRemain = 60;
}

BLYNK_WRITE(V2) 
{
  digitalWrite(RELAYPIN, HIGH);
  digitalWrite(LEDPIN, LOW);
  timer.enable(CountdownTimer);
  CountdownRemain = 300;
}

BLYNK_WRITE(V3) 
{
  digitalWrite(RELAYPIN, HIGH);
  digitalWrite(LEDPIN, LOW);
  timer.enable(CountdownTimer);
  CountdownRemain = 900;
}

BLYNK_WRITE(V4) 
{
  digitalWrite(RELAYPIN, LOW);
  digitalWrite(LEDPIN, HIGH);
  timer.disable(CountdownTimer);
}


void CountdownTimerFunction() {
  CountdownRemain--; // remove 1 every second
  if (!CountdownRemain) { // check if CountdownRemain == 0/FALSE/LOW
    timer.disable(CountdownTimer); // if 0 stop timer
    digitalWrite(RELAYPIN, LOW);
    digitalWrite(LEDPIN, HIGH);
  } 
}

void loop()
{
  Blynk.run();
  timer.run();
}
