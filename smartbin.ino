#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
Servo myservo;

//ultrasonic measure 1
const int trig_1 = 4;
const int echo_1 = 5;
//ultrasonic front
const int trig_4 = 10;
const int echo_4 = 11;
//myservo
const int servo_pin = 12;

long duration_1;
long duration_2;
long duration_3;
long duration_4;
int distanceCm_1, distanceCm_2, distanceCm_3, distanceCm_4, distanceCm_avg;

LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()
{
  //measure ultrasonic 1
  pinMode(trig_1, OUTPUT);
  pinMode(echo_1, INPUT);

  //ultrasonic front
  pinMode(trig_4, OUTPUT);
  pinMode(echo_4, INPUT);

  //servo pin
  pinMode(servo_pin, OUTPUT);
  myservo.attach(servo_pin);

  Serial.begin(9600);
  //LCD CODE//
  lcd.init();                      // initialize the lcd
  lcd.setBacklight(HIGH);

}


void loop()
{
  // ----------------------------------------- //
  digitalWrite(trig_1, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_1, LOW);
  duration_1 = pulseIn(echo_1, HIGH);
  delayMicroseconds(5);
  // ----------------------------------------- //
  digitalWrite(trig_4, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_4, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_4, LOW);
  duration_4 = pulseIn(echo_4, HIGH);
  // ----------------------------------------- //

  // Convert duration to cm
  distanceCm_1 = duration_1 / 29.1 / 2;
  distanceCm_4 = duration_4 / 29.1 / 2;

  if (distanceCm_1 > 23) {
    distanceCm_1 = 23;
  }
  if (distanceCm_1 <= 2) {
    distanceCm_1 = 2;
  }

  Serial.print("ultrasonic 1: ");
  Serial.print(distanceCm_1);
  Serial.println("cm");
  Serial.print("*** ");
  Serial.print(distanceCm_4);
  Serial.println("cm ***");
  int P = (23 - distanceCm_1) * 100 / 21;
  Serial.println(P);
  Serial.println("----------------------------");


  lcd.clear();
  lcd.setCursor(6, 0);
  lcd.print(P);
  lcd.print("%");
  lcd.setCursor(0, 1);

  // Servo
  for (int i = 0; i < P * 16 / 100 ; i++)
  {
    lcd.print(char(255));
  }

  if ( distanceCm_4 <= 20 ) {
    myservo.write(0);
    delay(3000);
  }
  if ( distanceCm_4 > 20 ) {
    myservo.write(145);
    delay(1000);
  }
  //lcd.print("%");
  delay(500);

}
