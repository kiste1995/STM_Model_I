#ifndef ZETA_STM_KINETIC_MYUTIL_H_
#define ZETA_STM_KINETIC_MYUTIL_H_
#include "variables/instances.h"
#include "configurations/robotConfig.h"
#include "rosHeader.hpp" 
extern ros::NodeHandle nh;
extern MPU9250_SPI mpu;
namespace myUtil
{
void mydelay(int count); 
void stop();
void myLog(const char* myLog);
void myLog(const char* varName, uint16_t val);
void myLog(const char* varName, int val);
void myLog(const char* varName, float val);
void calibrationProcess();
void applyCalbratedValue();
void set_msg(char* msg, const char* contents, size_t length);
}
#endif
