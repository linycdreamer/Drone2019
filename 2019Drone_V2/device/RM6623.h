#ifndef __RM6623_H__
#define __RM6623_H__
#include "pid.h"
#include "ZeroCheck.h"
/**
  * @note  
  * ID ���õķ�ΧΪ1-8
  * ���͵ı�ʶ�� 0x1ff ---��ӦidΪ205-pitch 206-yaw
  * ������Χ -5000~+5000
  * DATA[0] id-5 ��8λ  
  * DATA[1] id-5 ��8λ
  * DATA[2] id-6 ��8λ
  * DATA[3] id-6 ��8λ
  * DATA[4] id-7 ��8λ
  * DATA[5] id-7 ��8λ
  * DATA[6] id-8 ��8λ
  * DATA[7] id-8 ��8λ
  * ����id 0x205+id(��idΪ0����ʶ��Ϊ 0x205,id���Ϊ7)
  * ��������
  * DATA[0] ת�ӻ�е�Ƕȸ�8λ
  * DATA[1] ת�ӻ�е�Ƕȵ�8λ
  * DATA[2] ת�ӵ�����8λ
  * DATA[3] ת�ӵ�����8λ
  * DATA[4] ����ת�ص�����8λ
  * DATA[5] ����ת�ص�����8λ
  * ����Ƶ�� 1kHZ
  * ת�ӻ�е�Ƕȷ�Χ 0~8191
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
