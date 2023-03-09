#include "initFunction.h"

void init_function::InitThread()
{
    int index = 0;
    instances::gThread[index++].start(thread_functions::IMU_thread);
    instances::gThread[index++].start(thread_functions::bt_thread);
    instances::gThread[index++].start(thread_functions::sonar_thread);
    instances::gThread[index++].start(thread_functions::sonar_pub_thread);
    instances::gThread[index++].start(thread_functions::bt_pub_thread);
#ifdef NO_ROS
    instances::gThread[index++].start(thread_functions::print_thread);
#else
    instances::gThread[index++].start(thread_functions::version_pub_thread);
    instances::gThread[index++].start(thread_functions::imu_pub_thread);
    instances::gThread[index++].start(thread_functions::estop_pub_thread);
#if (ROBOT_TYPE == MODEL_D)
    instances::gThread[index++].start(thread_functions::level_sensor_thread);
#endif
#if ((ROBOT_TYPE == MODEL_I) || (ROBOT_TYPE == MODEL_I2))
    instances::gThread[index++].start(thread_functions::lidar_dusty_pub_thread);
    instances::gThread[index++].start(thread_functions::coop_flag_thread);
    // 2022. 09. 07
    instances::gThread[index++].start(thread_functions::laser_detecting_pub_thread);
#endif
#endif /* #ifdef NO_ROS */
    //gThread[8].start(test_thread);
}

void init_function::InitBT()
{
    bt.baud(9600);
    global_variables::bt_data.rec = '\0';
    global_variables::bt_data.sen = '\0';
}

#ifdef NO_ROS
void init_function::InitSerial()
{
    pc.baud(115200);
}
#else
void init_function::InitROS()
{
    nh.getHardware()->setBaud(ROSSERIAL_BUADRATE);
    nh.initNode();
    nh.advertise(instances::version_publisher);
    instances::US_msg.data = (float*)malloc(sizeof(float) * NUM_SONAR);
    instances::US_msg.data_length = NUM_SONAR;
    nh.advertise(instances::IMU_publisher);
    nh.advertise(instances::EStop_publisher);
    //nh.advertise(Bumper_publisher);
    nh.advertise(instances::US_publisher);
    nh.advertise(instances::Bluetooth_publisher);
    nh.subscribe(instances::Bluetooth_subscriber);
    nh.subscribe(instances::SsrTest_subscriber);
#if (ROBOT_TYPE == MODEL_D)
    nh.advertise(instances::water_level_publisher);
#endif
#if (ROBOT_TYPE == MODEL_I)
    nh.subscribe(instances::ScrubberControl_subscriber);
    nh.advertise(instances::LidarDusty_publisher);
    nh.advertise(instances::EmergencyStop_publisher);
    nh.subscribe(instances::WarningFieldSelect_subscriber);
    nh.subscribe(instances::IgnoreWarningField_subscriber);
#endif
#if (ROBOT_TYPE == MODEL_I2)
    nh.advertise(instances::LidarDusty_publisher);
    nh.advertise(instances::EmergencyStop_publisher);
    nh.subscribe(instances::WarningFieldSelect_subscriber);
    nh.subscribe(instances::IgnoreWarningField_subscriber);
    // 2022. 09. 07
    nh.advertise(instances::LDetect_publisher);
#endif
    instances::waitTmr.start();
}
#endif
