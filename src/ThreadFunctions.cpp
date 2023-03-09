#include "ThreadFunctions.h"

#ifdef NO_ROS
void thread_functions::print_thread()
{
    const float time2print = 10.0;
    const float print_thread_hz = 3.0;
    while(instances::waitTmr.read() < time2print) {;}
    while(true)
    {
        /*
        for(int i = 0; i < NUM_SONAR; i++) {
            //pc.printf("%2.2f\t%2.2f\t",dist[i],dist_raw[i]);
        }*/
        pc.printf("\n\r");
        pc.printf("Acc_x:%2.2f\tAcc_y:%2.2f\tAcc_z:%2.2f\n\r",
            gAcc_raw.x,gAcc_raw.y,gAcc_raw.z);
        pc.printf("Gyro_x:%2.2f\tGyro_y:%2.2f\tGyro_z:%2.2f\n\r",
            gGyro_raw.x,gGyro_raw.y,gGyro_raw.z);
        pc.printf("Mag_x:%2.2f\tMag_y:%2.2f\tMag_z:%2.2f\n\r",
            gMag_raw.x,gMag_raw.y,gMag_raw.z);
        pc.printf("quaternion: %2.2f  %2.2f  %2.2f  %2.2f\n\r",
            gQ[0],gQ[1],gQ[2],gQ[3]);
        pc.printf("RPY: %2.2f\t%2.2f\t%2.2f\n\r",gRoll,gPitch,gYaw);
        pc.printf("Theta_z: %2.2f degree\n\r", gTheta);
        ThisThread::sleep_for(1000/print_thread_hz);
    }    
}
#else

void thread_functions::version_pub_thread()
{
    const float version_pub_hz = 1.0f;
    instances::version_msg.data = __FW_VERSION__;
    while(1)
    {
        if(__builtin_expect(instances::waitTmr.read() < 10.0, 0)) continue;
        if(__builtin_expect(nh.connected(),1))
        {
            instances::version_publisher.publish(&instances::version_msg);
        }
        ThisThread::sleep_for(1000/version_pub_hz);
    }
}

#if ((ROBOT_TYPE == MODEL_C) || (ROBOT_TYPE == MODEL_D))
void thread_functions::bt_pub_thread()
{
    const float bt_pub_hz = 40.0;
    char seq_state_msg[SEQ_STATE_MSG_SIZE] = {'\0'};
    const char contact[] = "contact";
    const char BT_waiting[] = "BT_waiting";
    const char start[] = "start";
    const char search[] = "search";
    const char adjustment[] = "adjustment";
    const char guidance[] = "guidance";
    const char charging[] = "charging";
    const char finish[] = "finish";
    const char not_connected[] = "not_connected";
    const char left[] = "left";
    const char right[] = "right";
    const char disconnected[] = "disconnected";
    char* buff = NULL;
    enum class AUTO_CHARGE_STATE : int
    {
        start = 1,
        BT_waiting = 1,
        search,
        adjustment,
        guidance,
        charging,
        finish,
    };
    instances::charging_control.off();
    while(1)
    {
        if(__builtin_expect(instances::waitTmr.read() < 10.0, 0)) continue;
        if(global_variables::charging_control_flag)
        {
            instances::charging_control.on();
            continue;
        }
        if(global_variables::bt_data.rec == 0)
        {
            instances::charging_control.off();
        }
        switch(global_variables::NUC_sub_state)
        {
            case static_cast<int>(AUTO_CHARGE_STATE::start):
                if(global_variables::bt_data.rec == 1 || global_variables::bt_data.rec == 2) {
                    myUtil::set_msg(seq_state_msg, start, sizeof(start));
                    global_variables::bt_data.sen = 3;
                }
                else {
                    myUtil::set_msg(seq_state_msg, BT_waiting, sizeof(BT_waiting));
                    global_variables::bt_data.sen = 2;
                }
                instances::charging_control.off();
                break;
            case static_cast<int>(AUTO_CHARGE_STATE::search):
                myUtil::set_msg(seq_state_msg, search, sizeof(search));
                global_variables::bt_data.sen = 4;
                break;
            case static_cast<int>(AUTO_CHARGE_STATE::adjustment):
                myUtil::set_msg(seq_state_msg, adjustment, sizeof(adjustment));
                global_variables::bt_data.sen = 5;
                break;
            case static_cast<int>(AUTO_CHARGE_STATE::guidance):
                myUtil::set_msg(seq_state_msg, guidance, sizeof(guidance));
                global_variables::bt_data.sen = 6;
                break;
            case static_cast<int>(AUTO_CHARGE_STATE::charging):
                myUtil::set_msg(seq_state_msg, charging, sizeof(charging));
                global_variables::bt_data.sen = 7;
                break;
            case static_cast<int>(AUTO_CHARGE_STATE::finish):
                myUtil::set_msg(seq_state_msg, finish, sizeof(finish));
                instances::charging_control.off();
                global_variables::bt_data.sen = 8;
                break;    
        }
        
        if(strstr(seq_state_msg,guidance) != NULL)
        {
            switch(global_variables::bt_data.rec)
            {
                case 69:
                    myUtil::set_msg(seq_state_msg, contact, sizeof(contact));
                    break;
                case 66:
                    myUtil::set_msg(seq_state_msg, left, sizeof(left));
                    break;
                case 63:
                    myUtil::set_msg(seq_state_msg, right, sizeof(right));
                    break;
                default:
                    myUtil::set_msg(seq_state_msg, not_connected, sizeof(not_connected));
                    instances::charging_control.off();
                    break;
            }
        }
        else if(strstr(seq_state_msg,charging) != NULL)
        {
            switch(global_variables::bt_data.rec)
            {
                case 79:
                    myUtil::set_msg(seq_state_msg, contact, sizeof(contact));
                    instances::charging_control.on();
                    break;
                default:
                    myUtil::set_msg(seq_state_msg, disconnected, sizeof(disconnected));
                    instances::charging_control.off();
            }    
        }
        instances::Bluetooth_msg.data = seq_state_msg;
        if(__builtin_expect(nh.connected(),1))
        {
            instances::Bluetooth_publisher.publish(&instances::Bluetooth_msg);
        }
        ThisThread::sleep_for(1000/bt_pub_hz);
    }
}

#elif ((ROBOT_TYPE == MODEL_I) || (ROBOT_TYPE == MODEL_I2))
void thread_functions::bt_pub_thread()
{
    const float bt_pub_hz = 40.0;
    char seq_state_msg[SEQ_STATE_MSG_SIZE] = {'\0'};
    const char contact[] = "contact";
    const char BT_waiting[] = "BT_waiting";
    const char start[] = "start";
    const char search[] = "search";
    const char adjustment[] = "adjustment";
    const char guidance[] = "guidance";
    const char charging[] = "charging";
    const char finish[] = "finish";
    const char not_connected[] = "not_connected";
    const char left[] = "left";
    const char right[] = "right";
    const char disconnected[] = "disconnected";
    char* buff = NULL;
    enum class AUTO_CHARGE_STATE : int {
        start = 1,
        BT_waiting = 1,
        search,
        adjustment,
        guidance,
        charging,
        finish,
    };
    instances::ChargingSsr = 0;
    while(1)
    {
        if(__builtin_expect(instances::waitTmr.read() < 10.0, 0)) continue;
        if(global_variables::charging_control_flag)
        {
            instances::ChargingSsr = 1;
            continue;
        }
        switch(global_variables::NUC_sub_state)
        {
            case static_cast<int>(AUTO_CHARGE_STATE::start):
                if(global_variables::bt_data.rec == 1 || global_variables::bt_data.rec == 2)
                {
                    myUtil::set_msg(seq_state_msg, start, sizeof(start));
                    global_variables::bt_data.sen = 3;
                }
                else
                {
                    myUtil::set_msg(seq_state_msg, BT_waiting, sizeof(BT_waiting));
                    global_variables::bt_data.sen = 2;
                }
                instances::ChargingSsr = 0;
                break;
            case static_cast<int>(AUTO_CHARGE_STATE::search):
                myUtil::set_msg(seq_state_msg, search, sizeof(search));
                global_variables::bt_data.sen = 4;
                break;
            case static_cast<int>(AUTO_CHARGE_STATE::adjustment):
                myUtil::set_msg(seq_state_msg, adjustment, sizeof(adjustment));
                global_variables::bt_data.sen = 5;
                break;
            case static_cast<int>(AUTO_CHARGE_STATE::guidance):
                myUtil::set_msg(seq_state_msg, guidance, sizeof(guidance));
                global_variables::bt_data.sen = 6;
                break;
            case static_cast<int>(AUTO_CHARGE_STATE::charging):
                myUtil::set_msg(seq_state_msg, charging, sizeof(charging));
                global_variables::bt_data.sen = 7;
                break;
            case static_cast<int>(AUTO_CHARGE_STATE::finish):
                myUtil::set_msg(seq_state_msg, finish, sizeof(finish));
                instances::ChargingSsr = 0;
                global_variables::bt_data.sen = 8;
                break;    
        }
        
        if(strstr(seq_state_msg,guidance) != NULL)
        {
            switch(global_variables::bt_data.rec)
            {
                case 69:
                    myUtil::set_msg(seq_state_msg, contact, sizeof(contact));
                    break;
                case 66:
                    myUtil::set_msg(seq_state_msg, left, sizeof(left));
                    break;
                case 63:
                    myUtil::set_msg(seq_state_msg, right, sizeof(right));
                    break;
                default:
                    myUtil::set_msg(seq_state_msg, not_connected, sizeof(not_connected));
                    instances::ChargingSsr = 0;
                    break;
            }
        }
        else if(strstr(seq_state_msg,charging) != NULL)
        {
            switch(global_variables::bt_data.rec)
            {
                case 79:
                    myUtil::set_msg(seq_state_msg, contact, sizeof(contact));
                    instances::ChargingSsr = 1;
                    break;
                default:
                    myUtil::set_msg(seq_state_msg, disconnected, sizeof(disconnected));
                    instances::ChargingSsr = 0;
            }    
        }
        instances::Bluetooth_msg.data = seq_state_msg;
        if(__builtin_expect(nh.connected(),1))
        {
            instances::Bluetooth_publisher.publish(&instances::Bluetooth_msg);
        }
        ThisThread::sleep_for(1000/bt_pub_hz);
    }
}
#endif

// DigitalIn  instances::LidarStopPin(LIDAR_DETECT_OBSTACLE);
#if ((ROBOT_TYPE == MODEL_I) || (ROBOT_TYPE == MODEL_I2))
void thread_functions::laser_detecting_pub_thread()
{
    const float ldetect_pub_hz = 10; // ms
    instances::LaserDetectPin.mode(PullDown);

    while(1)
    {
        if(__builtin_expect(instances::waitTmr.read() < 10.0, 0)) continue;

        bool ldetect_status = false;
        if(instances::LaserDetectPin)
        {
            ldetect_status = true; // from PLC signal, HIGH: detection    LOW: no-detection 
        }
        else
        {
            ldetect_status = false;
        }
        instances::LDetect_msg.data = ldetect_status;
        if(__builtin_expect(nh.connected(),1))
        {
            instances::LDetect_publisher.publish(&instances::LDetect_msg);
        }
        ThisThread::sleep_for(1000/ldetect_pub_hz);
    }  
}
#endif

void thread_functions::imu_pub_thread()
{
    // const float imu_pub_hz = 30.0;
    const float imu_pub_hz = 50.0;
    instances::imu_msg.header.frame_id = "imu_link";
    //mag_msg.header.frame_id = "/imu/mag";
    instances::waitTmr.start();
    while(1) {
        if(__builtin_expect(instances::waitTmr.read() < 10.0, 0)) continue;
        instances::imu_msg.header.stamp = nh.now();
        instances::imu_msg.orientation.w = global_variables::gQ[0];
        instances::imu_msg.orientation.x = global_variables::gQ[1];
        instances::imu_msg.orientation.y = global_variables::gQ[2];
        instances::imu_msg.orientation.z = global_variables::gQ[3];
              
        instances::imu_msg.angular_velocity.x = global_variables::gGyro_raw.x;
        instances::imu_msg.angular_velocity.y = global_variables::gGyro_raw.y;
        instances::imu_msg.angular_velocity.z = global_variables::gGyro_raw.z;
        
        instances::imu_msg.linear_acceleration.x = global_variables::gAcc_raw.x;
        instances::imu_msg.linear_acceleration.y = global_variables::gAcc_raw.y;
        instances::imu_msg.linear_acceleration.z = global_variables::gAcc_raw.z;
        if(__builtin_expect(nh.connected(),1))
        {
            instances::IMU_publisher.publish(&instances::imu_msg);
        }    
        ThisThread::sleep_for(1000/imu_pub_hz);
    }
}

void thread_functions::sonar_pub_thread()
{
    const float sonar_pub_hz = 15.0;
    int ii = 0;
    for(;ii < NUM_SONAR; ii++)
    {
        instances::US_msg.data[ii] = 0.0; 
    }
    while(1)
    {
        if(__builtin_expect(instances::waitTmr.read() < 10.0, 0)) continue;
        for(ii = 0;ii < NUM_SONAR; ii++)
        {
            instances::US_msg.data[ii] = global_variables::dist[ii]; 
        }
        if(__builtin_expect(nh.connected(),1))
        {
            instances::US_publisher.publish(&instances::US_msg);
        }
        ThisThread::sleep_for(1000/sonar_pub_hz);
    }  
}

void thread_functions::estop_pub_thread()
{
    const float estop_pub_hz = 10; // ms
#if (ROBOT_TYPE == MODEL_I)
    instances::LidarStopPin.mode(PullDown);
    instances::EmergencyStopPin.mode(PullDown);
#endif
    while(1)
    {
        if(__builtin_expect(instances::waitTmr.read() < 10.0, 0)) continue;
#if ((ROBOT_TYPE == MODEL_D) || (ROBOT_TYPE == MODEL_C))
        instances::EStop_msg.data = instances::estop;
        if(__builtin_expect(nh.connected(),1))
        {
            instances::EStop_publisher.publish(&instances::EStop_msg);
        }
        //Bumper_publisher.publish(&Bumper_msg);
#elif ((ROBOT_TYPE == MODEL_I) || (ROBOT_TYPE == MODEL_I2))
        uint8_t stop_status = 0;
        if(instances::LidarStopPin)
        {
            stop_status += (0b1 << 0); // from PLC signal, HIGH: no-detection    LOW: detection 
        }
        if(instances::EmergencyStopPin)
        {
            stop_status += (0b1 << 1);
        }
        instances::emergency_stop_msg.data = stop_status;
        if(__builtin_expect(nh.connected(),1))
        {
            instances::EmergencyStop_publisher.publish(&instances::emergency_stop_msg);
        }
#endif
        ThisThread::sleep_for(1000/estop_pub_hz);
    }   
}

#if (ROBOT_TYPE == MODEL_D)
void thread_functions::level_sensor_thread()
{
    const float level_pub_hz = 1;
    bool sense = false;
    while(1)
    {
        if(__builtin_expect(instances::waitTmr.read() < 10.0, 0)) continue;
        if(instances::level_sensor)
        {
            instances::water_level_msg.data = true;
        }
        else
        {
            instances::water_level_msg.data = false;
        }
        if(__builtin_expect(nh.connected(),1))
        {
            instances::water_level_publisher.publish(&instances::water_level_msg);
        }
        ThisThread::sleep_for(1000/level_pub_hz);
    }
}
#endif

#if ((ROBOT_TYPE == MODEL_I) || (ROBOT_TYPE == MODEL_I2))
void thread_functions::lidar_dusty_pub_thread()
{
    const float lidar_dust_pub_hz = 10.0f;
    int dust_count = 0;
    instances::LidarDustSensingPin.mode(PullUp);
    while(1)
    {
        if(__builtin_expect(instances::waitTmr.read() < 10.0, 0)) continue;
        if(!instances::LidarDustSensingPin)
        {
            dust_count++;
        }
        else
        {
            dust_count = 0;
        }
        if(dust_count > 3)
        {
            instances::lidar_dusty_msg.data = true;
        }
        else
        {
            instances::lidar_dusty_msg.data = false;
        }
        if(__builtin_expect(nh.connected(),1))
        {
            instances::LidarDusty_publisher.publish(&instances::lidar_dusty_msg);
        }
        ThisThread::sleep_for(1000/lidar_dust_pub_hz);
    }   
}
#endif

#endif /* #ifdef NO_ROS */

void thread_functions::bt_thread()
{
    const float bt_thread_hz = 30.0f;
    const float bt_sen_hz    = 10.0f;
    const float bt_timeout   = 3.0f;
    char temp[2] = {'\0',};
    Timer bt_sen_tmr;
    Timer bt_timeout_tmr;
    bt_sen_tmr.start();
    bt_timeout_tmr.start();
    while(1)
    {
        if(bt.readable())
        {
            global_variables::bt_data.rec = bt.getc();
            bt_timeout_tmr.reset();
            bt_timeout_tmr.start();
        }
        if(bt_sen_tmr.read() > (1.0 / bt_sen_hz))
        {
            bt_sen_tmr.reset();
            bt.putc(global_variables::bt_data.sen);
        }
        if(bt_timeout_tmr.read() > bt_timeout)
        {
            bt_timeout_tmr.stop();
            global_variables::bt_data.rec = 0;
            global_variables::bt_data.sen = 0;
        }
        ThisThread::sleep_for(1000/bt_thread_hz);
    }
}

void thread_functions::sonar_thread()
{
    const float sonar_hz = 15.0;
    instances::sonar_manager.Begin(sonar_hz);
    while(true)
    {
        instances::sonar_manager.GetDistance(global_variables::dist);
        ThisThread::sleep_for(1000/sonar_hz);
    }
}

#define CALIBRATION_MODE 1
void thread_functions::IMU_thread()
{
    const float imu_hz = 100.0;
    
    Vect3  a, g, m;
    instances::mpu.setup();
#if (CALIBRATION_MODE)
    myUtil::calibrationProcess();
#endif
    myUtil::applyCalbratedValue();
    instances::mpu.enableDataReadyInterrupt();
    memset(global_variables::gQ,0.,4*sizeof(float));
    
    while(true)
    {
        if (instances::mpu.isDataReady())
        {
            Vect3  a, g;//, m;  // acc/gyro/mag vectors
            instances::mpu.update(MADGWICK);
            a = instances::mpu.getAccelVect();
            g = instances::mpu.getGyroVect();
            // m = mpu.getMagVect();
            global_variables::gAcc_raw.x = a.x*G;
            global_variables::gAcc_raw.y = a.y*G;
            global_variables::gAcc_raw.z = a.z*G;
            global_variables::gGyro_raw.x = g.x*DEG_TO_RAD;
            global_variables::gGyro_raw.y = g.y*DEG_TO_RAD;
            global_variables::gGyro_raw.z = g.z*DEG_TO_RAD;          
            global_variables::gQ[0] = instances::mpu.getq0();
            global_variables::gQ[1] = instances::mpu.getq1();
            global_variables::gQ[2] = instances::mpu.getq2();
            global_variables::gQ[3] = instances::mpu.getq3();
        }
        ThisThread::sleep_for(1000/imu_hz);
    }
}

void thread_functions::test_thread()
{
    while(true)
    {
        if(instances::waitTmr.read() < 10.0) continue;
        bt.putc('a');
        ThisThread::sleep_for(10);
        if(bt.readable())
        {
            char debug_str[6];
            sprintf(debug_str,"%c",bt.getc());
            nh.loginfo(debug_str);
        }
        ThisThread::sleep_for(500);
    }   
}

#if ((ROBOT_TYPE == MODEL_I) || (ROBOT_TYPE == MODEL_I2))
void thread_functions::coop_flag_thread()
{
    const float coop_flag_thread_hz = 50.0;
    while(true)
    {
        instances::IgnoreWarningFieldPin1 = global_variables::IgnoreWarningFieldPin1;
        instances::IgnoreWarningFieldPin2 = global_variables::IgnoreWarningFieldPin2;
        instances::WaringFieldSelectPin1 = global_variables::WaringFieldSelectPin1;
        instances::WaringFieldSelectPin2 = global_variables::WaringFieldSelectPin2;
#if (ROBOT_TYPE == MODEL_I)
        instances::ScrubberControl = global_variables::ScrubberControl;
#endif
        ThisThread::sleep_for(1000/coop_flag_thread_hz);
    }
}
#endif