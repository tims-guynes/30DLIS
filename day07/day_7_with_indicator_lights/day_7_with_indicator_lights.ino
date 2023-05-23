// Day 7 code...
 
int sensorPin = A0;   // select the *analog zero* input pin for probing the photoresistor
int onboardLED = 13;  // select the pin for the HERO's built-in LED
int sensorValue = 0;  // variable that we'll use to store the value reading from the sensor

int LED1 = 10; //red LED
int LED2 = 11; //yellow LED
int LED3 = 12; //green LED

unsigned int batteryCapacity = 50000;
unsigned int batteryLevel = 0;
unsigned int ticks = 0;
unsigned int wait = 100;
double PercentFull;
 
void setup() {
  // put your setup code here, to run once:
 
 pinMode(onboardLED, OUTPUT);
 pinMode(LED1, OUTPUT);
 pinMode(LED2, OUTPUT);
 pinMode(LED3, OUTPUT);
 Serial.begin(9600);
}
 
void PrintBatteryPercentage() {
// print the elasped time
  Serial.print(ticks);
  Serial.print(" ms    charge at ");
 
//  convert the integers to decimal numbers, divide them and print...
  PercentFull=100*((double)batteryLevel / (double)batteryCapacity);
  Serial.print(PercentFull);
 
// print a percent character and line return...
  Serial.println("%");
}
 
void loop() {
  sensorValue = analogRead(sensorPin); // read the value from the sensor:
  batteryLevel += sensorValue;
  ticks += wait;
 
  if(batteryLevel >= batteryCapacity) {
    // turn on light based on batter level
    
    Serial.print(ticks);
    Serial.print(" ms     ");
    Serial.println("FULLY CHARGED");
    batteryLevel = batteryCapacity; // to prevent integer from continuing to increase
    ticks = 0;
    delay(20000);      // long pause
  }
  else {
    //indicator light to show level of batter capacity
    if(batteryLevel <= (batteryCapacity * 0.3)){
      digitalWrite(LED1, HIGH);
    }else if (batteryLevel <= (batteryCapacity * 0.7)){
      digitalWrite(LED2, HIGH);
    }else {
      digitalWrite(LED3, HIGH);
    }
    PrintBatteryPercentage();
  }
 
  delay(wait);
}