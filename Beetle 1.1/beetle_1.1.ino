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
#define RED_LED 8
#define BLUE_LED 10

SoftwareSerial path(RX,TX);
char c;
float battery_volt=0.0;
int i=0,check=1;

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
  pinMode(RED_LED,1);
  pinMode(BLUE_LED,1);
  pinMode(9,1);
  pinMode(12,1);
  digitalWrite(12,0);
  digitalWrite(9,0);
  path.begin(9600);
  for(i=0;i<5;i++)
  {
  digitalWrite(BLUE_LED,1);
  digitalWrite(RED_LED,0);
  delay(200);
  digitalWrite(RED_LED,1);
  digitalWrite(BLUE_LED,0);
  delay(200);
  }
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
  else if(c=='b') //character sent for battery level information
   {
    if(battery_volt>=8.0)
    {
      path.print('1');
    }
    else if(battery_volt>=7.8)
    {
      path.print('2');
    }
    else if(battery_volt>=7.6)
    {
      path.print('3');
    }
    else if(battery_volt>=7.4)
    {
      path.print('4');
    }
    else if(battery_volt>=7.2)
    {
      path.print('5');
    }
    else if(battery_volt>=7.0)
    {
      path.print('6');
    }
    else if(battery_volt>=6.8)
    {
      path.print('7');
    }
    else if(battery_volt>=6.4)
    {
      path.print('8');
    }
    else
    {
      path.print('9');
    }
   }
}

void battery_level() //constantly reading battery voltage by polling
{
  float tot=0.0;
  for(i=0;i<20;i++)
  tot+=(float)analogRead(A6)*0.04760f; //callibrated voltage reading
  battery_volt=tot/20.0f;
  if(battery_volt<=6.4) //lighting the RED led for low power indication
  {
    digitalWrite(RED_LED,1);
    digitalWrite(BLUE_LED,0);
    check=0;
  }
  else
  {
    check=1;
    digitalWrite(RED_LED,0); // RED led turned off when battery has higher voltage than cutoff
  }
}

void loop()
{
  digitalWrite(BLUE_LED,0);
  battery_level(); // constant check onbattery levels
  if(check) // cut off for character reception on low battery power
  {
  if(path.available())
  {
    digitalWrite(BLUE_LED,1);
    c=path.read(); //reading from serial port
    dir(c);//function for direction control
  }
  }
}
