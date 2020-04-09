#include <Servo.h>
Servo ser1;
Servo ser2;

int motor1Pin1 = 3; // pin 2 on L293D IC
int motor1Pin2 = 4; // pin 7 on L293D IC
int enable1Pin = 6; // pin 1 on L293D IC
int motor2Pin1 = 8; // pin 10 on L293D IC
int motor2Pin2 = 9; // pin 15 on L293D IC
int enable2Pin = 11; // pin 9 on L293D IC


int type = 0;
int flag = 0;      //makes sure that the serial only prints once the state
int data = 0;


void setup() {
  Serial.setTimeout(300);
  // sets the pins as outputs:
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(enable1Pin, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(enable2Pin, OUTPUT);
  ser1.attach(15);
  ser1.write(1);
  ser2.attach(5);
  ser2.write(15);
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

void loop() {
  //if some date is sent, reads it and saves in state
  if (Serial.available() > 0) {
    type = Serial.parseInt();
    data = Serial.parseInt();
    flag = 0;
    Serial.println(String(type) + ":" + String(data) + "&" );
  }

  if (type == 0) {  //Stops the Motor
    analogWrite(enable1Pin, data);
    analogWrite(enable2Pin, data);
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, LOW);
    digitalWrite(motor2Pin1, LOW);
    digitalWrite(motor2Pin2, LOW);
    if (flag == 0) {
      Serial.println("Stopped");
      flag = 1;
    }
  }
  if (type == 1)          {
    if (data == 1) { // Should Go forward
      analogWrite(enable1Pin, 100);
      analogWrite(enable2Pin, 100);
      digitalWrite(motor1Pin1, HIGH);
      digitalWrite(motor1Pin2, LOW);
      digitalWrite(motor2Pin1, HIGH);
      digitalWrite(motor2Pin2, LOW);
      if (flag == 0) {
        Serial.println("Moving Forwards!");
        flag = 1;
      }
    }


    else if (data == 2) { // Should go Backwards
      analogWrite(enable1Pin, 100);
      analogWrite(enable2Pin, 100);
      digitalWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, HIGH);
      digitalWrite(motor2Pin1, LOW);
      digitalWrite(motor2Pin2, HIGH);
      if (flag == 0) {
        Serial.println("Moving Back!");
        flag = 1;
      }
    }
    else if (data == 3) { // Should go Right
      analogWrite(enable1Pin, 90);
      analogWrite(enable2Pin, 90);
      digitalWrite(motor1Pin1, HIGH);
      digitalWrite(motor1Pin2, LOW);
      digitalWrite(motor2Pin1, LOW);
      digitalWrite(motor2Pin2, LOW);
      if (flag == 0) {
        Serial.println("Turning Right!");
        flag = 1;
      }
    }
    else if (data == 4) { // Should go Left

      analogWrite(enable1Pin, 90);
      analogWrite(enable2Pin, 90);
      digitalWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, LOW);
      digitalWrite(motor2Pin1, LOW);
      digitalWrite(motor2Pin2, HIGH);
      if (flag == 0) {
        Serial.println("Turning Left!");
        flag = 1;
      }
    }
  }

  else if (type == 2) { // Operates the servomotor for the clamping gear
    ser1.write(data);
    delay(15);

  }
 
  else if (type == 3) {
    ser2.write(data);
    delay(15);
  }



}
