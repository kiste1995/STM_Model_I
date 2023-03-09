#include "myUtil.h"

void myUtil::mydelay(int count)
{
    ThisThread::sleep_for(count);    // threads should yield by sleep
}

void myUtil::stop() {
#if (NO_ROS)
    pc.printf("I stop here!\n\r");
#endif
    while(true) {;}
}

#if !(NO_ROS)



void myUtil::myLog(const char* myLog) {
    nh.loginfo(myLog);
}
// Template T_T
void myUtil::myLog(const char* varName, uint16_t val) {
    char temp[64] = {'\0',};
    sprintf(temp,"var: %s\tvalue: %u",varName,val);
    nh.loginfo(temp);
}
void myUtil::myLog(const char* varName, int val) {
    char temp[32] = {'\0',};
    sprintf(temp,"var: %s\tvalue: %d",varName,val);
    nh.loginfo(temp);
}
void myUtil::myLog(const char* varName, float val) {
    char temp[32] = {'\0',};
    sprintf(temp,"var: %s\tvalue: %f",varName,val);
    nh.loginfo(temp);
}
#endif
void myUtil::calibrationProcess() {
    nh.loginfo("IMU calibration is running... please don't move the robot");
    instances::mpu.calibrateGyro();   
    //mpu.calibrateMag();
#if (NO_ROS)
    pc.printf("Calibration Completed !!!!!!!!\n");  
#else
    nh.loginfo("IMU calibration Completed!!!!!!!!");
#endif
    //while(true) {;}   //stop here
}

void myUtil::applyCalbratedValue() {
    //Vect3 gBias ={ 1.881,   -2.630  ,   0.226};
    //mpu.setGyroBias(gBias); 
    //Vect3 mBias ={12.885,  314.122  , -594.508};
    //mpu.setMagBias(mBias);
    //Vect3 mScale={ 1.852,    1.176  ,   0.621}; 
    //mpu.setMagScale(mScale);
    ;
}

void myUtil::set_msg(char* msg, const char* contents, size_t length) {
    memset(msg, '\0', SEQ_STATE_MSG_SIZE);
    memcpy(msg, contents, length);
}
