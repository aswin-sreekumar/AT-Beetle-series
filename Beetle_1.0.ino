// Beetle program for combined movement from blueBase PC terminal
// movements - acc-'F'|left-'L'|rev-'B'|right-'R'|stop-'S'
// combined - acc+left-'G'|acc+right-'I'|rev+left-'H'|rev+right-'J'
// Developed by ASWIN SREEKUMAR

#include<SoftwareSerial.h>

#define LEFT_ENABLE1 A2  
#define LEFT_ENABLE2 A3  
#define RIGHT_ENABLE1 A0 
#define RIGHT_ENABLE2 A5
#define LEFT_SPEED PD6
#define RIGHT_SPEED PD5
#define TX PD3
#define RX PD2

SoftwareSerial path(RX,TX);
char c;

void setup()
{
  pinMode(LEFT_ENABLE1,1);
  pinMode(LEFT_ENABLE2,1);
  pinMode(RIGHT_ENABLE1,1);
  pinMode(RIGHT_ENABLE2,1);
  pinMode(LEFT_SPEED,1);
  pinMode(RIGHT_SPEED,1);
  digitalWrite(LEFT_ENABLE1,0);
  digitalWrite(LEFT_ENABLE2,0);
  digitalWrite(RIGHT_ENABLE1,0);
  digitalWrite(RIGHT_ENABLE2,0);
  digitalWrite(LEFT_SPEED,0);
  digitalWrite(RIGHT_SPEED,0);
  Serial.begin(9600);
  path.begin(9600);
}

void dir(char c) // direction control based on sent character
{
  if(c=='F')
  {
    digitalWrite(LEFT_ENABLE1,1);
    digitalWrite(LEFT_ENABLE2,0);
    digitalWrite(RIGHT_ENABLE1,1);
    digitalWrite(RIGHT_ENABLE2,0);
    analogWrite(LEFT_SPEED,255);
    analogWrite(RIGHT_SPEED,255);
  }
  else if(c=='L')
  {
    digitalWrite(LEFT_ENABLE1,0);
    digitalWrite(LEFT_ENABLE2,1);
    digitalWrite(RIGHT_ENABLE1,1);
    digitalWrite(RIGHT_ENABLE2,0);
    analogWrite(LEFT_SPEED,255);
    analogWrite(RIGHT_SPEED,255);
  }
  else if(c=='B')
  {
    digitalWrite(LEFT_ENABLE1,0);
    digitalWrite(LEFT_ENABLE2,1);
    digitalWrite(RIGHT_ENABLE1,0);
    digitalWrite(RIGHT_ENABLE2,1);
    analogWrite(LEFT_SPEED,255);
    analogWrite(RIGHT_SPEED,255);
  }
  else if(c=='R')
  {
    digitalWrite(LEFT_ENABLE1,1);
    digitalWrite(LEFT_ENABLE2,0);
    digitalWrite(RIGHT_ENABLE1,0);
    digitalWrite(RIGHT_ENABLE2,1);
    analogWrite(LEFT_SPEED,255);
    analogWrite(RIGHT_SPEED,255);  
  }
  else if(c=='S')
  {
    digitalWrite(LEFT_ENABLE1,0);
    digitalWrite(LEFT_ENABLE2,0);
    digitalWrite(RIGHT_ENABLE1,0);
    digitalWrite(RIGHT_ENABLE2,0);
  }
  else if(c=='I')
  {
    digitalWrite(LEFT_ENABLE1,1);
    digitalWrite(LEFT_ENABLE2,0);
    digitalWrite(RIGHT_ENABLE1,0);
    digitalWrite(RIGHT_ENABLE2,0);
    analogWrite(LEFT_SPEED,255);
  }
  else if(c=='G')
  {
    digitalWrite(LEFT_ENABLE1,0);
    digitalWrite(LEFT_ENABLE2,0);
    digitalWrite(RIGHT_ENABLE1,1);
    digitalWrite(RIGHT_ENABLE2,0);
    analogWrite(RIGHT_SPEED,255);
  }
  else if(c=='J')
  {
    digitalWrite(LEFT_ENABLE1,0);
    digitalWrite(LEFT_ENABLE2,1);
    digitalWrite(RIGHT_ENABLE1,0);
    digitalWrite(RIGHT_ENABLE2,0);
    analogWrite(LEFT_SPEED,255);
  }
  else if(c=='H')
  {
    digitalWrite(LEFT_ENABLE1,0);
    digitalWrite(LEFT_ENABLE2,0);
    digitalWrite(RIGHT_ENABLE1,0);
    digitalWrite(RIGHT_ENABLE2,1);
    analogWrite(RIGHT_SPEED,255);
  }
}

void loop()
{
  if(path.available())
  {
    c=path.read(); //reading from serial port
    Serial.println(c);
    dir(c); //function for direction control
  }
  if(!path)
  {
    digitalWrite(LEFT_ENABLE1,0);
    digitalWrite(LEFT_ENABLE2,0);
    digitalWrite(RIGHT_ENABLE1,0);
    digitalWrite(RIGHT_ENABLE2,0);
    digitalWrite(LEFT_SPEED,0);
    digitalWrite(RIGHT_SPEED,0);
  }
}
