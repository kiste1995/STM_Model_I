#ifndef ZETA_STM_KINETIC_THREADFUNCTIONS_H_
#define ZETA_STM_KINETIC_THREADFUNCTIONS_H_
#include "mbedHeader.hpp"
#include "rosHeader.hpp"
#include "modules/ChargingControl.h"
#include "HCSR04/SONAR_MANAGER.hpp"
#include "variables/defineHeader.h"
#include "variables/instances.h"
#include "variables/GlobalVariables.h"
#include "configurations/robotConfig.h"
#include "myUtil.h"


/* Threads begin ------------------------------------------------------------ */
namespace thread_functions
{
void print_thread();
void version_pub_thread();
void bt_pub_thread();
void imu_pub_thread();
void sonar_pub_thread();
void estop_pub_thread();
void level_sensor_thread();
void lidar_dusty_pub_thread();
void laser_detecting_pub_thread();
void bt_thread();
void sonar_thread();
void IMU_thread();
void test_thread();
#if ((ROBOT_TYPE == MODEL_I) || (ROBOT_TYPE == MODEL_I2))
void coop_flag_thread();
#endif
}
/* Threads end -------------------------------------------------------------- */
#endif /* ZETA_STM_KINETIC_THREADFUNCTIONS_H_ */
