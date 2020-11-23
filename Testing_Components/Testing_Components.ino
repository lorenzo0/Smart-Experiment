#define PIR 7
#define LED_UNO 3
#define LED_DUE 5
#define SENS_TEMP_HUM 13
#define POT A0
#define BUTTON_START 4
#define BUTTON_END 13
#define SONAR_TRIG 10
#define SONAR_ECHO 11

#define CALIBRATION_TIME_SEC 10
#define DHTTYPE DHT11

#include "DHT.h"
//#include "servo_motor_impl.h"
#include <EnableInterrupt.h>

DHT dht(SENS_TEMP_HUM, DHTTYPE);
//ServoMotor* pMotor;

const double vs = 331.45 + 0.62*20;
int pos, delta;

void setup(){
  pinMode(PIR,INPUT);
  pinMode(POT,INPUT);
  pinMode(BUTTON_START,INPUT);
  pinMode(BUTTON_END,INPUT);
  pinMode(SONAR_ECHO, INPUT); 

  pinMode(SONAR_TRIG, OUTPUT);
  pinMode(LED_UNO,OUTPUT);
  pinMode(LED_DUE,OUTPUT);
  
  Serial.begin(9600);
  
  /*Serial.print("Calibrating sensors... ");
  
  for(int i = 0; i < CALIBRATION_TIME_SEC; i++){
    Serial.print(".");
    delay(1000);
  }
  
  Serial.println("PIR SENSOR READY.");
  dht.begin("DHT SENSOR READY.");*/

  //pMotor = new servo_motor_impl(9);
  pos = 0;
  delta = 1;

  enableInterrupt(BUTTON_START, inc, RISING);
  enableInterrupt(BUTTON_END, inc1, RISING);
  
  delay(50);
}
void loop() {

  //Testing_Components
  
  

  //switchOnLeds(); 
  //readFromButtons();
  //detectPir(); 
  //readDHT(); 
  //readFromPot(); 
  //readFromSonar();
  //testServo();
}

void detectPir(){
  if (digitalRead(PIR) == HIGH)
    Serial.println("detected!");  
}

void inc(){
  Serial.println("BUTTON_START!");
}

void inc1(){
  Serial.println("BUTTON_END!");
}

void readDHT(){
  float hum = dht.readHumidity();
  float temp = dht.readTemperature();

  if(isnan(hum) || isnan(temp))
    Serial.println("Failed to read from DHT");
    
  Serial.print("Temperature: ");
  Serial.println(temp);
  Serial.print("Humidity: ");
  Serial.println(hum);
}

void switchOnLeds(){
  digitalWrite(LED_UNO, HIGH);
  digitalWrite(LED_DUE, HIGH);
}

void readFromButtons(){
  if(digitalRead(BUTTON_START) == HIGH)
    Serial.println("Button start clicked!");

  if(digitalRead(BUTTON_END) == HIGH)
    Serial.println("Button end clicked!");
}

void readFromPot(){
  Serial.print("Pot: ");
  Serial.println(analogRead(POT));
}

void readFromSonar(){
  float distance = getDistance();
  Serial.print("Distance Sonar: ");
  Serial.println(distance);
  delay(500);
}

float getDistance()
{
    digitalWrite(SONAR_TRIG,LOW);
    delayMicroseconds(3);
    digitalWrite(SONAR_TRIG,HIGH);
    delayMicroseconds(5);
    digitalWrite(SONAR_TRIG,LOW);
    
    long tUS = pulseInLong(SONAR_ECHO, HIGH);
    Serial.println(tUS);

    double t = tUS / 1000.0 / 1000.0 / 2;
    double d = t*vs;
    return d;
}

/*void testServo(){
  pMotor->on();
  for (int i = 0; i < 180; i++) {
    //Serial.println(pos);
    pMotor->setPosition(pos);         
    delay(5);            
    pos += delta;
  }
  pMotor->off();
  pos -= delta;
  delta = -delta;
  delay(1000);
}*/
