#ifndef __DBUS_H__
#define __DBUS_H__

/***********RC***********/
typedef __packed struct
{
	unsigned short ch0;
	unsigned short ch1;
	unsigned short ch2;
	unsigned short ch3;
	unsigned char s1;
	unsigned char s2;
}Remote;
typedef __packed 	struct
{
		short x;
		short y;
		short z;
		unsigned char press_l;
		unsigned char press_r;
}Mouse;
typedef __packed struct
{
		unsigned short w_,s_,a_,d_,q_,e_,r_,f_,g_,z_,x_,c_,v_,b_,shift_,ctrl_;
}Key;

typedef struct
{
	Remote rc;
	Mouse mouse;
	Key key;
    char RCrecvd,RCDisconnectCnt;
	unsigned char *rx_buffer;
}RC_Ctl_t;
void RemoteReceive(void);
RC_Ctl_t getRCData(void);
#endif // __DBUS_H__
