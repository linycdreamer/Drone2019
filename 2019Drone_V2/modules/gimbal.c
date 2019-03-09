#include "gimbal.h"
#include "motor.h"
#include "IMU.h"
#include "dbus.h"
//struct M2006 pitch;
//struct DM50 yaw;
struct RM6623 pitch;
struct RM6623 yaw;
extern CAN_HandleTypeDef hcan1;
extern CAN_HandleTypeDef hcan2;
void gimbal_init(void)
{
	/**********yaw***********/
	yaw.id = 0;
	ZeroCheck_Init_Interface(&yaw.zero,8191);
	yaw.mode = doubleLoop;
	yaw.speedPID.p = -2000.0f;
	yaw.speedPID.i = -0.001f;
	yaw.speedPID.d = 0.0f;
	yaw.speedPID.integral_limit = 0.0f;
	yaw.positionPID.p = 0.2f;
	yaw.positionPID.i = 0.001f;
	yaw.positionPID.d = 0.2f;
	yaw.positionPID.integral_limit = 1000.0f;
	yaw.speedPID.max_out = 5000;
	yaw.positionPID.max_out = 5000;
	/**********pitch***********/
    pitch.id = 1;
	ZeroCheck_Init_Interface(&pitch.zero,8191);
	pitch.mode = doubleLoop;
	pitch.speedPID.p = -800.0f;
	pitch.speedPID.i = -0.008f;
	pitch.speedPID.d = -500.0f;
	pitch.speedPID.integral_limit = 80.0f;
	pitch.positionPID.p = -0.1f;
	pitch.positionPID.i = -0.0008f;
	pitch.positionPID.d = -0.002f;
	pitch.positionPID.integral_limit = 0.0f;
	pitch.speedPID.max_out = 5000;
	pitch.positionPID.max_out = 5000;
	
}
short gimbal_delay;
float initYawAngle;
void gimbal_tast(unsigned char model)
{
	imuDiscode();
	yaw.imu_angle = getYawAngle();
	yaw.imu_speed =getYawSpeed();
	pitch.imu_angle = getPitchAngle();
	pitch.imu_speed = getPitchSpeed();
	if(gimbal_delay>4000)
	{
		yaw.setPoint = (getRCData().rc.ch2-1024)*0.03+initYawAngle;
		pitch.setPoint = (getRCData().rc.ch3-1024)*0.03;
		RM6623_control(&pitch,1);
		RM6623_control(&yaw,1);
		
		hcan1.SendBuffer[0] = (unsigned char)((yaw.sendData>>8)&0xff); //Yaw
		hcan1.SendBuffer[1] = (unsigned char)(yaw.sendData&0xff);  
		hcan1.SendBuffer[2] = (unsigned char)((pitch.sendData>>8)&0xff);//Ptich
		hcan1.SendBuffer[3] = (unsigned char)(pitch.sendData&0xff);
		CAN_SendData(&hcan1,0x1ff);
	}
	else
	{
		yaw.setPoint = yaw.imu_angle;
		initYawAngle = yaw.imu_angle;
		gimbal_delay++;
	}
	
}