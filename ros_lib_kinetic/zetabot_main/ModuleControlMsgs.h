#ifndef _ROS_zetabot_main_ModuleControlMsgs_h
#define _ROS_zetabot_main_ModuleControlMsgs_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace zetabot_main
{

  class ModuleControlMsgs : public ros::Msg
  {
    public:
      bool module_power[11];
      uint8_t led[4];
      typedef uint16_t _pulifier_type;
      _pulifier_type pulifier;

    ModuleControlMsgs():
      module_power(),
      led(),
      pulifier(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      for( uint32_t i = 0; i < 11; i++){
      union {
        bool real;
        uint8_t base;
      } u_module_poweri;
      u_module_poweri.real = this->module_power[i];
      *(outbuffer + offset + 0) = (u_module_poweri.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->module_power[i]);
      }
      for( uint32_t i = 0; i < 4; i++){
      *(outbuffer + offset + 0) = (this->led[i] >> (8 * 0)) & 0xFF;
      offset += sizeof(this->led[i]);
      }
      *(outbuffer + offset + 0) = (this->pulifier >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->pulifier >> (8 * 1)) & 0xFF;
      offset += sizeof(this->pulifier);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      for( uint32_t i = 0; i < 11; i++){
      union {
        bool real;
        uint8_t base;
      } u_module_poweri;
      u_module_poweri.base = 0;
      u_module_poweri.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->module_power[i] = u_module_poweri.real;
      offset += sizeof(this->module_power[i]);
      }
      for( uint32_t i = 0; i < 4; i++){
      this->led[i] =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->led[i]);
      }
      this->pulifier =  ((uint16_t) (*(inbuffer + offset)));
      this->pulifier |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->pulifier);
     return offset;
    }

    const char * getType(){ return "zetabot_main/ModuleControlMsgs"; };
    const char * getMD5(){ return "a6e1b56a9c48d8ddceea7d34c90fe596"; };

  };

}
#endif

