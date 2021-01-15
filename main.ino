/*
  Code for Arduino
*/

/* Motor Values
  0= power off
  1 = autopilot
  4 = forward
  3 = left
  6 = right
  5 = backward

*/

int motorval = 2; //initial motor value

const int motor1pin = 5;//motor 1 fwd
const int motor2pin = 6;//motor 1 backward
const int motor3pin = 10;//motor 2 bwd
const int motor4pin = 9;//motor 2 fwd
const int echopin = 11;// echo pin for ultrasonic
const int trigpin = 12;// echo pin for ultrasonic


void setup()
{
  Serial.begin (9600);// creates a way for bluetooth and ultrasonic to input information to the arduino to be processed

  pinMode(motor1pin, OUTPUT);//set motor 1 fwd as output
  pinMode(motor2pin, OUTPUT);//Set motor 1 bwd as output

  pinMode(motor3pin, OUTPUT);//Set motor 2 bwd as output

  pinMode(motor4pin, OUTPUT);//Set  motor 2 fwd as output



  pinMode (echopin, INPUT);

  pinMode (trigpin, OUTPUT);
}



void loop()
{
  long duration, distance;
  digitalWrite(trigpin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigpin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin, LOW);
  duration = pulseIn(echopin, HIGH);
  distance = (duration / 2) / 29.1;
  /* this code portion is for the ultrasonic.
      It was provided by the CETA Peel website
      The code makes the trig pin send an ultrasonic wave
      Then the echo pin measures how long it takes for the signal to come back
      The duration is divided by 2 because the wave goes forward and back
      Then the duration is divided by 29.1, presumably because it is the speed in cm/s

  */


  if (Serial.available()) {
    //the arduino reads the value that the bluetooth inputs into it (that it recieves from the phone)
    motorval = Serial.read();
    Serial.println(motorval);
  }

  if (motorval == 0) { //power off
    digitalWrite(motor1pin, LOW);
    digitalWrite(motor2pin, LOW);
    digitalWrite(motor3pin, LOW);
    digitalWrite(motor4pin, LOW);
  } else if (motorval >= 2) {
    if (motorval == 4) { //fwd

      digitalWrite(motor1pin, HIGH);
      digitalWrite(motor2pin, LOW);
      digitalWrite(motor3pin, LOW);
      digitalWrite(motor4pin, HIGH);

    } else if (motorval == 3) { //left

      digitalWrite(motor1pin, HIGH);
      digitalWrite(motor2pin, LOW);
      digitalWrite(motor3pin, HIGH);
      digitalWrite(motor4pin, LOW);


    } else if (motorval == 6) { //right

      digitalWrite(motor1pin, LOW);
      digitalWrite(motor2pin, HIGH);
      digitalWrite(motor3pin, LOW);
      digitalWrite(motor4pin, HIGH);


    } else if (motorval == 5) { //bwd

      digitalWrite(motor1pin, LOW);
      digitalWrite(motor2pin, HIGH);
      digitalWrite(motor3pin, HIGH);
      digitalWrite(motor4pin, LOW);
    } else {
      digitalWrite(motor1pin, LOW);
      digitalWrite(motor2pin, LOW);
      digitalWrite(motor3pin, LOW);
      digitalWrite(motor4pin, LOW);
    }
  } else if (motorval == 1) { //autopilot
    //Serial.print(distance);
    //Serial.println(" cm");


    if (distance > 15) {
      //Forward

      digitalWrite(motor1pin, HIGH);//Motor 1 Forward
      digitalWrite(motor2pin, LOW);
      digitalWrite(motor3pin, LOW);
      digitalWrite(motor4pin, HIGH);//Motor 2 Forward

      delay(1500);//for 1.5 seconds
    }  else {
      
      digitalWrite(motor1pin, LOW);
      digitalWrite(motor2pin, LOW);
      digitalWrite(motor3pin, LOW);
      digitalWrite(motor4pin, LOW);
      delay(2000);//stop for two seconds
      digitalWrite(motor1pin, HIGH);
      digitalWrite(motor2pin, LOW);
      digitalWrite(motor3pin, HIGH);
      digitalWrite(motor4pin, LOW);
      delay(2000);//turn left for two seconds
      //Backward
      digitalWrite(motor1pin, LOW);//Motor 1 fwd
      digitalWrite(motor2pin, HIGH); //motor 1 bwd
      digitalWrite(motor3pin, HIGH);//Motor 2 bwd
      digitalWrite(motor4pin, LOW); //motor 2 fwd


    }

    delay(1000);

  } else {
    //the car won't work if motorval is not a valid value (this never happens but this is just a failsafe
    digitalWrite(motor1pin, LOW);
    digitalWrite(motor2pin, LOW);
    digitalWrite(motor3pin, LOW);
    digitalWrite(motor4pin, LOW);
  }
 
}
