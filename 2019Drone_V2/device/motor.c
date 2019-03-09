#include "motor.h"

void RM6623_control(struct RM6623 *motor,uint8_t model)
{
	uint8_t *receiveBuffer;
	//update
	receiveBuffer = getCan1Msg(motor->id);
	motor->receiveAngle = receiveBuffer[0]<<8|receiveBuffer[1];
	motor->real_flow = receiveBuffer[2]<<8|receiveBuffer[3]; 
	motor->set_flow = receiveBuffer[4]<<8|receiveBuffer[5]; 
	//zero check
	motor->Angle_zoroCheck = Get_ZeroCheck_Value_Interface(&motor->zero,motor->receiveAngle);
	//calculate PID
	if(model==0)
	{
		motor->sendData = (short)motor_PID_cal(&motor->speedPID,&motor->positionPID,motor->setPoint,
				   motor->real_flow ,motor->Angle_zoroCheck,motor->mode);
    }
	else if(model ==1)
	{
		motor->sendData = (short)motor_PID_cal(&motor->speedPID,&motor->positionPID,motor->setPoint,
				   motor->imu_speed ,motor->imu_angle,motor->mode);
	}
}
void M2006_control(struct M2006 *motor)
{
	//update
	//zero check
	motor->Angle_zoroCheck = Get_ZeroCheck_Value_Interface(&motor->zero,motor->receiveAngle);
	//calculate PID
	motor_PID_cal(&motor->speedPID,&motor->positionPID,motor->setPoint,
	           motor->speed ,motor->Angle_zoroCheck,motor->mode);
	//send databuff
//	CAN_sendData(motor->sendBuffer,can1,motor->sendId);
}
void DM50_control(struct DM50 *motor)
{
	
}
float motor_PID_cal(pid_t *speedPID,pid_t *positionPID,
	    float setPoint,float speedFeedback,
		float positionFeedback,uint8_t mode)
{
	
	if(mode == openLoop)
	{
		return setPoint;
	}
	else if(mode == speedLoop)
	{
		return pid_calc(speedPID,speedFeedback,setPoint);
	}
	else if(mode == positionLoop)
	{
		return pid_calc(positionPID,positionFeedback,setPoint);
	}
	else if(mode ==doubleLoop)
	{
		float temp;
		temp = pid_calc(positionPID,positionFeedback,setPoint);
		return pid_calc(speedPID,speedFeedback,temp);
	}
}

