#ifndef HCSR04_H_TVZMT
#define HCSR04_H_TVZMT
#include "mbed.h"
#define HCSR04_TIMEOUT  2.0f
#include <vector>

class HCSR04 {
    
    public:
    
        /** Receives two PinName variables.
         * @param echoPin mbed pin to which the echo signal is connected to
         * @param triggerPin mbed pin to which the trigger signal is connected to
         */
        HCSR04(PinName echoPin, PinName triggerPin, int windowsize, int index);  // smahn add 20201207
        /** Start the measurement. Measurement time depends on the distance.
         *  Maximum measurement time is limited to 25 ms (400 cm).
         */
        /** Returns the distance in cm. Requires previous call of startMeasurement().
         * @returns distance of the measuring object in cm.
         */
        float getDistance_cm();
        
        /** Returns the distance in mm. Requires previous call of startMeasurement().
         * @returns distance of the measuring object in mm.
         */
        float getDistance_mm();
        
        /** Sets the minimum and maximum ranges between the factory values of 2 cm and 400 cm.
         *  @param minRange Minimum range in cm. Must be between 2 cm and maxRange.
         *  @param maxRange Maximum range in cm. Must be between minRange and 400 cm.
         */
        void setRanges(float minRange, float maxRange);
        
        /** Retreives the minimum sensor range set by the user.
         * @returns the minimum sensor range set by the user in cm.
         */
        float getMinRange();
        
        /** Retreives the maximum sensor range set by the user.
         * @returns the maximum sensor range set by the user in cm.
         */
        float getMaxRange();
        
        /** Checks if the new data is ready.
         * @returns true if new data is ready, false otherwise.
         */
        bool isNewDataReady();
        void startMeasurement(); 
        float getDistance_raw();
        
        
        
        uint64_t _ii;
    private:
        int index;
        InterruptIn echo;       // echo pin
        DigitalOut trigger;     // trigger pin
        Timer timer;            // echo pulsewidth measurement
        float distance;         // store the distance in cm
        vector<float> distance_v; // smahn add 20201207
        int _windowsize;
        volatile float distance_filter;
        float minDistance;      // minimum measurable distance
        float maxDistance;      // maximum measurable distance
        bool  timerStarted;
        volatile bool newDataReady;
        volatile bool timeout_echo;
        bool _timeOut;          // smahn add 20201207
        
        float _distance_filterpre;
        Ticker timeout_manager;
        Timeout echoFallTimeout, echoRiseTimeout;
        void startTimer();
        void stopTimer();
        void init();
        void turnOnTrigger();
        void turnOffTrigger();
        void NoResponse();
        void MAF();
        void SetTrigger(int);
        void NoEchoTimeout();
        void SetTimeoutRoutine();  
};

#endif

