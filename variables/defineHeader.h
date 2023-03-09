#ifndef ZETA_STM_KINETIC_DEFINEHEADER_H_
#define ZETA_STM_KINETIC_DEFINEHEADER_H_
#include "configurations/pinConfig.h"
#include "configurations/robotConfig.h"

#define __FW_VERSION__  "1.2.9"
#define NUM_THREAD  16  // 1 for test

#if ((ROBOT_TYPE == MODEL_C) || (ROBOT_TYPE == MODEL_D))
#define NUM_SONAR  10
#elif (ROBOT_TYPE == MODEL_I)
#define NUM_SONAR  2
#elif (ROBOT_TYPE == MODEL_I2)
#define NUM_SONAR  8
#endif

#define SEQ_STATE_MSG_SIZE 16
#define G  9.80665f

#define ROSSERIAL_BUADRATE  460800
#endif