#ifndef __RM6623_H__
#define __RM6623_H__
#include "pid.h"
#include "ZeroCheck.h"
/**
  * @note  
  * ID 设置的范围为1-8
  * 发送的标识符 0x1ff ---对应id为205-pitch 206-yaw
  * 电流范围 -5000~+5000
  * DATA[0] id-5 高8位  
  * DATA[1] id-5 低8位
  * DATA[2] id-6 高8位
  * DATA[3] id-6 低8位
  * DATA[4] id-7 高8位
  * DATA[5] id-7 低8位
  * DATA[6] id-8 高8位
  * DATA[7] id-8 低8位
  * 反馈id 0x205+id(如id为0，标识符为 0x205,id最大为7)
  * 反馈内容
  * DATA[0] 转子机械角度高8位
  * DATA[1] 转子机械角度低8位
  * DATA[2] 转子电流高8位
  * DATA[3] 转子电流低8位
  * DATA[4] 给定转矩电流高8位
  * DATA[5] 给定转矩电流低8位
  * 发送频率 1kHZ
  * 转子机械角度范围 0~8191
  */
  
struct RM6623
{
	uint8_t id;
	uint32_t sendId;
	uint32_t receiveId;
	uint8_t mode;
	uint32_t sendMax;
	short sendData;
	uint8_t sendBuffer[8];
	uint16_t receiveAngle;
	float Angle_zoroCheck;
	short real_flow;
	short set_flow;
	float setPoint;
	pid_t speedPID;
	pid_t positionPID;
	ZeroCheck_Typedef zero;
	float imu_speed;
	float imu_angle;
};

#endif // __M2006_H__
