#include "CallbackFunctions.h"

void callback_functions::BluetoothCB(const std_msgs::UInt8& msg)
{
    global_variables::NUC_sub_state = msg.data;
}

void callback_functions::SsrTestCB(const std_msgs::Bool& msg)
{
    if(msg.data)
    {
        global_variables::charging_control_flag = true;
    }
    else
    {
        global_variables::charging_control_flag = false;
    }
}
    

#if ((ROBOT_TYPE == MODEL_I) || (ROBOT_TYPE == MODEL_I2))
void callback_functions::WarningFieldSelectCB(const std_msgs::UInt8& msg)
{
    const unsigned char pos_front = 0U;
    const unsigned char pos_rear  = 1U;
    enum warning_field_select_enum
    {
        field1 = 0,
        field2,
    };
    if(msg.data & (1U << pos_front))
    {
        global_variables::WaringFieldSelectPin1 = 1;   
    }
    else
    {
        global_variables::WaringFieldSelectPin1 = 0;   
    }
    if(msg.data & (1U << pos_rear))
    {
        global_variables::WaringFieldSelectPin2 = 1;
    }
    else
    {
        global_variables::WaringFieldSelectPin2 = 0;   
    }
}

void callback_functions::IgnoreWarningFieldCB(const std_msgs::UInt8& msg)
{
    const unsigned char pos_front = 0U;
    const unsigned char pos_rear  = 1U;
    enum warning_field_select_enum
    {
        field1 = 0,
        field2,
    };
    if(msg.data & (1U << pos_front))
    {
        global_variables::IgnoreWarningFieldPin1 = 1;
    }
    else
    {
        global_variables::IgnoreWarningFieldPin1 = 0;   
    }
    if(msg.data & (1U << pos_rear))
    {
        global_variables::IgnoreWarningFieldPin2 = 1;
    }
    else
    {
        global_variables::IgnoreWarningFieldPin2 = 0;   
    }
}

#if (ROBOT_TYPE != MODEL_I2)
void callback_functions::ScrubberControlCB(const std_msgs::Bool& msg)
{
    if(msg.data)
    {
        global_variables::ScrubberControl = 1;
    }
    else
    {
        global_variables::ScrubberControl = 0;
    }
}
#endif /* (ROBOT_TYPE != MODEL_I2) */
#endif /* (ROBOT_TYPE == MODEL_I) */
