
#define BLYNK_PRINT Serial
#define Motor_A_1A 12 // Motor A PWM Speed
#define Motor_A_1B 14 // Motor A Direction

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "f9d9d9743f3940db96cd7c8bca04b60d"; //Your-Authentication-Token-Provided-in-App

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "iot";
char pass[] = "12345678";

int sensorData;
int sensorData1;

int previousflag  = 0;
int currentflag = 0;
String body =  "Motor Stopped"; 

BlynkTimer timer;

// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void myTimerEvent()
{
  sensorData = analogRead(A0);
  
  if (sensorData > 512)
  {
    digitalWrite( Motor_A_1B, HIGH );
    analogWrite( Motor_A_1A, 128); 
    Serial.println("Hi");
  }
  else
  {
    digitalWrite( Motor_A_1B, LOW);
    analogWrite( Motor_A_1A, 0); 
    Serial.println("Lo");
  }
  sensorData1 = digitalRead(D1);
  if (sensorData1 == 0)
  {
    sensorData = 500;
    digitalWrite(D0, LOW);

    currentflag = 1;

    if (currentflag == 1 && previousflag == 1)
    {
      Blynk.email("nmishra1309@gmail.com", "Subject: Alert ", body);
      previousflag = 0;
    }
            
  }
  else
  {
    sensorData = 20;
    previousflag = 1;    
    digitalWrite(D0, HIGH);
    
  }
  Serial.println(sensorData);
  Blynk.virtualWrite(V1, sensorData);
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
}

void setup()
{
  // Debug console
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  pinMode( Motor_A_1B, OUTPUT );
  pinMode( Motor_A_1A, OUTPUT );
  digitalWrite( Motor_A_1B, LOW );
  digitalWrite( Motor_A_1A, LOW );

  pinMode(D1,INPUT);
  pinMode(D0, OUTPUT);

  // Setup a function to be called every second
  timer.setInterval(1000L, myTimerEvent);
}

void loop()
{
  Blynk.run();
  timer.run(); // Initiates BlynkTimer
}