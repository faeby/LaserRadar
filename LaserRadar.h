#ifndef LaserRadar_h
#define LaserRadar_h

#include "Arduino.h"
#include "PhotodiodeTrigger.h"

class LaserRadar
{
  public:
    LaserRadar(PhotodiodeTrigger start, PhotodiodeTrigger end, float distance);
    float check();
  private:
    PhotodiodeTrigger _startPhotoTrigger;
    PhotodiodeTrigger _endPhotoTrigger;
    float _distance;

    bool _startTriggeredCurrent;
    bool _startTriggeredLast;
    bool _endTriggeredCurrent;
    bool _endTriggeredLast;

    int _timerStartedAt;
    int _timerEndedAt;

    float cmpmsToKmph(float cmpms);
    void reset();
};

#endif
