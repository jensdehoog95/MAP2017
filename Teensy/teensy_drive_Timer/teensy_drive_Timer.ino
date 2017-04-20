#include <ros.h>
#include <std_msgs/Bool.h>
#include <std_msgs/String.h>
#include <std_msgs/Int32.h>
#include <std_msgs/Empty.h>
#include <race/drive_values.h>
#include <TimerOne.h>
//#include "Arduino.h"
//#include "WProgram.h"
//#include "config/known_16bit_timers.h"
ros::NodeHandle nh;
boolean flagStop = false;
volatile boolean toggle = false;
volatile int counterThrottleRef = 0;
volatile int counterThrottle;

int pwm_center_value = 9830; // 15% duty cycle
int pwm_lowerlimit = 6554; // 10% duty cycle
int pwm_upperlimit = 13108; // 20% duty cycle

int pwm_interval_forward_low = 9862;
int pwm_interval_forward_high = 10120;
int pwm_ticks_on = 10470;
int pwm_ticks_off = 9900;

int kill_pin = 2;
unsigned long duration = 0;
void messageDrive( const race::drive_values& pwm )
{
  if (flagStop == false)
  {
    if (pwm.pwm_drive < pwm_lowerlimit)
    {
      analogWrite(5, pwm_lowerlimit); // Safety lower limit
      Timer1.stop();
    }
    else if (pwm.pwm_drive > pwm_upperlimit)
    {
      analogWrite(5, pwm_upperlimit); // Safety upper limit
      Timer1.stop();
    }
    else if (pwm.pwm_drive < pwm_interval_forward_high && pwm.pwm_drive > pwm_interval_forward_low)
    {
      Timer1.resume();
      float tempPWM = pwm.pwm_drive - pwm_interval_forward_low;
      float pwm_interval_range = pwm_interval_forward_high - pwm_interval_forward_low;
      counterThrottleRef = ((tempPWM/pwm_interval_range) * 65) + 5;
    }
    else
    {
      analogWrite(5, pwm.pwm_drive); // Incoming data
      Timer1.stop();
      counterThrottleRef = 0;
    }
    
    if (pwm.pwm_angle < pwm_lowerlimit)
    {
      analogWrite(6, pwm_lowerlimit); // Safety lower limit
    } 
    else if (pwm.pwm_angle > pwm_upperlimit)
    {
      analogWrite(6, pwm_upperlimit); // Safety upper limit
    }
    else
    {
      analogWrite(6, pwm.pwm_angle); // Incoming data
    }
  }
  else
  {
    analogWrite(5, pwm_center_value);
    analogWrite(6, pwm_center_value);
  }
}
void messageEmergencyStop( const std_msgs::Bool& flag )
{
  flagStop = flag.data;
  if (flagStop == true)
  {
    analogWrite(5, pwm_center_value);
    analogWrite(6, pwm_center_value);
  }
}

void interruptHandler() 
{
  if(counterThrottle < counterThrottleRef) {
    counterThrottle++;
  } else {
    counterThrottle = 0;
    toggle = !toggle;
    if(toggle) analogWrite(5, pwm_ticks_on);
    else analogWrite(5, pwm_ticks_off);
  }
}


ros::Subscriber<race::drive_values> sub_drive("drive_pwm", &messageDrive );
ros::Subscriber<std_msgs::Bool> sub_stop("eStop", &messageEmergencyStop );
void setup() {

  //noInterrupts();

  Serial.begin(115200);

  // Initialise PWM-signals
  analogWriteFrequency(5, 100);
  analogWriteFrequency(6, 100);
  analogWriteResolution(16);
  
  analogWrite(5, pwm_center_value);
  analogWrite(6, pwm_center_value);

  // Configure built-in LED as output
  pinMode(13, OUTPUT);

  // Configure killswitch at port 2 as input
  pinMode(2, OUTPUT);

  // Configure rosnode & subscriber
  nh.initNode();
  nh.subscribe(sub_drive);
  nh.subscribe(sub_stop);
  //nh.advertise(chatter);

  //interrupts();

  Timer1.initialize(10000);
  Timer1.stop();
  //Timer1.pwm(3, 0);
  Timer1.attachInterrupt(interruptHandler);
  //attachInterrupt(digitalPinToInterrupt(3), interruptHandler, CHANGE);
}

void loop() {
  nh.spinOnce();
  duration = pulseIn(kill_pin, HIGH, 30000);
  while (duration > 1900)
  {
    duration = pulseIn(kill_pin, HIGH, 30000);
    analogWrite(5, pwm_center_value);
    analogWrite(6, pwm_center_value);
  }
  // put your main code here, to run repeatedly:

    delay(1);
  
}

