#ifndef ZETA_STM_KINETIC_INITFUNCTION_H_
#define ZETA_STM_KINETIC_INITFUNCTION_H_
#include "mbed.h"
#include "ThreadFunctions.h"
#include "variables/instances.h"
#include "variables/GlobalVariables.h"
#include "rosHeader.hpp"
#include "configurations/robotConfig.h"
extern volatile bt_data_t bt_data;
namespace init_function
{
void InitThread();
void InitBT();
void InitSerial();
void InitROS();
}

#endif
