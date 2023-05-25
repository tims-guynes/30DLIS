// Day 10 creativity
 
int sensorPin = A0;   // select the *analog zero* input pin for probing the photoresistor
int sensorValue = 0;  // variable that we'll use to store the value reading from the sensor
 
int red = 11;  // these are our output pins for three LED colors
int green = 10;
int blue = 9;

int ledPins[] = {
  5, 6, 7, 8
};
int pinCount = 4;

int switch1 = 2;
int switch2 = 3;
int switch3 = 4;


 
unsigned int batteryCapacity = 50000;
unsigned int batteryLevel = 0;
unsigned int ticks = 0;
unsigned int wait = 100;
double PercentFull;
 
//******************************************
 
void setup() {
  // Declare the RGB LED pins as outputs:
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  // Declare the 3 switch DIPSWITCH
  pinMode(switch1, INPUT);
  pinMode(switch2, INPUT);
  pinMode(switch3, INPUT);
  //
  for (int thisPin = 0; thisPin < pinCount; thisPin++) {
    pinMode(ledPins[thisPin], OUTPUT);
  }


  // Start serial monitor
  Serial.begin(9600);
}
 
//******************************************
 
void RGB_color(int red_value, int green_value, int blue_value)
 {
// custom function to set three PWM color channels to any given mixture
// it returns NO numerical result (void)
 
  analogWrite(red, red_value);
  analogWrite(green, green_value);
  analogWrite(blue, blue_value);
 }
//******************************************
 
 double getBatteryPercentage() {
// custom function calculates battery charge percentage
// and returns the result as a double precision number
 
  return (((double)batteryLevel / (double)batteryCapacity)*100);
 
}
 
//******************************************
 
void ShowBatteryPercentage() {
  //  send battery results to both serial and LED outputs
   //  calculate the charge percentage with a custom function...
  PercentFull=getBatteryPercentage();
 
// print the elasped time
  Serial.print(ticks);
  Serial.print(" ms    charge at ");
// print the percent charge
  Serial.print(PercentFull);
// print a percent character and line return...
  Serial.println("%");
 
// Now let's light the LED with the appropriate color...
 
  if (PercentFull > 0 && PercentFull <= 25)
  {
    RGB_color(125, 0, 0); // red
  }
  else if (PercentFull > 25 && PercentFull <= 50){
    RGB_color(125, 80, 0); // yellow-ish
  }
  else if (PercentFull > 50 && PercentFull <= 75) {
    RGB_color(0, 125, 125); // blue-ish
  }
  else if (PercentFull > 75 && PercentFull < 100) {
    RGB_color(125, 125, 125); // white
  }
 
 
}
 
void chargeBattery(){
    sensorValue = analogRead(sensorPin); // read the value from the sensor
    batteryLevel += sensorValue;
    ticks += wait;
  
    if(batteryLevel >= batteryCapacity) {
      Serial.print(ticks);
      Serial.print(" ms     ");
      Serial.println("FULLY CHARGED");
      batteryLevel = batteryCapacity; // to prevent integer from continuing to increase
      ticks = 0;
      RGB_color(0, 125, 0); // Green for charging complete
      delay(30000);      // long pause
    }
    else {
      ShowBatteryPercentage();
    }
  
    delay(wait);
    }

void blink_colors(){
  RGB_color(125, 125, 125);
  delay(250);
  RGB_color(125, 0, 125);
  delay(250);
  RGB_color(125, 125, 0);
  delay(250);
  RGB_color(0, 0, 0);
  delay(250);
}


//******************************************
 
void loop() {
  


  if (digitalRead(switch1) == HIGH){
    chargeBattery();
  }
  if (digitalRead(switch1) == HIGH && digitalRead(switch2) == HIGH){
    blink_colors();
  }
  if (digitalRead(switch2) == HIGH && digitalRead(switch3) == HIGH){
    for (int thisPin = 0; thisPin < pinCount; thisPin++) {
      digitalWrite(ledPins[thisPin], HIGH);
      delay(100);
      digitalWrite(ledPins[thisPin], LOW);
  }
  }

}