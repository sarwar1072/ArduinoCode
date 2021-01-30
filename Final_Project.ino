#include <Servo.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(2,3,4,5,6,7);
Servo servoMain;
float value, milivolt;
int celsius, fahrenheit;
int duration;
int distanceCm, distanceInch;
int trigPin = 13;
int echoPin = 12;
int greenLight = 9;
int redLight = 10;

void setup() {
  lcd.begin(16,2);
  servoMain.attach(8);
  Serial.begin(9600);
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(greenLight, OUTPUT);
  pinMode(redLight, OUTPUT);
}
void loop() {
  //  Temperature
  value =  analogRead(A0);
  milivolt = (value / 1024.0) * 5000;
  celsius = milivolt/10;
  fahrenheit = (celsius * 9)/5 + 32;
  
  lcd.setCursor(10,0);
  lcd.print("| 25");
  lcd.print(char(223));
  lcd.print("C");

  lcd.setCursor(10,1);
  lcd.print("| 77");
  lcd.print(char(223));
  lcd.print("F");
  delay(1000);
  lcd.clear();




  //  Servo and Sonar
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distanceCm= duration*0.034/2;
  distanceInch = duration*0.0133/2;

  Serial.print("Centimeter = ");
  Serial.print(distanceCm);
  Serial.print("\t");
  Serial.print("Inch = ");
  Serial.print("\t");
  Serial.println(distanceInch);

  lcd.setCursor(0,0);
  lcd.print("C.M.= ");
  lcd.print(distanceCm);
  lcd.setCursor(0,1);
  lcd.print("I.N.= ");
  lcd.print(distanceInch);
  
  
  
  if (distanceCm <= 20) {
    servoMain.write(100);
    digitalWrite(redLight, LOW);
    digitalWrite(greenLight, HIGH);
  }
  if (distanceCm >= 20)
  {
    servoMain.write(0);
    digitalWrite(redLight, HIGH);
    digitalWrite(greenLight, LOW);
  }





  // LED
  


  
  
}
