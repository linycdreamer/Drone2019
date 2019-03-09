#include "dbus.h"
#include "stm32f10x.h"
RC_Ctl_t RC_Ctl;
extern uint8_t uart3_RxBuffer[18];
/**
  * @brief  discoding message
  * @param  
  * @retval None 	
  */ 
void RemoteReceive()
{
	
	RC_Ctl.rx_buffer = uart3_RxBuffer;
	RC_Ctl.rc.ch0 = (RC_Ctl.rx_buffer[0]| (RC_Ctl.rx_buffer[1] << 8)) & 0x07ff; //!< Channel 0
	RC_Ctl.rc.ch1 = ((RC_Ctl.rx_buffer[1] >> 3) | (RC_Ctl.rx_buffer[2] << 5)) & 0x07ff; //!< Channel 1
	RC_Ctl.rc.ch2 = ((RC_Ctl.rx_buffer[2] >> 6) | (RC_Ctl.rx_buffer[3] << 2) | (RC_Ctl.rx_buffer[4] << 10)) & 0x07ff;//!< Channel 2
	RC_Ctl.rc.ch3 = ((RC_Ctl.rx_buffer[4] >> 1) | (RC_Ctl.rx_buffer[5] << 7)) & 0x07ff; //!< Channel 3
	RC_Ctl.rc.s1 = ((RC_Ctl.rx_buffer[5] >> 4)& 0x0003); //!< Switch left
	RC_Ctl.rc.s2 = ((RC_Ctl.rx_buffer[5] >> 6)& 0x0003);

	RC_Ctl.mouse.x = RC_Ctl.rx_buffer[6] | (RC_Ctl.rx_buffer[7] << 8); //!< Mouse X axis
	RC_Ctl.mouse.y = RC_Ctl.rx_buffer[8] | (RC_Ctl.rx_buffer[9] << 8); //!< Mouse Y axis
	RC_Ctl.mouse.z = RC_Ctl.rx_buffer[10] | (RC_Ctl.rx_buffer[11] << 8); //!< Mouse Z axis
	RC_Ctl.mouse.press_l = RC_Ctl.rx_buffer[12]; //!< Mouse Left Is Press ?
	RC_Ctl.mouse.press_r = RC_Ctl.rx_buffer[13]; //!< Mouse Right Is Press ?

	RC_Ctl.key.w_ = RC_Ctl.rx_buffer[14]&0x01; // KeyBoard value
	RC_Ctl.key.s_ = (RC_Ctl.rx_buffer[14]>>1)&0x01;
	RC_Ctl.key.a_ = (RC_Ctl.rx_buffer[14]>>2)&0x01;
	RC_Ctl.key.d_ = (RC_Ctl.rx_buffer[14]>>3)&0x01;
	RC_Ctl.key.shift_ =(RC_Ctl.rx_buffer[14]>>4)&0x01;
	RC_Ctl.key.ctrl_ = (RC_Ctl.rx_buffer[14]>>5)&0x01;
	RC_Ctl.key.q_ = (RC_Ctl.rx_buffer[14]>>6)&0x01;
	RC_Ctl.key.e_ = (RC_Ctl.rx_buffer[14]>>7)&0x01;	
	RC_Ctl.key.r_ = (RC_Ctl.rx_buffer[15])&0x01;
	RC_Ctl.key.f_ = (RC_Ctl.rx_buffer[15]>>1)&0x01;
	RC_Ctl.key.g_ = (RC_Ctl.rx_buffer[15]>>2)&0x01; 
	RC_Ctl.key.z_ = (RC_Ctl.rx_buffer[15]>>3)&0x01;
	RC_Ctl.key.x_ = (RC_Ctl.rx_buffer[15]>>4)&0x01;
	RC_Ctl.key.c_ = (RC_Ctl.rx_buffer[15]>>5)&0x01;
	RC_Ctl.key.v_ = (RC_Ctl.rx_buffer[15]>>6)&0x01;
	RC_Ctl.key.b_ = (RC_Ctl.rx_buffer[15]>>7)&0x01;
	
	RC_Ctl.RCrecvd = 1; //数据接收标志位
	RC_Ctl.RCDisconnectCnt = 0;    //断线数据清零
	
	if((RC_Ctl.rc.ch0-1024<15)&&(RC_Ctl.rc.ch0-1024>-15)) RC_Ctl.rc.ch0=1024;
	if((RC_Ctl.rc.ch1-1024<15)&&(RC_Ctl.rc.ch1-1024>-15)) RC_Ctl.rc.ch1=1024;
	if((RC_Ctl.rc.ch2-1024<10)&&(RC_Ctl.rc.ch2-1024>-10)) RC_Ctl.rc.ch2=1024;
	if((RC_Ctl.rc.ch3-1024<10)&&(RC_Ctl.rc.ch3-1024>-10)) RC_Ctl.rc.ch3=1024;
	
}


/*
 * @brief initial remote control number
 */
void reset_remote_control_msg(void)
{
	RC_Ctl.rc.ch0 = 1024;
	RC_Ctl.rc.ch1 = 1024;
	RC_Ctl.rc.ch2 = 1024;
	RC_Ctl.rc.ch3 = 1024;
	RC_Ctl.mouse.x = 0;
	RC_Ctl.mouse.y = 0;
	RC_Ctl.mouse.z = 0;
	RC_Ctl.mouse.press_l = 0;                                                
	RC_Ctl.mouse.press_r = 0;
	
	RC_Ctl.key.w_ = 0;
	RC_Ctl.key.s_ = 0;                            
	RC_Ctl.key.a_ = 0;
	RC_Ctl.key.d_ = 0;
	RC_Ctl.key.q_ = 0;
	RC_Ctl.key.e_ = 0;
	RC_Ctl.key.r_ = 0;
	RC_Ctl.key.f_ = 0;
	RC_Ctl.key.shift_ = 0;
	RC_Ctl.key.ctrl_ = 0;
	
	RC_Ctl.rc.s1 = 2;
	RC_Ctl.rc.s2 = 2;
}
RC_Ctl_t getRCData(void)
{
	return RC_Ctl;
}








