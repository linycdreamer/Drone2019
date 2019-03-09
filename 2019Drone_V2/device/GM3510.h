#ifndef __GM3510_H__
#define __GM3510_H__
#include "pid.h"
#include "ZeroCheck.h"
/**
  * @note  
  * ID ���õķ�ΧΪ1-8
  * ���͵ı�ʶ�� 0x200 ---��ӦidΪ 1-4
  * ���ֵ��ΧΪ -10000~10000
  * DATA[0] id-1 ��8λ  
  * DATA[1] id-1 ��8λ
  * DATA[2] id-2 ��8λ
  * DATA[3] id-2 ��8λ
  * DATA[4] id-3 ��8λ
  * DATA[5] id-3 ��8λ
  * DATA[6] id-4 ��8λ
  * DATA[7] id-4 ��8λ
  * ���͵ı�ʶ�� 0x1ff ---��ӦidΪ 5-8
  * DATA[0] id-5 ��8λ  
  * DATA[1] id-5 ��8λ
  * DATA[2] id-6 ��8λ
  * DATA[3] id-6 ��8λ
  * DATA[4] id-7 ��8λ
  * DATA[5] id-7 ��8λ
  * DATA[6] id-8 ��8λ
  * DATA[7] id-8 ��8λ
  * ����id 0x20+id(��idΪ1����ʶ��Ϊ 0x201)
  * ��������
  * DATA[0] ת�ӻ�е�Ƕȸ�8λ
  * DATA[1] ת�ӻ�е�Ƕȵ�8λ
  * DATA[2] ת��ת�ٸ�8λ
  * DATA[3] ת��ת�ٵ�8λ
  * DATA[4] ʵ�����ת�ظ�8λ
  * DATA[5] ʵ�����ת�ص�8λ
  * ����Ƶ�� 1kHZ
  * ת�ӻ�е�Ƕȷ�Χ 0~8191
  * ���ٱ� 36:1
  */
  
struct GM3510
{
	uint8_t id;
	uint32_t sendId;
	uint32_t receiveId;
	uint8_t mode;
	uint32_t sendMax;
	int16_t sendData;
	uint8_t sendBuffer[8];
	uint16_t receiveAngle;
	float Angle_zoroCheck;
	short speed;
	uint16_t qorque;//����
	float setPoint;
	pid_t speedPID;
	pid_t positionPID;
	ZeroCheck_Typedef zero;
};

#endif // __M2006_H__
