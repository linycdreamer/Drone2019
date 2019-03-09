#ifndef __IMU_H__
#define __IMU_H__
#include "stm32f10x.h"
typedef  struct IMU
{
	float yawAngle;
	float pitchAngle;
	float yawSpeed;
	float pitchSpeed;
	uint32_t sendId;
	uint32_t receiveId;
}IMU;
void imuDiscode(void);
float getYawAngle(void);
float getPitchAngle(void);
float getYawSpeed(void);
float getPitchSpeed(void);
#endif // __DBUS_H__
