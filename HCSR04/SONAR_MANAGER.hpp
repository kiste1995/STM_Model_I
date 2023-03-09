#ifndef ZETA_BOT_MODULE_SONAR_MANAGER_HPP_
#define ZETA_BOT_MODULE_SONAR_MANAGER_HPP_
#include "HCSR04.h"
#include "mbed.h"

#define SONAR_FILTER_WS  5
template<size_t NUM_SONAR>
class SONAR_MANAGER
{
    public:
        SONAR_MANAGER(PinName echo[], PinName trigger_pin) : trigger(trigger_pin)
        {
            for(int i = 0; i < NUM_SONAR; i++)
            {
                sonar[i] = new HCSR04(echo[i], trigger_pin, SONAR_FILTER_WS, i);
            }
        }
        ~SONAR_MANAGER()
        {
            for(int i = 0; i < NUM_SONAR; i++)
            {
                delete sonar[i]; // TODO
            }
        }
        void GetDistance(volatile float dest[])
        {
            for(int i = 0; i < NUM_SONAR; i++)
            {
                dest[i] = distance[i];
            }
        }
        void PrintReady();
        void Begin(float control_freq_)
        {
            control_freq = control_freq_;
            for(int i = 0; i < NUM_SONAR; i++)
            {
                sonar[i]->setRanges(3, 70);
                distance[i] = 0.0;
                ready[i] = 0;
            }
            scheduler.attach(callback(this, &SONAR_MANAGER::Loop), float(1.0 / control_freq));
            memset(ready,0,sizeof(NUM_SONAR));
        }
    private:
        DigitalOut trigger;
        HCSR04* sonar[NUM_SONAR];
        float distance[NUM_SONAR];
        int ready[NUM_SONAR];
        float control_freq;
        Ticker scheduler;
        Timeout triggerTimeout;
        
        void Loop()
        {
            int i;
            memset(ready,0,sizeof(ready));
            trigger = 1;
            triggerTimeout.attach_us(callback(this, &SONAR_MANAGER::turnOffTrigger), 10);
            for(i = 0; i < NUM_SONAR; i++)
            {
                ready[i] = sonar[i]->isNewDataReady();
                sonar[i]->startMeasurement();
                if(ready[i] != 0)
                {   
                    distance[i] = sonar[i]->getDistance_cm();
                } 
            }
        }
        void turnOffTrigger()
        {
            trigger = 0;
        }
};
#endif

