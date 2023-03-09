#include "GlobalVariables.h"
/* global variables begin --------------------------------------------------- */
// Sonar variables
volatile float global_variables::dist[NUM_SONAR] = {0.,};
//volatile float dist_raw[NUM_SONAR] = {0.,};

// subscriber variables
volatile bool global_variables::isSubscribe = false;

volatile bt_data_t global_variables::bt_data;
volatile uint8_t global_variables::NUC_sub_state = '\0';
// volatile bool start_check = false;


// print variables
struct Vect3 global_variables::gAcc_raw, global_variables::gGyro_raw, global_variables::gMag_raw;
float global_variables::gQ[4],global_variables::gTheta,global_variables::gRoll,global_variables::gPitch,global_variables::gYaw;
volatile bool global_variables::charging_control_flag = false;
#if ((ROBOT_TYPE == MODEL_I) || (ROBOT_TYPE == MODEL_I2))
volatile bool global_variables::WaringFieldSelectPin1, global_variables::WaringFieldSelectPin2 = false; // follow instances::IgnoreWarningFieldPin
volatile bool global_variables::IgnoreWarningFieldPin1, global_variables::IgnoreWarningFieldPin2 = false;
#if (ROBOT_TYPE == MODEL_I)
volatile bool global_variables::ScrubberControl = false;
#endif
#endif

/* global variables end ----------------------------------------------------- */