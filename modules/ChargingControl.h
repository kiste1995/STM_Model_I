#ifndef ZETA_STM_KINETIC_CHARGINGCONTROL_H_
#define ZETA_STM_KINETIC_CHARGINGCONTROL_H_
#include "mbed.h"
#include "../configurations/robotConfig.h"
#ifndef __RELAY__
#define SSR_OFF 1
#define SSR_ON  0
#else
#define SSR1_OFF 0
#define SSR1_ON  1
#define SSR2_OFF 1
#define SSR2_ON  0
#endif
class ChargingControl {
    public:
#ifndef __RELAY__
        ChargingControl(PinName pinP, PinName pinN) : _pinP(pinP,SSR_OFF), _pinN(pinN,SSR_OFF) {}
        void on()
        {
            if(_pinN == SSR_OFF)
            {
                //nh.loginfo("ssr on");
                _pinN = SSR_ON;
                //ThisThread::sleep_for(100);
                _pinP = SSR_ON;
            }
        }
        void off()
        {
            if(_pinP == SSR_ON)
            {
                //nh.loginfo("ssr off");
                _pinP = SSR_OFF;
                //ThisThread::sleep_for(100);
                _pinN = SSR_OFF;
            }
        }
#else
        ChargingControl(PinName pinP, PinName pinN) : _pinP(pinP,SSR1_OFF), _pinN(pinN,SSR2_OFF) {}
        void on()
        {
            if(_pinN == SSR2_OFF)
            {
                //nh.loginfo("ssr on");
                _pinN = SSR2_ON;
                //ThisThread::sleep_for(100);
                _pinP = SSR1_ON;
            }
        }
        void off()
        {
            if(_pinP == SSR1_ON)
            {
                //nh.loginfo("ssr off");
                _pinP = SSR1_OFF;
                //ThisThread::sleep_for(100);
                _pinN = SSR2_OFF;
            }
        }

#endif
    private:
        void init();
        DigitalOut _pinP;
        DigitalOut _pinN;
};




#endif /* ZETA_STM_KINETIC_CHARGINGCONTROL_H_ */