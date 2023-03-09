#ifndef ZETA_STM_KINETIC_GLOBALVARIABLE_H_
#define ZETA_STM_KINETIC_GLOBALVARIABLE_H_
#include "configurations/robotConfig.h"
#include "variables/defineHeader.h"
#include "MPU9250/MPU9250_SPI.h"
#include "mbed.h"
// bluetooth variables
typedef struct bt_data_
{
    int rec;
    int sen;
}bt_data_t;

namespace global_variables
{
extern volatile float dist[NUM_SONAR];
extern volatile bool isSubscribe;


extern volatile bt_data_t bt_data;
extern volatile uint8_t NUC_sub_state;
// volatile bool start_check = false;

extern volatile bool charging_control_flag;
// print variables
extern Vect3 gAcc_raw, gGyro_raw, gMag_raw;
extern float gQ[4],gTheta,gRoll,gPitch,gYaw;
#if ((ROBOT_TYPE == MODEL_I) || (ROBOT_TYPE == MODEL_I2))
extern volatile bool WaringFieldSelectPin1, WaringFieldSelectPin2;
extern volatile bool IgnoreWarningFieldPin1, IgnoreWarningFieldPin2;
#if (ROBOT_TYPE == MODEL_I)
extern volatile bool ScrubberControl;
#endif
#endif
}
#endif /* ZETA_STM_KINETIC_GLOBALVARIABLE_H_ */
