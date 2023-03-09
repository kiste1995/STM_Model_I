#include "instances.h"

/* ROS variables ------------------------------------------------------------ */
// Publisher
//zetabot_main::SonarArray US_msg;
//ros::Publisher US_publisher("sonar", &US_msg);
std_msgs::String instances::version_msg;
ros::Publisher instances::version_publisher("stm_version", &instances::version_msg);

std_msgs::Float32MultiArray instances::US_msg;
ros::Publisher instances::US_publisher("sonar", &US_msg);

std_msgs::String instances::Bluetooth_msg;
ros::Publisher instances::Bluetooth_publisher("autocharge_state_INO", &instances::Bluetooth_msg);

#if (ROBOT_TYPE == MODEL_D)
//std_msgs::UInt8 water_level_msg;
//ros::Publisher water_level_publisher("water_level", &water_level_msg);
std_msgs::Bool instances::water_level_msg;
ros::Publisher instances::water_level_publisher("water_level", &instances::water_level_msg);
#endif

#if ((ROBOT_TYPE == MODEL_I) || (ROBOT_TYPE == MODEL_I2))
std_msgs::Bool instances::lidar_dusty_msg;
ros::Publisher instances::LidarDusty_publisher("LidarDusty", &instances::lidar_dusty_msg);

std_msgs::UInt8 instances::emergency_stop_msg;
ros::Publisher instances::EmergencyStop_publisher("EmergencyStop", &instances::emergency_stop_msg);

// 2022. 09. 07
std_msgs::Bool instances::LDetect_msg;
ros::Publisher instances::LDetect_publisher("ldetect", &instances::LDetect_msg);

#endif

sensor_msgs::Imu instances::imu_msg;
ros::Publisher instances::IMU_publisher("imu", &instances::imu_msg);

std_msgs::Bool instances::EStop_msg;
ros::Publisher instances::EStop_publisher("estop", &instances::EStop_msg);

std_msgs::Bool instances::Bumper_msg;
ros::Publisher instances::Bumper_publisher("bumper", &instances::Bumper_msg);


// Subscriber
ros::Subscriber<std_msgs::UInt8> instances::Bluetooth_subscriber("autocharge_state_NUC", &callback_functions::BluetoothCB);
ros::Subscriber<std_msgs::Bool> instances::SsrTest_subscriber("SsrControlTest", &callback_functions::SsrTestCB);

#if (ROBOT_TYPE == MODEL_I)
ros::Subscriber<std_msgs::UInt8> instances::WarningFieldSelect_subscriber("WarningFieldSelect", &callback_functions::WarningFieldSelectCB);
ros::Subscriber<std_msgs::UInt8> instances::IgnoreWarningField_subscriber("IgnoreWarningField", &callback_functions::IgnoreWarningFieldCB);
ros::Subscriber<std_msgs::Bool>  instances::ScrubberControl_subscriber("ScrubberControl", &callback_functions::ScrubberControlCB);
#endif

#if (ROBOT_TYPE == MODEL_I2)
ros::Subscriber<std_msgs::UInt8> instances::WarningFieldSelect_subscriber("WarningFieldSelect", &callback_functions::WarningFieldSelectCB);
ros::Subscriber<std_msgs::UInt8> instances::IgnoreWarningField_subscriber("IgnoreWarningField", &callback_functions::IgnoreWarningFieldCB);
#endif
/* Threads and Timers ------------------------------------------------------- */
Thread instances::gThread[NUM_THREAD];

Timer instances::waitTmr;


/* Modules ------------------------------------------------------------------ */
MPU9250_SPI instances::mpu(IMU_MOSI, IMU_MISO, IMU_SCK, IMU_NCS, IMU_INT);

#if ((ROBOT_TYPE == MODEL_C) || (ROBOT_TYPE == MODEL_D))
ChargingControl instances::charging_control(CHARGE_RELAYP, CHARGE_RELAYN);
DigitalIn instances::estop(EMERGENCY_STOP);
PinName instances::echo[NUM_SONAR] = {RS_ECH01, RS_ECH02, RS_ECH03, RS_ECH04, RS_ECH05, RS_ECH06, RS_ECH07, RU_ECH01, RU_ECH02, RU_ECH03};
SONAR_MANAGER<NUM_SONAR> instances::sonar_manager(instances::echo, TRIG);
#elif (ROBOT_TYPE == MODEL_I)
PinName instances::echo[NUM_SONAR] = {SONAR_LEFT, SONAR_RIGHT};
SONAR_MANAGER<NUM_SONAR> instances::sonar_manager(instances::echo, SONAR_TRIG);
#elif (ROBOT_TYPE == MODEL_I2)
PinName instances::echo[NUM_SONAR] = {RS_ECH01, RS_ECH02, RS_ECH03, RS_ECH04, RS_ECH05, RS_ECH06, RU_ECH01, RU_ECH02};
SONAR_MANAGER<NUM_SONAR> instances::sonar_manager(instances::echo, TRIG);
#endif

#if (ROBOT_TYPE == MODEL_D)
//DigitalIn level_blue(LEVEL_SENSE1);
//DigitalIn level_yellow(LEVEL_SENSE2);
DigitalIn instances::level_sensor(LEVEL_SENSE);
#endif

#if (ROBOT_TYPE == MODEL_I)
DigitalOut instances::ChargingSsr(SSR_CTRL, 0);
DigitalOut instances::ScrubberControl(SCRUBBER_CTRL, 0);
DigitalOut instances::WaringFieldSelectPin1(LIDAR_WARNING1, 1);
DigitalOut instances::WaringFieldSelectPin2(LIDAR_WARNING2, 1);
DigitalOut instances::IgnoreWarningFieldPin1(IGNORE_WARNING1, 0);
DigitalOut instances::IgnoreWarningFieldPin2(IGNORE_WARNING2, 0);
DigitalIn  instances::LidarDustSensingPin(LIDAR_DUSTSENSING);
DigitalIn  instances::EmergencyStopPin(EMERGENCY_STOP);
DigitalIn  instances::LidarStopPin(LIDAR_DETECT_OBSTACLE);
#endif /* (ROBOT_TYPE == MODEL_I) */
#if (ROBOT_TYPE == MODEL_I2)
DigitalOut instances::ChargingSsr(SSR_CTRL, 1);
DigitalOut instances::WaringFieldSelectPin1(LIDAR_WARNING1, 0);
DigitalOut instances::WaringFieldSelectPin2(LIDAR_WARNING2, 0);
DigitalOut instances::IgnoreWarningFieldPin1(IGNORE_WARNING1, 0); // 0 is enable safety field
DigitalOut instances::IgnoreWarningFieldPin2(IGNORE_WARNING2, 0);
DigitalIn  instances::LidarDustSensingPin(LIDAR_DUSTSENSING);
DigitalIn  instances::EmergencyStopPin(EMERGENCY_STOP);
DigitalIn  instances::LidarStopPin(LIDAR_DETECT_OBSTACLE);

// 2022. 09. 07
DigitalIn  instances::LaserDetectPin(LASER_DETECTING);
#endif

//EStop estop(EMERGENCY);
/* For test ----------------------------------------------------------------- */
