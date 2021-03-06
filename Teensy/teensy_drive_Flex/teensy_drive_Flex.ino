#include <ros.h>
#include <std_msgs/Bool.h>
#include <std_msgs/String.h>
#include <std_msgs/Int32.h>
#include <std_msgs/Empty.h>
#include <race/drive_values.h>
//#include <TimerOne.h>
#include <TimerThree.h>
#include "Flextimer.hpp"

//#include "Arduino.h"
//#include "WProgram.h"
//#include "config/known_16bit_timers.h"

ros::NodeHandle nh;
std_msgs::Int32 int_msg;

Flextimer flex;
const int windowingFrame = 100;
volatile int counterWindowingFrame = 0;

volatile boolean flagRPM = 0;
volatile boolean deadzone = 0;
volatile boolean backward = 0;
boolean flagStop = false;

volatile boolean toggle = false;
volatile int counterThrottleRef = 0;
volatile int counterThrottle;

int pwm_lowerlimit = 6554; // 10% duty cycle
int pwm_center_value = 9830; // 15% duty cycle
int pwm_upperlimit = 13108; // 20% duty cycle

int pwm_interval_forward_low = 9862;
int pwm_interval_forward_high = 10120;
int pwm_interval_backward_low = 9797;
int pwm_interval_backward_high = 9509;
int pwm_forward_ticks_on = 10470;
int pwm_forward_ticks_off = 9900;
int pwm_backward_ticks_on = 9191;
int pwm_backward_ticks_off = 9762;

int kill_pin = 2;
unsigned long duration = 0;
void messageDrive( const race::drive_values& pwm )
{
  if (flagStop == false)
  {
    if (pwm.pwm_drive < pwm_lowerlimit)
    {
      analogWrite(5, pwm_lowerlimit); // Safety lower limit
      deadzone = 0;
    }
    else if (pwm.pwm_drive > pwm_upperlimit)
    {
      analogWrite(5, pwm_upperlimit); // Safety upper limit
      deadzone = 0;
    }
    // Forward deadzone
    else if (pwm.pwm_drive < pwm_interval_forward_high && pwm.pwm_drive > pwm_interval_forward_low)
    {
      backward = 0;
      deadzone = 1;
      float tempPWM = pwm.pwm_drive - pwm_interval_forward_low;
      float pwm_interval_range = pwm_interval_forward_high - pwm_interval_forward_low;
      counterThrottleRef = ((tempPWM/pwm_interval_range) * 65) + 5;
    }
    // Backward deadzone
    else if (pwm.pwm_drive < pwm_interval_backward_low && pwm.pwm_drive > pwm_interval_backward_high) 
    {
      backward = 1;
      deadzone = 1;
      float tempPWM = pwm.pwm_drive - pwm_interval_backward_high;
      float pwm_interval_range = pwm_interval_backward_low - pwm_interval_backward_high;
      counterThrottleRef = (((pwm_interval_range - tempPWM)/pwm_interval_range) * 65) + 5;
    }
    else
    {
      analogWrite(5, pwm.pwm_drive); // Incoming data
      deadzone = 0;
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
  if(deadzone) {
    if(counterThrottle < counterThrottleRef) {
      counterThrottle++;
    } else {
      counterThrottle = 0;
      toggle = !toggle;
      if (!backward) {
        if(toggle) analogWrite(5, pwm_forward_ticks_on);
        else analogWrite(5, pwm_forward_ticks_off);
      } else {
        if(toggle) analogWrite(5, pwm_backward_ticks_on);
        else analogWrite(5, pwm_backward_ticks_off);
      }
    }
  }

  if(counterWindowingFrame + 10 >= windowingFrame) {
    flagRPM = 1;
    flex.trapCount();
    flex.resetCounter();
    counterWindowingFrame = 0;
  } else {
    counterWindowingFrame += 10;
  }
  
}

ros::Publisher RPMCounter("RPMCounter", &int_msg);
ros::Subscriber<race::drive_values> sub_drive("drive_pwm", &messageDrive );
ros::Subscriber<std_msgs::Bool> sub_stop("eStop", &messageEmergencyStop );

void setup() {

  // Setting pin 4 high -> incrementing counter instead of decreasing!
  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH);

  Serial.begin(115200);

  flex.initialize(499);

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
  digitalWrite(2, HIGH);

  // Configure rosnode & subscriber
  nh.initNode();
  nh.subscribe(sub_drive);
  nh.subscribe(sub_stop);
  nh.advertise(RPMCounter);

  Timer3.initialize(10000);
  Timer3.attachInterrupt(interruptHandler);
}

void loop() {

  if(flagRPM == 1) {
    int_msg.data = flex.getCount();
    RPMCounter.publish( &int_msg);
    flagRPM = 0;
  }
  
  nh.spinOnce();
  duration = pulseIn(kill_pin, HIGH, 30000);
  while (duration > 1900)
  {
    duration = pulseIn(kill_pin, HIGH, 30000);
    analogWrite(5, pwm_center_value);
    analogWrite(6, pwm_center_value);
  }
  
  delay(1);
  
}

