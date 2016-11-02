#ifndef LaserRadar_h
#define LaserRadar_h

#include "Arduino.h"
#include "PhotodiodeTrigger.h"

class LaserRadar
{
  public:
    LaserRadar(PhotodiodeTrigger start, PhotodiodeTrigger end, double distance);
    double check();
  private:
    PhotodiodeTrigger _startPhotoTrigger;
    PhotodiodeTrigger _endPhotoTrigger;
    double _distance;

    bool _startTriggeredCurrent;
    bool _startTriggeredLast;
    bool _endTriggeredCurrent;
    bool _endTriggeredLast;

    unsigned int _timerStartedAt;
    unsigned int _timerEndedAt;

    double computeKmph(double distance, unsigned int time);
    void reset();
};

#endif
