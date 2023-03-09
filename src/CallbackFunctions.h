#ifndef ZETA_STM_KINETIC_CALLBACKHEADER_H_
#define ZETA_STM_KINETIC_CALLBACKHEADER_H_
#include "rosHeader.hpp"
#include "mbed.h"
#include "configurations/robotConfig.h"
#include "modules/ChargingControl.h"
#include "variables/GlobalVariables.h"
//extern std_msgs::Bool UVCcontrolMsg;
extern ros::NodeHandle nh;
namespace callback_functions
{
void BluetoothCB(const std_msgs::UInt8& msg);
void SsrTestCB(const std_msgs::Bool& msg);
#if ((ROBOT_TYPE == MODEL_I) || (ROBOT_TYPE == MODEL_I2))
void WarningFieldSelectCB(const std_msgs::UInt8& msg);
void IgnoreWarningFieldCB(const std_msgs::UInt8& msg);
#if (ROBOT_TYPE != MODEL_I2)
void ScrubberControlCB(const std_msgs::Bool& msg);
#endif /* (ROBOT_TYPE != MODEL_I2) */
#endif /* (ROBOT_TYPE == MODEL_I) */
}
#endif /* ZETA_STM_KINETIC_CALLBACKHEADER_H_ */
