/** mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 *
 * @file    
 * @author  Ahn semin <asm5206@gmail.com>
 * @date    2022.01.25
 * @version 1.2.8
 *
 * @section DESCRIPTION
 * 
 * Control board
 * 2021.06.09 Ahn: V1.1.0, Add delay on ssr control sequence
 *                  SSR logic change npn
 * 2021.07.19 Ahn: V1.1.0b, add relay off in finish state
 * 2021.07.20 Ahn: V1.2.0c, remove bt receive loginfo
 * 2021.07.27 Ahn: V1.1.0e, Compatible to various robot types
 * 2021.07.29 Ahn: V1.2.0, Add satety lidar warining ignorance pin
 * 2021.08.09 Ahn: V1.2.1, Change baudrate to 115200 & add Emergency for ModelI
                    nightly, Fix SSR control(too many relay off occurs imu data discontinuity)
 * 2021.08.19 Ahn: V1.2.2, fix imu data discontinuity during autocharge state
 * 2021.10.08 Ahn: V1.2.4, Add some pins for model I ( scrubber control )
 */

#include "src/mbedHeader.hpp"
#include "ros.h"
#include "variables/instances.h"
#include "src/initFunction.h"

/* function protopytes begin ------------------------------------------------ */

/* function protopytes end -------------------------------------------------- */


/* Instancs begin ----------------------------------------------------------- */
#ifdef NO_ROS
mbed::Serial pc(USBTX, USBRX); // maybe after systemcoreclockupdate???
#else
ros::NodeHandle nh;
#endif

Serial bt(BT_TX,BT_RX);
/* Instancs end ------------------------------------------------------------- */
int main() {
    SystemCoreClockUpdate();
#if (NO_ROS)
    init_function::InitSerial();
    //pc.printf("- Start of Program. CPU SystemCoreClock is %d Hz\r\n", SystemCoreClock);
#else
    init_function::InitROS();
#endif
    init_function::InitBT();
    init_function::InitThread();   
    while(1) {nh.spinOnce();}
#if (NO_ROS)
    pc.printf("- End of Program\r\n");
#endif
    return 0;
}

/***** EOF *****/