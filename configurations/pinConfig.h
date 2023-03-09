#ifndef PINCONFIG_H_
#define PINCONFIG_H_
#include "robotConfig.h"
#include "mbed.h"
#include "mbed_config.h"


/* PORTA -------------------------------------------------------------------- */
#define SPI1_SCK   PA_5
#define SPI1_MISO  PA_6
#define SPI1_MOSI  PA_7
#define SPI1_CS    PA_15
/* PORTB -------------------------------------------------------------------- */
#define SSR_CON_01  PB_10
#define SSR_CON_02  PB_11
/* PORTC -------------------------------------------------------------------- */

/* PORTD -------------------------------------------------------------------- */
#define EMERGENCY_01  PD_11

/* PORTE -------------------------------------------------------------------- */
#define BT_RX         PE_0
#define BT_TX         PE_1
#define IMU_SCK       PE_2
#define TRIG          PE_3
#define IMU_MISO      PE_5
#define IMU_MOSI      PE_6
#define BUMPER_04     PE_9
#define EMERGENCY_02  PE_10
#define BUMPER_03     PE_11
#define EMERGENCY_03  PE_12
#define BUMPER_02     PE_13
#define EMERGENCY_04  PE_14
#define BUMPER_01     PE_15
/* PORTF -------------------------------------------------------------------- */
#define RELAY_CTRL1  PF_12
#define RELAY_CTRL2  PF_13
#define RELAY_CTRL3  PF_14
#define RELAY_CTRL4  PF_15

/* PORTG -------------------------------------------------------------------- */
#define IMU_INT   PG_0
#define IMU_NCS   PG_1
#define RS_ECH01  PG_2
#define RS_ECH02  PG_3
#define RS_ECH03  PG_4
#define RS_ECH04  PG_5
#define RS_ECH05  PG_6
#define RS_ECH06  PG_7
#define RS_ECH07  PG_8
#define RU_ECH01  PG_9
#define RU_ECH02  PG_10
#define RU_ECH03  PG_11
#define RU_ECH04  PG_12

/* PORTH -------------------------------------------------------------------- */


/* Definition according to the robot model */

#if ((ROBOT_TYPE == MODEL_C) || (ROBOT_TYPE == MODEL_D))
#define CHARGE_RELAYP  SSR_CON_01
#define CHARGE_RELAYN  SSR_CON_02
#define EMERGENCY_STOP  EMERGENCY_01
#endif /* ((ROBOT_TYPE == MODEL_C) || (ROBOT_TYPE == MODEL_D)) */

#if (ROBOT_TYPE == MODEL_D)
#define LEVEL_SENSE     EMERGENCY_04
#endif

#if (ROBOT_TYPE == MODEL_I)
#undef IMU_SCK
#undef IMU_MISO
#undef IMU_MOSI
#undef IMU_NCS
#undef IMU_INT
#undef BT_RX
#undef BT_TX
#undef TRIG
#define SSR_CTRL       PB_15
#define SCRUBBER_CTRL  PB_1
#define IMU_SCK   SPI1_SCK
#define IMU_MISO  SPI1_MISO
#define IMU_MOSI  SPI1_MOSI
#define LIDAR_DETECT_OBSTACLE  PE_6
#define RESERVE_PIN            PE_1
#define IMU_NCS                PE_12
#define IMU_INT                PE_14
#define SONAR_LEFT     PF_3
#define BT_RX          PF_6
#define BT_TX          PF_7
#define SONAR_TRIG     PF_11
#define SONAR_RIGHT    PF_15
#define LIDAR_WARNING1     PG_9
#define IGNORE_WARNING2    PG_10
#define LIDAR_DUSTSENSING  PG_11
#define LIDAR_WARNING2     PG_12
#define EMERGENCY_STOP     PG_13
#define IGNORE_WARNING1    PG_15
#endif

#if (ROBOT_TYPE == MODEL_I2)
// original
// #define LIDAR_WARNING1         RELAY_CTRL3 // PF14
// #define LIDAR_WARNING2         RELAY_CTRL4 // PF15
// #define IGNORE_WARNING1        RELAY_CTRL1 // PF12
// #define IGNORE_WARNING2        RELAY_CTRL2 // PF13
#define LIDAR_WARNING1         RELAY_CTRL1 // PF12 
#define LIDAR_WARNING2         RELAY_CTRL2 // PF13
#define IGNORE_WARNING1        RELAY_CTRL3 // PF14
#define IGNORE_WARNING2        RELAY_CTRL4 // PF15
#define SSR_CTRL               SSR_CON_01
#define EMERGENCY_STOP         EMERGENCY_01
#define LIDAR_DETECT_OBSTACLE  BUMPER_01
#define LIDAR_DUSTSENSING      BUMPER_02
// #define SCRUBBER_CTRL  POWERBOARD
// UVC_B UVC_T SOL

// 2022. 09. 07
#define LASER_DETECTING        BUMPER_03
#endif

#endif /* PINCONFIG_H_ */