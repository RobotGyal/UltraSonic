#include <NewPing.h>

#define SONAR_NUM 5
#define MAX_DIST 800
#define PING_INTERVAL 30

unsigned long pingTimer[SONAR_NUM];  //when each pings
unsigned int cm[SONAR_NUM]; //stores ping distances
byte currentSensor = 0;

NewPing sonar[SONAR_NUM] = {
  //NewPing(trigger, echo, max)
  NewPing(7, 6, MAX_DIST),  //left 2
  NewPing(11, 10, MAX_DIST),  //left 
  NewPing(9, 8, MAX_DIST),  //center 5
  NewPing(13, 12, MAX_DIST),  //right 
  NewPing(5, 4, MAX_DIST)  //right 2
};

void setup() {
  Serial.begin(9600);
  pingTimer[0] = millis() + 75;
  for (byte i=1; i <SONAR_NUM; i++)
    pingTimer[i] = pingTimer[i-1] + PING_INTERVAL;
}

void loop() {
  for (byte i = 0; i < SONAR_NUM; i++)
  {
    if(millis() >= pingTimer[i])
    {
      pingTimer[i] += PING_INTERVAL * SONAR_NUM;
      if (i==0 && currentSensor == SONAR_NUM -1)
        oneSensorCycle();
      sonar[currentSensor].timer_stop();
      currentSensor = i;
      cm[currentSensor]=0;
      sonar[currentSensor].ping_timer(echoCheck);
    }
  }
  //........
}

void echoCheck()
{
  if(sonar[currentSensor].check_timer())
    cm[currentSensor] = sonar[currentSensor].ping_result / US_ROUNDTRIP_CM;
}

void oneSensorCycle()
{
  for (byte i = 0; i < SONAR_NUM; i++)
  {
    //Serial.print(i);
    //Serial.print("=");
    Serial.print(cm[i]);
    Serial.print(",");
    //Serial.println("cm");
  }
  Serial.println("");
}

