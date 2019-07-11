/*for motor*/
#define m1a 2
#define m1b 3
#define m2a 4
#define m2b 5

/*for sensors*/
const int trigF = 6;
const int echoF = 7;
const int trigR = 8;
const int echoR = 9;
const int trigL = 12;
const int echoL = 13;

int speedPinA = 10; // Needs to be a PWM pin to be able to control motor speed
int speedPinB = 11; // Needs to be a PWM pin to be able to control motor speed

long durationF, durationR, durationL;
int distF, distR, distL;
boolean AU = false;

char data;
void bth()
{
  if (Serial.available() >= 0)
  {
    data = Serial.read(); 
    Serial.println(data);
    }
  

}

void left()
{
  analogWrite(speedPinA, 100);
  analogWrite(speedPinB, 100);
  digitalWrite(m1a, HIGH);
  digitalWrite(m1b, LOW);
  digitalWrite(m2a, LOW);
  digitalWrite(m2b, HIGH);

}
void right()
{
  analogWrite(speedPinA, 100);
  analogWrite(speedPinB, 100);
  digitalWrite(m1a, LOW);
  digitalWrite(m1b, HIGH);
  digitalWrite(m2a, HIGH);
  digitalWrite(m2b, LOW);
}
void forward()
{
  analogWrite(speedPinA, 45);
  analogWrite(speedPinB, 45);
  digitalWrite(m1a, HIGH);
  digitalWrite(m1b, LOW);
  digitalWrite(m2a, HIGH);
  digitalWrite(m2b, LOW);

}
void backward()
{
  analogWrite(speedPinA, 45);
  analogWrite(speedPinB, 45);
  digitalWrite(m1a, LOW);
  digitalWrite(m1b, HIGH);
  digitalWrite(m2a, LOW);
  digitalWrite(m2b, HIGH);

}

void wait()
{
   analogWrite(speedPinA, 0);
  analogWrite(speedPinB, 0);
  digitalWrite(m1a, LOW);
  digitalWrite(m1b, LOW);
  digitalWrite(m2a, LOW);
  digitalWrite(m2b, LOW);
}
void setup()
{
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);

  pinMode(speedPinA,OUTPUT);
  pinMode(speedPinB,OUTPUT);

  pinMode(trigF, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoF, INPUT); // Sets the echoPin as an Input
  pinMode(trigR, OUTPUT);
  pinMode(echoR, INPUT);
  pinMode(trigL, OUTPUT);
  pinMode(echoL, INPUT);
}

void a()
{
  // Clears the trigPin
  digitalWrite(trigF, LOW);
  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigF, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigF, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  durationF = pulseIn(echoF, HIGH);

  // Calculating the distance
  distF = durationF * 0.034 / 2;

  // Prints the distance on the Serial Monitor
  Serial.print("distF: ");
  Serial.println(distF);

  // Clears the trigPin
  digitalWrite(trigR, LOW);
  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigR, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigR, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  durationR = pulseIn(echoR, HIGH);

  // Calculating the distance
  distR = durationR * 0.034 / 2;

  // Prints the distance on the Serial Monitor
  Serial.print("distR: ");
  Serial.println(distR);

  // Clears the trigPin
  digitalWrite(trigL, LOW);
  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigL, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigL, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  durationL = pulseIn(echoL, HIGH);

  // Calculating the distance
  distL = durationL * 0.034 / 2;

  // Prints the distance on the Serial Monitor
  Serial.print("distL: ");
  Serial.println(distL);

}

void AU1()
{
  a();
  if (distL <= 10 && distR >= 10 && distF <= 23)
  { 
  wait();
  delay(300);
  right();
  delay(650);
  wait();
  delay(300);
 
}
else if( distF <= 23 && distL > distR)
{
  wait();
  delay(300);
  left();
  delay(650);
  wait();
  delay(300); 
}
else if ( distF <= 23 && distR > distL)
{
  wait();
  delay(300);
  right();
  delay(650);
  wait();
  delay(300);
}
else if (distR <= 10 && distL >= 10 && distF <= 23)
{
    wait();
  delay(300);
  left();
  delay(650);
  wait();
  delay(300);
}
else if (distR <= 10 && distL <= 10 && distF <=23)
{
      wait();
  delay(300);
  backward();
  delay(200);
  wait();
  delay(300);
}
}

void loop() {


  bth();
    switch (data)
  {
    case 'F':
      forward();
      Serial.println("forward");
      break;

    case 'B':
      backward();
      Serial.println("backward");
      break;

    case 'R':
      right();
      Serial.println("right");
      break;

    case 'L':
      left();
      Serial.println("left");
      break;

    case 'S':
      wait();
      Serial.println("stop");
      break;
      
    case 'W':
      AU=true;
      break;
      
    case 'w':
      AU=false;
      break;
  }

 if(AU)
   AU1();
}
