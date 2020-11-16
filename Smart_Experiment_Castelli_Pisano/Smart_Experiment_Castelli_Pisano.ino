#define PIR 7
#define LED_UNO 3
#define LED_DUE 5
#define SENS_TEMP_HUM 4
#define POT A0
#define BUTTON_START 8
#define BUTTON_END 12
#define SONAR_TRIG 10
#define SONAR_ECHO 11

#define CALIBRATION_TIME_SEC 10
#define DHTTYPE DHT11

#include "DHT.h"
#include "Timer.h"
DHT dht(SENS_TEMP_HUM, DHTTYPE);
//ServoMotor* pMotor;

Timer* timer;
/*Timer* errorTimer;
Timer* sleepTimer;*/

const double vs = 331.45 + 0.62*20;
int pos, delta, fadeValue;
boolean startSystemDetected, errorSystem;


const int SLEEP_TIME  = 5000;
const int MAX_TIME = 20000; 
const int ERROR_TIME = 2000; 
/*
  MINFREQ = 1 Hz
  MAXFREQ = 50 Hz
  MAXVEL = TBD
*/


void setup(){
  pinMode(PIR,INPUT);
  pinMode(POT,INPUT);
  pinMode(BUTTON_START,INPUT);
  pinMode(BUTTON_END,INPUT);
  pinMode(SONAR_ECHO, INPUT); 

  pinMode(SONAR_TRIG, OUTPUT);
  pinMode(LED_UNO,OUTPUT);
  pinMode(LED_DUE,OUTPUT);


  //quando parte l'esperimento (Button start), allora faccio partire questo timer
  timer = new Timer();

  //quando parte ma il pir non localizza, allora faccio partire questo timer
  /*errorTimer = new Timer();
  errorTimer -> setupPeriod(ERROR_TIME);

  //quando non viene fatto partire l'esperimento, allora faccio partire questo timer
  sleepTimer = new Timer();
  sleepTimer -> setupPeriod(SLEEP_TIME);*/

  
  //pMotor = new ServoMotorImpl(6);
  //attachInterrupt(digitalPinToInterrupt(PIR), wakeUpSystem, RISING); 
  
  pos, fadeValue = 0;
  delta = 1;
  startSystemDetected, errorSystem = false;
  //time = 0;
  
  Serial.begin(9600);
  
  Serial.print("Calibrating sensors... ");
  
  /*for(int i = 0; i < CALIBRATION_TIME_SEC; i++){
    Serial.print(".");
    delay(1000);
  }
  
  Serial.println("PIR SENSOR READY.");
  dht.begin("DHT SENSOR READY.");*/
  
  delay(50);
}
void loop() {
  timer -> setupPeriod(SLEEP_TIME);
  timer -> printCurrentTime();
  Serial.print("Millisec: ");
  Serial.println(millis());
  /*while(startSystemDetected != true){
    idlePeriod();
  }*/
}

/*void idlePeriod(){
  if(digitalRead(BUTTON_START) == HIGH){
    startSystemDetected = true;
    if(digitalRead(PIR) != HIGH)
      systemError();
  }
}

void systemError(){
  //time = millis();
  //fadeValue = 128+127*cos(2*PI/2000*time);
  //analogWrite(LED_DUE, fadeValue);
}

void detectPir(){
  if (digitalRead(PIR) == HIGH)
    Serial.println("detected!");  
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

void testServo(){
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
}

void sleepySystem(){
  Serial.flush();
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);  
  sleep_enable();
  sleep_mode();  
}

void wakeUpSystem(){
  sleep_disable();
}*/
