#include "mbed.h"
#include "HCSR04.h"
extern Serial pc;

HCSR04::HCSR04(PinName echoPin, PinName triggerPin, int windowsize, int idx) : 
                echo(echoPin), trigger(triggerPin), _windowsize(windowsize), index(idx) {
    init();
}

void HCSR04::init() {
    distance = 0;      // initial distance
    minDistance = 3;
    maxDistance = 400;
    timerStarted = false;
    newDataReady = 0;
    distance_v.reserve(_windowsize);
    distance_v.assign(_windowsize, 0);
    distance_filter = 0;
    _distance_filterpre = 0;
    _ii = 1;
    timeout_echo = false;
    timeout_manager.attach(callback(this,&HCSR04::SetTimeoutRoutine),5);
}

void HCSR04::startTimer() {
    echo.rise(NULL);
    timer.start(); // start the timer
    echoFallTimeout.attach_us(callback(this, &HCSR04::stopTimer), 58.8235 * maxDistance); // in case echo fall does not occur
    echo.fall(callback(this, &HCSR04::stopTimer));
}

void HCSR04::stopTimer()
{
    timer.stop();
    distance = timer.read() * 1e6 / 58.8235;
    timer.reset();
    echoRiseTimeout.detach();
    echoFallTimeout.detach();
    echo.fall(NULL);
    newDataReady = true;
    timeout_echo = false;
}

void HCSR04::startMeasurement() {
    newDataReady = false;
    echo.rise(callback(this, &HCSR04::startTimer));
}

void HCSR04::NoEchoTimeout()
{
    timeout_echo = true;
    newDataReady = true;
}

void HCSR04::SetTimeoutRoutine()
{
    echoRiseTimeout.attach(callback(this, &HCSR04::NoEchoTimeout),HCSR04_TIMEOUT);
}

float HCSR04::getDistance_cm() {
    
    if(timeout_echo)
    {
        return -1.0f;
    }
    
    if(distance < minDistance)
    {
        distance = minDistance;
    }
    MAF();
    return distance_filter;
}

float HCSR04::getDistance_raw() {
    return distance;
}

float HCSR04::getDistance_mm() {
    return HCSR04::getDistance_cm() * 10;
}

bool HCSR04::isNewDataReady() {
    return newDataReady;
}

void HCSR04::setRanges(float minRange, float maxRange) {
    if (minRange < maxRange)
    {
        if (minRange >= 2 && minRange < 400) // bug from revs. 4 and 5 corrected
            minDistance = minRange;
        if (maxRange <= 400)
            maxDistance = maxRange;
    }
}

float HCSR04::getMinRange()
{
    return minDistance;
}

float HCSR04::getMaxRange()
{
    return maxDistance;
}

void HCSR04::MAF() {
    float sum = 0;
    float beta = 0.9;
    if(__builtin_expect((_ii <= _windowsize),0))
    { // pass when data is not ready
        if(_ii <= 1) distance_v[_ii-1] = distance;
        _ii++;
        return;
    }
    if(__builtin_expect((_ii == _windowsize + 1),0))
    {
        for(int j = 0 ; j < _windowsize; j++) {
            sum += distance_v[j];
        }
        _distance_filterpre = sum / _windowsize;
    }
    distance_filter = _distance_filterpre + (distance - distance_v[(_ii - 1)%_windowsize]) / _windowsize;  // x_bar[k] = x_bar[k-1] + (x[k] + x[k-n])/n
    distance_v[(_ii - 1)%_windowsize] = distance;  // x[k-n] = x[k]
    _distance_filterpre = distance_filter;  // x_bar[k-1] = x[k]
    distance_filter = distance_filter * (1-beta) + _distance_filterpre*beta;
    _ii++;
    
}

void HCSR04::SetTrigger(int level)
{
    trigger = level;
}

void HCSR04::turnOnTrigger()
{
    SetTrigger(1);
}

void HCSR04::turnOffTrigger() {
    SetTrigger(0);
}

// EOF
