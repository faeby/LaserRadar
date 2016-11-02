#include "Arduino.h"
#include "LaserRadar.h"

LaserRadar::LaserRadar(PhotodiodeTrigger start, PhotodiodeTrigger end, double distance)
{
  _startPhotoTrigger = start;
  _endPhotoTrigger = end;
  _distance = distance;

  _startTriggeredCurrent = false;
  _startTriggeredLast = false;
  _endTriggeredCurrent = false;
  _endTriggeredLast = false;

  _timerStartedAt = -1;
  _timerEndedAt = -1;
}

double LaserRadar::check(){

  // Check start photodiode state
  _startTriggeredCurrent = _startPhotoTrigger.triggered();

  if (_startTriggeredCurrent && !_startTriggeredLast) {
    // something triggered the sensor
    _startTriggeredLast = true;
    _timerStartedAt = micros();
    //Serial.print("Start Laser: broken, timer started at ");
    //Serial.println(_timerStartedAt);

  } else if (!_startTriggeredCurrent && _startTriggeredLast) {
    //Serial.println("Start Laser: No more broken");
    _startTriggeredLast = false;
  }

  // Check end photodiode sensor
  _endTriggeredCurrent = _endPhotoTrigger.triggered();

  if (_endTriggeredCurrent && !_endTriggeredLast) {
    //Serial.println("End Laser: broken");
    if (_timerStartedAt != -1) {
      _timerEndedAt = micros();
      unsigned int time = _timerEndedAt - _timerStartedAt;
      Serial.print("Time between 2 lasers: ");
      Serial.print(time);
      Serial.println(" micros");

      double lastSpeed = computeKmph(_distance, time);

      _timerStartedAt = -1;
      return lastSpeed;
    }

    _endTriggeredLast = true;
  } else if (!_endTriggeredCurrent && _endTriggeredLast) {
    //Serial.println("End Laser: No more broken");
    _endTriggeredLast = false;
  }

  return 0.0;
}

double LaserRadar::computeKmph(double distance, unsigned int time){
  return distance * 36000 / time;
}

void LaserRadar::reset(){
  _startTriggeredCurrent = false;
  _startTriggeredLast = false;
  _endTriggeredCurrent = false;
  _endTriggeredLast = false;

  _timerStartedAt = -1;
  _timerEndedAt = -1;
}
