#include <Arduino.h>
int leftmtr = 6;  //left motor
int rightmtr = 5; //right motor
int leftmtrrev = 9;  //left reverse
int rightmtrrev = 3; //right reverse
int photo1 = 2; //photoresistor 1 (leftmost)
int photo2 = 4; //photoresistor 2 (middle)
int photo3 = 7; //photoresistor 3  (rightmost)
int irSensor = 8; //distance sensor *pins subject to change

int light = 5000; //set the photoresistor value for white (measured ohms)
int dark = 20000; //set the photoresistor value for dark (measured ohms)
int nothing = 4000; //set the photoresistor value for no lines (measured ohms)
int red = 9000; //set the photoresistor value for red (measured ohms)
int tooClose = 1.5; //distance sensor is 6 inches away from object (measured voltage)

final int ZERO == 0; //is this syntax even right?

void setup() {
  // put your setup code here, to run once:
  pinMode(leftmtr, OUTPUT); //intiializes pin as output
  pinMode(leftmtrrev, OUTPUT); //intiializes pin as output
  pinMode(rightmtr, OUTPUT); //intiializes pin as output
  pinMode(rightmtrrev, OUTPUT); //intiializes pin as output

  pinMode(photo1, OUTPUT);
  pinMode(photo2, OUTPUT);
  pinMode(photo3, OUTPUT);
  pinMode(irSensor, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  //obstacle in front
  if(irSensor == tooClose)
  {
    while(5){
    digitalWrite(rightmtrrev, HIGH);}
    while(5){
    digitalWrite(leftmtrrev, HIGH);}
  }

  //straight black line
  while (photo1 == dark && photo2 == dark && photo3 == dark)
  {
    digitalWrite(rightmtr, HIGH);
    digitalWrite(leftmtr, HIGH);
  }

  //wide angle left turn
  while (photo1 == dark && photo2 == dark && photo3 == light)
  //might be too extreme of turn, need to test
  {
    digitalWrite(leftmtr, HIGH);
    digitalWrite(rightmtr, LOW);
  }

  //wide angle right turn
  while (photo1 == light && photo2 == dark && photo3 == dark)
  //might be too extreme of turn, need to test
  {
    digitalWrite(rightmtr, HIGH);
    digitalWrite(leftmtr, LOW);
  }

  //90 degree left turn
  if (photo1 == dark && photo2 == light && photo3 == light)
  {
    digitalWrite(leftmtr, HIGH);
  }

  //90 degree right turn
  if (photo1 == light && photo2 == light && photo3 == dark)
  {
    digitalWrite(rightmtr, HIGH);
  }

  //navigating through walls
  if ((photo1 == nothing && photo2 == nothing && photo3 == nothing) ||
      (photo1 == light && photo2 == nothing && photo3 == nothing) ||
      (photo1 == light && photo2 == light && photo3 == nothing) ||
      (photo1 == light && photo2 == nothing && photo3 == light) ||
      (photo1 == nothing && photo2 == light && photo3 == nothing) ||
      (photo1 == nothing && photo2 == light && photo3 == light) ||
      (photo1 == nothing && photo2 == nothing && photo3 == light) ||
      (photo1 == light && photo2 == light && photo3 == light) 
      )
  {
    while(irSensor == LOW) //reading below 1.5V, at least 6 inches away
    {
      digitalWrite(leftmtr, HIGH);
      digitalWrite(rightmtr, HIGH);
    }

    while(irSensor == tooClose) //***CONFUSED, keeps going straight, backs up at wall, goes forward again bc we only have one IR sensor...unless we have more than one
    {
      digitalWrite(rightmtrrev, HIGH);
      digitalWrite(leftmtrrev, HIGH);
    }
  }

  //red line
  if(photo1 == red && photo2 == red && photo3 == red)
  {
    digitalWrite(rightmtrrev, ZERO);
    digitalWrite(leftmtrrev, ZERO);
    exit(0);
  }
  
}
