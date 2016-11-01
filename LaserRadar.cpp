#include "Arduino.h"
#include "LaserRadar.h"

LaserRadar::LaserRadar(PhotodiodeTrigger start, PhotodiodeTrigger end, float distance)
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

float LaserRadar::check(){

  // Check start photodiode state
  _startTriggeredCurrent = _startPhotoTrigger.triggered();

  if (_startTriggeredCurrent && !_startTriggeredLast) {
    // something triggered the sensor
    _timerStartedAt = millis();
    Serial.print("Start Laser: broken, timer started at ");
    Serial.println(_timerStartedAt);
    _startTriggeredLast = true;
  } else if (!_startTriggeredCurrent && _startTriggeredLast) {
    Serial.println("Start Laser: No more broken");
    _startTriggeredLast = false;
  }

  // Check end photodiode sensor
  _endTriggeredCurrent = _endPhotoTrigger.triggered();

  if (_endTriggeredCurrent && !_endTriggeredLast) {
    Serial.println("End Laser: broken");
    if (_timerStartedAt != -1) {
      _timerEndedAt = millis();
      int time = _timerEndedAt - _timerStartedAt;
      Serial.print("Time between 2 lasers: ");
      Serial.print(time);
      Serial.println(" ms");

      float centimeterPerMillis = _distance / time;
      float lastSpeed = cmpmsToKmph(centimeterPerMillis);

      _timerStartedAt = -1;
      return lastSpeed;
    }

    _endTriggeredLast = true;
  } else if (!_endTriggeredCurrent && _endTriggeredLast) {
    Serial.println("End Laser: No more broken");
    _endTriggeredLast = false;
  }

  return 0.0;
}

float LaserRadar::cmpmsToKmph(float cmpms){
  return cmpms * 36;
}

void LaserRadar::reset(){
  _startTriggeredCurrent = false;
  _startTriggeredLast = false;
  _endTriggeredCurrent = false;
  _endTriggeredLast = false;

  _timerStartedAt = -1;
  _timerEndedAt = -1;
}
