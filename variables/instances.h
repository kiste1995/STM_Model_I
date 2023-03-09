#ifndef ZETA_STM_KINETIC_INSTANCEHEADER_H_
#define ZETA_STM_KINETIC_INSTANCEHEADER_H_
#include "mbed.h"
#include "src/rosHeader.hpp"
#include "modules/ChargingControl.h"
#include "HCSR04/SONAR_MANAGER.hpp"
#include "src/CallbackFunctions.h"
#include "defineHeader.h"
#include "configurations/robotConfig.h"
/* COM variables ------------------------------------------------------------ */
extern Serial bt;
extern ros::NodeHandle nh;
namespace instances
{
extern std_msgs::String version_msg;
extern ros::Publisher version_publisher;
extern std_msgs::Float32MultiArray US_msg;
extern ros::Publisher US_publisher;
extern std_msgs::String Bluetooth_msg;
extern ros::Publisher Bluetooth_publisher;

#if (ROBOT_TYPE == MODEL_D)
//std_msgs::UInt8 water_level_msg;
//ros::Publisher water_level_publisher("water_level", &water_level_msg);
extern std_msgs::Bool water_level_msg;
extern ros::Publisher water_level_publisher;
#endif

#if ((ROBOT_TYPE == MODEL_I) || (ROBOT_TYPE == MODEL_I2))
extern std_msgs::Bool lidar_dusty_msg;
extern ros::Publisher LidarDusty_publisher;
extern std_msgs::UInt8 emergency_stop_msg;
extern ros::Publisher EmergencyStop_publisher;
// 2022. 09. 07
extern std_msgs::Bool LDetect_msg;
extern ros::Publisher LDetect_publisher;
#endif
extern sensor_msgs::Imu imu_msg;
extern ros::Publisher IMU_publisher;
extern std_msgs::Bool EStop_msg;
extern ros::Publisher EStop_publisher;
extern std_msgs::Bool Bumper_msg;
extern ros::Publisher Bumper_publisher;
extern ros::Subscriber<std_msgs::UInt8> Bluetooth_subscriber;
extern ros::Subscriber<std_msgs::Bool> SsrTest_subscriber;

#if (ROBOT_TYPE == MODEL_I)
extern ros::Subscriber<std_msgs::UInt8> WarningFieldSelect_subscriber;
extern ros::Subscriber<std_msgs::UInt8> IgnoreWarningField_subscriber;
extern ros::Subscriber<std_msgs::Bool> ScrubberControl_subscriber;
#endif

#if (ROBOT_TYPE == MODEL_I2)
extern ros::Subscriber<std_msgs::UInt8> WarningFieldSelect_subscriber;
extern ros::Subscriber<std_msgs::UInt8> IgnoreWarningField_subscriber;
#endif
/* Threads and Timers ------------------------------------------------------- */
extern Thread gThread[NUM_THREAD];

extern Timer waitTmr;


/* Modules ------------------------------------------------------------------ */
extern MPU9250_SPI mpu;

#if ((ROBOT_TYPE == MODEL_C) || (ROBOT_TYPE == MODEL_D))
extern ChargingControl charging_control;
extern DigitalIn estop;
extern PinName echo[NUM_SONAR];
extern SONAR_MANAGER<NUM_SONAR> sonar_manager;
#elif (ROBOT_TYPE == MODEL_I)
extern PinName echo[NUM_SONAR];
extern SONAR_MANAGER<NUM_SONAR> sonar_manager;
#elif (ROBOT_TYPE == MODEL_I2)
extern PinName echo[NUM_SONAR];
extern SONAR_MANAGER<NUM_SONAR> sonar_manager;
#endif

#if (ROBOT_TYPE == MODEL_D)
//DigitalIn level_blue(LEVEL_SENSE1);
//DigitalIn level_yellow(LEVEL_SENSE2);
extern DigitalIn level_sensor;
#endif

#if (ROBOT_TYPE == MODEL_I)
extern DigitalOut ChargingSsr;
extern DigitalOut ScrubberControl;
extern DigitalOut WaringFieldSelectPin1;
extern DigitalOut WaringFieldSelectPin2;
extern DigitalOut IgnoreWarningFieldPin1;
extern DigitalOut IgnoreWarningFieldPin2;
extern DigitalIn LidarDustSensingPin;
extern DigitalIn EmergencyStopPin;
extern DigitalIn LidarStopPin;
#endif /* (ROBOT_TYPE == MODEL_I) */
#if (ROBOT_TYPE == MODEL_I2)
extern DigitalOut ChargingSsr;
extern DigitalOut WaringFieldSelectPin1;
extern DigitalOut WaringFieldSelectPin2;
extern DigitalOut IgnoreWarningFieldPin1;
extern DigitalOut IgnoreWarningFieldPin2;
extern DigitalIn LidarDustSensingPin;
extern DigitalIn EmergencyStopPin;
extern DigitalIn LidarStopPin;
extern DigitalIn LaserDetectPin;
#endif

}
#endif
